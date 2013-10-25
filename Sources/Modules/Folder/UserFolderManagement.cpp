//! \file UserFolderManagement.cpp
//! \brief	implementation of the header UserFolderManagement : gestion of the user folder
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include    "UserFolderManagement.hh"
#include    "FileSystemWatcher.hh"
#include    "WodaSemaphore.hh"
#include    "ConfFile.hh"
#include    "Account.hh"
#include    "AccountDB.hh"
#include    "FolderDB.hh"
#include    "RequestHttpFile.hh"
#include    "RequestHttpDownloadFile.hh"
#include    <fstream>
#include    <QFile>
#include    <QFileInfo>
#include    <QDir>
#include    <QTextStream>
#include    "parser.h"

#include    <iostream>

//! \param[in] parent QObject parent or nothing
//! \brief Constructor
UserFolderManagement::UserFolderManagement(QObject * parent)
    : QObject(parent), _folderPath(QString("")),
      _instanceSemaphore(QString(INSTANCE_USER_FOLDER_MANAGEMENT)),
      _folderPathTemp(QString("")) {
    WodaSemaphore::getInstance(_instanceSemaphore);
    WodaSemaphore::createSemaphore(_instanceSemaphore);
    _folderPathTemp.append(QDir::homePath()).append("/AppData/Local/Woda");
}


//! \brief Destructor
UserFolderManagement::~UserFolderManagement() {
    WodaSemaphore::deleteOneInstance(_instanceSemaphore);
}


//! \param[in] bytes string json serialize
//! \brief Deserialize the json send by the server
//! \return number of byte to read or 0
int         UserFolderManagement::deserializeJsonAccount(QByteArray & bytes) {
    QJson::Parser parser;
    bool ok;


    QVariantMap result = parser.parse(bytes, &ok).toMap();
    if (ok && !result["success"].toString().isEmpty() && result["success"].toString() == QString("true")) {
        QString newFolder(_folderPath);
        if (result["need_upload"].toString() == QString("true")) {
            std::cout << "need upload" << std::endl;
            QVariantMap fileMap = result["file"].toMap();
            return this->insertHashFileIntoDB(fileMap, newFolder);
        }
        else if (!result["last_update"].toString().isEmpty()) {
            if (!result["files"].toList().isEmpty()) {
                QVariantList filelist = result["files"].toList();
                this->deserializeJsonFileList(filelist, newFolder);
            }
            if (!result["folders"].toList().isEmpty()) {
                QVariantList folderlist = result["folders"].toList();
                this->deserializeJsonFolderList(folderlist, newFolder);
            }
        }
    }

    std::cout << "recup file list" << std::endl;

    /* else {

    QVariantList result = parser.parse(bytes, &ok).toList();
    foreach(QVariant record, result) {
        QVariantMap map = record.toMap();
        QString newFolder(_folderPath);
        if (map["full_path"].toString().indexOf(".") == 0) {
            newFolder.append(map["full_path"].toString().right(map["full_path"].toString().size() - 1));
            newFolder.append("/").append(map["name"].toString());
            std::cout << newFolder.toStdString() << std::endl;
            this->createSimpleFolder(newFolder);
        }
        QVariantList filelist = map["files"].toList();
        foreach(QVariant file, filelist) {
            QVariantMap mapFile = file.toMap();
            QString newFile(newFolder);
            newFile.append("/").append(mapFile["name"].toString());
            this->createSimpleFile(newFile);
            std::cout << newFile.toStdString() << std::endl;
        }
    }*/
    return 0;
}


//! \param[in] filelist QVariantList json serialize list of file
//! \param[in] folderName QString the path of the folder who contains the file
//! \brief Deserialize the json of files
void        UserFolderManagement::deserializeJsonFileList(QVariantList & filelist, QString & folderName) {
    foreach(QVariant file, filelist) {
        QVariantMap mapFile = file.toMap();
        QString newFile(folderName);
        QString name = mapFile["name"].toString();
        QString size = mapFile["size"].toString();
        newFile.append("/").append(name);
        this->downloadFileIfNotExist(mapFile["id"].toInt(), name, folderName, size);
        this->insertFileIntoDB(mapFile, folderName);
        this->createSimpleFile(newFile);
        std::cout << newFile.toStdString() << std::endl;
    }
}

//! \param[in] mapFile QVariantMap json serialize properties of the file
//! \param[in] folderName QString the path of the folder who contains the file
//! \brief send the properties hash into the db
//! \return the size of the file in byte
int         UserFolderManagement::insertHashFileIntoDB(QVariantMap & mapFile,
                                                       QString & folderName) {
    FolderDB db;

    QString name = mapFile["name"].toString();
    QString hash = mapFile["content_hash"].toString();
    db.insertFile(name, folderName, hash);
    return this->insertFileIntoDB(mapFile, folderName);
}

//! \param[in] mapFile QVariantMap json serialize properties of the file
//! \param[in] folderName QString the path of the folder who contains the file
//! \brief send the properties of the file to the db
//! \return the size of the file in byte
int         UserFolderManagement::insertFileIntoDB(QVariantMap & mapFile,
                                                   QString & folderName) {
    FolderDB db;

    int id = mapFile["id"].toInt();
    QString name = mapFile["name"].toString();
    bool favorite = mapFile["favorite"].toString() == QString("true") ? true : false;
    bool publicness = mapFile["publicness"].toString() == QString("true") ? true : false;
    QString size = mapFile["size"].toString();
    QString partSize = mapFile["part_size"].toString();
    db.insertFile(id, name, folderName, favorite, publicness, size, partSize);
    return mapFile["size"].toInt();
}


//! \param[in] id int id of the file
//! \param[in] name QString of the name of the file with extension
//! \param[in] idFolder QString the path of the folder who contains the file
//! \brief download the file if it is not exist in the db
void        UserFolderManagement::downloadFileIfNotExist(int id, QString & name,
                                                         QString & idFolder,
                                                         QString & size) {
    FolderDB db;
    if (!db.checkFile(id)) {
        RequestHttpDownloadFile::getSingletonPtr()->recoverFile(name, idFolder, size);
    }
}


//! \param[in] folderlist QVariantList json serialize list of folder
//! \param[in] folder QString the path of the folder who contains the folder
//! \brief Deserialize the json of folder
void        UserFolderManagement::deserializeJsonFolderList(QVariantList & folderlist, QString & folderName) {
    foreach(QVariant folder, folderlist) {
        QVariantMap mapFolder = folder.toMap();
        QString newFolder(folderName);
        if (!mapFolder["name"].toString().isEmpty()) {
            newFolder.append("/").append(mapFolder["name"].toString());
        }
        this->createSimpleFolder(newFolder);
        std::cout << newFolder.toStdString() << std::endl;
        if (!mapFolder["files"].toList().isEmpty()) {
            QVariantList filelist = mapFolder["files"].toList();
            deserializeJsonFileList(filelist, newFolder);
        }
        if (!mapFolder["folders"].toList().isEmpty()) {
            QVariantList folderlist = mapFolder["folders"].toList();
            this->deserializeJsonFolderList(folderlist, newFolder);
        } else {
            continue;
        }
    }
}



//! \param[in] folderPath QString of the path of the folder
//! \brief create the folder pass as parameter
void        UserFolderManagement::createDirectory(QString & folderPath) {
    if (this->checkDirectoryExist(folderPath)) {
        this->removeAllContentAndFolder(folderPath);
        return;
    }
    QDir directory(folderPath);
    directory.mkdir(folderPath);
}


//! \param[in] folderPath QString of the path of the user folder
//! \brief change the current directory of the user
void        UserFolderManagement::changeDirectory(QString & folderPath) {
    if (folderPath == _folderPath) {
        return;
    }
    if (!this->checkDirectoryExist(folderPath)) {
        this->createDirectory(folderPath);
    } else if (!_folderPath.isEmpty() && folderPath != _folderPath) {
        this->moveDirectory(folderPath);
    }
    _folderPath = folderPath;

    this->insertDirectoryIntoDatabase();

    FileSystemWatcher * fsWatcher = FileSystemWatcher::getSingletonPtr();
    fsWatcher->addDirectory(_folderPath);
}


void        UserFolderManagement::insertDirectoryIntoDatabase(void) {
//#if  CONFFILE
    ConfFile::getSingletonPtr()->setValue(DIRECTORY, QVariant(_folderPath));
//#else
    AccountDB db;
    db.insertAccountDirectory(_folderPath, Account::getSingletonPtr()->login());
//#endif

}


//! \brief delete the current directory of the user
void        UserFolderManagement::deleteDirectory(void) {
    this->deleteFileSystemWatcher();
    if (!_folderPath.isEmpty()) {
        this->removeAllContentAndFolder(_folderPath);

        _folderPath.clear();

    #if  CONFFILE
        ConfFile::getSingletonPtr()->setValue(DIRECTORY, QVariant(""));
    #else
        AccountDB db;
        QString empty("");
        db.insertAccountDirectory(empty, Account::getSingletonPtr()->login());
    #endif
    }
}

//! \param[in] folderPath QString of the new path of the user folder
//! \brief move the current directory of the user to another place
void        UserFolderManagement::moveDirectory(QString & folderPath) {
    this->deleteFileSystemWatcher();

    // delete old content for the new user directory
    this->removeAllContentAndFolder(folderPath);

    // move all content from the current directory to the new directory
    QDir dir;
    if( !dir.rename(_folderPath, folderPath) ){
      qWarning("move failed");
    }
}


//! \brief delete the File System Watcher on the current folder
void        UserFolderManagement::deleteFileSystemWatcher(void) {
    FileSystemWatcher::del();
}


//! \param[in] folderPath QString of the path of the user folder
//! \brief delete all content who are into the user folder
//! \brief and delete the user folder
bool        UserFolderManagement::removeAllContentAndFolder(const QString & folderPath)
{
    bool result = false;
    QDir directory(folderPath);

    if (directory.exists(folderPath)) {
        Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = this->removeAllContentAndFolder(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) {
                return result;
            }
        }
        result = directory.rmdir(folderPath);
    }
    return result;
}


//! \brief check if the directory pass as parameter exist
//! \param[in] folderPath QString of the path
//! \return true if exist, otherwise false
bool        UserFolderManagement::checkDirectoryExist(const QString & folderPath) {
    QDir directory(folderPath);
    return directory.exists(folderPath);
}


//! \brief check if the file pass as parameter exist
//! \param[in] filePath QString of the path
//! \return true if exist, otherwise false
bool        UserFolderManagement::checkFileExist(const QString & filePath) {
    QFile file(filePath);
    return file.exists(filePath);
}


//! \return the path of the user directory
const QString & UserFolderManagement::getCurrentDirectory(void) const {
    return _folderPath;
}


//! \return the path of the temp directory
const QString & UserFolderManagement::getTempDirectory(void) const {
    return _folderPathTemp;
}


//! \brief create a directory with the path pass as parameter
//! \param[in] folderPath QString of the directory
void        UserFolderManagement::createSimpleFolder(QString & folderPath) {
    if (this->checkDirectoryExist(folderPath)) {
        return;
    }
    QDir directory(folderPath);
    directory.mkdir(folderPath);
}


//! \brief create a file with the path pass as parameter
//! \param[in] filePath QString of the file
void        UserFolderManagement::createSimpleFile(QString & filePath) {
    if (this->checkFileExist(filePath)) {
        return;
    }
    QFile file(filePath);
    file.open(QIODevice::ReadWrite);
    file.close();
}


//! \brief create a file with the path and the content pass as parameter
//! \param[in] filePath QString of the file
//! \param[in] content char * content of the file
void        UserFolderManagement::createDownloadFile(QString & filePath,
                                                     char * content, int size) {
//    std::ofstream file(filePath.toStdString().c_str(), std::ios_base::out | std::ios_base::trunc);
//    if (file.is_open())
//      {
//        file << content;
//        file.close();
//      }

    //std::cout << "size = " << size << std::endl;
    //std::cout << "content = " << content << std::endl;

    QFile file(filePath);
    file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    file.write(content, size);
    file.close();
}






void        UserFolderManagement::copyAFileToTempFolder(QString & filePath) {
    if (!this->checkFileExist(filePath)) {
        return;
    }
    std::cout << "filePath = " << filePath.toStdString() << std::endl;
    QFile file(filePath);
    QString fileTemp(_folderPathTemp);
    fileTemp.append(filePath.mid(_folderPath.length()));
    std::cout << "fileTemp = " << fileTemp.toStdString() << std::endl;
    if (this->checkFileExist(fileTemp)) {
        std::cout << "CA DOIR PASSER PAR LA" << std::endl;
        QFile::remove(fileTemp);
    }
    QString dirTemp = fileTemp.mid(0, fileTemp.lastIndexOf('/'));
    std::cout << "dirTemp = " << dirTemp.toStdString() << std::endl;
    if (!this->checkDirectoryExist(dirTemp)) {
        QDir dir;
        dir.mkpath(dirTemp);
    }
    file.copy(fileTemp);
}


void        UserFolderManagement::copyEntireTempFolder() {
//    this->removeAllContentAndFolder(_folderPath);
    this->copyFolderTemp(_folderPathTemp);
}

bool        UserFolderManagement::copyFolderTemp(const QString & folderPath) {
        bool result = false;
        QDir directory(folderPath);

        if (directory.exists(folderPath)) {
            Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
                if (info.isDir()) {
                    QString str = _folderPath;
                    str.append(info.absoluteFilePath().mid(_folderPathTemp.length()));
                    std::cout << str.toStdString() << std::endl;
                    if (!this->checkDirectoryExist(str)) {
                        QDir dir;
                        dir.mkpath(str);
                    }
                    this->copyFolderTemp(info.absoluteFilePath());
                } else {
                    QFile file(info.absoluteFilePath());
                    QString str = _folderPath;
                    str.append(info.absoluteFilePath().mid(_folderPathTemp.length()));
                    file.copy(str);
                }
            }
        }
        return result;
}


// FOR TEST ONLY

//! \brief Constructor for Unit Test Only
UserFolderManagement::UserFolderManagement(QString folderPath, QObject * parent)
    : QObject(parent), _folderPath(folderPath) {
}


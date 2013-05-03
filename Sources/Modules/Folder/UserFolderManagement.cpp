//! \file UserFolderManagement.cpp
//! \brief	implementation of the header UserFolderManagement : gestion of the user folder
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include    "UserFolderManagement.hh"
#include    "FileSystemWatcher.hh"
#include    "WodaSemaphore.hh"
#include    "ConfFile.hh"
#include    <QFile>
#include    <QFileInfo>
#include    <QDir>
#include    "parser.h"

#include    <iostream>

//! \param[in] parent QObject parent or nothing
//! \brief Constructor
UserFolderManagement::UserFolderManagement(QObject * parent)
    : QObject(parent), _folderPath(QString("")),
      _instanceSemaphore(QString(INSTANCE_USER_FOLDER_MANAGEMENT)) {
    WodaSemaphore::getInstance(_instanceSemaphore);
    WodaSemaphore::createSemaphore(_instanceSemaphore);
}


//! \brief Destructor
UserFolderManagement::~UserFolderManagement() {
    WodaSemaphore::deleteOneInstance(_instanceSemaphore);
}


//! \param[in] bytes string json serialize
//! \brief Deserialize the json send by the server
void            UserFolderManagement::deserializeJsonAccount(QByteArray & bytes) {
    QJson::Parser parser;
    bool ok;
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
    if (!this->checkDirectoryExist(folderPath)) {
        this->createDirectory(folderPath);
    }
    if (!_folderPath.isEmpty() && folderPath != _folderPath)
        this->moveDirectory(folderPath);
    _folderPath = folderPath;
    ConfFile::getSingletonPtr()->setValue(DIRECTORY, QVariant(_folderPath));

    FileSystemWatcher * fsWatcher = FileSystemWatcher::getSingletonPtr();
    fsWatcher->addDirectory(_folderPath);
}


//! \brief delete the current directory of the user
void        UserFolderManagement::deleteDirectory(void) {
    this->deleteFileSystemWatcher();
    if (!_folderPath.isEmpty()) {
        this->removeAllContentAndFolder(_folderPath);

        _folderPath.clear();
        // TO DO : database
        ConfFile::getSingletonPtr()->setValue(DIRECTORY, QVariant(""));
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



// FOR TEST ONLY

//! \brief Constructor for Unit Test Only
UserFolderManagement::UserFolderManagement(QString folderPath, QObject * parent)
    : QObject(parent), _folderPath(folderPath) {
}

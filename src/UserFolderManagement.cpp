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


//! \param[in] folderPath QString of the path of the user folder
//! \brief change the current directory of the user
void        UserFolderManagement::changeDirectory(QString & folderPath) {
    if (!this->checkDirectoryExist(folderPath)) {
        return;
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
    // TO DO
    // voir si enlever semaphore
    // mettre un semaphore
    WodaSemaphore::getInstance(_instanceSemaphore)->acquire(1);
    this->deleteFileSystemWatcher();
    // relacher le semaphore
    WodaSemaphore::getInstance(_instanceSemaphore)->release(1);
    if (!_folderPath.isEmpty()) {
        // mettre un semaphore
        WodaSemaphore::getInstance(_instanceSemaphore)->acquire(1);
        this->removeAllContentAndFolder(_folderPath);
        // relacher le semaphore
        WodaSemaphore::getInstance(_instanceSemaphore)->release(1);

        _folderPath.clear();
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

bool        UserFolderManagement::checkDirectoryExist(const QString & folderPath) {
    QDir directory(folderPath);
    return directory.exists(folderPath);
}

const QString & UserFolderManagement::getCurrentDirectory(void) const {
    return _folderPath;
}

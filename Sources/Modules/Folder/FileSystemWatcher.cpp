//! \file FileSystemWatcher.cpp
//! \brief	implementation of the header FileSystemWatcher to know the changes in a directory
//! \author Woda Corporation
//! \version 1.2
//! \date 2012-11

#include	"FileSystemWatcher.hh"
#include    "RequestHttpFile.hh"
#include    "FolderDB.hh"
#include    "Hash.hh"
#include    "FileManagement.hh"
#include    "Account.hh"

#include    <QDir>
#include    <QFileInfo>


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! initialize QFileSystemWatcher, listFile and connect signal fileChanged and directoryChanged to slots
FileSystemWatcher::FileSystemWatcher(QObject * parent)
 : QObject(parent), _fsWatcher(new QFileSystemWatcher(parent)), _path(""),
   _listFile(new QList<QString>()), _listChange(new QList<QString>()) {
    connect(_fsWatcher, SIGNAL(fileChanged(QString)),
            this, SLOT(eventFile(QString)));
    connect(_fsWatcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(eventFolder(QString)));

    _popup = new Popup(220, 150);
}


//! \brief Destructor
//! delete QFileSystemWatcher, listFile and listChange
FileSystemWatcher::~FileSystemWatcher() {
    this->deleteDirectory();
    delete _fsWatcher;
    delete _listFile;
    delete _listChange;
}


//! \param[in] dir main folder path
//! \brief add the main folder path to check
void        FileSystemWatcher::addDirectory(QString & dir) {
    if (dir == QString("")) {
        this->deleteDirectory();
    } else {
        bool begin = false;
        if (_path == "") {
            begin = true;
        }
        _path = dir;
        _fsWatcher->addPath(_path);
        this->fillFolderInDatabase(_path);


        // TO DO
        if (begin) {
            // if _path before addDirectory is empty
            // call checkFileIntoFolder for add all files
            this->checkFileIntoFolder(_path);
            _prevCountFile = _listFile->count();
        }
    }
}


//! \brief delete the main folder path
void        FileSystemWatcher::deleteDirectory(void) {
    if (_path != QString("")) {
        for (QList<QString>::Iterator it = _listChange->begin();
             it != _listChange->end(); ++it) {
            _fsWatcher->removePath(*it);
        }
        _fsWatcher->removePath(_path);
    }
    _path = "";
    delete _listFile;
    _listFile = new QList<QString>();
    delete _listChange;
    _listChange = new QList<QString>();
}


//! \param[in] path file path
//! \brief private slot for event on a file
//! if a file is create, update or delete
void        FileSystemWatcher::eventFile(const QString & path) {
    this->fillListChange();

    QString str = path;
    // file name
    str = str.mid(str.lastIndexOf('/') + 1);

    // popup
    if (_prevCountFile > _listChange->count()) {
        str.append(" deleted");
        _popup->showUp(str, 5000);
    } else {
        str.append(" updated");
        _popup->showUp(str, 5000);
        //RequestHttpFile::getSingletonPtr()->AddingAFile(path);
    }

    _prevCountFile = _listChange->count();
    this->fillFolderInDatabase(_path);
}


//! \param[in] path folder path
//! \brief private slot for event on a folder
//! if a folder is create, update or delete
void        FileSystemWatcher::eventFolder(const QString & path) {
    this->fillListChange();

    QString str = path;
    // file name
    str = str.mid(str.lastIndexOf('/') + 1);

    // popup
    if (_prevCountFile < _listChange->count()) {
        str.append(" updated");
        _popup->showUp(str, 5000);
    } else if (_prevCountFile > _listChange->count()) {
        str.append(" deleted");
        _popup->showUp(str, 5000);
    }

    _prevCountFile = _listChange->count();
    this->fillFolderInDatabase(_path);
}


//! \brief push into database all directories contents in the main folder
void        FileSystemWatcher::fillFolderInDatabase(QString & pathFolder) {
    FolderDB db;
    QDir directory(pathFolder);

    if (directory.exists(pathFolder)) {
        Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot  | QDir::AllDirs)) {
            if (info.isDir()) {
                QString str = info.absoluteFilePath();
                if (!db.checkFolderExistInDatabase(str)) {
                    db.insertFolder(str);
                }
                if (db.checkFolderSynchronizedWithFileSystem(str)) {
                    _fsWatcher->addPath(str);
                    this->fillFolderInDatabase(str);
                } else {
                    _fsWatcher->removePath(str);
                    this->removeFolderChild(str);
                }
            }
        }
    }
}


//! \brief remove in file system watcher all child for a folder and sync off in database
void        FileSystemWatcher::removeFolderChild(QString & pathFolder) {
    FolderDB db;
    QDir directory(pathFolder);

    if (directory.exists(pathFolder)) {
        Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot  | QDir::AllDirs)) {
            if (info.isDir()) {
                QString str = info.absoluteFilePath();
                _fsWatcher->removePath(str);
                if (db.checkFolderSynchronizedWithFileSystem(str)) {
                    db.insertFolder(str, 0);
                }
                this->removeFolderChild(str);
            }
        }
    }
}

#include <iostream>
//! \brief push into a list all directories and files contents in the main folder
void        FileSystemWatcher::fillListChange(void) {
    delete _listChange;
    _listChange = new QList<QString>();

    // push into listChange all directories
    QStringList directoryList = _fsWatcher->directories();
    foreach (QString directory, directoryList) {
        _listChange->push_back(directory);
    }

    // push into listChange all files
    QStringList fileList = _fsWatcher->files();
    foreach (QString file, fileList) {
        _listChange->push_back(file);
    }


//    QListIterator<QString> it(&_listFile); // iterator for employee list
//    for ( ; it.current(); ++it ) {
//        if (!_listChange->contains(it.current()))
//            std::cout << it.current().toStdString() << std::endl;
//    }
    QList<QString>::iterator it = _listFile->begin();
    for (; it != _listFile->end(); ++it ) {
        if (!_listChange->contains(*it)) {
            std::cout << (*it).toStdString() << std::endl;
            std::cout << FileManagement::getSingletonPtr()->getIdFile(*it) << std::endl;
            RequestHttpFile::getSingletonPtr()->deleteFile(FileManagement::getSingletonPtr()->getIdFile(*it));
            std::cout << "2" << std::endl;
            FolderDB db;
            db.deleteLineFile(*it);
            std::cout << "3" << std::endl;
            _listFile->erase(it);
        }
    }

    // if new elem, call checkFileIntoFolder
    //if (_listChange->count() != _listFile->count()) {
        this->checkFileIntoFolder(_path);
    //} else {
        //_listFile = _listChange;
    //}


}


//! \param[in] dir folder path
//! \brief recursive function, for list all subfolders ans files
void        FileSystemWatcher::checkFileIntoFolder(QString dir) {
    QDir folder(dir);
    folder.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    folder.setNameFilters(QStringList() << "*");
    FolderDB db;

    // browse all documents in the folder
    foreach (QFileInfo fileInfo, folder.entryInfoList()) {
        // check if already exists
        QString file(fileInfo.absoluteFilePath());
        if (!_listFile->contains(file) && !fileInfo.isDir()) {
            _fsWatcher->addPath(file);
            _listFile->push_back(file);
            if (Hash::getLength(file) > 0 && Account::getSingletonPtr()->isConnected()) {
                QString path = file.left(file.lastIndexOf("/"));
                if (path == _path || db.checkFolderSynchronizedWithFileSystem(path)) {
                    db.insertFile(file, Hash::getHash(file));
                    RequestHttpFile::getSingletonPtr()->AddingAFile(file);
                }
            }
        } else if (!_listChange->contains(fileInfo.absoluteFilePath())) {
            std::cout << fileInfo.absoluteFilePath().toStdString() << std::endl;
//            db.deleteLineFile(fileInfo.absoluteFilePath());
////            RequestHttpFile::getSingletonPtr()->deleteAFile(fileInfo.absoluteFilePath());
        }
        // recursive
        if (fileInfo.isDir()) {
            this->checkFileIntoFolder(file);
        }
    }
}



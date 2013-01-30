//! \file FileSystemWatcher.cpp
//! \brief	implementation of the interface to know the changes in a directory
//! \author Woda Corporation
//! \version 1.2
//! \date 2012-11

#include	"FileSystemWatcher.hh"
#include    <QDir>
#include    <QFileInfo>


//! \fn FileSystemWatcher::FileSystemWatcher(QObject * parent)
//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
FileSystemWatcher::FileSystemWatcher(QObject * parent)
 : QObject(parent), _fsWatcher(new QFileSystemWatcher(parent)), _path(""),
   _listFile(new QList<QString>()), _listChange(new QList<QString>()) {
    connect(_fsWatcher, SIGNAL(fileChanged(QString)),
            this, SLOT(eventFile(QString)));
    connect(_fsWatcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(eventFolder(QString)));

    _popup = new Popup(220, 150);
}


//! \fn FileSystemWatcher::~FileSystemWatcher()
//! \brief Destructor
FileSystemWatcher::~FileSystemWatcher() {
    delete _fsWatcher;
    delete _listFile;
    delete _listChange;
}


//! \fn void FileSystemWatcher::addDirectory(QString & dir)
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
        if (begin) {
            // if _path before addDirectory is empty
            // call checkFileIntoFolder for add all files
            this->checkFileIntoFolder(_path);
            _prevCountFile = _listFile->count();
        }
    }
}


//! \fn void FileSystemWatcher::deleteDirectory(void)
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
}


//! \fn void FileSystemWatcher::eventFile(const QString & path)
//! \param[in] path file path
//! \brief private slot for event on a file
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
    }

    _prevCountFile = _listChange->count();
}


//! \fn void FileSystemWatcher::eventFolder(const QString & path)
//! \param[in] path folder path
//! \brief private slot for event on a folder
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
}


//! \fn void FileSystemWatcher::fillListChange(void)
//! \brief push into a list all directories and files contents in the main folder
void        FileSystemWatcher::fillListChange(void) {
    delete _listChange;
    _listChange = new QList<QString>();

    // push into listChange all directories
    QStringList directoryList = _fsWatcher->directories();
    foreach (QString directory, directoryList)
        _listChange->push_back(directory);

    // push into listChange all files
    QStringList fileList = _fsWatcher->files();
    foreach (QString file, fileList)
        _listChange->push_back(file);

    // if new elem, call checkFileIntoFolder
    if (_listChange->count() >= _listFile->count()) {
        this->checkFileIntoFolder(_path);
    } else {
        _listFile = _listChange;
    }
}


//! \fn void FileSystemWatcher::checkFileIntoFolder(QString dir)
//! \param[in] dir folder path
//! \brief recursive function, for list all subfolders ans files
void        FileSystemWatcher::checkFileIntoFolder(QString dir) {
    QDir folder(dir);
    folder.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    folder.setNameFilters(QStringList() << "*");

    // browse all documents in the folder
    foreach (QFileInfo fileInfo, folder.entryInfoList()) {
        // check if already exists
        if (!_listFile->contains(fileInfo.absoluteFilePath())) {
            _fsWatcher->addPath(fileInfo.absoluteFilePath());
            _listFile->push_back(fileInfo.absoluteFilePath());
        }
        // recursive
        if (fileInfo.isDir()) {
            this->checkFileIntoFolder(fileInfo.absoluteFilePath());
        }
    }
}



//! \file FileManagement.cpp
//! \brief	implementation of the header FileManagement : gestion of the user file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-11

#include    "FileManagement.hh"
#include    "FolderDB.hh"


//! \param[in] parent QObject parent or nothing
//! \brief Constructor
FileManagement::FileManagement(QObject * parent)
    : QObject(parent) {
}


//! \brief Destructor
FileManagement::~FileManagement() {
}


//! \brief get the id of the file with the folder and the file name
//! \param[in] filePath QString of the folder append with the file name
//! \return the id of the file
int         FileManagement::getIdFile(const QString & filePath) {
    QString fileName(filePath);
    fileName = fileName.right(fileName.lastIndexOf("/"));
    QString folderPath(filePath);
    folderPath = folderPath.left(fileName.lastIndexOf("/"));

    FolderDB db;
    return db.getIdFile(fileName, folderPath);
}

//! \brief get the name of the file with the unique ID of the file
//! \param[in] id int unique id of the file
//! \return the file name
QString     FileManagement::getFileName(int id) {
    FolderDB db;
    return db.getFileName(id);
}


//! \brief get the folder path of the file with the unique ID of the file
//! \param[in] id int unique id of the file
//! \return the folder path
QString     FileManagement::getFileFolder(int id) {
    FolderDB db;
    return db.getFileFolderPath(id);
}


//! \brief get the file path of the file with the unique ID of the file
//! \param[in] id int unique id of the file
//! \return the file path
QString     FileManagement::getFilePath(int id) {
    QString filename = this->getFileName(id);
    QString folderPath = this->getFileFolder(id);

    QString filePath(folderPath);
    filePath.append("/");
    filePath.append(filename);

    return filePath;
}


//! \brief get the id of the file with the folder and the file name
//! \param[in] id int unique id of the file
//! \return the size
int         FileManagement::getFilePartSize(int id) {
    FolderDB db;
    return db.getFilePartSize(id);
}


//! \brief set the synchronised boolean if it's download
//! \param[in] sync bool
void        FileManagement::setSynchronized(int id, bool sync) {
    FolderDB db;
    if (sync) db.insertFile(id, 1);
    else db.insertFile(id, 0);
}

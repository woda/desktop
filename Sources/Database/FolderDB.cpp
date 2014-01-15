//! \file FolderDB.hh
//! \brief header FolderDB : information about user folder and his content for create DB
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#include    <QString>
#include    <map>
#include    <vector>
#include    "FolderDB.hh"
#include    "DataBase.hh"


//! \brief Constructor
FolderDB::FolderDB() {
}


//! \brief Destructor
FolderDB::~FolderDB() {
}


//! \brief create the querry for create the folder table and the file table
//! \return a vector fill with querry for create account tables
std::vector<QString>    FolderDB::createTable(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("CREATE TABLE folder (path text)"));
    vstr.push_back(QString("CREATE TABLE file (id integer, name text, "
                           "id_folder text, favorite integer, "
                           "publicness integer, size text, part_size text, "
                           "synchronized id, hash text)"));
    return vstr;
}


//! \return a vector fill with the primary keys for the foler table
std::vector<QString>    FolderDB::folderPrimaryKey(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("path"));
    return vstr;
}


//! \return a vector fill with the primary keys for the file table
std::vector<QString>    FolderDB::filePrimaryKey(void) {
    std::vector<QString> vstr(0);
    //vstr.push_back(QString("id"));
    vstr.push_back(QString("name"));
    vstr.push_back(QString("id_folder"));
    return vstr;
}


//! \return a string with the name of the folder table
QString                 FolderDB::folderTable(void) {
    return QString("folder");
}


//! \return a string with the name of the file table
QString                 FolderDB::fileTable(void) {
    return QString("file");
}


//! \brief add quote between the string pass as parameter
//! \param[in] str string
//! \return a string with quotes
QString                 FolderDB::addQuotes(QString str) {
    return QString("\"").append(str).append("\"");
}


//! \brief insert the path of a folder who is in the user directory
//! \brief in the folder table in database
//! \param[in] folderPath QString
void                    FolderDB::insertFolder(QString & folderPath) {
    QString table = this->folderTable();
    std::map<QString, QString> map;
    map[QString(FOLDER_PATH)] = this->addQuotes(folderPath);

    DataBase::getSingletonPtr()->insert(table, map);
}


//! \brief insert the path of a file who is in the user directory
//! \brief in the file table in database
//! \param[in] filePath QString
void                    FolderDB::insertFile(const QString & filePath, const QByteArray hashContent) {
    QString table = this->fileTable();
    std::map<QString, QString> map;

    QString fileName(filePath);
    fileName = fileName.right(filePath.length() - filePath.lastIndexOf("/") - 1);
    map[QString(FILE_NAME)] = this->addQuotes(fileName);

    QString folderPath(filePath);
    folderPath = folderPath.left(filePath.lastIndexOf("/"));
    map[QString(FILE_ID_FOLDER)] = this->addQuotes(folderPath);

    QString hash(hashContent);
    map[QString(FILE_HASH)] = this->addQuotes(hash);
    map[QString(FILE_SYNCHRONIZED)] = QString().setNum(0);

    DataBase::getSingletonPtr()->insert(table, map);
}

//! \brief insert the properties of a file who is in the user directory
//! \brief in the file table in database
//! \param[in] id int
//! \param[in] name QString &
//! \param[in] idFolder QString &
//! \param[in] favorite bool
//! \param[in] publicness bool
//! \param[in] size QString &
//! \param[in] partSize QString &
void                    FolderDB::insertFile(QString & name, QString & idFolder,
                                             QString & hash) {
    QString table = this->fileTable();
    std::map<QString, QString> map;

    map[QString(FILE_NAME)] = this->addQuotes(name);
    map[QString(FILE_ID_FOLDER)] = this->addQuotes(idFolder);
    map[QString(FILE_HASH)] = this->addQuotes(hash);

    DataBase::getSingletonPtr()->insert(table, map);
}


void                    FolderDB::insertFile(int id, QString & hash) {
    QString table = this->fileTable();
    std::map<QString, QString> map;

    map[QString(FILE_ID)] = QString().setNum(id);
    map[QString(FILE_NAME)] = this->addQuotes(this->getFileName(id));
    map[QString(FILE_ID_FOLDER)] = this->addQuotes(this->getFileFolderPath(id));
    map[QString(FILE_HASH)] = this->addQuotes(hash);

    DataBase::getSingletonPtr()->insert(table, map);
}


void                    FolderDB::insertFile(int id, int sync) {
    QString table = this->fileTable();
    std::map<QString, QString> map;

    map[QString(FILE_ID)] = QString().setNum(id);
    map[QString(FILE_NAME)] = this->addQuotes(this->getFileName(id));
    map[QString(FILE_ID_FOLDER)] = this->addQuotes(this->getFileFolderPath(id));
    map[QString(FILE_SYNCHRONIZED)] = QString().setNum(sync);

    DataBase::getSingletonPtr()->insert(table, map);
}


//! \brief insert the properties of a file who is in the user directory
//! \brief in the file table in database
//! \param[in] id int
//! \param[in] name QString &
//! \param[in] idFolder QString &
//! \param[in] favorite bool
//! \param[in] publicness bool
//! \param[in] size QString &
//! \param[in] partSize QString &
void                    FolderDB::insertFile(int id, QString & name,
                                             QString & idFolder, bool favorite,
                                             bool publicness, QString & size,
                                             QString & partSize) {
    QString table = this->fileTable();
    std::map<QString, QString> map;

    map[QString(FILE_ID)] = QString().setNum(id);
    map[QString(FILE_NAME)] = this->addQuotes(name);
    map[QString(FILE_ID_FOLDER)] = this->addQuotes(idFolder);
    map[QString(FILE_FAVORITE)] = QString().setNum(favorite);
    map[QString(FILE_PUBLICNESS)] = QString().setNum(publicness);
    map[QString(FILE_SIZE)] = this->addQuotes(size);
    map[QString(FILE_PART_SIZE)] = this->addQuotes(partSize);

    DataBase::getSingletonPtr()->insert(table, map);
}


//! \brief check if the file is in the database
//! \param[in] id int
//! \return true if exist, otherwise false
bool                    FolderDB::checkFile(int id) {
    QString str("SELECT ");
    str.append(FILE_ID).append(" FROM ");
    str.append(FolderDB::fileTable());
    str.append(" WHERE ").append(FILE_ID).append("=");
    str.append(QString().setNum(id));

    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    if ((*((*map)[QString(FILE_ID)])).size() > 0) {
        return true;
    }
    return false;
}

#include <iostream>
//! \brief check if the file is synchronized with the server
//! \param[in] id int
//! \return true if synchro, otherwise false
bool                    FolderDB::checkFileSynchronized(int id) {
    QString str("SELECT ");
    str.append(FILE_SYNCHRONIZED).append(" FROM ");
    str.append(FolderDB::fileTable());
    str.append(" WHERE ").append(FILE_ID).append("=");
    str.append(QString().setNum(id));

    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    std::cout << "0" << std::endl;
    if ((*((*map)[QString(FILE_SYNCHRONIZED)])).size() > 0) {
        std::cout << "1" << std::endl;
        if ((*((*map)[QString(FILE_SYNCHRONIZED)])).front().toInt()) {
            std::cout << "2" << std::endl;
            return true;
        }
    }
    return false;
}


//! \brief select all info in folder table
//! \return a map with QString of the column name and a vector of string with all informations line by line
std::map<QString, std::vector<QString> *> * FolderDB::selectAllFolder(void) {
    QString str("SELECT * FROM ");
    str.append(FolderDB::folderTable());
    return DataBase::getSingletonPtr()->select(str);
}


//! \brief select all info in file table
//! \return a map with QString of the column name and a vector of string with all informations line by line
std::map<QString, std::vector<QString> *> * FolderDB::selectAllFile(void) {
    QString str("SELECT * FROM ");
    str.append(FolderDB::fileTable());
    return DataBase::getSingletonPtr()->select(str);
}


//! \brief delete informations of the directory in folder table
//! \param[in] folderPath QString
void                    FolderDB::deleteLineFolder(QString & folderPath) {
    this->deleteLineAllFilesInFolder(folderPath);
    // appel delete avec les PK insere dans la clause where
    QString table = this->folderTable();
    std::vector<QString> where;
    QString key(FOLDER_PATH);
    key.append(" = ").append(folderPath);
    where.push_back(key);
    DataBase::getSingletonPtr()->deleteLine(table, where);
}


//! \brief delete all file in file table with the folderPath as paramater
//! \param[in] folderPath QString
void                    FolderDB::deleteLineAllFilesInFolder(QString & folderPath) {
    // appel delete avec les PK insere dans la clause where
    QString table = this->fileTable();
    std::vector<QString> where;
    QString key(FILE_ID_FOLDER);
    key.append(" = ").append(folderPath);
    where.push_back(key);
    DataBase::getSingletonPtr()->deleteLine(table, where);
}


//! \brief delete informations of the file in file table
//! \param[in] filePath QString
void                    FolderDB::deleteLineFile(const QString & filePath) {
    // appel delete avec les PK insere dans la clause where
    QString table = this->fileTable();
    std::vector<QString> where;

    QString fileName(filePath);
    fileName = fileName.right(fileName.lastIndexOf("/"));
    QString folderPath(filePath);
    folderPath = folderPath.left(fileName.lastIndexOf("/"));

    QString key1(FILE_NAME);
    key1.append(" = ").append(fileName);
    where.push_back(key1);

    QString key2(FILE_ID_FOLDER);
    key2.append(" = ").append(folderPath);
    where.push_back(key2);

    DataBase::getSingletonPtr()->deleteLine(table, where);
}


//! \brief select the id of the file with the filename and the folder path
//! \param[in] filename QString
//! \param[in] folderPath QString
int                     FolderDB::getIdFile(const QString & filename,
                                            const QString & folderPath) {
    QString table = this->fileTable();
    std::vector<QString> select;
    std::vector<QString> where;

    // select
    select.push_back(FILE_ID);

    // where
    QString key1(FILE_NAME);
    key1.append(" = ").append(filename);
    where.push_back(key1);

    QString key2(FILE_ID_FOLDER);
    key2.append(" = ").append(folderPath);
    where.push_back(key2);

    // result
    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(table, select, where);
    if ((*((*map)[QString(FILE_ID)])).size() > 0) {
        return (*((*map)[QString(FILE_ID)])).front().toInt();
    }
    return 0;
}


//! \brief select the name of the file with the unique id of the file
//! \param[in] id int unique id of the file
QString                 FolderDB::getFileName(int id) {
    QString str("SELECT ");
    str.append(FILE_NAME).append(" FROM ");
    str.append(FolderDB::fileTable());
    str.append(" WHERE ").append(FILE_ID).append("=");
    str.append(QString().setNum(id));

    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    if ((*((*map)[QString(FILE_NAME)])).size() > 0) {
        return (*((*map)[QString(FILE_NAME)])).front();
    }
    return "";
}


//! \brief select the folder of the file with the unique id of the file
//! \param[in] id int unique id of the file
QString                 FolderDB::getFileFolderPath(int id) {
    QString str("SELECT ");
    str.append(FILE_ID_FOLDER).append(" FROM ");
    str.append(FolderDB::fileTable());
    str.append(" WHERE ").append(FILE_ID).append("=");
    str.append(QString().setNum(id));

    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    if ((*((*map)[QString(FILE_ID_FOLDER)])).size() > 0) {
        return (*((*map)[QString(FILE_ID_FOLDER)])).front();
    }
    return "";
}


//! \brief select the part size of the file with the unique id of the file
//! \param[in] id int unique id of the file
int                 FolderDB::getFilePartSize(int id) {
    QString str("SELECT ");
    str.append(FILE_PART_SIZE).append(" FROM ");
    str.append(FolderDB::fileTable());
    str.append(" WHERE ").append(FILE_ID).append("=");
    str.append(QString().setNum(id));

    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    if ((*((*map)[QString(FILE_PART_SIZE)])).size() > 0) {
        return (*((*map)[QString(FILE_PART_SIZE)])).front().toInt();
    }
    return 0;
}


//! \brief select the size of the file with the unique id of the file
//! \param[in] id int unique id of the file
int                 FolderDB::getFileSize(int id) {
    QString str("SELECT ");
    str.append(FILE_SIZE).append(" FROM ");
    str.append(FolderDB::fileTable());
    str.append(" WHERE ").append(FILE_ID).append("=");
    str.append(QString().setNum(id));

    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    if ((*((*map)[QString(FILE_SIZE)])).size() > 0) {
        return (*((*map)[QString(FILE_SIZE)])).front().toInt();
    }
    return 0;
}

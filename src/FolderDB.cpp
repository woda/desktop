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

FolderDB::FolderDB() {
}

FolderDB::~FolderDB() {
}

std::vector<QString>    FolderDB::createTable(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("CREATE TABLE folder (path text)"));
    vstr.push_back(QString("CREATE TABLE file (name text, "
                           "idFolder text, hash text)"));
    return vstr;
}

std::vector<QString>    FolderDB::folderPrimaryKey(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("path"));
    return vstr;
}

std::vector<QString>    FolderDB::filePrimaryKey(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("name"));
    vstr.push_back(QString("idFolder"));
    return vstr;
}

QString                 FolderDB::folderTable(void) {
    return QString("folder");
}

QString                 FolderDB::fileTable(void) {
    return QString("folder");
}

QString                 FolderDB::addQuotes(QString str) {
    return QString("\"").append(str).append("\"");
}


void                    FolderDB::insertFolder(QString & folderPath) {
    QString table = this->folderTable();
    std::map<QString, QString> map;
    map[QString(FOLDER_PATH)] = this->addQuotes(folderPath);

    DataBase::getSingletonPtr()->insert(table, map);
}

void                    FolderDB::insertFile(QString & filePath) {
    QString table = this->fileTable();
    std::map<QString, QString> map;

    QString fileName(filePath);
    fileName = fileName.right(fileName.lastIndexOf("/"));
    map[QString(FILE_NAME)] = this->addQuotes(fileName);

    QString folderPath(filePath);
    folderPath = folderPath.left(fileName.lastIndexOf("/"));
    map[QString(FILE_ID_FOLDER)] = this->addQuotes(folderPath);

    QString hash("hash");
    map[QString(FILE_HASH)] = this->addQuotes(hash);

    DataBase::getSingletonPtr()->insert(table, map);
}



std::map<QString, std::vector<QString> *> * FolderDB::selectAllFolder(void) {
    QString str("SELECT * FROM ");
    str.append(FolderDB::folderTable());
    return DataBase::getSingletonPtr()->select(str);
}

std::map<QString, std::vector<QString> *> * FolderDB::selectAllFile(void) {
    QString str("SELECT * FROM ");
    str.append(FolderDB::fileTable());
    return DataBase::getSingletonPtr()->select(str);
}



void                    FolderDB::deleteLine(void) {
}

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

void                    FolderDB::deleteLineAllFilesInFolder(QString & folderPath) {
    // appel delete avec les PK insere dans la clause where
    QString table = this->fileTable();
    std::vector<QString> where;
    QString key(FILE_ID_FOLDER);
    key.append(" = ").append(folderPath);
    where.push_back(key);
    DataBase::getSingletonPtr()->deleteLine(table, where);
}

void                    FolderDB::deleteLineFile(QString & filePath) {
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

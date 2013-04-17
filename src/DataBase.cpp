//! \file DataBase.cpp
//! \brief	header DataBase : interaction with the database
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04


#include    <QDebug>
#include    <QtSql>
#include    <QString>
#include    <utility>
#include    <map>
#include    <vector>
#include    <iostream>

#include    "DataBase.hh"
#include    "AccountDB.hh"
#include    "FolderDB.hh"

DataBase::DataBase()
    :   _connect(0),
        _create(0),
        _vQuery(new std::vector<QString>()),
        _empty(true) {
    //
    // Add static createTable method for create the table
    _mapCreate = new std::vector<func>();
    _mapCreate->push_back(&AccountDB::createTable);
    _mapCreate->push_back(&FolderDB::createTable);


    _mapPrimaryKey = new std::map<QString, func>();
    // if change TourneeDB::tourneeTable(), also change in checkDataBase()
    _mapPrimaryKey->insert(std::pair<QString, func>(AccountDB::accountTable(),
                                                    &AccountDB::accountPrimaryKey));
    _mapPrimaryKey->insert(std::pair<QString, func>(FolderDB::folderTable(),
                                                    &FolderDB::folderPrimaryKey));
    _mapPrimaryKey->insert(std::pair<QString, func>(FolderDB::fileTable(),
                                                    &FolderDB::filePrimaryKey));


    // Open Database
    _db = new QSqlDatabase();
    *_db = QSqlDatabase::addDatabase(DB_TYPE);
    _db->setDatabaseName(DB_NAME);

    // Check if software can connect to the database
    this->open();
    this->close();

    // Check if db is empty or not
//    _empty = this->checkDataBase();
//    std::cout << "empty = " << _empty << std::endl;
}

DataBase::~DataBase() {
    QString str = _db->connectionName();
    this->close();
    delete _db;
    delete _vQuery;
    delete _mapCreate;
    delete _mapPrimaryKey;
    QSqlDatabase::removeDatabase(str);
}

void        DataBase::open() {
    bool    beforeOpen = _connect;
    _db->open();
    if (_db->lastError().isValid()) {
        _connect = 0;
        qDebug() << _db->lastError();
    } else {
        _connect = 1;
    }
    if (beforeOpen == 0 && _connect == 1) {
        this->close();
        if (!_create) {
            this->create();
        }
        this->executeQuery();
        this->open();
    }
}

inline void DataBase::close() {
    _db->close();
}

inline void DataBase::execute(QString & str) {
    QSqlQuery query;
    if (str == NULL)
        return;
    if (!query.exec(str))
        qDebug() << query.lastError();
}

void        DataBase::create() {
    this->open();
    for (std::vector<func>::iterator it = _mapCreate->begin();
         it != _mapCreate->end(); ++it) {
        QSqlQuery query;
        std::vector<QString> vstr = (*it)();
        for (std::vector<QString>::iterator it2 = vstr.begin();
             it2 != vstr.end(); ++it2) {
            if (!query.exec(*it2)) {
                if (query.lastError().number() != 1)
                    qDebug() << query.lastError();
            }
        }
    }
    _create = 1;
    this->close();
}

bool        DataBase::checkInsertWithoutPrimary(QString & table,
                                        std::map<QString, QString> &mapInsert) {
    // si la table n'a pas de PK, regarde si tous les elements sont identique
    QString str("SELECT ");
    bool    begin = false;
    for (std::map<QString, QString>::iterator it = mapInsert.begin();
         it != mapInsert.end(); ++it) {
        if (begin)
            str.append(" || ");
        begin = true;
        str.append(it->first);
    }
    str.append(" as id FROM ").append(table).append(" WHERE ");
    begin = false;
    for (std::map<QString, QString>::iterator it = mapInsert.begin();
         it != mapInsert.end(); ++it) {
        if (begin)
            str.append(" AND ");
        begin = true;
        str.append(it->first).append(" = ").append(it->second);
    }
    std::map<QString, std::vector<QString> *> * res;
    res = this->select(str);
    if ((*res)[QString("id")]->size() > 0)
        return false;
    return true;
}

bool        DataBase::checkInsert(QString & table,
                                  std::map<QString, QString> & mapInsert) {
    // verifie que la ligne n'existe pas (cle primaire), sinon return false
    bool    begin = false;
    std::vector<QString> vstr = (*_mapPrimaryKey)[table]();
    if (vstr.size() == 0)
        return this->checkInsertWithoutPrimary(table, mapInsert);
    QString str("SELECT ");
    for (std::vector<QString>::iterator it = vstr.begin();
         it != vstr.end(); ++it) {
        if (begin)
            str.append(" || ");
        begin = true;
        str.append(*it);
    }
    str.append(" as id FROM ").append(table).append(" WHERE ");
    begin = false;
    for (std::vector<QString>::iterator it = vstr.begin();
         it != vstr.end(); ++it) {
        if (begin)
            str.append(" AND ");
        begin = true;
        str.append(*it).append(" = ").append(mapInsert[*it]);
    }
    std::map<QString, std::vector<QString> *> * res;
    res = this->select(str);
    if ((*res)[QString("id")]->size() > 0)
        return false;
    return true;
}

std::vector<QString> DataBase::insertToUpdate(QString & table,
                                        std::map<QString, QString> & mapInsert){
    std::vector<QString> vWhere;
    std::vector<QString> vstr = (*_mapPrimaryKey)[table]();
    for (std::vector<QString>::iterator it = vstr.begin();
         it != vstr.end(); ++it) {
        QString str("");
        str.append(*it).append(" = ").append(mapInsert[*it]);
        vWhere.push_back(str);
    }
    return vWhere;
}

void        DataBase::insert(QString & from,
                             std::map<QString, QString> & mapInsert) {
    // effectue un insert a partir d'un nom table
    // et d'une map avec pour cle le nom de la colonne et pour valeur, ben la valeur :p
    bool begin = false;
    if (!this->checkInsert(from, mapInsert)) {
        if ((*_mapPrimaryKey)[from]().size() == 0)
            return;
        std::vector<QString> vWhere = this->insertToUpdate(from, mapInsert);
        this->update(from, mapInsert, vWhere);
        return;
    }
    QString str("INSERT INTO ");
    str.append(from).append(" (");
    for (std::map<QString, QString>::iterator it = mapInsert.begin();
         it != mapInsert.end(); ++it) {
        if (begin)
            str.append(", ");
        begin = true;
        str.append(it->first);
    }
    begin = false;
    str.append(") VALUES (");
    for (std::map<QString, QString>::iterator it = mapInsert.begin();
         it != mapInsert.end(); ++it) {
        if (begin)
            str.append(", ");
        begin = true;
        str.append(it->second);
    }
    str.append(")");
    this->open();
    if (_connect)
        this->execute(str);
    else
        this->addQuery(str);
    this->close();
}

bool        DataBase::checkUpdate(QString & table,
                                  std::map<QString, QString> & mapUpdate) {
    // verifie que la ligne existe bien, sinon return false
    bool    begin = false;
    std::vector<QString> vstr = (*_mapPrimaryKey)[table]();
    if (vstr.size() == 0)
        return false;
    QString str("SELECT ");
    for (std::vector<QString>::iterator it = vstr.begin();
         it != vstr.end(); ++it) {
        if (begin)
            str.append(" || ");
        begin = true;
        str.append(*it);
    }
    str.append(" as id FROM ").append(table).append(" WHERE ");
    begin = false;
    for (std::vector<QString>::iterator it = vstr.begin();
         it != vstr.end(); ++it) {
        if (begin)
            str.append(" AND ");
        begin = true;
        str.append(*it).append(" = ").append(mapUpdate[*it]);
    }
    std::map<QString, std::vector<QString> *> * res;
    res = this->select(str);
    if ((*res)[QString("id")]->size() > 0)
        return true;
    return false;
}

void        DataBase::update(QString & table,
                             std::map<QString, QString> & mapUpdate,
                             std::vector<QString> & vWhere) {
    // effectue un update a partir d'un nom table, d'une liste pour where
    // et d'une map avec pour cle le nom de la colonne et pour valeur, ben la valeur :p
    bool begin = false;
    if (!this->checkUpdate(table, mapUpdate)) {
        this->insert(table, mapUpdate);
        return;
    }
    QString str("UPDATE ");
    str.append(table).append(" SET ");
    for (std::map<QString, QString>::iterator it = mapUpdate.begin();
         it != mapUpdate.end(); ++it) {
        if (begin)
            str.append(", ");
        begin = true;
        str.append(it->first).append("=").append(it->second);
    }
    begin = false;
    str.append(" WHERE ");
    for (std::vector<QString>::iterator it = vWhere.begin();
         it != vWhere.end(); ++it) {
        if (begin)
            str.append(" AND ");
        begin = true;
        str.append(*it);
    }
    this->open();
    if (_connect)
        this->execute(str);
    else
        this->addQuery(str);
    this->close();
}

void        DataBase::deleteLine(QString & table,
                                 std::vector<QString> & vWhere) {
    // effectue un delete a partir d'un nom table et d'une liste pour where
    bool begin = false;
    this->open();
    QString str("DELETE FROM ");
    str.append(table).append(" WHERE ");
    for (std::vector<QString>::iterator it = vWhere.begin();
         it != vWhere.end(); ++it) {
        if (begin)
            str.append(" AND ");
        begin = true;
        str.append(*it);
    }
    if (_connect)
        this->execute(str);
    else
        this->addQuery(str);
    this->close();
}

std::map<QString, std::vector<QString> *> * DataBase::select(QString & from,
                                                             std::vector<QString> & vSelect) {
    // effectue un SELECT a l'aide d'une table et de list select, sans where
    bool    begin = false;
    QString str("SELECT ");
    for (std::vector<QString>::iterator it = vSelect.begin();
         it != vSelect.end(); ++it) {
        if (begin)
            str.append(", ");
        begin = true;
        str.append(*it);
    }
    str.append(" FROM ");
    str.append(from);
    return this->select(str);
}

std::map<QString, std::vector<QString> *> * DataBase::select(QString & from,
                                                             std::vector<QString> & vSelect,
                                                             std::vector<QString> & vWhere) {
    // effectue un SELECT a l'aide d'une table et de list select et where
    bool    begin = false;
    QString str("SELECT ");
    for (std::vector<QString>::iterator it = vSelect.begin();
         it != vSelect.end(); ++it) {
        if (begin)
            str.append(", ");
        begin = true;
        str.append(*it);
    }
    str.append(" FROM ");
    str.append(from);
    begin = false;
    for (std::vector<QString>::iterator it = vWhere.begin();
         it != vWhere.end(); ++it) {
        if (begin)
            str.append(" AND ");
        begin = true;
        str.append(*it);
    }
    return this->select(str);
}

std::map<QString, std::vector<QString> *> * DataBase::select(QString & strQuery) {
    // effectue un SELECT a l'aide d'une requete complete en string
    std::map<QString, std::vector<QString> *> * mapResult;
    mapResult = new std::map<QString, std::vector<QString> *>();
    this->open();
    if (!_connect)
        return mapResult;
    QSqlQuery query(strQuery);
    QSqlRecord rec = query.record();
    for (int i = 0; i < rec.count(); ++i) {
        std::vector<QString> * vecResult = new std::vector<QString>();
        QString header = rec.fieldName(i);
        std::pair<QString, std::vector<QString> *> pair;
        pair.first = header;
        pair.second = vecResult;
        mapResult->insert(pair);
    }
    while (query.next()) {
        for (int i = 0; i < rec.count(); ++i) {
            std::vector<QString> * vecResult = (*mapResult)[rec.fieldName(i)];
            vecResult->push_back(query.value(i).toString());
        }
    }
    query.clear();
    query.finish();
    this->close();
    return mapResult;
}


bool        DataBase::checkDataBase(void) {
    // regarde si la db contient des elements
    QString table = AccountDB::accountTable();
    QString str("SELECT * FROM");
    str.append(table);

    std::map<QString, std::vector<QString> *> * mapResult = this->select(str);

    if (((*mapResult)[QString("login")])->size() > 0)
        return false;
    return true;
}

bool        DataBase::getEmpty(void) const {
    return _empty;
}

//////////////////////////
// QUERY IF NO CONNECTION
//////////////////////////
inline void DataBase::addQuery(QString & str) {
    _vQuery->push_back(str);
}

inline void DataBase::deleteQuery(void) {
    _vQuery->clear();
}

void        DataBase::executeQuery(void) {
    for (std::vector<QString>::iterator it = _vQuery->begin();
         it != _vQuery->end(); ++it) {
        this->open();
        if (_connect) {
            this->execute(*it);
            it = _vQuery->erase(it);
        }
        this->close();
    }
}

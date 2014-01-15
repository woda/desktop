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

#include    <QMessageBox>


//! \brief Constructor
//! \brief create map with function pointer for create all tables in database
//! \brief create map Primary Key
//! \brief Create and Open the Sql Database
DataBase::DataBase()
    :   _connect(0),
        _create(0),
        _vQuery(new std::vector<QString>()),
        _empty(true) {

    // Add static createTable method for create the table
    _mapCreate = new std::vector<func>();
    _mapCreate->push_back(&AccountDB::createTable);
    _mapCreate->push_back(&FolderDB::createTable);


    _mapPrimaryKey = new std::map<QString, func>();
    // if change AccountDB::accountTable(), also change in checkDataBase()
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
    _empty = this->checkDataBase();
//    std::cout << "empty = " << _empty << std::endl;

}


//! \brief Destructor
//! \brief Close the Database and remove the database into the Qt Module
DataBase::~DataBase() {
    QString str = _db->connectionName();
    this->close();
    delete _db;
    delete _vQuery;
    delete _mapCreate;
    delete _mapPrimaryKey;
    QSqlDatabase::removeDatabase(str);
}


//! \brief open the database, if the database is not create call create method
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


//! \brief close the database
inline void DataBase::close() {
    _db->close();
}


//! \brief execute the query
//! \param[in] strQuery QString query
inline void DataBase::execute(QString & strQuery) {
    QSqlQuery query;
    if (strQuery == NULL)
        return;
    if (!query.exec(strQuery))
        qDebug() << query.lastError();
}


//! \brief create all table, call all function pointer for create tables
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


//! \brief If the table have no Primary Key
//! \brief check if the table have already the elements in database
//! \brief for not to have 2 rows with the same values
//! \param[in] table QString
//! \param[in] mapInsert QString map with columns and values
//! \return false if all element are already in database, otherwise true
bool        DataBase::checkInsertWithoutPrimary(QString & table,
                                        std::map<QString, QString> &mapInsert) {
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


//! \brief If the table have Primary Key
//! \brief check if the table have already the element with the primary key in database
//! \param[in] table QString
//! \param[in] mapInsert QString map with columns and values
//! \return false if the primary key is already in database, otherwise true
bool        DataBase::checkInsert(QString & table,
                                  std::map<QString, QString> & mapInsert) {
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


//! \brief change the map for insert elements to a vector for update elements
//! \param[in] table QString
//! \param[in] mapInsert map with column name for key and value for the value
//! \return a vector of QString for update the element
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


//! \brief insert the element contained in the map into the database
//! \param[in] table QString
//! \param[in] mapInsert map with column name for key and value for the value
void        DataBase::insert(QString & table,
                             std::map<QString, QString> & mapInsert) {
    bool begin = false;
    if (!this->checkInsert(table, mapInsert)) {
        if ((*_mapPrimaryKey)[table]().size() == 0)
            return;
        std::vector<QString> vWhere = this->insertToUpdate(table, mapInsert);
        this->update(table, mapInsert, vWhere);
        return;
    }
    QString str("INSERT INTO ");
    str.append(table).append(" (");
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


//! \brief check if the table have already the element in database
//! \param[in] table QString
//! \param[in] mapUpdate map with column name for key and value for the value
//! \return true if the elements are already in database, otherwise false
bool        DataBase::checkUpdate(QString & table,
                                  std::map<QString, QString> & mapUpdate) {
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


//! \brief update the database with a map for know the values
//! \brief and a where clause for update just 1 or more rows
//! \param[in] table QString
//! \param[in] mapUpdate map with column name for key and value for the value
//! \param[in] vWhere vector of QString for where clause
void        DataBase::update(QString & table,
                             std::map<QString, QString> & mapUpdate,
                             std::vector<QString> & vWhere) {
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


//! \brief delete line(s) in the table with a where clause
//! \param[in] table QString
//! \param[in] vWhere vector of QString for where clause
void        DataBase::deleteLine(QString & table,
                                 std::vector<QString> & vWhere) {
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


//! \brief delete all line(s) in the table
//! \param[in] table QString
void        DataBase::deleteAllLine(QString & table) {
    this->open();
    QString str("DELETE FROM ");
    str.append(table);
    if (_connect)
        this->execute(str);
    else
        this->addQuery(str);
    this->close();
}


//! \brief select the element(s) thanks to the column name in the the vSelect
//! \param[in] table QString
//! \param[in] vSelect vector of QString with name of the column for the select
//! \return a map with QString of the column name and a vector of string with all informations line by line
std::map<QString, std::vector<QString> *> * DataBase::select(QString & table,
                                                             std::vector<QString> & vSelect) {
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
    str.append(table);
    return this->select(str);
}


//! \brief select the element(s) thanks to the column name in the the vSelect and a where clause
//! \param[in] table QString
//! \param[in] vSelect vector of QString with name of the column for the select
//! \param[in] vWhere vector of QString for where clause
//! \return a map with QString of the column name and a vector of string with all informations line by line
std::map<QString, std::vector<QString> *> * DataBase::select(QString & from,
                                                             std::vector<QString> & vSelect,
                                                             std::vector<QString> & vWhere) {
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


//! \brief select the element(s) with a complete query
//! \param[in] strQuery QString
//! \return a map with QString of the column name and a vector of string with all informations line by line
std::map<QString, std::vector<QString> *> * DataBase::select(QString & strQuery) {
    std::map<QString, std::vector<QString> *> * mapResult;
    mapResult = new std::map<QString, std::vector<QString> *>();
    this->open();
    if (!_connect) {
        return mapResult;
    }
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


//! \brief check if the database contains element(s)
//! \return false if the database contains elements, otherwise true
bool        DataBase::checkDataBase(void) {
    QString table = AccountDB::accountTable();
    QString str("SELECT * FROM ");
    str.append(table);

    std::map<QString, std::vector<QString> *> * mapResult = this->select(str);
    if (((*mapResult)[QString("login")])->size() > 0) {
        return false;
    }
    return true;
}


//! \return false if the database contains elements, otherwise true
bool        DataBase::getEmpty(void) const {
    return _empty;
}



//////////////////////////
// QUERY IF NO CONNECTION
//////////////////////////

//! \brief add the query in a vector for execute the query
//! \brief once the database is available
//! \param[in] query QString
inline void DataBase::addQuery(QString & query) {
    _vQuery->push_back(query);
}


//! \brief delete all query  contained in the vector for query if the database is offline
inline void DataBase::deleteQuery(void) {
    _vQuery->clear();
}


//! \brief execute the querys contained into the vector
//! \brief when the database will be available
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

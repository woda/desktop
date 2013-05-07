//! \file FolderDB.hh
//! \brief header FolderDB : information about user folder and his content for create DB
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#include    <QString>
#include    <map>
#include    <vector>
#include    "AccountDB.hh"
#include    "DataBase.hh"


//! \brief Constructor
AccountDB::AccountDB() {
}


//! \brief Destructor
AccountDB::~AccountDB() {
}


//! \brief create the querry for create the account table
//! \return a vector fill with querry for create account tables
std::vector<QString>    AccountDB::createTable(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("CREATE TABLE account (login text, "
                           "password text, directory text)"));
    return vstr;
}


//! \return a vector fill with the primary keys for the account table
std::vector<QString>    AccountDB::accountPrimaryKey(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("login"));
    return vstr;
}


//! \return a string with the name of the account table
QString                 AccountDB::accountTable(void) {
    return QString("account");
}


//! \brief add quote between the string pass as parameter
//! \param[in] str string
//! \return a string with quotes
QString                 AccountDB::addQuotes(QString str) {
    return QString("\"").append(str).append("\"");
}

#include <iostream>
//! \brief insert the login and the password in the account table in database
//! \param[in] login QString
//! \param[in] password QString
void                    AccountDB::insertAccountLoginPassword(QString & login,
                                                              QString & password) {
    QString table = this->accountTable();
    std::map<QString, QString> map;
    map[QString(ACCOUNT_LOGIN)] = this->addQuotes(login);
    map[QString(ACCOUNT_PASSWORD)] = this->addQuotes(password);

    std::cout << login.toStdString() << " " << password.toStdString() << std::endl;

    DataBase::getSingletonPtr()->insert(table, map);
}


//! \brief insert the path of the user directory in the account table in database
//! \param[in] folderPath QString
//! \param[in] login QString
void                    AccountDB::insertAccountDirectory(QString & folderPath,
                                                          const QString & login) {
    QString table = this->accountTable();
    std::map<QString, QString> map;
    map[QString(ACCOUNT_DIRECTORY)] = this->addQuotes(folderPath);
    map[QString(ACCOUNT_LOGIN)] = this->addQuotes(login);

    DataBase::getSingletonPtr()->insert(table, map);
}


//! \brief select all info in account table
//! \return a map with QString of the column name and a vector of string with all informations line by line
std::map<QString, std::vector<QString> *> * AccountDB::selectAllAccount(void) {
    // TO DO
    QString str("SELECT * FROM ");
    str.append(AccountDB::accountTable());
    return DataBase::getSingletonPtr()->select(str);
}


//! \brief select login in account table
//! \return a QString of the login
QString & AccountDB::selectAccountLogin(void) {
    QString str("SELECT login FROM ");
    str.append(AccountDB::accountTable());
    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    return (*((*map)[QString("login")])).front();
}


//! \brief select password in account table
//! \return a QString of the password
QString & AccountDB::selectAccountPassword(void) {
    QString str("SELECT password FROM ");
    str.append(AccountDB::accountTable());
    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    return (*((*map)[QString("password")])).front();
}


//! \brief select directory path in account table
//! \return a QString of the folder path
QString & AccountDB::selectAccountDirectory(void) {
    QString str("SELECT directory FROM ");
    str.append(AccountDB::accountTable());
    std::map<QString, std::vector<QString> *> * map;
    map = DataBase::getSingletonPtr()->select(str);
    return (*((*map)[QString("directory")])).front();
}


//! \brief delete all informations of the user in database
//! \param[in] login QString
void                    AccountDB::deleteLineAccount(QString & login) {
    // appel delete avec les PK insere dans la clause where
    QString table = this->accountTable();
    std::vector<QString> where;
    QString key(ACCOUNT_LOGIN);
    key.append(" = ").append(login);
    where.push_back(key);
    DataBase::getSingletonPtr()->deleteLine(table, where);
}


//! \brief delete the path of the user directory in database
//! \param[in] folderPath QString
void                    AccountDB::deleteLineDirectory(QString & folderPath) {
    // appel delete avec les PK insere dans la clause where
    QString table = this->accountTable();
    std::map<QString, QString> map;
    map[QString(ACCOUNT_DIRECTORY)] = this->addQuotes(QString(""));
    std::vector<QString> where;
    QString key(ACCOUNT_DIRECTORY);
    key.append(" = ").append(folderPath);
    where.push_back(key);
    DataBase::getSingletonPtr()->update(table, map, where);
}

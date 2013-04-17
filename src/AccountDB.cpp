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

AccountDB::AccountDB() {
}

AccountDB::~AccountDB() {
}

std::vector<QString>    AccountDB::createTable(void) {
    std::vector<QString> vstr(0);
    vstr.push_back(QString("CREATE TABLE account (login text, "
                           "password text, directory text)"));
    return vstr;
}

std::vector<QString>    AccountDB::accountPrimaryKey(void) {
    std::vector<QString> vstr(0);
    return vstr;
}

QString                 AccountDB::accountTable(void) {
    return QString("account");
}

QString                 AccountDB::addQuotes(QString str) {
    return QString("\"").append(str).append("\"");
}


void                    AccountDB::insertAccountLoginPassword(QString & login,
                                                              QString & password) {
    QString table = this->accountTable();
    std::map<QString, QString> map;
    map[QString(ACCOUNT_LOGIN)] = this->addQuotes(login);
    map[QString(ACCOUNT_PASSWORD)] = this->addQuotes(password);

    DataBase::getSingletonPtr()->insert(table, map);
}

void                    AccountDB::insertAccountDirectory(QString & folderPath) {
    QString table = this->accountTable();
    std::map<QString, QString> map;
    map[QString(ACCOUNT_DIRECTORY)] = this->addQuotes(folderPath);

    DataBase::getSingletonPtr()->insert(table, map);
}



std::map<QString, std::vector<QString> *> * AccountDB::selectAllAccount(void) {
    QString str("SELECT * FROM ");
    str.append(AccountDB::accountTable());
    return DataBase::getSingletonPtr()->select(str);
}



void                    AccountDB::deleteLineAccount(QString & login) {
    // appel delete avec les PK insere dans la clause where
    QString table = this->accountTable();
    std::vector<QString> where;
    QString key(ACCOUNT_LOGIN);
    key.append(" = ").append(login);
    where.push_back(key);
    DataBase::getSingletonPtr()->deleteLine(table, where);
}

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

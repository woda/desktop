//! \file Account.cpp
//! \brief implementation of the header Account for information about account
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#include	"Account.hh"
#include    "ConfFile.hh"
#include    "RequestHttpAccount.hh"
#include    "RequestHttpFile.hh"
#include    "parser.h"
#include    "AccountDB.hh"
#include    "UserFolderManagement.hh"

#include <iostream>

//! \brief Constructor
//! \brief retrieves the login and password in the Class ConfFile
//! \brief if the login and pass exist, connect to the server
Account::Account()
    : _connected(false), _firstName(QString("")), _lastName(QString("")),
      _email(QString("")), _corner(0), _errorHttp(false),
      _errorServer(QString("")) {
#if CONFFILE
    _login = ConfFile::getSingletonPtr()->getValue(LOGIN_CONFFILE).toString();
    _password = ConfFile::getSingletonPtr()->getValue(PASSWORD_CONFFILE).toString();
    _corner = ConfFile::getSingletonPtr()->getValue(CONFFILE_CORNER).toInt();
#else
    AccountDB db;
    _login = db.selectAccountLogin();
    _password = db.selectAccountPassword();
    _corner = db.selectAccountCorner();
#endif
    _corner = ConfFile::getSingletonPtr()->getValue(CONFFILE_CORNER).toInt();

    if (!_login.isEmpty() && !_password.isEmpty()) {
        RequestHttpAccount::getSingletonPtr()->loginToServer(_login, _password);
    }
}


//! \brief Constructor for UnitTest
Account::Account(bool)
    : _connected(false), _login(QString("")), _password(QString("")),
      _firstName(QString("")), _lastName(QString("")),
      _email(QString("")), _errorHttp(false), _errorServer(QString("")) {
}


//! \brief Destructor
Account::~Account() {
}


//! \param[in] bytes string json serialize
//! \brief Deserialize the json send by the server
void            Account::deserializeJsonAccount(QByteArray & bytes) {
    QJson::Parser parser;
    bool ok;
    QVariantMap result = parser.parse(bytes, &ok).toMap();
    if (ok && !result["user"].toMap().isEmpty()) {
        QVariantMap user = result["user"].toMap();
        _login = user["login"].toString();
        _email = user["email"].toString();
        this->connect();
    } else if (!result["success"].toString().isEmpty()) {
        this->disconnect();
    } else if (!result["error"].toString().isEmpty()) {
        QString error(result["message"].toString());
        this->serverError(error);
    }
    QString str(bytes);
    std::cout << str.toStdString() << std::endl;
}


//! \param[in] error string of the error send by the server
//! \brief set the string of the error send by the server
void            Account::serverError(QString & error) {
    _errorServer = error;
}


//! \return true if an error is detected, otherwise false
//! \brief see if an error occurred
bool            Account::isServerError(void) const {
    if (_errorServer.isEmpty())
        return false;
    return true;
}


//! \return string of the error
//! \brief return the server error
const QString & Account::textServerError(void) const {
    return _errorServer;
}


//! \brief set an error of http
void            Account::httpError(void) {
    _errorHttp = true;
}


//! \return true if an error http is detected, otherwise false
//! \brief see if an error http occurred
bool            Account::isHttpError(void) const {
    return _errorHttp;
}


//! \return true if connected to the server, otherwise false
//! \brief see if connected to the server
bool            Account::isConnected(void) const {
    return _connected;
}


//! \brief set connected to the server
void            Account::connect(void) {
    _errorHttp = false;
    _errorServer = QString("");
    _connected = true;
    // reset corner in db
    this->setCorner(_corner);
    // reset user folder in db
    UserFolderManagement::getSingletonPtr()->insertDirectoryIntoDatabase();
    RequestHttpFile::getSingletonPtr()->recoverFilesList();
}


//! \brief set disconnect to the server
void            Account::disconnect(void) {
    _connected = false;

#if CONFFILE
    QString empty("");
    this->setLogin(empty);
    this->setPassword(empty);
#else
    AccountDB db;
    db.deleteLineAccount();
#endif
}


//! \param[in] login login
//! \brief set the login into the class and ConfFile class
void            Account::setLogin(QString & login) {
    _login = login;

#if CONFFILE
    ConfFile::getSingletonPtr()->setValue(LOGIN_CONFFILE, QVariant(login));
#else
    AccountDB db;
    db.insertAccountLoginPassword(_login, _password);
#endif
}


//! \param[in] password password
//! \brief set the password into the class and ConfFile class
void            Account::setPassword(QString & password) {
    _password = password;

#if CONFFILE
    ConfFile::getSingletonPtr()->setValue(PASSWORD_CONFFILE, QVariant(password));
#else
    AccountDB db;
    db.insertAccountLoginPassword(_login, _password);
#endif
}


//! \param[in] firstName firstName
//! \brief set the firstName into the class
void            Account::setFirstName(QString & firstName) {
    _firstName = firstName;
}


//! \param[in] lastName lastName
//! \brief set the lastName into the class
void            Account::setLastName(QString & lastName) {
    _lastName = lastName;
}


//! \param[in] email email
//! \brief set the email into the class
void            Account::setEmail(QString & email) {
    _email = email;
}


//! \param[in] corner int
//! \brief set the id of the corner into the class
void            Account::setCorner(int id) {
    _corner = id;

//#if CONFFILE
    ConfFile::getSingletonPtr()->setValue(CONFFILE_CORNER, QVariant(id));
//#else
//    AccountDB db;
//    db.insertAccountCorner(id, _login);
//#endif
}


//! \return string of the login
//! \brief return the string of the login stored in the class
const QString & Account::login(void) const {
    return _login;
}


//! \return string of the password
//! \brief return the string of the password stored in the class
const QString & Account::password(void) const {
    return _password;
}


//! \return string of the first name
//! \brief return the string of the first name stored in the class
const QString & Account::firstName(void) const {
    return _firstName;
}


//! \return string of the last name
//! \brief return the string of the last name stored in the class
const QString & Account::lastName(void) const {
    return _lastName;
}


//! \return string of the email
//! \brief return the string of the email stored in the class
const QString & Account::email(void) const {
    return _email;
}

//! \return id of the corner
//! \brief return the id of the corner stored in the class
int             Account::corner(void) const {
    return _corner;
}

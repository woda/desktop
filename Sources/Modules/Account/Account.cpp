//! \file Account.cpp
//! \brief implementation of the header Account for information about account
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#include	"Account.hh"
#include    "ConfFile.hh"
#include    "RequestHttpAccount.hh"
#include    "dll/qjson/src/parser.h"

#include <iostream>

//! \brief Constructor
//! \brief retrieves the login and password in the Class ConfFile
//! \brief if the login and pass exist, connect to the server
Account::Account()
    : _connected(false), _firstName(QString("")), _lastName(QString("")),
      _email(QString("")), _errorHttp(false), _errorServer(QString("")) {
    _login = ConfFile::getSingletonPtr()->getValue(LOGIN_CONFFILE).toString();
    _password = ConfFile::getSingletonPtr()->getValue(PASSWORD_CONFFILE).toString();
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
    if (ok && !result["login"].toString().isEmpty()) {
        _login = result["login"].toString();
        _firstName = result["first_name"].toString();
        _lastName = result["last_name"].toString();
        _email = result["email"].toString();
        this->connect();
    } else if (!result["success"].toString().isEmpty()) {
        this->disconnect();
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
}


//! \brief set disconnect to the server
void            Account::disconnect(void) {
    _connected = false;
}


//! \param[in] login login
//! \brief set the login into the class and ConfFile class
void            Account::setLogin(QString & login) {
    _login = login;
    ConfFile::getSingletonPtr()->setValue(LOGIN_CONFFILE, QVariant(login));
}


//! \param[in] password password
//! \brief set the password into the class and ConfFile class
void            Account::setPassword(QString & password) {
    _password = password;
    ConfFile::getSingletonPtr()->setValue(PASSWORD_CONFFILE, QVariant(password));
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

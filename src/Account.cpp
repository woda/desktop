//! \file Account.cpp
//! \brief implementation of the interface for information about account
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#include	"Account.hh"
#include    "ConfFile.hh"
#include    "RequestHttp.hh"
#include    "dll/qjson/src/parser.h"

#include <iostream>

//! \fn Account::Account()
//! \brief Constructor
Account::Account()
    : _connected(false), _firstName(QString("")), _lastName(QString("")),
      _email(QString("")), _errorHttp(false), _errorServer(QString("")) {
    _login = ConfFile::getSingletonPtr()->getValue(LOGIN_CONFFILE).toString();
    _password = ConfFile::getSingletonPtr()->getValue(PASSWORD_CONFFILE).toString();
    if (!_login.isEmpty() && !_password.isEmpty()) {
        RequestHttp::getSingletonPtr()->loginToServer(_login, _password);
    }
}


//! \fn Account::Account()
//! \brief Constructor for UnitTest
Account::Account(bool)
    : _connected(false), _login(QString("")), _password(QString("")),
      _firstName(QString("")), _lastName(QString("")),
      _email(QString("")), _errorHttp(false), _errorServer(QString("")) {
}


//! \fn Account::~Account()
//! \brief Destructor
Account::~Account() {
}


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

void            Account::serverError(QString & error) {
    _errorServer = error;
}

bool            Account::isServerError(void) const {
    if (_errorServer.isEmpty())
        return false;
    return true;
}

const QString & Account::textServerError(void) const {
    return _errorServer;
}

void            Account::httpError(void) {
    _errorHttp = true;
}

bool            Account::isHttpError(void) const {
    return _errorHttp;
}

bool            Account::isConnected(void) const {
    return _connected;
}

void            Account::connect(void) {
    _errorHttp = false;
    _errorServer = QString("");
    _connected = true;
}

void            Account::disconnect(void) {
    _connected = false;
}

void            Account::setLogin(QString & login) {
    _login = login;
    ConfFile::getSingletonPtr()->setValue(LOGIN_CONFFILE, QVariant(login));
}

void            Account::setPassword(QString & password) {
    _password = password;
    ConfFile::getSingletonPtr()->setValue(PASSWORD_CONFFILE, QVariant(password));
}

void            Account::setFirstName(QString & firstName) {
    _firstName = firstName;
}

void            Account::setLastName(QString & lastName) {
    _lastName = lastName;
}

void            Account::setEmail(QString & email) {
    _email = email;
}

const QString & Account::login(void) const {
    return _login;
}

const QString & Account::password(void) const {
    return _password;
}

const QString & Account::firstName(void) const {
    return _firstName;
}

const QString & Account::lastName(void) const {
    return _lastName;
}

const QString & Account::email(void) const {
    return _email;
}

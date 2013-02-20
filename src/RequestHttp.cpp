//! \file RequestHttp.cpp
//! \brief	implementation of the interface for send request to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#include	"RequestHttp.hh"
#include    "Account.hh"
#include    <QUrl>
#include    <QNetworkRequest>
#include    <QNetworkReply>
#include    <QSslConfiguration>
#include    <QTextCodec>
#include    <QNetworkCookieJar>
#include    <cstddef>

#include <iostream>

//! \fn RequestHttp::RequestHttp()
//! \brief		Constructor, initialize QHttp
RequestHttp::RequestHttp(QObject * parent)
    : QObject(parent), _http(new QNetworkAccessManager(this)) {
    connect(_http, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedSlot(QNetworkReply*)));

    _http->setCookieJar(new QNetworkCookieJar(_http));
}

//! \fn RequestHttp::~RequestHttp()
//! \brief		Destructor
RequestHttp::~RequestHttp() {
    delete _http;
}

//! \fn void ConfFile::setValue(const QString & key, const QVariant & value)
//! \param[in] key key in the ini file for save the information
//! \param[in] value value to save in the ini file
//! \brief add or update the value with the key pass in parameter in the ini file
void        RequestHttp::send() {
    std::cout << "----------------------------------------------" << std::endl;
    QString str(URL);
    str.append("/").append(USER);
    QUrl param(str);

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    _reply = _http->get(request);
    _reply->ignoreSslErrors();
}

//! \fn void ConfFile::setValue(const QString & key, const QVariant & value)
//! \param[in] key key in the ini file for save the information
//! \param[in] value value to save in the ini file
//! \brief add or update the value with the key pass in parameter in the ini file
void        RequestHttp::loginToServer(QString & login, QString & password) {
    QString str(URL);
    str.append("/").append(USER).append("/");
    str.append(login).append("/").append(LOGIN);
    QUrl param(str);

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QByteArray body = "password=";
    body.append(password);
    _reply = _http->post(request, body);
    _reply->ignoreSslErrors();
}


//! \fn void ConfFile::setValue(const QString & key, const QVariant & value)
//! \param[in] key key in the ini file for save the information
//! \param[in] value value to save in the ini file
//! \brief add or update the value with the key pass in parameter in the ini file
void        RequestHttp::logoutToServer() {
    QString str(URL);
    str.append("/").append(USER).append("/").append(LOGOUT);
    QUrl param(str);

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QByteArray body = "";
    _reply = _http->post(request, body);
    _reply->ignoreSslErrors();
}


//! \fn void ConfFile::setValue(const QString & key, const QVariant & value)
//! \param[in] key key in the ini file for save the information
//! \param[in] value value to save in the ini file
//! \brief add or update the value with the key pass in parameter in the ini file
void        RequestHttp::sendUpdate(QString & email, QString & password) {
    QString str(URL);
    str.append("/").append(USER);
    QUrl param(str);

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QByteArray body = "password=";
    body.append(password);
    body.append("&");
    body.append("email=").append(email);
    _reply = _http->post(request, body);
    _reply->ignoreSslErrors();
}

//! \fn void ConfFile::setValue(const QString & key, const QVariant & value)
//! \param[in] key key in the ini file for save the information
//! \param[in] value value to save in the ini file
//! \brief add or update the value with the key pass in parameter in the ini file
void        RequestHttp::sendCreate(QString & login) {
    QString str(URL);
    str.append("/").append(USER).append("/");
    str.append(login);
    QUrl param(str);

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QByteArray body = "first_name=Super&last_name=Poivron&password=123456&email=superpoivron@gmail.com";
    _reply = _http->put(request, body);
    _reply->ignoreSslErrors();
}

void        RequestHttp::finishedSlot(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        Account::getSingletonPtr()->deserializeJsonAccount(bytes);
    } else {
        Account::getSingletonPtr()->httpError();
    }
    reply->deleteLater();
}

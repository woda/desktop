//! \file RequestHttp.cpp
//! \brief	implementation of the header RequestHttp for send request account to the server
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


//! \brief Constructor
//! initialize QNetworkAccessManager, connect the reply of the server to a slot
//! initialize cookie
RequestHttp::RequestHttp(QObject * parent)
    : QObject(parent), _http(new QNetworkAccessManager(this)) {
    connect(_http, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedSlot(QNetworkReply*)));

    _http->setCookieJar(new QNetworkCookieJar(_http));
}


//! \brief Destructor
//! delete QNetworkAccessManager
RequestHttp::~RequestHttp() {
    delete _http;
}


void        RequestHttp::send() {
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

//! \param[in] login to connecct to server
//! \param[in] password to connect to server
//! \brief send a request post to login to the server
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


//! \brief send a request post to logout to the server
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


//! \param[in] email new email for the account or the same
//! \param[in] password new password for the account or the same
//! \brief send a request post for update email information and/or password to the server
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


//! \param[in] reply QNetworkReply send by web server
//! \brief verify if the server send an error, else deserialize the Json into Account class
void        RequestHttp::finishedSlot(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        Account::getSingletonPtr()->deserializeJsonAccount(bytes);
    } else {
        Account::getSingletonPtr()->httpError();
    }
    reply->deleteLater();
}

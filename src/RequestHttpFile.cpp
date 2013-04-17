//! \file RequestHttpFile.cpp
//! \brief	implementation of the header RequestHttpFile for send request account to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#include	"RequestHttpFile.hh"
#include    <QUrl>
#include    <QNetworkRequest>
#include    <QNetworkReply>
#include    <QSslConfiguration>
#include    <QTextCodec>
#include    <QNetworkCookieJar>
#include    <cstddef>

#include <iostream>


//! \brief Constructor
//! \brief initialize QNetworkAccessManager, connect the reply of the server to a slot
//! \brief initialize cookie
RequestHttpFile::RequestHttpFile(QObject * parent)
    : QObject(parent), _http(new QNetworkAccessManager(this)) {
    connect(_http, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));

    _http->setCookieJar(new QNetworkCookieJar(_http));
}


//! \brief Destructor
//! \brief delete QNetworkAccessManager
RequestHttpFile::~RequestHttpFile() {
    delete _http;
}


//! \param[in] login to connecct to server
//! \param[in] password to connect to server
//! \brief send a request post to login to the server
void        RequestHttpFile::loginToServer(QString & login, QString & password) {
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

    std::cout << request.url().toString().toStdString() << std::endl;
    QString temp(body);
    std::cout << temp.toStdString() << std::endl;

    _reply = _http->post(request, body);
    _reply->ignoreSslErrors();
}


//! \param[in] reply QNetworkReply send by web server
//! \brief verify if the server send an error, else deserialize the Json into Account class
void        RequestHttpFile::finishedSlot(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        //Account::getSingletonPtr()->deserializeJsonAccount(bytes);
    } else {
        //Account::getSingletonPtr()->httpError();
        QByteArray bytes2 = reply->readAll();
        QString str(bytes2);
        std::cout << str.toStdString() << std::endl;
    }
    reply->deleteLater();
}

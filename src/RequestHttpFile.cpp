//! \file RequestHttpFile.cpp
//! \brief	implementation of the header RequestHttpFile for send request account to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#include	"RequestHttpFile.hh"
#include    "RequestHttp.hpp"
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
    : QObject(parent), _http(new QNetworkAccessManager(this)),
      _recoverTree(false) {
    connect(_http, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));

    _timer = new QTimer(this);
    _timer->setInterval(TIMER_REFRESH);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->start(TIMER_REFRESH);
}


//! \brief Destructor
//! \brief delete QNetworkAccessManager
RequestHttpFile::~RequestHttpFile() {
    delete _http;
}


//! \brief update RequestHttpFile
void        RequestHttpFile::update() {
    if (!_recoverTree) {
        if (RequestHttp::getSingletonPtr()->hasCookie()) {
            _http->setCookieJar(RequestHttp::getSingletonPtr()->getCookie());
            this->recoverFilesList();
            _recoverTree = true;
        }
    } else if (!RequestHttp::getSingletonPtr()->hasCookie()) {
        _recoverTree = false;
    }
}


//! \brief send a request post to login to the server
void        RequestHttpFile::recoverFilesList(void) {
    QString str(URL);
    str.append("/").append(USER).append("/").append(FILES);
    QUrl param(str);

    std::cout << "url : " << str.toStdString() << std::endl;

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QByteArray body = "";
    _reply = _http->get(request);
    _reply->ignoreSslErrors();
}


//! \param[in] reply QNetworkReply send by web server
//! \brief verify if the server send an error, else deserialize the Json into Account class
void        RequestHttpFile::finishedSlot(QNetworkReply* reply) {

    std::cout << "REPLY FILE " << std::endl;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString str(bytes);
        std::cout << "no error : " << str.toStdString() << std::endl;
        //Account::getSingletonPtr()->deserializeJsonAccount(bytes);
    } else {
        //Account::getSingletonPtr()->httpError();
        QByteArray bytes2 = reply->readAll();
        QString str2(bytes2);
        std::cout << "error : "  << str2.toStdString() << std::endl;
    }
    reply->deleteLater();
}

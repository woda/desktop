//! \file RequestHttpDownloadFile.cpp
//! \brief	implementation of the header RequestHttpDownloadFile for send request fow download file to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-10

#include	"RequestHttpDownloadFile.hh"
#include    "RequestHttp.hpp"
#include    "UserFolderManagement.hh"
#include    "Account.hh"
#include    "WodaSemaphore.hh"
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
RequestHttpDownloadFile::RequestHttpDownloadFile(QObject * parent)
    : QObject(parent), _http(new QNetworkAccessManager(this)),
      _recoverTree(false) {
    connect(_http, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));

    if (RequestHttp::getSingletonPtr()->hasCookie() &&
        Account::getSingletonPtr()->isConnected()) {
        _http->setCookieJar(RequestHttp::getSingletonPtr()->getCookie());
    }

    _timer = new QTimer(this);
    _timer->setInterval(TIMER_REFRESH_DOWNLOAD);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->start(TIMER_REFRESH_DOWNLOAD);
}


//! \brief Destructor
//! \brief delete QNetworkAccessManager
RequestHttpDownloadFile::~RequestHttpDownloadFile() {
    delete _http;
}


//! \brief update RequestHttpFile
void        RequestHttpDownloadFile::update() {

}


//! \brief send a request get to recover the file from the server
void        RequestHttpDownloadFile::recoverFile(int id) {
    QString str(URL_LIST);
    str.append("/").append(SYNC).append("/").append(QString().setNum(id)).append("/0");

    QNetworkRequest request;
    request.setUrl(str);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    _reply = _http->get(request);
    _reply->ignoreSslErrors();
}


//! \param[in] reply QNetworkReply send by web server
//! \brief verify if the server send an error, else create the file
void        RequestHttpDownloadFile::finishedSlot(QNetworkReply* reply) {

    std::cout << "REPLY FILE " << std::endl;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
//        char * data;
//        data = new char[PART_SIZE];
//        reply->read(data, PART_SIZE);
        QString str(bytes);
        std::cout << "no error : " << str.toStdString() << std::endl;
        UserFolderManagement::getSingletonPtr()->deserializeJsonDownloadFile(bytes, reply->url().toString());
    } else {
        QByteArray bytes2 = reply->readAll();
        QString str2(bytes2);
        std::cout << "error : "  << str2.toStdString() << std::endl;
    }
//    QString sem(FILE_SEMAPHORE);
//    WodaSemaphore::getInstance(sem)->release();
    reply->deleteLater();
}

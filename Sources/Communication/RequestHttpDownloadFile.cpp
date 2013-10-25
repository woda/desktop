//! \file RequestHttpDownloadFile.cpp
//! \brief	implementation of the header RequestHttpDownloadFile for send request fow download file to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-10

#include	"RequestHttpDownloadFile.hh"
#include    "RequestHttp.hpp"
#include    "UserFolderManagement.hh"
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
//! \brief initialize QNetworkAccessManager, connect the reply of the server to a slot
//! \brief initialize cookie
RequestHttpDownloadFile::RequestHttpDownloadFile(QObject * parent)
    : QObject(parent), _http(new QNetworkAccessManager(this)),
      _recoverTree(false) {
    connect(_http, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));

    _listDownload = new QVector<QVector<QString> >;
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
    delete _listDownload;
}


//! \brief update RequestHttpFile
void        RequestHttpDownloadFile::update() {

}


//! \brief send a request get to recover the file from the server
void        RequestHttpDownloadFile::recoverFile(QString & name, QString & idFolder, QString & size) {
    QString str(URL_LIST);
    str.append("/").append(PART_SYNC).append("/0/");
    QString folder = "";
    if (idFolder != UserFolderManagement::getSingletonPtr()->getCurrentDirectory()) {
        folder = idFolder.right(idFolder.length() - UserFolderManagement::getSingletonPtr()->getCurrentDirectory().length() - 1);
        folder.append("/");
    }
    folder.append(name);
    str.append(folder);
    QUrl param(str);

    QVector<QString> vector;
    vector.push_back(folder);
    vector.push_back("0");
    vector.push_back(size);
    _listDownload->push_back(vector);

    QString test(param.toEncoded());
    std::cout << "folder and file to download : " << folder.toStdString() << std::endl;
    std::cout << "url file to download : " << test.toStdString() << std::endl;

    QNetworkRequest request;
    request.setUrl(param);
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
        //QByteArray bytes = reply->readAll();
        char * data;
        data = new char[PART_SIZE];
        reply->read(data, PART_SIZE);
        //QString str(bytes);
        //std::cout << "no error : " << str.toStdString() << std::endl;
        QVector<QString> vector = _listDownload->first();
        QString folder = UserFolderManagement::getSingletonPtr()->getCurrentDirectory();
        folder.append("/").append(vector.first());
        int size = vector[2].toInt();
        UserFolderManagement::getSingletonPtr()->createDownloadFile(folder, data, size);
        _listDownload->pop_front();
    } else {
        QByteArray bytes2 = reply->readAll();
        QString str2(bytes2);
        std::cout << "error : "  << str2.toStdString() << std::endl;
        _listDownload->pop_front();
    }
    reply->deleteLater();
}

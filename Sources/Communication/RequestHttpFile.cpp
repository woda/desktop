//! \file RequestHttpFile.cpp
//! \brief	implementation of the header RequestHttpFile for send request account to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#include	"RequestHttpFile.hh"
#include    "RequestHttp.hpp"
#include    "UserFolderManagement.hh"
#include    "Hash.hh"
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
RequestHttpFile::RequestHttpFile(QObject * parent)
    : QObject(parent), _http(new QNetworkAccessManager(this)),
      _recoverTree(false) {
    connect(_http, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));

    _timer = new QTimer(this);
    _timer->setInterval(TIMER_REFRESH_FILE);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->start(TIMER_REFRESH_FILE);
}


//! \brief Destructor
//! \brief delete QNetworkAccessManager
RequestHttpFile::~RequestHttpFile() {
    delete _http;
}


//! \brief update RequestHttpFile
void        RequestHttpFile::update() {
    if (!_recoverTree) {
        if (RequestHttp::getSingletonPtr()->hasCookie() &&
            Account::getSingletonPtr()->isConnected()) {
            _http->setCookieJar(RequestHttp::getSingletonPtr()->getCookie());
            this->recoverFilesList();
            _recoverTree = true;
        }
    } else if (!RequestHttp::getSingletonPtr()->hasCookie()) {
        _recoverTree = false;
    }
}


//! \brief send a request post for adding a file to the server
void        RequestHttpFile::AddingAFile(const QString & filename) {
    QString str(URL);
    str.append("/").append(SYNC).append(filename.mid(UserFolderManagement::getSingletonPtr()->getCurrentDirectory().length()));
    QUrl param(str);

    _filePath = filename;
    std::cout << "url adding file : " << str.toStdString() << std::endl;

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QByteArray body = "content_hash=";
    body.append(Hash::getHash(filename));
    body.append("&");
    body.append("size=").append(Hash::getLength(filename));
    if (Hash::getLength(filename) != QString("0")) {
        _reply = _http->put(request, body);
        _reply->ignoreSslErrors();
    }
}


//! \brief send a request post to uploading a file into the server
void        RequestHttpFile::UploadingAFile(const QString & filename, int size) {
    QString str(URL);
    str.append("/").append(PART_SYNC).append("/0").append(filename.mid(UserFolderManagement::getSingletonPtr()->getCurrentDirectory().length()));
    QUrl param(str);

    std::cout << "url uploading file : " << str.toStdString() << std::endl;

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QByteArray body = "";
    body.append(Hash::getContent(filename, size));

    std::cout << "size = " << size << std::endl;
    std::cout << QString(body).toStdString() << std::endl;

    _reply = _http->put(request, body);
    _reply->ignoreSslErrors();
}


//! \brief send a request post to confirming that a file is upload to the server
void        RequestHttpFile::ConfirmingUpload(QString & filename) {
    QString str(URL);
    str.append("/").append(SUCCES_SYNC).append(filename.mid(UserFolderManagement::getSingletonPtr()->getCurrentDirectory().length()));
    QUrl param(str);

    std::cout << "url confirming : " << str.toStdString() << std::endl;

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

////! \brief send a request post to confirming that a file is upload to the server
//void        RequestHttpFile::changeAFile(QString & filename) {
//    QString str(URL);
//    str.append("/").append(SUCCES_SYNC).append(filename.mid(UserFolderManagement::getSingletonPtr()->getCurrentDirectory().length()));
//    QUrl param(str);

//    std::cout << "url confirming : " << str.toStdString() << std::endl;

//    QNetworkRequest request;
//    request.setUrl(param);
//    request.setHeader(QNetworkRequest::ContentTypeHeader,
//                      "application/x-www-form-urlencoded");
//    request.setRawHeader("Connection", "keep-alive");
//    request.setRawHeader("User-Agent", WEBAGENTNAME);
//    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

//    QByteArray body = "";
//    _reply = _http->post(request, body);
//    _reply->ignoreSslErrors();
//}


////! \brief send a request get to recover the file from the server
//void        RequestHttpFile::recoverFile(QString & name, QString & idFolder) {
//    QString str(URL_LIST);
//    str.append("/").append(PART_SYNC).append("/0/");
//    if (idFolder != UserFolderManagement::getSingletonPtr()->getCurrentDirectory()) {
//        QStringRef subString(&idFolder, UserFolderManagement::getSingletonPtr()->getCurrentDirectory().length() + 1,
//                             idFolder.length() - UserFolderManagement::getSingletonPtr()->getCurrentDirectory().length());
//        str.append(subString.toString()).append("/");
//    }
//    str.append(name);
//    QUrl param(str);

//    std::cout << "url file to download : " << str.toStdString() << std::endl;

//    QNetworkRequest request;
//    request.setUrl(param);
//    request.setHeader(QNetworkRequest::ContentTypeHeader,
//                      "application/x-www-form-urlencoded");
//    request.setRawHeader("Connection", "keep-alive");
//    request.setRawHeader("User-Agent", WEBAGENTNAME);
//    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

//    _reply = _http->get(request);
//    _reply->ignoreSslErrors();
//}


//! \brief send a request get to recover the file list
void        RequestHttpFile::recoverFilesList(void) {
    QString str(URL_LIST);
    str.append("/").append(USER).append("/").append(FILES).append("/");
    QUrl param(str);

    std::cout << "url file list : " << str.toStdString() << std::endl;

    QNetworkRequest request;
    request.setUrl(param);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("User-Agent", WEBAGENTNAME);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    _reply = _http->get(request);
    _reply->ignoreSslErrors();


//    UserFolderManagement::getSingletonPtr()->copyEntireTempFolder();
}


//! \param[in] reply QNetworkReply send by web server
//! \brief verify if the server send an error, else deserialize the Json into Account class
void        RequestHttpFile::finishedSlot(QNetworkReply* reply) {

    std::cout << "REPLY FILE " << std::endl;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString str(bytes);
        std::cout << "no error : " << str.toStdString() << std::endl;

//        // FOR TEST ONLY
//        QByteArray test("[\n{\n\"name\": \"Folder1\",\n\"full_path\": \".\",\n\"modification_time\": \"01/01/2013 23:42:42\",\n\"files\": [ \n{\n\"name\": \"File1.txt\",\n\"modification_time\": \"01/01/2013 23:42:42\" \n},\n{\n\"name\": \"File2.txt\",\n\"modification_time\": \"01/01/2013 23:42:42\" \n}\n]\n}, \n{\n\"name\": \"Folder2\",\n\"full_path\" : \"./Folder1\",\n\"modification_time\" : \"01/01/2013 23:42:42\",\n\"files\": [ \n{\n\"name\": \"File3.txt\",\n\"modification_time\": \"01/01/2013 23:42:42\" \n}\n]\n}\n]\n");
//        //std::cout << test.toStdString() << std::endl;
        if (int size = UserFolderManagement::getSingletonPtr()->deserializeJsonAccount(bytes)) {
//            UserFolderManagement::getSingletonPtr()->copyAFileToTempFolder(_filePath);
            std::cout << "||||||| size of content = " << size << std::endl;
            this->UploadingAFile(_filePath, size);
//            this->ConfirmingUpload(_filePath);
        }
//        UserFolderManagement::getSingletonPtr()->copyAFileToTempFolder(_filePath);

        //Account::getSingletonPtr()->deserializeJsonAccount(bytes);
    } else {
        //Account::getSingletonPtr()->httpError();
        QByteArray bytes2 = reply->readAll();
        QString str2(bytes2);
        std::cout << "error : "  << str2.toStdString() << std::endl;
    }
    std::cout << "num error = " << reply->error() << std::endl;
    reply->deleteLater();
}

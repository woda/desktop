//! \file RequestHttpDownloadFile.hh
//! \brief	header RequestHttpDownloadFile : send request download to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-10

#ifndef             INCLUDE_REQUESTHTTPDOWNLOADFILE_HH__
# define            INCLUDE_REQUESTHTTPDOWNLOADFILE_HH__

# include           <QObject>
# include           <QString>
# include           <QNetworkAccessManager>
# include           <QTimer>
# include           <QVector>
# include           "Singleton.hpp"

//! \def WEBAGENTNAME
# define            WEBAGENTNAME    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.57 Safari/537.17"
//! \def URL
# define            URL             "https://woda-server.com:3000" //"https://ec2-54-242-98-168.compute-1.amazonaws.com:3000"
//! \def URL
# define            URL_LIST        "https://woda-server.com:3000"
//! \def USER
# define            USER            "users"
//! \def FILES
# define            FILES           "files"
//! \def SYNC
# define            SYNC            "sync"
//! \def SYNC
# define            PART_SYNC       "partsync"
//! \def SYNC
# define            SUCCES_SYNC     "successsync"
//! \def TIMER_REFRESH
# define            TIMER_REFRESH_DOWNLOAD   3000
//! \def PART_SIZE
# define            PART_SIZE       5242880

class               QNetworkReply;

//! \class RequestHttpDownloadFile RequestHttpDownloadFile.hh
//! \brief class who send and receive request to the server for file download
class               RequestHttpDownloadFile : public QObject,
                                              public Singleton<RequestHttpDownloadFile>
{
 Q_OBJECT

    friend class    Singleton<RequestHttpDownloadFile>;

 private:
    RequestHttpDownloadFile(QObject * parent = 0);
    ~RequestHttpDownloadFile();

 public:
    void            recoverFile(QString & name, QString & idFolder, QString & size);

 private slots:
    void            update();
    void            finishedSlot(QNetworkReply* reply);

 private:
    QNetworkAccessManager * _http;
    QNetworkReply *         _reply;
    QTimer *                _timer;
    bool                    _recoverTree;
    QString                 _filePath;
    QVector<QVector<QString> > * _listDownload;
};

#endif              // !INCLUDE_REQUESTHTTPDOWNLOADFILE_HH__

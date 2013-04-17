//! \file RequestHttpFile.hh
//! \brief	header RequestHttpFile : send request to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#ifndef             INCLUDE_REQUESTHTTPFILE_HH__
# define            INCLUDE_REQUESTHTTPFILE_HH__

# include           <QObject>
# include           <QString>
# include           <QNetworkAccessManager>
# include           <QTimer>
# include           "Singleton.hpp"

//! \def WEBAGENTNAME
# define            WEBAGENTNAME    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.57 Safari/537.17"
//! \def URL
# define            URL             "https://ec2-54-242-98-168.compute-1.amazonaws.com:3000"
//! \def USER
# define            USER            "users"
//! \def FILES
# define            FILES           "files"
//! \def TIMER_REFRESH
# define    TIMER_REFRESH   1000

class               QNetworkReply;

//! \class RequestHttpFile RequestHttpFile.hh
//! \brief class who send and receive request to the server for file management
//! \brief send and receive files, files tree.
class               RequestHttpFile : public QObject,
                                      public Singleton<RequestHttpFile>
{
 Q_OBJECT

    friend class    Singleton<RequestHttpFile>;

 private:
    RequestHttpFile(QObject * parent = 0);
    ~RequestHttpFile();
    void            recoverFilesList(void);

 private slots:
    void            update();
    void            finishedSlot(QNetworkReply* reply);

 private:
    QNetworkAccessManager * _http;
    QNetworkReply *         _reply;
    QTimer *                _timer;
    bool                    _recoverTree;
};

#endif              // !INCLUDE_REQUESTHTTPFILE_HH__

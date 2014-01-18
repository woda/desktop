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
# define            URL             "http://kobhqlt.fr:3000" //"https://ec2-54-242-98-168.compute-1.amazonaws.com:3000"
//! \def URL
# define            URL_LIST        "http://kobhqlt.fr:3000"
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
# define            TIMER_REFRESH_FILE   5000
//! \def TIMER_REFRESH_FILE_LIST
# define            TIMER_REFRESH_FILE_LIST   30000

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

 public:
    void            AddingAFile(const QString & filename);
    void            UploadingAFile(int id);
    void            ConfirmingUpload(QString & filename);
    void            deleteFile(int id);
    void            recoverFilesList(void);
//    void            recoverFile(QString & name, QString & idFolder);

 private slots:
    void            update();
    void            updateFileList();
    void            finishedSlot(QNetworkReply* reply);

 private:
    QNetworkAccessManager * _http;
    QNetworkReply *         _reply;
    QTimer *                _timer;
    QTimer *                _timerFileList;
    bool                    _recoverTree;
    QString                 _filePath;
};

#endif              // !INCLUDE_REQUESTHTTPFILE_HH__

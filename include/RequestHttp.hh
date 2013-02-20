//! \file RequestHttp.cpp
//! \brief	implementation of the interface for send request to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#ifndef             INCLUDE_REQUESTHTTP_HH__
# define            INCLUDE_REQUESTHTTP_HH__

# include           <QObject>
# include           <QString>
# include           <QNetworkAccessManager>
# include           "Singleton.hpp"

# define            WEBAGENTNAME    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.57 Safari/537.17"
# define            URL             "https://ec2-54-242-98-168.compute-1.amazonaws.com:3000"
# define            USER            "users"
# define            LOGIN           "login"
# define            LOGOUT           "logout"

class               QNetworkReply;

class               RequestHttp : public QObject, public Singleton<RequestHttp>
{
Q_OBJECT

    friend class    Singleton<RequestHttp>;

private:
    RequestHttp(QObject * parent = 0);
    ~RequestHttp();

public:
    void            send();
    void            sendCreate(QString & login);
    void            sendUpdate(QString & email, QString & password);
    void            loginToServer(QString & login, QString & password);
    void            logoutToServer(void);

private slots:
    void            finishedSlot(QNetworkReply* reply);


private:
    QNetworkAccessManager * _http;
    QNetworkReply *         _reply;
};

#endif              // !INCLUDE_REQUESTHTTP_HH__

//! \file RequestHttp.hpp
//! \brief	header RequestHttp : send request to the server
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#ifndef             INCLUDE_REQUESTHTTP_HPP__
# define            INCLUDE_REQUESTHTTP_HPP__

# include           <QObject>
# include           <QNetworkCookieJar>
# include           "Singleton.hpp"


//! \class RequestHttp RequestHttp.hpp
//! \brief class who send and receive request to the server for file management
//! \brief send and receive files, files tree.
class               RequestHttp : public QObject,
                                  public Singleton<RequestHttp>
{
 Q_OBJECT

    friend class    Singleton<RequestHttp>;

 private:
    //! \brief Constructor
    RequestHttp(QObject * parent = 0) : QObject(parent), _hasCookie(false) {}

    //! \brief Destructor
    ~RequestHttp() {}

 public:
    //! \param[in] cookie QNetworkCookieJar, cookie provide by the login to the server
    //! \brief save the cookie for the authentification to the server
    void                setCookie(QNetworkCookieJar * cookie) {
        _cookie = cookie;
        _hasCookie = true;
    }

    //! \brief give the cookie for communicate with the server
    //! \return a QNetworkCookieJar *, who is login to the server
    QNetworkCookieJar * getCookie(void) const {
        return _cookie;
    }

    //! \brief delete the cookie
    void                deleteCookie(void) {
        _hasCookie = false;
    }

    //! \brief check if a cookie is present
    //! \return true if a cookie is set, otherwise false
    bool                hasCookie(void) const {
        return _hasCookie;
    }

 private:
    QNetworkCookieJar * _cookie;
    bool                _hasCookie;
};

#endif              // !INCLUDE_REQUESTHTTP_HPP__

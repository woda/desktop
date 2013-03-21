//! \file Account.hh
//! \brief header Account : information about account
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-02

#ifndef             INCLUDE_ACCOUNT_HH__
# define            INCLUDE_ACCOUNT_HH__

# include           <QString>
# include           "Singleton.hpp"

//! \def LOGIN_CONFFILE
# define            LOGIN_CONFFILE       "account/login"
//! \def PASSWORD_CONFFILE
# define            PASSWORD_CONFFILE    "account/password"

//! \class Account Account.hh
//! \brief class with information about account
//! Obtain information as json, deserialize it, fill the account information or an error.
class               Account : public Singleton<Account>
{
    friend class    Singleton<Account>;

 private:
    Account();
    Account(bool);
    ~Account();

 public:
    void            deserializeJsonAccount(QByteArray & bytes);

    bool            isConnected(void) const;
    void            connect(void);
    void            disconnect(void);

    void            setLogin(QString & login);
    void            setPassword(QString & password);
    void            setFirstName(QString & firstName);
    void            setLastName(QString & lastName);
    void            setEmail(QString & email);

    const QString & login(void) const;
    const QString & password(void) const;
    const QString & firstName(void) const;
    const QString & lastName(void) const;
    const QString & email(void) const;

    void            httpError(void);
    bool            isHttpError(void) const;
    void            serverError(QString & error);
    bool            isServerError(void) const;
    const QString & textServerError(void) const;

 private:
    bool            _connected;
    QString         _login;
    QString         _password;
    QString         _firstName;
    QString         _lastName;
    QString         _email;
    bool            _errorHttp;
    QString         _errorServer;
};

#endif              // !INCLUDE_ACCOUNT_HH__

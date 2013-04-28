//! \file AccountDB.hh
//! \brief header AccountDB : information about account for create DB
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#ifndef             INCLUDE_ACCOUNTDB_HH__
# define            INCLUDE_ACCOUNTDB_HH__

# include           <vector>

//! \def ACCOUNT_LOGIN
# define            ACCOUNT_LOGIN       "login"
//! \def ACCOUNT_PASSWORD
# define            ACCOUNT_PASSWORD    "password"
//! \def ACCOUNT_DIRECTORY
# define            ACCOUNT_DIRECTORY   "directory"


class               QString;

//! \class AccountDB AccountDB.hh
//! \brief content for create table with account content
class               AccountDB {
 public:
    AccountDB();
    ~AccountDB();

    static std::vector<QString> createTable(void);
    static std::vector<QString> accountPrimaryKey(void);
    static QString              accountTable(void);
    static std::map<QString, std::vector<QString> *> * selectAllAccount(void);

    void                insertAccountLoginPassword(QString & login, QString & password);
    void                insertAccountDirectory(QString & folderPath);
    void                deleteLineAccount(QString & login);
    void                deleteLineDirectory(QString & folderPath);

 private:
    QString             addQuotes(QString str);
};

#endif              // !INCLUDE_ACCOUNTDB_HH__

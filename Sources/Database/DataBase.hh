//! \file DataBase.hh
//! \brief	header DataBase : interaction with the database
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#ifndef             INCLUDE_DATABASE_HH__
# define            INCLUDE_DATABASE_HH__

# include           <QtSql/QSqlDatabase>
# include           <vector>
# include           <map>
# include           "Singleton.hpp"


//! \def DB_TYPE
# define            DB_TYPE         "QSQLITE"
//! \def DB_NAME
# define            DB_NAME         "Woda.db"

class               QString;

//! \class DataBase DataBase.hh
//! \brief class for the interactions with the database, insert, update, delete
class               DataBase : public Singleton<DataBase> {
    friend class    Singleton<DataBase>;

    typedef std::vector<QString> (*func)(void);

    DataBase();
    ~DataBase();

 public:
    std::map<QString, std::vector<QString> *> *  select(QString & strQuery);
    std::map<QString, std::vector<QString> *> *  select(QString & from,
                                                std::vector<QString> & vSelect);
    std::map<QString, std::vector<QString> *> *  select(QString & from,
                                                 std::vector<QString> & vSelect,
                                                 std::vector<QString> & vWhere);
    void            insert(QString & from,
                           std::map<QString, QString> & mapInsert);
    void            update(QString & table,
                           std::map<QString, QString> & mapUpdate,
                           std::vector<QString> & vWhere);
    void            deleteLine(QString & table,
                               std::vector<QString> & vWhere);
    bool            getEmpty(void) const;

 private:
    void            create();
    void            open();
    inline void     close();
    inline void     execute(QString & str);
    inline void     addQuery(QString & str);
    inline void     deleteQuery(void);
    void            executeQuery(void);
    bool            checkInsert(QString & table,
                                std::map<QString, QString> & mapInsert);
    bool            checkInsertWithoutPrimary(QString & table,
                                std::map<QString, QString> & mapInsert);
    bool            checkUpdate(QString & table,
                                std::map<QString, QString> & mapUpdate);
    std::vector<QString>    insertToUpdate(QString & table,
                                        std::map<QString, QString> & mapInsert);
    bool            checkDataBase(void);

 private:
    QSqlDatabase *              _db;
    std::vector<func> *         _mapCreate;
    std::map<QString, func> *   _mapPrimaryKey;
    bool                        _connect;
    bool                        _create;
    std::vector<QString> *      _vQuery;
    bool                        _empty;
};

#endif              // !INCLUDE_DATABASE_HH__

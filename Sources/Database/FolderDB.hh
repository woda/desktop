//! \file FolderDB.hh
//! \brief header FolderDB : information about user folder and his content for create DB
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04


#ifndef             INCLUDE_FOLDERDB_HH__
# define            INCLUDE_FOLDERDB_HH__

# include           <vector>
# include           <QByteArray>

//! \def FOLDER_PATH
# define            FOLDER_PATH             "path"

//! \def FILE_ID
# define            FILE_ID                 "id"
//! \def FILE_NAME
# define            FILE_NAME               "name"
//! \def FILE_ID_FOLDER
# define            FILE_ID_FOLDER          "id_folder"
//! \def FILE_FAVORITE
# define            FILE_FAVORITE           "favorite"
//! \def FILE_PUBLICNESS
# define            FILE_PUBLICNESS         "publicness"
//! \def FILE_SIZE
# define            FILE_SIZE               "size"
//! \def FILE_PART_SIZE
# define            FILE_PART_SIZE          "part_size"
//! \def FILE_SYNCHRONIZED
# define            FILE_SYNCHRONIZED       "synchronized"
//! \def FILE_HASH
# define            FILE_HASH               "hash"

class               QString;

//! \class FolderDB FolderDB.hh
//! \brief content for create table with folder content
class               FolderDB {
 public:
    FolderDB();
    ~FolderDB();

    static std::vector<QString> createTable(void);
    static std::vector<QString> folderPrimaryKey(void);
    static std::vector<QString> filePrimaryKey(void);

    static QString              folderTable(void);
    static QString              fileTable(void);

    static std::map<QString, std::vector<QString> *> * selectAllFolder(void);
    static std::map<QString, std::vector<QString> *> * selectAllFile(void);

    void                insertFolder(QString & folderPath);
    void                insertFile(const QString &filePath, const QByteArray);
    void                insertFile(QString & name, QString & idFolder,
                                   QString & hash);
    void                insertFile(int id, QString & name, QString & idFolder,
                                   bool favorite, bool publicness,
                                   QString & size, QString & partSize);
    void                deleteLine(void);
    void                deleteLineFile(const QString &filePath);
    void                deleteLineFolder(QString & folderPath);
    bool                checkFile(int id);

 private:
    QString             addQuotes(QString str);
    void                deleteLineAllFilesInFolder(QString & folderPath);
};

#endif              // !INCLUDE_FOLDERDB_HH__

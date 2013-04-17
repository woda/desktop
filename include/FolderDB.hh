//! \file FolderDB.hh
//! \brief header FolderDB : information about user folder and his content for create DB
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04


#ifndef             INCLUDE_FOLDERDB_HH__
# define            INCLUDE_FOLDERDB_HH__

# include           <vector>

# define            FOLDER_PATH             "path"

# define            FILE_NAME               "name"
# define            FILE_ID_FOLDER          "idFolder"
# define            FILE_HASH               "hash"

class               QString;

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
    void                insertFile(QString & filePath);
    void                deleteLine(void);
    void                deleteLineFile(QString & filePath);
    void                deleteLineFolder(QString & folderPath);

 private:
    QString             addQuotes(QString str);
    void                deleteLineAllFilesInFolder(QString & folderPath);
};

#endif              // !INCLUDE_FOLDERDB_HH__

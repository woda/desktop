//! \file UserFolderManagement.hh
//! \brief	implementation of the interface for the gestion of the user folder
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#ifndef     INCLUDE_USERFOLDERMANAGEMENT_HH__
# define    INCLUDE_USERFOLDERMANAGEMENT_HH__

# include	"Singleton.hpp"
# include   <QWidget>
# include   <QString>
# include   <QVariantList>

//! \def INSTANCE_USER_FOLDER_MANAGEMENT
# define    INSTANCE_USER_FOLDER_MANAGEMENT "UserFolderManagement"
//! \def DIRECTORY
# define    DIRECTORY       "global/directory"

//! \class UserFolderManagement UserFolderManagement.hh
//! \brief manage the user directory, create, change, delete
//! \brief manage the file system watcher
class       UserFolderManagement : public QObject,
                                   public Singleton<UserFolderManagement>
{
 Q_OBJECT

    friend class    Singleton<UserFolderManagement>;
    
 public:
    UserFolderManagement(QObject * parent = 0);
    ~UserFolderManagement();

    int             deserializeJsonAccount(QByteArray & bytes);
    void            deserializeJsonFileList(QVariantList & filelist, QString & folderName);
    int             insertHashFileIntoDB(QVariantMap & mapFile, QString & folderName);
    int             insertFileIntoDB(QVariantMap & mapFile, QString & folderName);
    void            deserializeJsonFolderList(QVariantList & folderlist, QString & folderName);
    void            createDirectory(QString & folderPath);
    void            changeDirectory(QString & folderPath);
    void            insertDirectoryIntoDatabase(void);
    void            deleteDirectory(void);
    const QString & getCurrentDirectory(void) const;
    const QString & getTempDirectory(void) const;
    bool            checkDirectoryExist(const QString & folderPath);
    bool            checkFileExist(const QString & filePath);
    void            deserializeJsonDownloadFile(QByteArray & bytes, QString url);

    void            copyEntireTempFolder();
    bool            copyFolderTemp(const QString & folderPath);

 private:
    void            moveDirectory(QString & folderPath);
    void            deleteFileSystemWatcher(void);
    bool            removeAllContentAndFolder(const QString & folderPath);
    void            createSimpleFolder(QString & folderPath);
    void            createSimpleFile(QString & filePath);
    void            copyBytesIntoFile(QByteArray & bytes, QString & filePath,
                                      int size);
    void            checkDirectoryExistAndCreateDirectory(QString & file);
    bool            downloadFileIfNotExist(int id, int size, int part_size);
    void            downloadAllPartFile(int id, int size, int part_size);
    void            checkFileCompleteWithAllPart(int id, QString & filePath,
                                                 int size, int part_size);
    QString         searchFolderPath(QString name);

 private:
    QString         _folderPath;
    QString         _instanceSemaphore;
    QString         _folderPathTemp;

 public:
    // for Test only
    void            copyAFileToTempFolder(QString & filePath);
    UserFolderManagement(QString folderPath, QObject * parent = 0);
};

#endif      // !INCLUDE_USERFOLDERMANAGEMENT_HH

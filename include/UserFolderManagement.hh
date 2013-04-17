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

//! \def INSTANCE_USER_FOLDER_MANAGEMENT
# define    INSTANCE_USER_FOLDER_MANAGEMENT "UserFolderManagement"
//! \def DIRECTORY
# define    DIRECTORY       "global/directory"

//! \class UserFolderManagement UserFolderManagement.hh
class       UserFolderManagement : public QObject,
                                   public Singleton<UserFolderManagement>
{
 Q_OBJECT

    friend class    Singleton<UserFolderManagement>;
    
 public:
    UserFolderManagement(QObject * parent = 0);
    ~UserFolderManagement();

    void            changeDirectory(QString & folderPath);
    void            deleteDirectory(void);
    const QString & getCurrentDirectory(void) const;

 private:
    void            moveDirectory(QString & folderPath);
    void            deleteFileSystemWatcher(void);
    bool            removeAllContentAndFolder(const QString & folderPath);
    bool            checkDirectoryExist(const QString & folderPath);

 private:
    QString         _folderPath;
    QString         _instanceSemaphore;
};

#endif      // !INCLUDE_USERFOLDERMANAGEMENT_HH
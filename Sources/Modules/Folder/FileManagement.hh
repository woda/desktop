//! \file FileManagement.hh
//! \brief	implementation of the interface for the gestion of the user file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-11

#ifndef     INCLUDE_FILEMANAGEMENT_HH__
# define    INCLUDE_FILEMANAGEMENT_HH__

# include	"Singleton.hpp"
# include   <QWidget>
# include   <QString>


//! \class FileManagement FileManagement.hh
//! \brief manage the user file
class       FileManagement : public QObject,
                             public Singleton<FileManagement>
{
 Q_OBJECT

    friend class    Singleton<FileManagement>;
    
 public:
    FileManagement(QObject * parent = 0);
    ~FileManagement();

    int             getIdFile(const QString & filePath);
    QString         getFileName(int id);
    QString         getFileFolder(int id);
    QString         getFilePath(int id);
    int             getFilePartSize(int id);
    void            setSynchronized(int id, bool sync);
};

#endif      // !INCLUDE_FILEMANAGEMENT_HH

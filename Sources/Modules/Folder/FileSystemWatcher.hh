//! \file FileSystemWatcher.hh
//! \brief	header FileSystemWatcher : to know the changes in a directory
//! \author Woda Corporation
//! \version 1.2
//! \date 2012-11

#ifndef		INCLUDE_FILESYSTEMWATCHER_HH__
# define	INCLUDE_FILESYSTEMWATCHER_HH__

# include	"Popup.hh"
# include	"Singleton.hpp"
# include   <QObject>
# include   <QString>
# include   <QList>
# include	<QFileSystemWatcher>

//! \class FileSystemWatcher FileSystemWatcher.hh
//! \brief class who knows the changes in a directory
//! each file that is added, modified or deleted emit a signal and the event is catch.
class       FileSystemWatcher : public QObject,
                                public Singleton<FileSystemWatcher>
{
 Q_OBJECT

    friend class	Singleton<FileSystemWatcher>;

 public:
    FileSystemWatcher(QObject * parent = 0);
    ~FileSystemWatcher();


    void    addDirectory(QString & dir);

 private:
    void    deleteDirectory(void);
    void    fillListChange(void);
    void    checkFileIntoFolder(QString dir);

 private slots:
    void    eventFile(const QString & path);
    void    eventFolder(const QString & path);

 private:

    QFileSystemWatcher * _fsWatcher;
    QString              _path;
    QList<QString> *     _listFile;
    QList<QString> *     _listChange;
    int                  _prevCountFile;

    Popup *	_popup;
};

#endif		// !INCLUDE_FILESYSTEMWATCHER_HH__

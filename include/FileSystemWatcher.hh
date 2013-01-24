//! \file FileSystemWatcher.cpp
//! \brief	implementation of the interface to know the changes in a directory
//! \author Woda Corporation
//! \version 1.2
//! \date 2012-11

#ifndef		FILESYSTEMWATCHER_HH__
# define	FILESYSTEMWATCHER_HH__

# include	"Popup.hh"
# include	"Singleton.hpp"
# include   <QObject>
# include   <QString>
# include   <QList>
# include	<QFileSystemWatcher>



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

#endif		// !FILESYSTEMWATCHER_HH__

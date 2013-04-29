//! \file ConfFile.hh
//! \brief	header ConfFile : save information in a configuration file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef             INCLUDE_CONFFILE_HH__
# define            INCLUDE_CONFFILE_HH__

# include           <QSettings>
# include           <QString>
# include           "Singleton.hpp"

//! \def CONFFILE_DIRECTORY
# define            CONFFILE_DIRECTORY      "global/directory"
//! \def CONFFILE_CORNER
# define            CONFFILE_CORNER         "global/corner"

//! \class ConfFile ConfFile.hh
//! \brief class for save information in a configuration file
//! save information with a pair of key / value.
class               ConfFile : public Singleton<ConfFile>
{
    friend class    Singleton<ConfFile>;

 private:
    ConfFile(const QString & path = "woda.ini");
    ~ConfFile();

 public:
    void            setValue(const QString & key, const QVariant & value);
    const QVariant  getValue(const QString & key) const;
    void            removeKey(const QString & key);

 private:
    QSettings *     _settings;
};

#endif              // !INCLUDE_CONFFILE_HH__

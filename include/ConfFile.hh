//! \file ConfFile.cpp
//! \brief	implementation of the interface to save information in a configuration file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef             CONFFILE_HH__
# define            CONFFILE_HH__

# include           <QSettings>
# include           <QString>
# include           "Singleton.hpp"

# define            CONFFILE_DIRECTORY      "global/directory"
# define            CONFFILE_CORNER         "global/corner"

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

#endif              // !CONFFILE_HH__

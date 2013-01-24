/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#ifndef             CONFFILE_HH__
# define            CONFFILE_HH__

# include           <QSettings>
# include           <QString>
# include           "Singleton.hpp"

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

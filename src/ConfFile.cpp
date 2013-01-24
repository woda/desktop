/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#include	"ConfFile.hh"
#include <iostream>

ConfFile::ConfFile(const QString & path)
{
  _settings = new QSettings(path , QSettings::IniFormat);
}

ConfFile::~ConfFile()
{
  delete _settings;
}

void ConfFile::setValue(const QString & key, const QVariant & value)
{
  _settings->setValue(key, value);
  _settings->sync();
}

const QVariant ConfFile::getValue(const QString & key) const
{
  _settings->sync();
  return _settings->value(key);
}

void ConfFile::removeKey(const QString & key)
{
  _settings->remove(key);
  _settings->sync();
}

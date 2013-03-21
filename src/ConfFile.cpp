//! \file ConfFile.cpp
//! \brief	implementation of the header ConfFile to save information in a configuration file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	"ConfFile.hh"


//! \param[in] path path of the ini file
//! \brief Constructor, initialize the ini file with the path
ConfFile::ConfFile(const QString & path) {
  _settings = new QSettings(path , QSettings::IniFormat);
}

//! \brief Destructor
ConfFile::~ConfFile() {
  delete _settings;
}

//! \param[in] key key in the ini file for save the information
//! \param[in] value value to save in the ini file
//! \brief add or update the value with the key pass in parameter in the ini file
void ConfFile::setValue(const QString & key, const QVariant & value) {
  _settings->setValue(key, value);
  _settings->sync();
}

//! \param[in] key key in the ini file for get the information
//! \return the information pair with the key
//! \brief get the value with the key in the ini file
const QVariant ConfFile::getValue(const QString & key) const {
  _settings->sync();
  return _settings->value(key);
}

//! \param[in] key key in the ini file for remove the information
//! \brief remove the value with the key in the ini file
void ConfFile::removeKey(const QString & key) {
  _settings->remove(key);
  _settings->sync();
}

//! \file ConfFile.cpp
//! \brief	implementation of the interface of CustomAction for display a Pixmap in the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include "MyCustomActionPixmap.hh"
#include <QImage>


//! \fn MyCustomActionPixmap::MyCustomActionPixmap(QWidget *parent, QString & path)
//! \param[in] parent Qobject parent or nothing
//! \param[in] path path of the image to display
//! \brief		Constructor
MyCustomActionPixmap::MyCustomActionPixmap(QWidget *parent, QString & path) :
  QWidgetAction(parent), _path(path)
{
}


//! \fn QWidget *MyCustomActionPixmap::createWidget(QWidget *parent)
//! \param[in] parent the parent widget where attach the Pixmap
//! \return A widget - the label widget who will display
//! \brief initialize a QLabel attach to the parent widget return the label to display
//! \brief attach a pixmap to the label and adjust the size
QWidget *MyCustomActionPixmap::createWidget(QWidget *parent)
{
  _label = new QLabel(parent);
  QImage image(_path);
  _label->setPixmap(QPixmap::fromImage(image));
  _label->adjustSize();
  return _label;
}

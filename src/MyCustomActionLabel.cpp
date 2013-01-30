//! \file ConfFile.cpp
//! \brief	implementation of the interface of CustomAction for display a label in the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	"MyCustomActionLabel.hh"
#include	<QLabel>


//! \fn MyCustomActionLabel::MyCustomActionLabel(QWidget *parent, QString str)
//! \param[in] parent Qobject parent or nothing
//! \param[in] str string of the label to display
//! \brief		Constructor
MyCustomActionLabel::MyCustomActionLabel(QWidget *parent, QString str) :
  QWidgetAction(parent), _str(str)
{
}


//! \fn QWidget * MyCustomActionLabel::createWidget(QWidget *parent)
//! \param[in] parent the parent widget where attach the label
//! \return A widget - the label widget who will display
//! \brief initialize a QLabel attach to the parent widget return the label to display
QWidget		*MyCustomActionLabel::createWidget(QWidget *parent)
{
  _label = new QLabel(parent);
  _label->setText(_str);
  return _label;
}

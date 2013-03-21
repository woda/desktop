//! \file MyCustomActionLabel.cpp
//! \brief implementation of the header MyCustomActionLabel : CustomAction for display a label in the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	"MyCustomActionLabel.hh"
#include	<QLabel>


//! \param[in] parent Qobject parent or nothing
//! \param[in] str string of the label to display
//! \brief Constructor
MyCustomActionLabel::MyCustomActionLabel(QWidget *parent, QString str) :
  QWidgetAction(parent), _str(str) {
}


//! \param[in] parent the parent widget where attach the label
//! \return A widget - the label widget who will display
//! \brief initialize a QLabel attach to the parent widget return the label to display
QWidget		*MyCustomActionLabel::createWidget(QWidget *parent) {
  _label = new QLabel(parent);
  _label->setText(_str);
  return _label;
}

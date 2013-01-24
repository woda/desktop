/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#include	"MyCustomActionLabel.hh"
#include	<QLabel>

MyCustomActionLabel::MyCustomActionLabel(QWidget *parent, QString str) :
  QWidgetAction(parent), _str(str)
{
}

QWidget		*MyCustomActionLabel::createWidget(QWidget *parent)
{
  _label = new QLabel(parent);
  _label->setText(_str);
  return _label;
}

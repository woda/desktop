/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#include "MyCustomActionPixmap.hh"
#include <QImage>

MyCustomActionPixmap::MyCustomActionPixmap(QWidget *parent, QString & path) :
  QWidgetAction(parent), _path(path)
{
}

QWidget *MyCustomActionPixmap::createWidget(QWidget *parent)
{
  _label = new QLabel(parent);
  QImage image(_path);
  _label->setPixmap(QPixmap::fromImage(image));
  _label->adjustSize();
  return _label;
}

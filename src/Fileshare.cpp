/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#include "Fileshare.hh"
#include "ui_Fileshare.h"

Fileshare::Fileshare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fileshare)
{
    ui->setupUi(this);
}

Fileshare::~Fileshare()
{
    delete ui;
}

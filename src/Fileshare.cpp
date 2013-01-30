//! \file ConfFile.cpp
//! \brief	implementation of the interface of the GUI for settings on a file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include "Fileshare.hh"
#include "ui_Fileshare.h"


//! \fn Fileshare::Fileshare(QWidget *parent)
//! \param[in] parent Qobject parent or nothing
//! \brief		Constructor
Fileshare::Fileshare(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::Fileshare)
{
    ui->setupUi(this);
}

//! \fn Fileshare::~Fileshare()
//! \brief		Destructor
Fileshare::~Fileshare()
{
    delete ui;
}

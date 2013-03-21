//! \file Fileshare.cpp
//! \brief	implementation of the header Fileshare : GUI for settings on a file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include "Fileshare.hh"
#include "ui_Fileshare.h"


//! \param[in] parent QObject parent or nothing
//! \brief Constructor, setup the Ui
Fileshare::Fileshare(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::Fileshare) {
    ui->setupUi(this);
}

//! \fn Fileshare::~Fileshare()
//! \brief Destructor, delete the Ui
Fileshare::~Fileshare() {
    delete ui;
}

//! \file FriendsManagement.cpp
//! \brief implementation of the header FriendsManagement : GUI for friend list management
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include "FriendsManagement.hh"
#include "ui_FriendsManagement.h"


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! initialize the Ui
FriendsManagement::FriendsManagement(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::FriendsManagement) {
    ui->setupUi(this);
}


//! \brief Destructor
//! delete the Ui
FriendsManagement::~FriendsManagement() {
    delete ui;
}


//! \param[in] index index of the friend
//! \brief
void FriendsManagement::on_userlist_clicked(const QModelIndex &index) {
}


//! \brief
void FriendsManagement::on_addfriendbutton_clicked() {
}


//! \brief
void FriendsManagement::on_quitbutton_clicked() {
    delete this;
}

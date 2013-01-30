//! \file ConfFile.cpp
//! \brief	implementation of the interface of the GUI for friend list management
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include "FriendsManagement.hh"
#include "ui_FriendsManagement.h"


//! \fn FriendsManagement::FriendsManagement(QWidget * parent)
//! \param[in] parent Qobject parent or nothing
//! \brief		Constructor
FriendsManagement::FriendsManagement(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::FriendsManagement)
{
    ui->setupUi(this);
}


//! \fn FriendsManagement::~FriendsManagement()
//! \brief		Destructor
FriendsManagement::~FriendsManagement()
{
    delete ui;
}


//! \fn void FriendsManagement::on_userlist_clicked(const QModelIndex &index)
//! \param[in] index index of the friend
//! \brief
void FriendsManagement::on_userlist_clicked(const QModelIndex &index)
{
    std::cout << index.column() << std::endl;
    if (index.column() == 1)
    {
        std::cout << "Yep." << std::endl;


    }
}


//! \fn void FriendsManagement::on_addfriendbutton_clicked()
//! \brief
void FriendsManagement::on_addfriendbutton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                        tr("Username or Email:"), QLineEdit::Normal,
                                        "", &ok);
    if (ok && !text.isEmpty())
       std::cout << text.toStdString() << std::endl;
}


//! \fn void FriendsManagement::on_quitbutton_clicked()
//! \brief
void FriendsManagement::on_quitbutton_clicked()
{
    delete this;
}

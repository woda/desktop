/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#include "FriendsManagement.hh"
#include "ui_FriendsManagement.h"

FriendsManagement::FriendsManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendsManagement)
{
    ui->setupUi(this);
}

FriendsManagement::~FriendsManagement()
{
    delete ui;
}

void FriendsManagement::on_userlist_clicked(const QModelIndex &index)
{
    std::cout << index.column() << std::endl;
    if (index.column() == 1)
    {
        std::cout << "Yep." << std::endl;


    }
}

void FriendsManagement::on_addfriendbutton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                        tr("Username or Email:"), QLineEdit::Normal,
                                        "", &ok);
    if (ok && !text.isEmpty())
       std::cout << text.toStdString() << std::endl;
}

void FriendsManagement::on_quitbutton_clicked()
{
    delete this;
}

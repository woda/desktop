/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#ifndef FRIENDSMANAGEMENT_H
#define FRIENDSMANAGEMENT_H

#include <QDialog>
#include <QModelIndex>
#include <iostream>
#include <QInputDialog>
#include <QDir>

namespace Ui {
class FriendsManagement;
}

class FriendsManagement : public QDialog
{
    Q_OBJECT
    
public:
    explicit FriendsManagement(QWidget *parent = 0);
    ~FriendsManagement();
    
private slots:
    void on_userlist_clicked(const QModelIndex &index);

    void on_addfriendbutton_clicked();

    void on_quitbutton_clicked();

private:
    Ui::FriendsManagement *ui;
};

#endif // FRIENDSMANAGEMENT_H

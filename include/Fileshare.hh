/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#ifndef FILESHARE_HH
#define FILESHARE_HH

#include <QDialog>

namespace Ui {
class Fileshare;
}

class Fileshare : public QDialog
{
    Q_OBJECT
    
public:
    explicit Fileshare(QWidget *parent = 0);
    ~Fileshare();
    
private:
    Ui::Fileshare *ui;
};

#endif // FILESHARE_HH

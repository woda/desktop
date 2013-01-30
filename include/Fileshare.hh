//! \file ConfFile.cpp
//! \brief	implementation of the interface of the GUI for settings on a file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

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
    explicit Fileshare(QWidget * parent = 0);
    ~Fileshare();
    
private:
    Ui::Fileshare *ui;
};

#endif // FILESHARE_HH

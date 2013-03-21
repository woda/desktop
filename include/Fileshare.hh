//! \file Fileshare.hh
//! \brief	implementation of the interface of the GUI for settings on a file
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef     INCLUDE_FILESHARE_HH__
# define    INCLUDE_FILESHARE_HH__

# include   <QDialog>

namespace   Ui {
    class   Fileshare;
}

//! \class Fileshare Fileshare.hh
class       Fileshare : public QDialog
{
 Q_OBJECT
    
 public:
    explicit Fileshare(QWidget * parent = 0);
    ~Fileshare();
    
 private:
    Ui::Fileshare *ui;
};

#endif      // !INCLUDE_FILESHARE_HH

//! \file FriendsManagement.hh
//! \brief	implementation of the interface of the GUI for friend list management
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef     INCLUDE_FRIENDSMANAGEMENT_HH__
# define    FRIENDSMANAGEMENT_HH__

# include   <QDialog>
# include   <QModelIndex>
# include   <QInputDialog>
# include   <QDir>

namespace   Ui {
    class   FriendsManagement;
}

//! \class FriendsManagement FriendsManagement.hh
class       FriendsManagement : public QDialog
{
 Q_OBJECT
    
 public:
    explicit FriendsManagement(QWidget *parent = 0);
    ~FriendsManagement();
    
 private slots:
    void    on_userlist_clicked(const QModelIndex &index);
    void    on_addfriendbutton_clicked();
    void    on_quitbutton_clicked();

 private:
    Ui::FriendsManagement *ui;
};

#endif      // !INCLUDE_FRIENDSMANAGEMENT_HH__

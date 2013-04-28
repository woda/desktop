//! \file Preferences.hh
//! \brief	header Preferences : GUI for preferences
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef     INCLUDE_PREFERENCES_HH__
# define    INCLUDE_PREFERENCES_HH__

# include   <QDialog>
# include   <QFileDialog>
# include   <QAbstractButton>

//! \def CORNER
# define    CORNER          "global/corner"
//! \def TIMER_REFRESH
# define    TIMER_REFRESH   1000


namespace   Ui {
    class   Preferences;
}

//! \class Preferences Preferences.hh
//! \brief Page who the user can choose his preferences
//! \brief choose a corner for the popup, select the folder will be synchronized,
//! \brief connect to an account, and change email, password.
class       Preferences : public QDialog
{
    Q_OBJECT
    
 public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();

 private:
    void    initCorner(void);
    void    initDirectory(void);
    void    initAccount(void);
    void    isDisconnected(void);
    void    isConnected(void);
    void    updateAccount();
    void    updateGeneral();
    
 private slots:
    void    on_checklimitdl_clicked();
    void    on_checklimitup_clicked();
    void    on_browse_button_clicked();
    void    notificationPositionClick(int id);
    void    buttonConnectAccount();
    void    buttonDisconnectAccount();
    void    buttonChangeAccount();
    void    update();

    void    buttonTest();

 private:
    Ui::Preferences *ui;
    QTimer * _timer;
    bool     _connected;


    //! \enum cornerPopUp
    enum cornerPopUp {
        TOP_LEFT = 1,   //!< Corner Top Left
        TOP_RIGHT,      //!< Corner Top Right
        BOTTOM_LEFT,    //!< Corner Bottom Left
        BOTTOM_RIGHT    //!< Corner Bottom Right
    };
};

#endif      // !INCLUDE_PREFERENCES_HH__

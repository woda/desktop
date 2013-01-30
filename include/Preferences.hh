//! \file ConfFile.cpp
//! \brief	implementation of the interface of GUI for preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef     PREFERENCES_HH__
# define    PREFERENCES_HH__

# include   <QDialog>
# include   <QFileDialog>
# include   <QAbstractButton>

# define    CORNER      "global/corner"
# define    DIRECTORY   "global/directory"

namespace Ui {
    class Preferences;
}

class       Preferences : public QDialog
{
    Q_OBJECT
    
 public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();

 private:
    void    initCorner(void);
    void    initDirectory(void);
    
 private slots:
    void    on_checklimitdl_clicked();
    void    on_checklimitup_clicked();
    void    on_browse_button_clicked();
    void    notificationPositionClick(int id);

 private:
    Ui::Preferences *ui;

    enum {
        TOP_LEFT = 1,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };
};

#endif      // ! PREFERENCES_HH__

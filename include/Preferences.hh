/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

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

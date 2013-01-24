/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<QSystemTrayIcon>
# include	<QWidget>
# include	"Popup.hh"
# include   "FriendsManagement.hh"
# include   "Preferences.hh"
# include   "Fileshare.hh"

# define    DIRECTORY       "global/directory"

class		QAction;
class		QCheckBox;
class		QComboBox;
class		QGroupBox;
class		QLabel;
class		QLineEdit;
class		QMenu;
class		QPushButton;
class		QSpinBox;
class		QTextEdit;

class		Window : public QWidget
{
  Q_OBJECT

public:
  Window(QWidget * parent = 0);
  ~Window();

  void		setVisible(bool visible);

public slots:
  void		clickLogo();
  void		closeEvent(QCloseEvent * event);

private slots:
  void		setIcon(int index);
  void		iconActivated(QSystemTrayIcon::ActivationReason reason);
  void		messageClicked();
  void      openFriendManager();
  void      openPreferences();
  void      openFileshare();
  void      openDirectory();
  void      openBrowserMoreStorage();
  void      openBrowserWoda();

private:
  void		createIconGroupBox();
  void		createMessageGroupBox();
  void		createActions();
  void		createTrayIcon();
  void      createFsWatcher();


  QComboBox *	iconComboBox;
  QComboBox *	typeComboBox;

  // QAction *	minimizeAction;
  // QAction *	maximizeAction;
  // QAction *	restoreAction;
  QAction *  _logoAction;
  //QAction *  _testAction;
  QAction *  openFolderAction;
  QAction *  goWebsiteAction;
  QAction *  recentFilesAction;
  QAction *  spaceAction;
  QAction *  getMoreAction;
  QAction *  helpAction;
  QAction *  preferencesAction;
  QAction *  quitAction;
  QAction *  friendsAction;

  QSystemTrayIcon * trayIcon;
  QMenu *	    trayIconMenu;

  Popup *	_popup;

  // faudra faire une classe a part pour gerer ca
  enum imageIcon
  {
    Normal,
    Synchronization,
    Synchronized
  };

  // faudra faire une classe a part pour gerer ca
  enum messageIcon
  {
    NoIcon,
    Information,
    Warning,
    Critical
  };


  // a voir pour le mettre ailleur
 private :
  void		showMessage(QString title, QString message,
                        Window::messageIcon type, int time);
};

#endif		// !__WINDOW_HH__

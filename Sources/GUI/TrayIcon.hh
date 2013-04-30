//! \file TrayIcon.hh
//! \brief	header TrayIcon : manages the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#ifndef		INCLUDE_TRAYICON_HH__
# define	INCLUDE_TRAYICON_HH__

# include	<QSystemTrayIcon>
# include	<QWidget>
# include	"Popup.hh"
# include   "Preferences.hh"

//! \def URL_MORE_STORAGE
# define    URL_MORE_STORAGE    "http://current.webapp.woda-server.com/app_dev.php"
//! \def URL_WODA_WEBPAGE
# define    URL_WODA_WEBPAGE    "http://current.webapp.woda-server.com/app_dev.php"


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

//! \class TrayIcon TrayIcon.hh
//! \brief class who manage the tray icon
class		TrayIcon : public QWidget
{
  Q_OBJECT

public:
  TrayIcon(QWidget * parent = 0);
  ~TrayIcon();
  void		setVisible(bool visible);

public slots:
  void		clickLogo();
  void		closeEvent(QCloseEvent * event);


private:
  //! \enum imageIcon
  enum imageIcon
  {
    Normal,             //!< default image
    Synchronization,    //!< image synchronization in progress
    Synchronized        //!< image up to date
  };


  //! \enum messageIcon
  //! \brief message in tray
  enum messageIcon
  {
    NoIcon,         //!< without icon
    Information,    //!< with information icon
    Warning,        //!< with warning icon
    Critical        //!< with critical icon
  };


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
  void		showMessage(QString title, QString message,
                        TrayIcon::messageIcon type, int time);
  void		createIconGroupBox();
  void		createMessageGroupBox();
  void		createActions();
  void		createTrayIcon();


  QComboBox *	iconComboBox;
  QComboBox *	typeComboBox;

  QAction *  _logoAction;
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
};

#endif		// !INCLUDE_TRAYICON_HH__

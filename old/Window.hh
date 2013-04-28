//! \file Window.hh
//! \brief	header Window : Window wich manages the interfaces
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<QSystemTrayIcon>
# include	<QWidget>
# include	"Popup.hh"
# include   "FriendsManagement.hh"
# include   "Preferences.hh"
# include   "Fileshare.hh"

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

//! \class Window Window.hh
//! \brief main Window who manage the tray icon
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
  void      checkUserFolder();


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
  //! \enum imageIcon
  enum imageIcon
  {
    Normal,             //!< default image
    Synchronization,    //!< image synchronization in progress
    Synchronized        //!< image up to date
  };

  // faudra faire une classe a part pour gerer ca
  //! \enum messageIcon
  //! \brief message in tray
  enum messageIcon
  {
    NoIcon,         //!< without icon
    Information,    //!< with information icon
    Warning,        //!< with warning icon
    Critical        //!< with critical icon
  };


  // a voir pour le mettre ailleur
 private :
  void		showMessage(QString title, QString message,
                        Window::messageIcon type, int time);
};

#endif		// !__WINDOW_HH__
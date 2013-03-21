//! \file Window.cpp
//! \brief	implementation of the header Window wich manages the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	<QtGui>
#include	"Window.hh"
#include	"ConfFile.hh"
#include    "FileSystemWatcher.hh"
#include	"MyCustomActionPixmap.hh"
#include	"MyCustomActionLabel.hh"


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! Create action, tray icon, signal, popup.
Window::Window(QWidget * parent)
  : QWidget(parent) {
  createIconGroupBox();
  createMessageGroupBox();
  createActions();
  createTrayIcon();

  this->setVisible(false);

  connect(iconComboBox, SIGNAL(currentIndexChanged(int)),
          this, SLOT(setIcon(int)));
  connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

  this->setIcon(Window::Normal);

  // a appeler pour changer l'icone
  iconComboBox->setCurrentIndex(Window::Normal);
  trayIcon->show();

  setWindowTitle(tr("Woda"));

  _popup = new Popup(220, 150);
  ConfFile::getSingletonPtr();
  this->createFsWatcher();
}


//! \brief Destructor
//! Delete the singleton ConfFile
Window::~Window() {
  ConfFile::del();
}


//! \brief set the main window visible or not
void		Window::setVisible(bool) {
   // minimizeAction->setEnabled(visible);
   // maximizeAction->setEnabled(!isMaximized());
   // restoreAction->setEnabled(isMaximized() || !visible);
   //  QDialog::setVisible(visible);
}


//! \param[in] event event received in the slot
//! \brief ignore the event for close the main window
void		Window::closeEvent(QCloseEvent * event) {
  if (trayIcon->isVisible()) {
      //      QMessageBox::information(this, tr("Woda"), tr("Test"));
      this->hide();
      event->ignore();
    }
}


//! \param[in] index of the icon in iconComboBox
//! \brief set the icon in the icon tray with an image (like in processing, normal)
void		Window::setIcon(int index) {
  QIcon icon = iconComboBox->itemIcon(index);

  trayIcon->setIcon(icon);
  setWindowIcon(icon);

  trayIcon->setToolTip(iconComboBox->itemText(index));
}


//! \param[in] reason event received in the slot
//! \brief slot for the click on the icon in the system tray
void		Window::iconActivated(QSystemTrayIcon::ActivationReason reason) {
//  switch (reason)
//    {
//    case QSystemTrayIcon::Trigger:
//    case QSystemTrayIcon::DoubleClick:
//      _popup->showUp("test", 5000);
//      ConfFile::getSingletonPtr()->setValue("global/doubleclick", "titi");
//      break;
//    case QSystemTrayIcon::MiddleClick:
//      this->showMessage(QString("Test"), QString("Critical"), Window::Critical, 10);
//      break;
//    default:
//      {}
//    }
}
 

//! \param[in] title title of the message
//! \param[in] message text of the message
//! \param[in] type type of the message (warning, information, ...)
//! \param[in] time time to display the message in second
//! \brief show an information message in the system tray
void		Window::showMessage(QString title, QString message,
                                    Window::messageIcon type, int time) {
  QSystemTrayIcon::MessageIcon icon;
  icon = QSystemTrayIcon::MessageIcon(typeComboBox->itemData(type).toInt());
  trayIcon->showMessage(title, message, icon, time * 1000);
}


//! \brief if click on the message in the system tray
void		Window::messageClicked() {
}


//! \brief open the friendlist management window
void        Window::openFriendManager() {
    FriendsManagement * friendsManagement = new FriendsManagement();

    friendsManagement->show();
}


//! \brief open the fileshare management window
void        Window::openFileshare() {
    Fileshare * fileshare = new Fileshare();

    fileshare->show();
}


//! \brief open the preference management window
void        Window::openPreferences() {
    Preferences * preferences = new Preferences();

    preferences->show();
}


//! \brief open the directory in the explorer
void        Window::openDirectory(void) {
    // if dir is empty, it does not open the explorer
    QString dir = ConfFile::getSingletonPtr()->getValue(CONFFILE_DIRECTORY).toString();
    QDesktopServices::openUrl(QUrl("file:///" + dir));
}


//! \brief open the web page for more storage in the browser
void        Window::openBrowserMoreStorage(void) {
    QDesktopServices::openUrl(QUrl(URL_MORE_STORAGE));
}


//! \brief open the woda web page in the browser
void        Window::openBrowserWoda(void) {
    QDesktopServices::openUrl(QUrl(URL_WODA_WEBPAGE));
}


//! \brief create the iconcombobox with different logo for the tray icon
void		Window::createIconGroupBox() {
  iconComboBox = new QComboBox;
  iconComboBox->addItem(QIcon(":/logoTray"), tr("Woda"));
}


//! \brief create the typeComboBox for the message in the system tray
void		Window::createMessageGroupBox() {
  typeComboBox = new QComboBox;
  typeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
  typeComboBox->addItem(style()->standardIcon(QStyle::SP_MessageBoxInformation),
                        tr("Information"), QSystemTrayIcon::Information);
  typeComboBox->addItem(style()->standardIcon(QStyle::SP_MessageBoxWarning),
                        tr("Warning"), QSystemTrayIcon::Warning);
  typeComboBox->addItem(style()->standardIcon(QStyle::SP_MessageBoxCritical),
                        tr("Critical"), QSystemTrayIcon::Critical);
  typeComboBox->setCurrentIndex(Window::Information);
}


//! \brief create the action with in the right clic on the icon
void		Window::createActions() {
  //--------------------------------------------------
  // Pour mettre une image dans le TrayIcon
  QString path(":/logoBig");
  _logoAction = new MyCustomActionPixmap(this, path);
  connect(_logoAction, SIGNAL(triggered()),
          this, SLOT(clickLogo()));
  //--------------------------------------------------

  //--------------------------------------------------
  // Pour mettre du text non cliquable
//  _testAction = new MyCustomActionLabel(this, tr("Coucou"));
  //--------------------------------------------------

  //--------------------------------------------------
  // Pour mettre du texte cliquable
  openFolderAction = new QAction(tr("&Open Woda folder"), this);
  connect(openFolderAction, SIGNAL(triggered()),
          this, SLOT(openDirectory()));
  goWebsiteAction = new QAction(tr("&Visit Woda on the web"), this);
  connect(goWebsiteAction, SIGNAL(triggered()),
          this, SLOT(openBrowserWoda()));
  //recentFilesAction = new QAction(tr("&Recent files"), this);
  friendsAction = new QAction(tr("&Manage Friendlist"), this);
  connect(friendsAction, SIGNAL(triggered()),
          this, SLOT(openFriendManager()));
  spaceAction = new QAction(tr("10GO (5%) used of 50GO"), this);
  spaceAction->setDisabled(true);
  getMoreAction = new QAction(tr("&Get more storage"), this);
  connect(getMoreAction, SIGNAL(triggered()),
          this, SLOT(openBrowserMoreStorage()));
  preferencesAction = new QAction(tr("&Preferences.."), this);
  connect(preferencesAction, SIGNAL(triggered()),
          this, SLOT(openPreferences()));
  helpAction = new QAction(tr("&Help"), this);
  connect(helpAction, SIGNAL(triggered()),
          this, SLOT(openFileshare()));
  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, SIGNAL(triggered()),
          qApp, SLOT(quit()));
  //--------------------------------------------------
}


//! \brief create all menu to show in the right clic on the icon
void		Window::createTrayIcon() {
  trayIconMenu = new QMenu(this);

  trayIconMenu->addAction(_logoAction);
//  trayIconMenu->addAction(_testAction);

  trayIconMenu->addSeparator();
  trayIconMenu->addAction(openFolderAction);
  trayIconMenu->addAction(goWebsiteAction);
  //trayIconMenu->addAction(recentFilesAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(spaceAction);
  trayIconMenu->addAction(getMoreAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(helpAction);
  trayIconMenu->addAction(preferencesAction);
  trayIconMenu->addAction(friendsAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(quitAction);

  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setContextMenu(trayIconMenu);
}


//! \brief If click on the logo call this method
void		Window::clickLogo() {
  QDesktopServices::openUrl(QUrl("http://webapp.woda-server.com/app_dev.php"));
}


//! \brief create the folder monitoring
void        Window::createFsWatcher(void) {
    FileSystemWatcher * fsWatcher = FileSystemWatcher::getSingletonPtr();
    QString dir = ConfFile::getSingletonPtr()->getValue(CONFFILE_DIRECTORY).toString();
    if (dir != QString("")) {
        fsWatcher->addDirectory(dir);
    }
}

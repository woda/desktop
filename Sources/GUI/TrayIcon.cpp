//! \file TrayIcon.cpp
//! \brief	implementation of the header TrayIcon wich manages the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#include	<QtGui>
#include	"TrayIcon.hh"
#include	"MyCustomActionPixmap.hh"
#include	"MyCustomActionLabel.hh"

#include	"ConfFile.hh"


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! \brief Create action, tray icon, signal, popup.
TrayIcon::TrayIcon(QWidget * parent)
  : QWidget(parent) {
  createIconGroupBox();
  createMessageGroupBox();
  createActions();
  createTrayIcon();

  connect(iconComboBox, SIGNAL(currentIndexChanged(int)),
          this, SLOT(setIcon(int)));
  connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

  this->setIcon(TrayIcon::Normal);

  // a appeler pour changer l'icone
  iconComboBox->setCurrentIndex(TrayIcon::Normal);
  trayIcon->show();

  _popup = new Popup(220, 150);
}


//! \brief Destructor
TrayIcon::~TrayIcon() {
}


//! \brief set the main window visible or not
void		TrayIcon::setVisible(bool) {

}


//! \param[in] event event received in the slot
//! \brief ignore the event for close the main window
void		TrayIcon::closeEvent(QCloseEvent * event) {
  if (trayIcon->isVisible()) {
      this->hide();
      event->ignore();
    }
}


//! \param[in] index of the icon in iconComboBox
//! \brief set the icon in the icon tray with an image (like in processing, normal, ...)
void		TrayIcon::setIcon(int index) {
  QIcon icon = iconComboBox->itemIcon(index);
  trayIcon->setIcon(icon);
  setWindowIcon(icon);
  trayIcon->setToolTip(iconComboBox->itemText(index));
}


//! \param[in] reason event received in the slot
//! \brief slot for the click on the icon in the system tray
void		TrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason) {
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
void		TrayIcon::showMessage(QString title, QString message,
                                  TrayIcon::messageIcon type, int time) {
  QSystemTrayIcon::MessageIcon icon;
  icon = QSystemTrayIcon::MessageIcon(typeComboBox->itemData(type).toInt());
  trayIcon->showMessage(title, message, icon, time * 1000);
}


//! \brief if click on the message in the system tray
void		TrayIcon::messageClicked() {
}


//! \brief open the friendlist management window
void        TrayIcon::openFriendManager() {

}


//! \brief open the fileshare management window
void        TrayIcon::openFileshare() {

}


//! \brief open the preference management window
void        TrayIcon::openPreferences() {
    // TO DO : if the preference window is already create, show this window and not another
    Preferences * preferences = new Preferences();
    preferences->show();
}


//! \brief open the directory in the explorer
void        TrayIcon::openDirectory(void) {
    // TO DO with the DB
    // if dir is empty, it does not open the explorer
    QString dir = ConfFile::getSingletonPtr()->getValue(CONFFILE_DIRECTORY).toString();
    QDesktopServices::openUrl(QUrl("file:///" + dir));
}


//! \brief open the web page for more storage in the browser
void        TrayIcon::openBrowserMoreStorage(void) {
    QDesktopServices::openUrl(QUrl(URL_MORE_STORAGE));
}


//! \brief open the woda web page in the browser
void        TrayIcon::openBrowserWoda(void) {
    QDesktopServices::openUrl(QUrl(URL_WODA_WEBPAGE));
}


//! \brief create the iconcombobox with different logo for the tray icon
void		TrayIcon::createIconGroupBox() {
  iconComboBox = new QComboBox;
  iconComboBox->addItem(QIcon(":/logoTray"), tr("Woda"));
}


//! \brief create the typeComboBox for the message in the system tray
void		TrayIcon::createMessageGroupBox() {
  typeComboBox = new QComboBox;
  typeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
  typeComboBox->addItem(style()->standardIcon(QStyle::SP_MessageBoxInformation),
                        tr("Information"), QSystemTrayIcon::Information);
  typeComboBox->addItem(style()->standardIcon(QStyle::SP_MessageBoxWarning),
                        tr("Warning"), QSystemTrayIcon::Warning);
  typeComboBox->addItem(style()->standardIcon(QStyle::SP_MessageBoxCritical),
                        tr("Critical"), QSystemTrayIcon::Critical);
  typeComboBox->setCurrentIndex(TrayIcon::Information);
}


//! \brief create the action with in the right clic on the icon
void		TrayIcon::createActions() {
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
void		TrayIcon::createTrayIcon() {
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
void		TrayIcon::clickLogo() {
  QDesktopServices::openUrl(QUrl("http://webapp.woda-server.com/app_dev.php"));
}

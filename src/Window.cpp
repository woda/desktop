//! \file ConfFile.cpp
//! \brief	implementation of the interface of Window wich manages the interfaces
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	<QtGui>
#include	"Window.hh"
#include	"ConfFile.hh"
#include    "FileSystemWatcher.hh"
#include	"MyCustomActionPixmap.hh"
#include	"MyCustomActionLabel.hh"


//! \fn Window::Window(QWidget * parent)
//! \param[in] parent Qobject parent or nothing
//! \brief Constructor, create action, tray icon, signal, popup
Window::Window(QWidget * parent)
  : QWidget(parent)
{
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


//! \fn Window::~Window()
//! \brief Destructor
Window::~Window()
{
  ConfFile::del();
}


//! \fn void Window::setVisible(bool)
//! \brief set the main window visible or not
void		Window::setVisible(bool)
{
//   // minimizeAction->setEnabled(visible);
//   // maximizeAction->setEnabled(!isMaximized());
//   // restoreAction->setEnabled(isMaximized() || !visible);
//   //  QDialog::setVisible(visible);
}


//! \fn void Window::closeEvent(QCloseEvent * event)
//! \param[in] event event received in the slot
//! \brief ignore the event for close the main window
void		Window::closeEvent(QCloseEvent * event)
{
  if (trayIcon->isVisible())
    {
      //      QMessageBox::information(this, tr("Woda"), tr("Test"));
      this->hide();
      event->ignore();
    }
}


//! \fn void Window::setIcon(int index)
//! \param[in] index of the icon in iconComboBox
//! \brief set the icon in the icon tray with an image (like in processing, normal)
void		Window::setIcon(int index)
{
  QIcon icon = iconComboBox->itemIcon(index);

  trayIcon->setIcon(icon);
  setWindowIcon(icon);

  trayIcon->setToolTip(iconComboBox->itemText(index));
}


//! \fn void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
//! \param[in] reason event received in the slot
//! \brief slot for the click on the icon in the system tray
void		Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
//  switch (reason)
//    {
//    case QSystemTrayIcon::Trigger:
//    case QSystemTrayIcon::DoubleClick:
//      _popup->showUp("Je ne sais pas si delord_k est le meilleur chef de projet :/", 5000);
//      ConfFile::getSingletonPtr()->setValue("global/doubleclick", "titi");
//      break;
//    case QSystemTrayIcon::MiddleClick:
//      // c'est pour voir si il va lire la seule classe de code qu'il y a
//      this->showMessage(QString("Delord_k"), QString("est un pd"), Window::Critical, 10);
//      break;
//    default:
//      {}
//    }
}
 

//! \fn void Window::showMessage(QString title, QString message, Window::messageIcon type, int time)
//! \param[in] title title of the message
//! \param[in] message text the the message
//! \param[in] type type of the message (warning, information, ...)
//! \param[in] time time to display the message
//! \brief show an information message in the system tray
void		Window::showMessage(QString title, QString message,
                                    Window::messageIcon type, int time)
{
  QSystemTrayIcon::MessageIcon icon;
  icon = QSystemTrayIcon::MessageIcon(typeComboBox->itemData(type).toInt());
  trayIcon->showMessage(title, message, icon, time * 1000);
}


//! \fn void Window::messageClicked()
//! \brief if click on the message in the system tray
void		Window::messageClicked()
{
  // action a faire ici, si il y a un clic sur le message du tray icon
}


//! \fn void Window::openFriendManager()
//! \brief open the friendlist management window
void        Window::openFriendManager()
{
    FriendsManagement *f = new FriendsManagement();

    f->show();
}


//! \fn void Window::openFileshare()
//! \brief open the fileshare management window
void        Window::openFileshare()
{
    Fileshare *f = new Fileshare();

    f->show();
}


//! \fn void Window::openPreferences()
//! \brief open the preference management window
void        Window::openPreferences()
{
    Preferences *f = new Preferences();

    f->show();
}


//! \fn void Window::openDirectory(void)
//! \brief open the directory in the explorer
void        Window::openDirectory(void) {
    // if dir is empty, it does not open the explorer
    QString dir = ConfFile::getSingletonPtr()->getValue(CONFFILE_DIRECTORY).toString();
    QDesktopServices::openUrl(QUrl("file:///" + dir));
}


//! \fn void Window::openBrowserMoreStorage(void)
//! \brief open the web page for more storage in the browser
void        Window::openBrowserMoreStorage(void) {
    QDesktopServices::openUrl(QUrl("http://webapp.woda-server.com/app_dev.php"));
}


//! \fn void Window::openBrowserWoda(void)
//! \brief open the woda web page in the browser
void        Window::openBrowserWoda(void) {
    QDesktopServices::openUrl(QUrl("http://webapp.woda-server.com/app_dev.php"));
}


//! \fn void Window::createIconGroupBox()
//! \brief create the iconcombobox with different logo for the tray icon
void		Window::createIconGroupBox() {
  iconComboBox = new QComboBox;
  iconComboBox->addItem(QIcon(":/logoTray"), tr("Woda"));
}


//! \fn void Window::createMessageGroupBox()
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


//! \fn void Window::createActions()
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


//! \fn void Window::createTrayIcon()
//! \brief create all menu to show in the right clic on the icon
void		Window::createTrayIcon()
{
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


//! \fn void Window::clickLogo()
//! \brief If click on the logo call this method
void		Window::clickLogo() {
  // a changer bien sur (c'est tj pour delord_k xD)
  //  std::cout << ConfFile::getSingletonPtr()->getValue("global/doubleclick").toString().toStdString() << std::endl;
  //QDesktopServices::openUrl(QUrl("http://meatspin.com/"));
  QDesktopServices::openUrl(QUrl("http://webapp.woda-server.com/app_dev.php"));
}


//! \fn void Window::createFsWatcher(void)
//! \brief create the folder monitoring
void        Window::createFsWatcher(void) {
    FileSystemWatcher * fsWatcher = FileSystemWatcher::getSingletonPtr();
    QString dir = ConfFile::getSingletonPtr()->getValue(CONFFILE_DIRECTORY).toString();
    if (dir != QString("")) {
        fsWatcher->addDirectory(dir);
    }/* else {
        this->showMessage(QString("Warning"),
                          QString("folder sync is not defined"),
                          Window::Warning, 10);
    }*/
}

//! \file Window.cpp
//! \brief	implementation of the header Window wich manages the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	<QtGui>
#include	"Window.hh"
#include    "TrayIcon.hh"
#include	"ConfFile.hh"
#include    "UserFolderManagement.hh"


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! Create action, tray icon, signal, popup.
Window::Window(QWidget * parent)
  : QWidget(parent) {
    this->setVisible(false);
    setWindowTitle(tr("Woda"));
    _trayIcon = new TrayIcon();
    this->checkUserFolder();
}


//! \brief Destructor
//! \brief Delete the singleton ConfFile
Window::~Window() {
    delete _trayIcon;
    ConfFile::del();
}


//! \param[in] event event received in the slot
//! \brief ignore the event for close the main window
//! \brief if the tray icon is visible
void		Window::closeEvent(QCloseEvent * event) {
    this->hide();
    event->ignore();
}

//! \brief create the folder monitoring
void        Window::checkUserFolder(void) {
    // TO DO : with Database
    QString dir = ConfFile::getSingletonPtr()->getValue(CONFFILE_DIRECTORY).toString();
    if (dir == QString("")) {
        dir = QDir::homePath();
        dir.append("/Woda");
        UserFolderManagement::getSingletonPtr()->createDirectory(dir);
    }
    UserFolderManagement::getSingletonPtr()->changeDirectory(dir);
}

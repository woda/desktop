//! \file Window.cpp
//! \brief	implementation of the header Window wich manages the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	<QtGui>
#include	"Window.hh"
#include    "TrayIcon.hh"


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! Create action, tray icon, signal, popup.
Window::Window(QWidget * parent)
  : QWidget(parent) {
  setWindowTitle(tr("Woda"));
  _trayIcon = new TrayIcon();
}


//! \brief Destructor
Window::~Window() {
    delete _trayIcon;
}


//! \param[in] event event received in the slot
//! \brief ignore the event for close the main window
//! \brief if the tray icon is visible
void		Window::closeEvent(QCloseEvent * event) {
  if (_trayIcon->trayIconIsVisible()) {
      this->hide();
      event->ignore();
  } else {
    this->show();
  }
}

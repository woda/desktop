//! \file FileSystemWatcher.cpp
//! \brief	implementation of the main,
//! \author Woda Corporation
//! \version 1.2
//! \date 2012-11

#include <QtGui>
#include <QtPlugin>
#include "Window.hh"
#include "Account.hh"

//Q_IMPORT_PLUGIN(qsvg)

void initialize(void) {
    Account::getSingletonPtr();
}

//! \fn int main(int argc, char *argv[])
//! \brief initialize the resources, check if the tray icon is available on the system
//! \brief do not quit if the last window is closed
int main(int argc, char *argv[]) {
  Q_INIT_RESOURCE(woda);
  QApplication app(argc, argv);

  if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
      QMessageBox::critical(0, QObject::tr("Systray"),
			    QObject::tr("I couldn't detect any system tray "
					"on this system."));
      return 1;
    }
  QApplication::setQuitOnLastWindowClosed(false);
  initialize();
  Window window;
  window.show();
  window.closeEvent(new QCloseEvent());
  return app.exec();
}

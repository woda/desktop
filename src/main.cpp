/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#include <QtGui>
#include <QtPlugin>
#include "Window.hh"

//Q_IMPORT_PLUGIN(qsvg)

int main(int argc, char *argv[])
{
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

  Window window;
  window.show();
  window.closeEvent(new QCloseEvent());
  return app.exec();
}

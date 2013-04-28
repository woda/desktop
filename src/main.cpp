//! \file main.cpp
//! \brief implementation of the main
//! \author Woda Corporation
//! \version 1.2
//! \date 2012-11

#include    <QtGui>
#include    <QtPlugin>
#include    "Window.hh"
#include    "Account.hh"
#include    "DataBase.hh"
#include    "Ipc.hh"
#include    "RequestHttpFile.hh"
#include    "ConfFile.hh"

//! \def ERROR
#define     ERROR       -1


//! \brief initialize singleton class, database, account, requestHttp
void        initialize(void) {
    DataBase::getSingletonPtr();
    Account::getSingletonPtr();
    RequestHttpFile::getSingletonPtr();
    ConfFile::getSingletonPtr();
}


//! \brief initialize the resources, check if the tray icon is available on the system
//! \brief do not quit if the last window is closed
int         main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(woda);
    QApplication app(argc, argv);
    Ipc * firstInstance = new Ipc();

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return ERROR;
    }
    QApplication::setQuitOnLastWindowClosed(false);
    if (firstInstance->isFirstInstance()) {
        initialize();
        Window window;
        window.show();
        window.closeEvent(new QCloseEvent());
        return app.exec();
    }
    delete firstInstance;
    return ERROR;
}

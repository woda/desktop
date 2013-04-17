#############################################################################
##
## Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
## All rights reserved.
## Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
##
#############################################################################

TEMPLATE        =       app

TARGET          =       woda

CONFIG          +=      qt #unittest
                        #debug #release #debug_and_release
                        #windows
                        #unix

#DEFINES         +=

INCLUDEPATH     =       include
DEPENDPATH      =       include

QT              +=      network                         \
                        sql                             \
                        gui

HEADERS         +=      Window.hh                       \
                        MyCustomActionPixmap.hh         \
                        MyCustomActionLabel.hh          \
                        Popup.hh                        \
                        ConfFile.hh                     \
                        Singleton.hpp                   \
                        FriendsManagement.hh            \
                        Preferences.hh                  \
                        Fileshare.hh                    \
                        FileSystemWatcher.hh            \
                        RequestHttpAccount.hh           \
                        Account.hh                      \
                        Ipc.hh                          \
                        UserFolderManagement.hh         \
                        WodaSemaphore.hh                \
                        RequestHttpFile.hh              \
                        RequestHttp.hpp                 \
                        DataBase.hh                     \
                        AccountDB.hh                    \
                        FolderDB.hh

SRC             =       src

SOURCES         +=      $$SRC/main.cpp                  \
                        $$SRC/Window.cpp                \
                        $$SRC/MyCustomActionPixmap.cpp  \
                        $$SRC/MyCustomActionLabel.cpp   \
                        $$SRC/Popup.cpp                 \
                        $$SRC/ConfFile.cpp              \
                        $$SRC/FriendsManagement.cpp     \
                        $$SRC/Preferences.cpp           \
                        $$SRC/Fileshare.cpp             \
                        $$SRC/FileSystemWatcher.cpp     \
                        $$SRC/RequestHttpAccount.cpp    \
                        $$SRC/Account.cpp               \
                        $$SRC/Ipc.cpp                   \
                        $$SRC/UserFolderManagement.cpp  \
                        $$SRC/WodaSemaphore.cpp         \
                        $$SRC/RequestHttpFile.cpp       \
                        $$SRC/DataBase.cpp              \
                        $$SRC/AccountDB.cpp             \
                        $$SRC/FolderDB.cpp

FORMS           +=      resources/FriendsManagement.ui  \
                        resources/Preferences.ui        \
                        resources/Fileshare.ui

RESOURCES       +=      woda.qrc

OTHER_FILES     +=      resources/woda.ini		\
                        resources/icone.rc
						
RC_FILE         +=	resources/icone.rc

LIBS            +=      -L"dll"                         \
                        -lqjson

#windows {
#        HEADERS +=      
#
#        SOURCE  +=      
#}

#unix {
#        HEADERS +=      
#
#        SOURCE  +=      
#}

static {
	CONFIG		+=		static
	DEFINES		+=		STATIC
	QTPLUGIN	+=		qsvg
}

unittest {
        CONFIG      +=  qtestlib
        INCLUDEPATH +=  UnitTest
        DEPENDPATH  +=  UnitTest
        HEADERS     +=  AccountTest.hh                  \
                        IpcTest.hh

        SOURCES     -=  $$SRC/main.cpp
        TEST        =   UnitTest
        SOURCES     +=  $$TEST/mainTest.cpp             \
                        $$TEST/AccountTest.cpp          \
                        $$TEST/IpcTest.cpp
}

#############################################################################
##
## Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
## All rights reserved.
## Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
##
#############################################################################

TEMPLATE        =       app

TARGET          =       woda

CONFIG          +=      qt
                        #debug #release #debug_and_release
                        #windows
                        #unix

#DEFINES         +=

INCLUDEPATH     =       include
DEPENDPATH      =       include

QT              +=      network                         \
                        svg                             \
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
                        RequestHttp.hh                  \
                        Account.hh

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
                        $$SRC/RequestHttp.cpp           \
                        $$SRC/Account.cpp

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

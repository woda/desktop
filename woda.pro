#############################################################################
##
## Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
## All rights reserved.
## Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
##
#############################################################################

TEMPLATE        =       app

TARGET          =       woda

CONFIG          +=      qt                              \
                        qjson #unittest
                        #debug #release #debug_and_release
                        #windows
                        #unix

#DEFINES         +=

INCLUDEPATH     +=      Sources/Communication           \
                        Sources/Core                    \
                        Sources/Database                \
                        Sources/GUI                     \
                        Sources/Utils                   \
                        Sources/Modules/Account         \
                        Sources/Modules/Folder

DEPENDPATH      +=      Sources/Communication           \
                        Sources/Core                    \
                        Sources/Database                \
                        Sources/GUI                     \
                        Sources/Utils                   \
                        Sources/Modules/Account         \
                        Sources/Modules/Folder

QT              +=      network                         \
                        sql                             \
                        gui

HEADERS         +=      Window.hh                       \
                        TrayIcon.hh                     \
                        MyCustomActionPixmap.hh         \
                        MyCustomActionLabel.hh          \
                        Popup.hh                        \
                        ConfFile.hh                     \
                        Singleton.hpp                   \
                        Preferences.hh                  \
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

SRC             =       Sources
COMMUNICATION   =       $$SRC/Communication
CORE            =       $$SRC/Core
DATABASE        =       $$SRC/Database
GUI             =       $$SRC/GUI
UTILS           =       $$SRC/Utils
FOLDER          =       $$SRC/Modules/Folder
ACCOUNT         =       $$SRC/Modules/Account

SOURCES         +=      $$CORE/main.cpp                         \
                        $$CORE/Window.cpp                       \
                        $$GUI/TrayIcon.cpp                      \
                        $$GUI/MyCustomActionPixmap.cpp          \
                        $$GUI/MyCustomActionLabel.cpp           \
                        $$GUI/Popup.cpp                         \
                        $$GUI/Preferences.cpp                   \
                        $$FOLDER/FileSystemWatcher.cpp          \
                        $$FOLDER/UserFolderManagement.cpp       \
                        $$ACCOUNT/Account.cpp                   \
                        $$COMMUNICATION/RequestHttpAccount.cpp  \
                        $$COMMUNICATION/RequestHttpFile.cpp     \
                        $$DATABASE/DataBase.cpp                 \
                        $$DATABASE/AccountDB.cpp                \
                        $$DATABASE/FolderDB.cpp                 \
                        $$UTILS/Ipc.cpp                         \
                        $$UTILS/ConfFile.cpp                    \
                        $$UTILS/WodaSemaphore.cpp

FORMS           +=      resources/Forms/Preferences.ui

RESOURCES       +=      resources/woda.qrc

OTHER_FILES     +=      resources/icone.rc
						
RC_FILE         +=	resources/icone.rc

#LIBS            +=      -L"dll"                         \
#                        -lqjson

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
        CONFIG      +=  static
        DEFINES     +=  STATIC
}

unittest {
        CONFIG      +=  qtestlib
        TEST        =   UnitTest
        INCLUDEPATH +=  TEST
        DEPENDPATH  +=  TEST
        HEADERS     +=  AccountTest.hh                  \
                        IpcTest.hh

        SOURCES     -=  $$SRC/main.cpp

        SOURCES     +=  $$TEST/mainTest.cpp             \
                        $$TEST/AccountTest.cpp          \
                        $$TEST/IpcTest.cpp
}


qjson {
        QJSON       =   Sources/Utils/QJson
        INCLUDEPATH +=  $$QJSON
        HEADERS     +=  $$QJSON/json_parser.hh          \
                        $$QJSON/json_scanner.h          \
                        $$QJSON/location.hh             \
                        $$QJSON/parser.h                \
                        $$QJSON/parser_p.h              \
                        $$QJSON/parserrunnable.h        \
                        $$QJSON/position.hh             \
                        $$QJSON/qjson_debug.h           \
                        $$QJSON/qobjecthelper.h         \
                        $$QJSON/serializer.h            \
                        $$QJSON/serializerrunnable.h    \
                        $$QJSON/stack.hh

        SOURCES     +=  $$QJSON/json_parser.cc          \
                        $$QJSON/json_scanner.cpp        \
                        $$QJSON/parser.cpp              \
                        $$QJSON/parserrunnable.cpp      \
                        $$QJSON/qobjecthelper.cpp       \
                        $$QJSON/serializer.cpp          \
                        $$QJSON/serializerrunnable.cpp

        OTHER_FILES +=  $$QJSON/json_parser.yy
}

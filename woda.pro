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
                        qjson                           \
                        crypto
                        #cryptlib #unittest
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

SRC             =       Sources
COMMUNICATION   =       $$SRC/Communication
CORE            =       $$SRC/Core
DATABASE        =       $$SRC/Database
GUI             =       $$SRC/GUI
UTILS           =       $$SRC/Utils
FOLDER          =       $$SRC/Modules/Folder
ACCOUNT         =       $$SRC/Modules/Account

HEADERS         +=      $$CORE/Window.hh                        \
                        $$GUI/TrayIcon.hh                       \
                        $$GUI/MyCustomActionPixmap.hh           \
                        $$GUI/MyCustomActionLabel.hh            \
                        $$GUI/Popup.hh                          \
                        $$GUI/Page.hh                           \
                        $$GUI/IGUI.hh                           \
                        $$GUI/GeneralGUI.hh                     \
                        $$GUI/AccountGUI.hh                     \
                        $$GUI/SyncGUI.hh                        \
                        $$GUI/SignInGUI.hh                      \
                        $$UTILS/ConfFile.hh                     \
                        $$UTILS/Singleton.hpp                   \
                        $$GUI/Preferences.hh                    \
                        $$FOLDER/FileSystemWatcher.hh           \
                        $$COMMUNICATION/RequestHttpAccount.hh   \
                        $$ACCOUNT/Account.hh                    \
                        $$UTILS/Ipc.hh                          \
                        $$UTILS/Hash.hh                         \
                        $$FOLDER/UserFolderManagement.hh        \
                        $$UTILS/WodaSemaphore.hh                \
                        $$COMMUNICATION/RequestHttpFile.hh      \
                        $$COMMUNICATION/RequestHttp.hpp         \
                        $$DATABASE/DataBase.hh                  \
                        $$DATABASE/AccountDB.hh                 \
                        $$DATABASE/FolderDB.hh                  \
                        $$COMMUNICATION/RequestHttpDownloadFile.hh

SOURCES         +=      $$CORE/main.cpp                         \
                        $$CORE/Window.cpp                       \
                        $$GUI/TrayIcon.cpp                      \
                        $$GUI/MyCustomActionPixmap.cpp          \
                        $$GUI/MyCustomActionLabel.cpp           \
                        $$GUI/Popup.cpp                         \
                        $$GUI/Preferences.cpp                   \
                        $$GUI/Page.cpp                          \
                        $$GUI/GeneralGUI.cpp                    \
                        $$GUI/AccountGUI.cpp                    \
                        $$GUI/SyncGUI.cpp                       \
                        $$GUI/SignInGUI.cpp                     \
                        $$FOLDER/FileSystemWatcher.cpp          \
                        $$FOLDER/UserFolderManagement.cpp       \
                        $$ACCOUNT/Account.cpp                   \
                        $$COMMUNICATION/RequestHttpAccount.cpp  \
                        $$COMMUNICATION/RequestHttpFile.cpp     \
                        $$DATABASE/DataBase.cpp                 \
                        $$DATABASE/AccountDB.cpp                \
                        $$DATABASE/FolderDB.cpp                 \
                        $$UTILS/Ipc.cpp                         \
                        $$UTILS/Hash.cpp                        \
                        $$UTILS/ConfFile.cpp                    \
                        $$UTILS/WodaSemaphore.cpp               \
                        $$COMMUNICATION/RequestHttpDownloadFile.cpp

FORMS           +=      resources/Forms/Preferences.ui          \
                        resources/Forms/GeneralGUI.ui           \
                        resources/Forms/AccountGUI.ui           \
                        resources/Forms/SyncGUI.ui              \
                        resources/Forms/SignInGUI.ui

RESOURCES       +=      resources/woda.qrc

OTHER_FILES     +=      resources/icone.rc
						
RC_FILE         +=	resources/icone.rc

#LIBS            +=      -L"dll" ./release/qca-ossl2.dll

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

#cryptlib {
#        CRYPT       =   Sources/Utils/CryptLib
#        INCLUDEPATH +=  $$CRYPT
#        HEADERS     +=  $$CRYPT/crypt.h                 \
#                        $$CRYPT/cryptlib.h              \
#                        $$CRYPT/sha2.h                  \
#                        $$CRYPT/brg_types.h

#        LIBS        +=  ./release/cl32.dll
#}

#cryptopp {
#        CRYPT       =   Sources/Utils/Cryptopp
#        INCLUDEPATH +=  $$CRYPT
#        HEADERS     +=  $$CRYPT/trdlocal.h              \
#                        $$CRYPT/skipjack.h              \
#                        $$CRYPT/sha.h                   \
#                        $$CRYPT/rw.h                    \
#                        $$CRYPT/rsa.h                   \
#                        $$CRYPT/randpool.h              \
#                        $$CRYPT/pssr.h                  \
#                        $$CRYPT/pkcspad.h               \
#                        $$CRYPT/osrng.h                 \
#                        $$CRYPT/nbtheory.h              \
#                        $$CRYPT/mqueue.h                \
#                        $$CRYPT/modes.h                 \
#                        $$CRYPT/hmac.h                  \
#                        $$CRYPT/hex.h                   \
#                        $$CRYPT/gcm.h                   \
#                        $$CRYPT/fips140.h               \
#                        $$CRYPT/files.h                 \
#                        $$CRYPT/ecp.h                   \
#                        $$CRYPT/eccrypto.h              \
#                        $$CRYPT/ec2n.h                  \
#                        $$CRYPT/dsa.h                   \
#                        $$CRYPT/dll.h                   \
#                        $$CRYPT/dh.h                    \
#                        $$CRYPT/des.h                   \
#                        $$CRYPT/cmac.h                  \
#                        $$CRYPT/channels.h              \
#                        $$CRYPT/ccm.h                   \
#                        $$CRYPT/cbcmac.h                \
#                        $$CRYPT/aes.h                   \
#                        $$CRYPT/iterhash.h              \
#                        $$CRYPT/config.h                \
#    Sources/Utils/Cryptopp/zlib.h \
#    Sources/Utils/Cryptopp/zinflate.h \
#    Sources/Utils/Cryptopp/zdeflate.h \
#    Sources/Utils/Cryptopp/xtrcrypt.h \
#    Sources/Utils/Cryptopp/xtr.h \
#    Sources/Utils/Cryptopp/words.h \
#    Sources/Utils/Cryptopp/winpipes.h \
#    Sources/Utils/Cryptopp/whrlpool.h \
#    Sources/Utils/Cryptopp/wake.h \
#    Sources/Utils/Cryptopp/wait.h \
#    Sources/Utils/Cryptopp/vmac.h \
#    Sources/Utils/Cryptopp/validate.h \
#    Sources/Utils/Cryptopp/twofish.h \
#    Sources/Utils/Cryptopp/ttmac.h \
#    Sources/Utils/Cryptopp/trunhash.h \
#    Sources/Utils/Cryptopp/tiger.h \
#    Sources/Utils/Cryptopp/tea.h \
#    Sources/Utils/Cryptopp/strciphr.h \
#    Sources/Utils/Cryptopp/stdcpp.h \
#    Sources/Utils/Cryptopp/square.h \
#    Sources/Utils/Cryptopp/sosemanuk.h \
#    Sources/Utils/Cryptopp/socketft.h \
#    Sources/Utils/Cryptopp/smartptr.h \
#    Sources/Utils/Cryptopp/simple.h \
#    Sources/Utils/Cryptopp/shark.h \
#    Sources/Utils/Cryptopp/shacal2.h \
#    Sources/Utils/Cryptopp/sha3.h \
#    Sources/Utils/Cryptopp/serpentp.h \
#    Sources/Utils/Cryptopp/serpent.h \
#    Sources/Utils/Cryptopp/seed.h \
#    Sources/Utils/Cryptopp/seckey.h \
#    Sources/Utils/Cryptopp/secblock.h \
#    Sources/Utils/Cryptopp/seal.h \
#    Sources/Utils/Cryptopp/salsa.h \
#    Sources/Utils/Cryptopp/safer.h \
#    Sources/Utils/Cryptopp/rng.h \
#    Sources/Utils/Cryptopp/ripemd.h \
#    Sources/Utils/Cryptopp/rijndael.h \
#    Sources/Utils/Cryptopp/resource.h \
#    Sources/Utils/Cryptopp/rc6.h \
#    Sources/Utils/Cryptopp/rc5.h \
#    Sources/Utils/Cryptopp/rc2.h \
#    Sources/Utils/Cryptopp/rabin.h \
#    Sources/Utils/Cryptopp/queue.h \
#    Sources/Utils/Cryptopp/pwdbased.h \
#    Sources/Utils/Cryptopp/pubkey.h \
#    Sources/Utils/Cryptopp/polynomi.h \
#    Sources/Utils/Cryptopp/pch.h \
#    Sources/Utils/Cryptopp/panama.h \
#    Sources/Utils/Cryptopp/oids.h \
#    Sources/Utils/Cryptopp/oaep.h \
#    Sources/Utils/Cryptopp/nr.h \
#    Sources/Utils/Cryptopp/network.h \
#    Sources/Utils/Cryptopp/mqv.h \
#    Sources/Utils/Cryptopp/modexppc.h \
#    Sources/Utils/Cryptopp/modarith.h \
#    Sources/Utils/Cryptopp/misc.h \
#    Sources/Utils/Cryptopp/mdc.h \
#    Sources/Utils/Cryptopp/md5.h \
#    Sources/Utils/Cryptopp/md4.h \
#    Sources/Utils/Cryptopp/md2.h \
#    Sources/Utils/Cryptopp/mars.h \
#    Sources/Utils/Cryptopp/luc.h \
#    Sources/Utils/Cryptopp/lubyrack.h \
#    Sources/Utils/Cryptopp/integer.h \
#    Sources/Utils/Cryptopp/idea.h \
#    Sources/Utils/Cryptopp/ida.h \
#    Sources/Utils/Cryptopp/hrtimer.h \
#    Sources/Utils/Cryptopp/gzip.h \
#    Sources/Utils/Cryptopp/gost.h \
#    Sources/Utils/Cryptopp/gfpcrypt.h \
#    Sources/Utils/Cryptopp/gf256.h \
#    Sources/Utils/Cryptopp/gf2n.h \
#    Sources/Utils/Cryptopp/gf2_32.h \
#    Sources/Utils/Cryptopp/fltrimpl.h \
#    Sources/Utils/Cryptopp/filters.h \
#    Sources/Utils/Cryptopp/factory.h \
#    Sources/Utils/Cryptopp/esign.h \
#    Sources/Utils/Cryptopp/eprecomp.h \
#    Sources/Utils/Cryptopp/emsa2.h \
#    Sources/Utils/Cryptopp/elgamal.h \
#    Sources/Utils/Cryptopp/eax.h \
#    Sources/Utils/Cryptopp/dmac.h \
#    Sources/Utils/Cryptopp/dh2.h \
#    Sources/Utils/Cryptopp/default.h \
#    Sources/Utils/Cryptopp/crc.h \
#    Sources/Utils/Cryptopp/cpu.h \
#    Sources/Utils/Cryptopp/cast.h \
#    Sources/Utils/Cryptopp/camellia.h \
#    Sources/Utils/Cryptopp/blumshub.h \
#    Sources/Utils/Cryptopp/blowfish.h \
#    Sources/Utils/Cryptopp/bench.h \
#    Sources/Utils/Cryptopp/basecode.h \
#    Sources/Utils/Cryptopp/base64.h \
#    Sources/Utils/Cryptopp/base32.h \
#    Sources/Utils/Cryptopp/authenc.h \
#    Sources/Utils/Cryptopp/asn.h \
#    Sources/Utils/Cryptopp/argnames.h \
#    Sources/Utils/Cryptopp/arc4.h \
#    Sources/Utils/Cryptopp/algparam.h \
#    Sources/Utils/Cryptopp/algebra.h \
#    Sources/Utils/Cryptopp/adler32.h \
#    Sources/Utils/Cryptopp/3way.h \
#    Sources/Utils/Cryptopp/cryptlib.h

#        LIBS        +=  ./release/cryptopp.dll
#}

unittest {
        CONFIG      +=  qtestlib
        TEST        =   UnitTest
        INCLUDEPATH +=  UnitTest
        DEPENDPATH  +=  UnitTest
        HEADERS     +=  AccountTest.hh                      \
                        IpcTest.hh                          \
                        UserFolderManagementTest.hh

        SOURCES     -=  $$CORE/main.cpp

        SOURCES     +=  $$TEST/mainTest.cpp                 \
                        $$TEST/AccountTest.cpp              \
                        $$TEST/IpcTest.cpp                  \
                        $$TEST/UserFolderManagementTest.cpp
}

static {
        CONFIG      +=  static
        DEFINES     +=  STATIC
}

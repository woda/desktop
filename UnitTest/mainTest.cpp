#include <QtTest/QtTest>
#include "AccountTest.hh"
#include "IpcTest.hh"
#include "UserFolderManagementTest.hh"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AccountTest account;
    IpcTest ipc;
    UserFolderManagementTest userFolderManagement;

    QStringList testCmd;
    QDir testLogDir;
    testLogDir.mkdir("UnitTest_Results");
    QFile testLogFile("UnitTest_Results/test_log.txt");
    testCmd<<" " << "-silent" << "-o" << testLogFile.fileName();

    QTest::qExec(&account, testCmd);
    QTest::qExec(&ipc, testCmd);
    QTest::qExec(&userFolderManagement, testCmd);

    QFile::remove(testLogFile.fileName());
    testLogDir.rmdir("UnitTest_Results");

    return 0;
}

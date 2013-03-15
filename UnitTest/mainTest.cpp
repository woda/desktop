#include <QtTest/QtTest>
#include "AccountTest.hh"
#include "IpcTest.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AccountTest account;
    IpcTest ipc;

    QTest::qExec(&account);
    QTest::qExec(&ipc);

    return 0;
}

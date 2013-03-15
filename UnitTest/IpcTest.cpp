#include    "IpcTest.hh"

void        IpcTest::initTestCase() {
}

void        IpcTest::firstInstancePass() {
    Ipc * ipc = new Ipc();
    QVERIFY(ipc->isFirstInstance());
    delete ipc;
}

void        IpcTest::instanceTwoCantPass() {
    Ipc * ipcOne = new Ipc();
    QVERIFY(ipcOne->isFirstInstance());
    Ipc * ipcTwo = new Ipc();
    QVERIFY(!ipcTwo->isFirstInstance());
    delete ipcOne;
    delete ipcTwo;
}

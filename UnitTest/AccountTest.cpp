#include    "AccountTest.hh"

void        AccountTest::initTestCase() {
    _account = Account::getSingletonPtr(true);
}

void        AccountTest::cleanupTestCase() {
    Account::del();
}

void        AccountTest::verifyDefaultParameter() {
    QCOMPARE(_account->login(), QString(""));
}

void        AccountTest::connectedToTheServer() {
    _account->connect();
    QVERIFY(_account->isConnected());
}

void        AccountTest::disconnectedToTheServer() {
    _account->connect();
    _account->disconnect();
    QVERIFY(!_account->isConnected());
}

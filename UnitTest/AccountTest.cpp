#include    <QtTest/QtTest>
#include    "Account.hh"

class       AccountTest: public QObject
{
    Q_OBJECT
private slots:
    void    initTestCase();
    void    cleanupTestCase();
    void    verifyDefaultParameter();
    void    connectedToTheServer();
    void    disconnectedToTheServer();

private:
    Account *   _account;
};

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


QTEST_MAIN(AccountTest)
#include "AccountTest.moc"

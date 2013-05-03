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

void        AccountTest::deserializeJson() {
    QByteArray test("{\"login\":\"Superpatate\",\"email\":\"superpatate@gmail.com\",\"first_name\":\"Super\",\"last_name\":\"Patate\"}");
    _account->deserializeJsonAccount(test);
    QCOMPARE(_account->login(), QString("Superpatate"));
    QCOMPARE(_account->email(), QString("superpatate@gmail.com"));
    QCOMPARE(_account->firstName(), QString("Super"));
    QCOMPARE(_account->lastName(), QString("Patate"));
}

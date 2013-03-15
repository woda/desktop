#ifndef             UNITTEST_ACCOUNTTEST_HH__
# define            UNITTEST_ACCOUNTTEST_HH__

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

#endif              // !UNITTEST_ACCOUNTTEST_HH__

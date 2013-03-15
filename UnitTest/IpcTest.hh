#ifndef             UNITTEST_IPCTEST_HH__
# define            UNITTEST_IPCTEST_HH__

#include    <QtTest/QtTest>
#include    "Ipc.hh"

class       IpcTest: public QObject
{
    Q_OBJECT
private slots:
    void    initTestCase();
    void    firstInstancePass();
    void    instanceTwoCantPass();
};

#endif              // !UNITTEST_ACCOUNTTEST_HH__

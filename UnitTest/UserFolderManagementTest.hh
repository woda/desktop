#ifndef             UNITTEST_USERFOLDERMANAGEMENTTEST_HH__
# define            UNITTEST_USERFOLDERMANAGEMENTTEST_HH__

# include   <QtTest/QtTest>
# include   "UserFolderManagement.hh"

# define    FOLDER_NAME     "./UnitTest_42"

class       UserFolderManagementTest: public QObject
{
    Q_OBJECT
private slots:
    void    initTestCase();
    void    cleanupTestCase();
    void    createDirectory();
    void    deserializeJson();
    void    deleteDirectory();


private:
    UserFolderManagement *  _folderManagement;
    QDir *                  _dir;
};

#endif              // !UNITTEST_USERFOLDERMANAGEMENTTEST_HH__

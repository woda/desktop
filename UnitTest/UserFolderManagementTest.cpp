#include    "UserFolderManagementTest.hh"

#include "iostream"

void        UserFolderManagementTest::initTestCase() {
    _dir = new QDir(QString(FOLDER_NAME));
    _folderManagement = UserFolderManagement::getSingletonPtr(_dir->absolutePath());
}

void        UserFolderManagementTest::cleanupTestCase() {
    //uncomment si wodaSemaphore est un mock passe en param du contructeur
    //UserFolderManagement::del();
    delete _dir;
}

void        UserFolderManagementTest::createDirectory() {
    QString folderName(_dir->absolutePath());
    _folderManagement->createDirectory(folderName);
    QVERIFY(_folderManagement->checkDirectoryExist(folderName));
}

void        UserFolderManagementTest::deserializeJson() {
    QByteArray test("[\n{\n\"name\": \"Folder1\",\n\"full_path\": \".\",\n\"modification_time\": \"01/01/2013 23:42:42\",\n\"files\": [ \n{\n\"name\": \"File1.txt\",\n\"modification_time\": \"01/01/2013 23:42:42\" \n},\n{\n\"name\": \"File2.txt\",\n\"modification_time\": \"01/01/2013 23:42:42\" \n}\n]\n}, \n{\n\"name\": \"Folder2\",\n\"full_path\" : \"./Folder1\",\n\"modification_time\" : \"01/01/2013 23:42:42\",\n\"files\": [ \n{\n\"name\": \"File3.txt\",\n\"modification_time\": \"01/01/2013 23:42:42\" \n}\n]\n}\n]\n");
    _folderManagement->deserializeJsonAccount(test);

    QString folder1(_dir->absolutePath());
    folder1.append("/Folder1");
    QVERIFY(_folderManagement->checkDirectoryExist(folder1));

    QString folder2(_dir->absolutePath());
    folder1.append("/Folder1/Folder2");
    QVERIFY(_folderManagement->checkDirectoryExist(folder2));

    QString file1(_dir->absolutePath());
    file1.append("/Folder1/File1.txt");
    QVERIFY(_folderManagement->checkFileExist(file1));

    QString file2(_dir->absolutePath());
    file2.append("/Folder1/File2.txt");
    QVERIFY(_folderManagement->checkFileExist(file2));

    QString file3(_dir->absolutePath());
    file3.append("/Folder1/Folder2/File3.txt");
    QVERIFY(_folderManagement->checkFileExist(file3));
}

//void        UserFolderManagementTest::changeDirectory() {
//    //mettre le FileSystemWatcher avec un mock
//}

void        UserFolderManagementTest::deleteDirectory() {
    QString folderName(_dir->absolutePath());

    _folderManagement->deleteDirectory();

    QVERIFY(!_folderManagement->checkDirectoryExist(folderName));

    QCOMPARE(_folderManagement->getCurrentDirectory(), QString(""));
}


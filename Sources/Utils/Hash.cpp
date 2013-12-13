//! \file Hash.cpp
//! \brief implementation of the header Hash
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-06


#include	"Hash.hh"
#include    <QtCrypto>
#include    <QString>
#include    <QFile>
#include    <QTime>
#include    <fstream>
#include    <QTextCodec>


//! \brief Constructor
Hash::Hash() {
}


//! \brief Destructor
Hash::~Hash() {
}


QByteArray      Hash::getHash(const QString & filePath, int size) {
    QFile file(filePath);
    QByteArray str = SHA256_ERROR_HASH;
//    if (filePath.mid(filePath.lastIndexOf('/') + 1) == QString("New Text Document.txt"))
//        return str;
    if (!file.open(QIODevice::ReadOnly))
        return str;

    char * fileContent = new char[size];
    file.read(fileContent, size);
    file.close();

    QByteArray fileContentByteArray(fileContent);
    if (fileContentByteArray.length() == 0) {
        return str;
    }

    str = QByteArray(hash(fileContentByteArray).toStdString().c_str());

//    // TO DO : refaire avec 5 mega
//    QByteArray fileContent = "";
//    while (!file.atEnd()) {
//        QByteArray line = file.readLine();
//        fileContent.append(line).append("\n");
//    }
//    file.close();




//    str = QCryptographicHash::hash(fileContent, QCryptographicHash::Sha1);

//    QString str2 = "c13858e5a13de1500e54a1c85f0132e688e131b93d7bf9a00192281e6c5";
//    QTime midnight(0, 0, 0);
//    qsrand(midnight.secsTo(QTime::currentTime()));
//    str2.append(qrand() % 10 + '0');
//    str2.append(qrand() % 10 + '0');
//    str2.append(qrand() % 10 + '0');
//    str2.append(qrand() % 10 + '0');
//    str2.append(qrand() % 10 + '0');

//    str = str2.toUtf8();

    return str;
}

#include    <iostream>


QString         Hash::hash(QByteArray & fileContent) {
    if(!QCA::isSupported("sha256")) {
        std::cout << "sha256 not supported!" << std::endl;
    } else {
        // this shows the incremental approach.
        // Otherwise - QString result = QCA::Hash("sha1").hashToString(arg);

        QCA::SecureArray part(fileContent);
        //QCA::SecureArray part2(fileContent2);

        // create the required object.
        QCA::Hash hashObject("sha256");

        // we split it into two parts to show incremental update
        hashObject.update(part);
        //hashObject.update(part2);

        // no more updates after calling final.
        QCA::SecureArray resultArray = hashObject.final();

        // convert the result into printable hexadecimal.
        QString result = QCA::arrayToHex(resultArray.toByteArray());
        std::cout << "sha256 = " << result.toStdString() << std::endl;
        return result;
    }
    return QString(SHA256_ERROR_HASH);
}

QString         Hash::getLength(const QString & filePath, int size) {
//    QFile file(filePath);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return QString("0");

//    QByteArray fileContent = "";
//    while (!file.atEnd()) {
//        QByteArray line = file.readLine();
//        fileContent.append(line);
//    }
//    file.close();
//    return QString::number(fileContent.length());


    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return 0;

    return QString::number(file.size());

//    char * fileContent = new char[size];
//    file.read(fileContent, size);
//    file.close();

//    QByteArray fileContentByteArray(fileContent);
//    return QString::number(fileContentByteArray.length());
}

QByteArray      Hash::getContent(const QString & filePath, int size) {
//    QFile file(filePath);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return 0;

//    QByteArray fileContent = "";
//    while (!file.atEnd()) {
//        QByteArray line = file.readLine();
//        fileContent.append(line);
//    }
//    file.close();
//    return fileContent;


//    QFile file(filePath);
//    if (!file.open(QIODevice::ReadOnly))
//        return 0;

//    QByteArray fileContent = file.re;

//    return fileContent;


//    char * fileContent = new char[size];
//    file.read(fileContent, size);
//    file.close();

//    QByteArray fileContentByteArray(fileContent);
//    fileContentByteArray = fileContentByteArray.left(size);
//    return fileContentByteArray;


    std::ifstream in(filePath.toStdString().c_str(), std::ios::in | std::ios::binary);
    if (!in) {
        return 0;
      }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    QByteArray array(contents.c_str(), contents.length());
    return array;
}

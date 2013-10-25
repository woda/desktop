//! \file Hash.hh
//! \brief header Hash : for hash function
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-03

#ifndef             INCLUDE_HASH_HH__
# define            INCLUDE_HASH_HH__

# include           <QString>

# define            SHA256_ERROR_HASH   "c13858e5a13de1500e54a1c85f0132e688e131b93d7bf9a00192281e6c555fd0"

//! \class Hash Hash.hh
//! \brief class for hash function
class               Hash {
 public:
    Hash();
    ~Hash();
    static QByteArray      getHash(const QString & filePath, int size = 5242880);
    static QString         getLength(const QString & filePath, int size = 5242880);
    static QByteArray      getContent(const QString & filePath, int size = 5242880);
    static QString         hash(QByteArray & fileContent);
};

#endif              // !INCLUDE_IPC_HH__

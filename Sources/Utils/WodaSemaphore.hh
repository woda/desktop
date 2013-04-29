//! \file WodaSemaphore.hh
//! \brief	implementation of the interface of Semaphore
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04

#ifndef         INCLUDE_WODASEMAPHORE_HH__
# define        INCLUDE_WODASEMAPHORE_HH__

# include       <map>
# include       <QString>
# include       <QSemaphore>

//! \def DEFAULTNAMEINSTANCE
# define        DEFAULTNAMEINSTANCE     "-42"

//! \class WodaSemaphore WodaSemaphore.hh
//! \brief map of semaphore
class           WodaSemaphore : public QSemaphore {
    WodaSemaphore(int n = 1);
    ~WodaSemaphore();

    static std::map<QString, WodaSemaphore *> * _singleton;
 public:
    static WodaSemaphore *  getInstance(QString str = QString(DEFAULTNAMEINSTANCE));
    static void         createSemaphore(QString & str);
    static void         deleteOneInstance(QString & str);
    static void         kill(void);
};

#endif          // !INCLUDE_WODASEMAPHORE_HH__

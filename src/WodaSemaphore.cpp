//! \file WodaSemaphore.cpp
//! \brief	implementation of the interface of Semaphore
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-04


#include    "WodaSemaphore.hh"


std::map<QString, WodaSemaphore *> * WodaSemaphore::_singleton = NULL;


//! \param[in] n number of semaphore
//! \brief Constructor
WodaSemaphore::WodaSemaphore(int n)
    :   QSemaphore(n) {
}


//! \brief Destructor, kill all semaphore
WodaSemaphore::~WodaSemaphore() {
    this->kill();
}


//! \param[in] str QString instance name of the semaphore
//! \brief search the semaphore with the instance name, and return it
//! \return return the semaphore if str where find, otherwise return NULL
WodaSemaphore * WodaSemaphore::getInstance(QString str) {
    if (_singleton == NULL)
        _singleton = new std::map<QString, WodaSemaphore *>();
    if (_singleton->find(str) == _singleton->end())
        return NULL;
    return (*_singleton)[str];
}


//! \param[in] str QString instance name of the semaphore
//! \brief create a semaphore with str for instance name
void        WodaSemaphore::createSemaphore(QString & str) {
    WodaSemaphore * sem = new WodaSemaphore();
    _singleton->insert(std::pair<QString, WodaSemaphore *>(str, sem));
}


//! \param[in] str QString instance name of the semaphore
//! \brief delete the semaphore with str for instance name
void        WodaSemaphore::deleteOneInstance(QString & str) {
    std::map<QString, WodaSemaphore *>::iterator it = _singleton->find(str);
    if (it == _singleton->end())
        return;
    delete it->second;
    _singleton->erase(it);
}


//! \param[in] str QString instance name of the semaphore
//! \brief delete all the semaphore stored
void        WodaSemaphore::kill(void) {
    for (std::map<QString, WodaSemaphore *>::iterator it = _singleton->begin();
         it != _singleton->end(); ++it) {
        delete it->second;
    }
    delete _singleton;
    _singleton = NULL;
}

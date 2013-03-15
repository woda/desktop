//! \file Ipc.cpp
//! \brief implementation of the interface for Inter Processus Communication
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-03


#include	"Ipc.hh"
#include    <QtNetwork>
#include    <QString>


//! \fn Ipc::Ipc(QWidget * parent)
//! \brief Constructor
Ipc::Ipc(QWidget * parent)
    : QWidget(parent), _server(0), _firstInstance(false)
{
    _socket = new QLocalSocket(this);
    connect(_socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(processAnError(QLocalSocket::LocalSocketError)));
    this->requestNewWodaInstance();
}


//! \fn Ipc::~Ipc()
//! \brief Destructor
Ipc::~Ipc() {
}


//! \fn Ipc::requestNewWodaInstance()
//! \brief check if a new instance is possible
void    Ipc::requestNewWodaInstance() {
    _socket->abort();
    _socket->connectToServer(QString(IPC_INSTANCE));
}


//! \fn Ipc::processAnError(QLocalSocket::LocalSocketError socketError)
//! \brief slots if error occured, it is the first instance and a server is create
void    Ipc::processAnError(QLocalSocket::LocalSocketError socketError) {
    if (socketError == QLocalSocket::ServerNotFoundError) {
        _firstInstance = true;
        _server = new QLocalServer(this);
        if (!_server->listen(IPC_INSTANCE)) {
            close();
            return;
        }
    }
}


//! \fn Ipc::isFirstInstance()
//! \brief if is the first instance of woda return true
bool    Ipc::isFirstInstance() {
    return _firstInstance;
}

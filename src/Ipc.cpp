//! \file Ipc.cpp
//! \brief implementation of the header Ipc for Inter Processus Communication
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-03


#include	"Ipc.hh"
#include    <QtNetwork>
#include    <QString>


//! \param[in] parent QObject parent or nothing
//! \brief Constructor
//! initialize the local socket and connect the signal to a slot
Ipc::Ipc(QWidget * parent)
    : QWidget(parent), _server(0), _firstInstance(false)
{
    _socket = new QLocalSocket(this);
    connect(_socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(processAnError(QLocalSocket::LocalSocketError)));
    this->requestNewWodaInstance();
}


//! \brief Destructor
Ipc::~Ipc() {
}


//! \brief check if a new instance is possible
void    Ipc::requestNewWodaInstance() {
    _socket->abort();
    _socket->connectToServer(QString(IPC_INSTANCE));
}


//! \param[in] socketError the error receive
//! \brief slots if error occured
//! If error occured, it is the first instance and a server is create
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


//! \brief if is the first instance of woda return true
//! \return true if it is the first instance
bool    Ipc::isFirstInstance() {
    return _firstInstance;
}

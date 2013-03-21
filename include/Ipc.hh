//! \file Ipc.hh
//! \brief header IPC : Inter Processus Communication
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-03

#ifndef             INCLUDE_IPC_HH__
# define            INCLUDE_IPC_HH__

# include           <QWidget>

# include           <QLocalSocket>
# include           <QLocalServer>

//! \def IPC_INSTANCE
# define            IPC_INSTANCE       "woda_client"

//! \class Ipc Ipc.hh
//! \brief class for Inter Processus Communication
//! if a second program is launched, it will automatically be closed.
class               Ipc : public QWidget {
 Q_OBJECT

 public:
    Ipc(QWidget * parent = 0);
    ~Ipc();
    bool            isFirstInstance();

 private:
    void            requestNewWodaInstance();

 private slots:
    void            processAnError(QLocalSocket::LocalSocketError socketError);

 private:
    QLocalSocket *  _socket;
    QLocalServer *  _server;
    bool            _firstInstance;
};

#endif              // !INCLUDE_IPC_HH__

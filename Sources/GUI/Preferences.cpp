//! \file Preferences.cpp
//! \brief	implementation of the header Preferences : GUI for preference
//! \author Woda Corporation
//! \version 1.3
//! \date 2013-01

#include    "Preferences.hh"
#include    "Account.hh"
#include    "ConfFile.hh"
#include    "AccountDB.hh"
#include    "FileSystemWatcher.hh"
#include    "RequestHttpAccount.hh"
#include    "UserFolderManagement.hh"

#include    <QFileDialog>


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! \brief initialize the Ui, corner preference, directory, account
Preferences::Preferences(QWidget *parent)
    : QWidget(parent), _connected(false) {
    setupUi(this);

    QObject::connect(buttonGroupNotification, SIGNAL(buttonClicked(int)),
                     this, SLOT(notificationPositionClick(int)));
    buttonGroupNotification->setId(radioButtonBottomLeft, BOTTOM_LEFT);
    buttonGroupNotification->setId(radioButtonBottomRight,BOTTOM_RIGHT);
    buttonGroupNotification->setId(radioButtonTopLeft,    TOP_LEFT);
    buttonGroupNotification->setId(radioButtonTopRight,   TOP_RIGHT);

    labelError->hide();
    buttonDisconnect->hide();

    this->initCorner();
    this->initDirectory();
    this->initAccount();

    _timer = new QTimer(this);
    _timer->setInterval(TIMER_REFRESH);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->start(TIMER_REFRESH);
}


//! \brief Destructor
Preferences::~Preferences() {
}


//! \brief update Preference
void    Preferences::update(void) {
    this->updateAccount();
    this->updateGeneral();
}


//! \brief update account information
void    Preferences::updateGeneral(void) {
    WodaFolder_input->setText(UserFolderManagement::getSingletonPtr()->getCurrentDirectory());
}


//! \brief update account information
void    Preferences::updateAccount(void) {
    Account * userAccount = Account::getSingletonPtr();
    if (_connected && userAccount->isConnected()) {
        return;
    }
    if (userAccount->isConnected()) {
        lineEditEmail->setText(userAccount->email());
        QString hello("hello ");
        hello.append(userAccount->firstName()).append(" ").append(userAccount->lastName());
        labelHello->setText(hello);
        this->isConnected();
        return;
    } else if (userAccount->isHttpError()) {
        labelError->setText("Error communicating with the server");
    } else if (userAccount->isServerError()) {
        labelError->setText(userAccount->textServerError());
    }
    this->isDisconnected();
}


//! \brief hide labels account information if not connected
void    Preferences::isDisconnected(void) {
    labelHello->hide();
    labelEmail->hide();
    labelConfirmPassword->hide();
    labelNewPassword->hide();
    lineEditConfirmPassword->hide();
    lineEditNewPassword->hide();
    lineEditEmail->hide();
    buttonChange->hide();
    buttonConnect->show();
    buttonDisconnect->hide();
    _connected = false;
}


//! \brief show labels account information if connected
void    Preferences::isConnected(void) {
    labelHello->show();
    labelEmail->show();
    labelConfirmPassword->show();
    labelNewPassword->show();
    lineEditConfirmPassword->show();
    lineEditNewPassword->show();
    lineEditEmail->show();
    buttonChange->show();
    buttonConnect->hide();
    buttonDisconnect->show();
    _connected = true;
}


//! \brief initialize the corner where the popup pop
void    Preferences::initCorner(void) {
    // check if corner is set in the ini file
    // if present set the radio button to the value in the ini file or database
    int corner = Account::getSingletonPtr()->corner();
    if (!corner) {
        radioButtonBottomRight->setChecked(true);
    } else {
        buttonGroupNotification->button(corner)->setChecked(true);
    }
}


//! \brief initialize the directory path for woda
void    Preferences::initDirectory(void) {
    // check if the directory is set in the ini file
    // if present set the QLineEdit to the value in the ini file
    // TO DO
    QString dir = ConfFile::getSingletonPtr()->getValue(DIRECTORY).toString();
    if (dir != QString(""))
        WodaFolder_input->setText(dir);
}


//! \brief initialize the lineEdit login and password
void    Preferences::initAccount(void) {
    lineEditLogin->setText(Account::getSingletonPtr()->login());
    lineEditPassword->setText(Account::getSingletonPtr()->password());
}


//! \brief checkbox for limited the download
void    Preferences::on_checklimitdl_clicked() {
    if (checklimitdl->isChecked()) {
        input_limitdl->setEnabled(true);
    } else {
        input_limitdl->setEnabled(false);
    }
}


//! \brief checkbox for limited the upload
void    Preferences::on_checklimitup_clicked() {
    if (checklimitup->isChecked()) {
        input_limitup->setEnabled(true);
    } else {
        input_limitup->setEnabled(false);
    }
}


//! \brief button to select a directory for woda
void    Preferences::on_browse_button_clicked() {
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            UserFolderManagement::getSingletonPtr()->getCurrentDirectory(),
                                            QFileDialog::ShowDirsOnly |
                                            QFileDialog::DontResolveSymlinks);
    if (dir.isEmpty()) {
        return;
    }
    WodaFolder_input->setText(dir);
    UserFolderManagement::getSingletonPtr()->changeDirectory(dir);
}


//! \param[in] id id of the radio button
//! \brief radio button for the popup corner
void    Preferences::notificationPositionClick(int id) {
    Account::getSingletonPtr()->setCorner(id);
}


//! \brief Button to click to connect to the server with the username and pass
void    Preferences::buttonConnectAccount() {
    if (lineEditLogin->text().isEmpty() || lineEditPassword->text().isEmpty()) {
        labelError->setText("Please enter login / password");
        labelError->show();
    } else {
        labelError->hide();
        QString login(lineEditLogin->text());
        QString password(lineEditPassword->text());
        Account::getSingletonPtr()->setLogin(login);
        Account::getSingletonPtr()->setPassword(password);
        RequestHttpAccount::getSingletonPtr()->loginToServer(login, password);
    }
}


//! \brief Button to click to disconnect to the server
void    Preferences::buttonDisconnectAccount() {
    UserFolderManagement::getSingletonPtr()->deleteDirectory();
    RequestHttpAccount::getSingletonPtr()->logoutToServer();
}


//! \brief Button to click to connect to the server with the username and pass
void    Preferences::buttonChangeAccount() {
    if (lineEditEmail->text().isEmpty()) {
        labelError->setText(QString("Please Enter an email"));
    }
    if (!lineEditNewPassword->text().isEmpty() &&
        lineEditNewPassword->text() == lineEditConfirmPassword->text()) {
        QString email(lineEditEmail->text());
        QString password(lineEditNewPassword->text());
        RequestHttpAccount::getSingletonPtr()->sendUpdate(email, password);
    } else {
        QString email(lineEditEmail->text());
        QString password(Account::getSingletonPtr()->password());
        RequestHttpAccount::getSingletonPtr()->sendUpdate(email, password);
    }
}


void    Preferences::buttonTest() {
    if (!lineEditLogin->text().isEmpty()) {
        QString login(lineEditLogin->text());
        RequestHttpAccount::getSingletonPtr()->sendCreate(login);
    }
}

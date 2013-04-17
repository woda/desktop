//! \file Preferences.cpp
//! \brief	implementation of the header Preferences : GUI for preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include    "Preferences.hh"
#include    "ui_Preferences.h"
#include    "ConfFile.hh"
#include    "FileSystemWatcher.hh"
#include    "RequestHttpAccount.hh"
#include    "Account.hh"
#include    "UserFolderManagement.hh"


//! \param[in] parent Qobject parent or nothing
//! \brief Constructor
//! initialize the Ui, corner preference, directory, account
Preferences::Preferences(QWidget *parent)
    : QDialog(parent), ui(new Ui::Preferences), _connected(false) {
    ui->setupUi(this);
    QObject::connect(ui->buttonGroupNotification, SIGNAL(buttonClicked(int)),
                     this, SLOT(notificationPositionClick(int)));
    ui->buttonGroupNotification->setId(ui->radioButtonBottomLeft, BOTTOM_LEFT);
    ui->buttonGroupNotification->setId(ui->radioButtonBottomRight,BOTTOM_RIGHT);
    ui->buttonGroupNotification->setId(ui->radioButtonTopLeft,    TOP_LEFT);
    ui->buttonGroupNotification->setId(ui->radioButtonTopRight,   TOP_RIGHT);
    ui->labelError->hide();
    ui->buttonDisconnect->hide();

    this->initCorner();
    this->initDirectory();
    this->initAccount();

    _timer = new QTimer(this);
    _timer->setInterval(TIMER_REFRESH);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->start(TIMER_REFRESH);
}


//! \brief Destructor
//! delete the Ui
Preferences::~Preferences() {
    delete ui;
}


//! \brief update Preference
void    Preferences::update(void) {
    this->updateAccount();
    this->updateGeneral();
}


//! \brief update account information
void    Preferences::updateGeneral(void) {
    ui->WodaFolder_input->setText(UserFolderManagement::getSingletonPtr()->getCurrentDirectory());
}


//! \brief update account information
void    Preferences::updateAccount(void) {
    Account * account = Account::getSingletonPtr();
    if (_connected && account->isConnected()) {
        return;
    }
    if (account->isConnected()) {
        ui->lineEditEmail->setText(account->email());
        QString hello("hello ");
        hello.append(account->firstName()).append(" ").append(account->lastName());
        ui->labelHello->setText(hello);
        this->isConnected();
        return;
    } else if (account->isHttpError()) {
        ui->labelError->setText("Error communicating with the server");
    } else if (account->isServerError()) {
        ui->labelError->setText(account->textServerError());
    }
    this->isDisconnected();
}


//! \brief hide labels account information if not connected
void    Preferences::isDisconnected(void) {
    ui->labelHello->hide();
    ui->labelEmail->hide();
    ui->labelConfirmPassword->hide();
    ui->labelNewPassword->hide();
    ui->lineEditConfirmPassword->hide();
    ui->lineEditNewPassword->hide();
    ui->lineEditEmail->hide();
    ui->buttonChange->hide();
    ui->buttonConnect->show();
    ui->buttonDisconnect->hide();
    _connected = false;
}


//! \brief show labels account information if connected
void    Preferences::isConnected(void) {
    ui->labelHello->show();
    ui->labelEmail->show();
    ui->labelConfirmPassword->show();
    ui->labelNewPassword->show();
    ui->lineEditConfirmPassword->show();
    ui->lineEditNewPassword->show();
    ui->lineEditEmail->show();
    ui->buttonChange->show();
    ui->buttonConnect->hide();
    ui->buttonDisconnect->show();
    _connected = true;
}


//! \brief initialize the corner where the popup pop
void    Preferences::initCorner(void) {
    // check if corner is set in the ini file
    // if present set the radio button to the value in the ini file
    int corner = ConfFile::getSingletonPtr()->getValue(CORNER).toInt();
    if (!corner) {
        ui->radioButtonBottomRight->setChecked(true);
        ConfFile::getSingletonPtr()->setValue(CORNER, QVariant(corner));
    } else {
        ui->buttonGroupNotification->button(corner)->setChecked(true);
    }
}


//! \brief initialize the directory path for woda
void    Preferences::initDirectory(void) {
    // check if the directory is set in the ini file
    // if present set the QLineEdit to the value in the ini file
    QString dir = ConfFile::getSingletonPtr()->getValue(DIRECTORY).toString();
    if (dir != QString(""))
        ui->WodaFolder_input->setText(dir);
}


//! \brief initialize the lineEdit login and password
void    Preferences::initAccount(void) {
    ui->lineEditLogin->setText(Account::getSingletonPtr()->login());
    ui->lineEditPassword->setText(Account::getSingletonPtr()->password());
}


//! \brief checkbox for limited the download
void    Preferences::on_checklimitdl_clicked() {
    if (ui->checklimitdl->isChecked()) {
        ui->input_limitdl->setEnabled(true);
    } else {
        ui->input_limitdl->setEnabled(false);
    }
}


//! \brief checkbox for limited the upload
void    Preferences::on_checklimitup_clicked() {
    if (ui->checklimitup->isChecked())
        ui->input_limitup->setEnabled(true);
    else
        ui->input_limitup->setEnabled(false);
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
    ui->WodaFolder_input->setText(dir);
    UserFolderManagement::getSingletonPtr()->changeDirectory(dir);
}


//! \param[in] id id of the radio button
//! \brief radio button for the popup corner
void    Preferences::notificationPositionClick(int id) {
    ConfFile::getSingletonPtr()->setValue(CORNER, QVariant(id));
}


//! \brief Button to click to connect to the server with the username and pass
void    Preferences::buttonConnectAccount() {
    if (ui->lineEditLogin->text().isEmpty() || ui->lineEditPassword->text().isEmpty()) {
        ui->labelError->setText("Please enter login / password");
        ui->labelError->show();
    }
    else {
        ui->labelError->hide();
        QString login(ui->lineEditLogin->text());
        QString password(ui->lineEditPassword->text());
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
    if (ui->lineEditEmail->text().isEmpty()) {
        ui->labelError->setText(QString("Please Enter an email"));
    }
    if (!ui->lineEditNewPassword->text().isEmpty() &&
        ui->lineEditNewPassword->text() == ui->lineEditConfirmPassword->text()) {
        QString email(ui->lineEditEmail->text());
        QString password(ui->lineEditNewPassword->text());
        RequestHttpAccount::getSingletonPtr()->sendUpdate(email, password);
    } else {
        QString email(ui->lineEditEmail->text());
        QString password(Account::getSingletonPtr()->password());
        RequestHttpAccount::getSingletonPtr()->sendUpdate(email, password);
    }
}


void    Preferences::buttonTest() {
    if (!ui->lineEditLogin->text().isEmpty()) {
        QString login(ui->lineEditLogin->text());
        RequestHttpAccount::getSingletonPtr()->sendCreate(login);
    }
}

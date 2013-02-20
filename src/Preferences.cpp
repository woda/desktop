//! \file ConfFile.cpp
//! \brief	implementation of the interface of GUI for preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include    "Preferences.hh"
#include    "ui_Preferences.h"
#include    "ConfFile.hh"
#include    "FileSystemWatcher.hh"
#include    "RequestHttp.hh"
#include    "Account.hh"

//! \fn Preferences::Preferences(QWidget *parent)
//! \param[in] parent Qobject parent or nothing
//! \brief Constructor, initialize the tray icon
Preferences::Preferences(QWidget *parent)
 : QDialog(parent), ui(new Ui::Preferences) {
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
    _timer->setInterval(1000);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateAccount()));
    _timer->start(1000);
}


//! \fn Preferences::~Preferences()
//! \brief Destructor
Preferences::~Preferences() {
    delete ui;
}


void    Preferences::updateAccount(void) {
    Account * account = Account::getSingletonPtr();
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
}


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
}

//! \fn Preferences::initCorner(void)
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


//! \fn Preferences::initDirectory(void)
//! \brief initialize the directory path for woda
void    Preferences::initDirectory(void) {
    // check if the directory is set in the ini file
    // if present set the QLineEdit to the value in the ini file
    QString dir = ConfFile::getSingletonPtr()->getValue(DIRECTORY).toString();
    if (dir != QString(""))
        ui->WodaFolder_input->setText(dir);
}


//! \fn Preferences::initAccount(void)
//! \brief initialize the lineEdit login and password
void    Preferences::initAccount(void) {
    ui->lineEditLogin->setText(Account::getSingletonPtr()->login());
    ui->lineEditPassword->setText(Account::getSingletonPtr()->password());
}


//! \fn Preferences::on_checklimitdl_clicked(void)
//! \brief checkbox for limited the download
void    Preferences::on_checklimitdl_clicked() {
    if (ui->checklimitdl->isChecked())
        ui->input_limitdl->setEnabled(true);
    else
        ui->input_limitdl->setEnabled(false);
}


//! \fn Preferences::on_checklimitup_clicked(void)
//! \brief checkbox for limited the upload
void    Preferences::on_checklimitup_clicked() {
    if (ui->checklimitup->isChecked())
        ui->input_limitup->setEnabled(true);
    else
        ui->input_limitup->setEnabled(false);
}


//! \fn Preferences::on_browse_button_clicked(void)
//! \brief button to select a directory for woda
void    Preferences::on_browse_button_clicked() {
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            "/home",
                                            QFileDialog::ShowDirsOnly |
                                            QFileDialog::DontResolveSymlinks);
    ui->WodaFolder_input->setText(dir);
    ConfFile::getSingletonPtr()->setValue(DIRECTORY, QVariant(dir));
    FileSystemWatcher * fsWatcher = FileSystemWatcher::getSingletonPtr();
    if (dir != QString("")) {
        QString tmp("");
        fsWatcher->addDirectory(tmp);
        fsWatcher->addDirectory(dir);
    }
}


//! \fn Preferences::notificationPositionClick(int id)
//! \param[in] id id of the radio button
//! \brief radio button for the popup corner
void    Preferences::notificationPositionClick(int id) {
    ConfFile::getSingletonPtr()->setValue(CORNER, QVariant(id));
}

//! \fn Preferences::buttonConnectAccount()
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
        RequestHttp::getSingletonPtr()->loginToServer(login, password);
    }
}

//! \fn Preferences::buttonDisconnectAccount()
//! \brief Button to click to connect to the server with the username and pass
void    Preferences::buttonDisconnectAccount() {
    RequestHttp::getSingletonPtr()->logoutToServer();
}

//! \fn Preferences::buttonConnectAccount()
//! \brief Button to click to connect to the server with the username and pass
void    Preferences::buttonChangeAccount() {
    if (ui->lineEditEmail->text().isEmpty()) {
        ui->labelError->setText(QString("Please Enter an email"));
    }
    if (!ui->lineEditNewPassword->text().isEmpty() &&
        ui->lineEditNewPassword->text() == ui->lineEditConfirmPassword->text()) {
        QString email(ui->lineEditEmail->text());
        QString password(ui->lineEditNewPassword->text());
        RequestHttp::getSingletonPtr()->sendUpdate(email, password);
    } else {
        QString email(ui->lineEditEmail->text());
        QString password(Account::getSingletonPtr()->password());
        RequestHttp::getSingletonPtr()->sendUpdate(email, password);
    }
}


void    Preferences::buttonTest() {
    if (!ui->lineEditLogin->text().isEmpty()) {
        QString login(ui->lineEditLogin->text());
        RequestHttp::getSingletonPtr()->sendCreate(login);
    }
}

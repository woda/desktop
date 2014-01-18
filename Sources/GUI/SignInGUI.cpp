//! \file SignInGUI.cpp
//! \brief	implementation of the header SignInGUI for display the Sign In Page
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#include	"SignInGUI.hh"
#include	"Page.hh"
#include    "Account.hh"
#include    "UserFolderManagement.hh"
#include    "RequestHttpAccount.hh"
#include    "ConfFile.hh"


SignInGUI::SignInGUI(QStackedWidget * stack, QWidget * parent)
    : QWidget(parent), _stack(stack) {
    setupUi(this);
    this->labelTextError->hide();
    _timer = new QTimer(this);
    _timer->setInterval(TIMER_REFRESH);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateUserAccount()));
}


SignInGUI::~SignInGUI() {
}


void	SignInGUI::update() {
    if (Account::getSingletonPtr()->isConnected()) {
        _stack->setCurrentIndex(Page::GENERAL_PAGE);
    }
    _timer->start(TIMER_REFRESH);
}

#include <iostream>
void	SignInGUI::updateUserAccount(void) {
    if (Account::getSingletonPtr()->isConnected()) {
        _timer->stop();
        this->labelTextError->hide();
        if (UserFolderManagement::getSingletonPtr()->getCurrentDirectory().isEmpty()) {
            this->setUserFolder();
        }
        _stack->setCurrentIndex(Page::GENERAL_PAGE);
    } else if (Account::getSingletonPtr()->isServerError()) {
        this->labelTextError->setText(Account::getSingletonPtr()->textServerError());
        this->labelTextError->show();
    }
    std::cout << Account::getSingletonPtr()->textServerError().toStdString() << std::endl;
}


void	SignInGUI::closePreference(void) {
    _stack->setCurrentIndex(Page::DESTROY_PAGE);
}


void	SignInGUI::btnWebApp(void) {
    QDesktopServices::openUrl(QUrl("http://kobhqlt.fr/wodajs/uptodate/#/"));
}

//! \brief Button to click to connect to the server
void    SignInGUI::btnSignIn() {
    QString login(lineEditUsername->text());
    QString password(lineEditPassword->text());
    Account::getSingletonPtr()->setLogin(login);
    Account::getSingletonPtr()->setPassword(password);
    RequestHttpAccount::getSingletonPtr()->loginToServer(login, password);
//    RequestHttpAccount::getSingletonPtr()->sendCreate(login);
}

void    SignInGUI::setUserFolder(void) {
    QString dir = ConfFile::getSingletonPtr()->getValue(CONFFILE_DIRECTORY).toString();
    if (dir == QString("")) {
        dir = QDir::homePath();
        dir.append("/Woda");
        UserFolderManagement::getSingletonPtr()->createDirectory(dir);
    }
    UserFolderManagement::getSingletonPtr()->changeDirectory(dir);
}

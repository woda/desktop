//! \file AccountGUI.cpp
//! \brief	implementation of the header AccountGUI for display the Account Preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#include	"AccountGUI.hh"
#include	"page.hh"
#include    "Account.hh"
#include    "UserFolderManagement.hh"
#include    "RequestHttpAccount.hh"


AccountGUI::AccountGUI(QStackedWidget * stack, QWidget * parent)
    : QWidget(parent), _stack(stack) {
  setupUi(this);

  _timer = new QTimer(this);
  _timer->setInterval(TIMER_REFRESH_DISCONNECT);
  connect(_timer, SIGNAL(timeout()), this, SLOT(updateUserAccount()));
}


AccountGUI::~AccountGUI() {
}


void	AccountGUI::update() {
    Account * userAccount = Account::getSingletonPtr();
    if (!userAccount->isConnected()) {
        _stack->setCurrentIndex(Page::SIGNIN_PAGE);
        return;
    }
    QString username("");
    username.append(userAccount->firstName()).append(" ").append(userAccount->lastName());
    this->labelUsername->setText(username);
    this->labelMailAdress->setText(userAccount->email());

    _timer->start(TIMER_REFRESH_DISCONNECT);
}


void	AccountGUI::updateUserAccount(void) {
    if (!Account::getSingletonPtr()->isConnected()) {
        _timer->stop();
        _stack->setCurrentIndex(Page::SIGNIN_PAGE);
    }
}


void	AccountGUI::closePreference(void) {
    _stack->setCurrentIndex(Page::DESTROY_PAGE);
}


void	AccountGUI::btnPageGeneral(void) {
    _stack->setCurrentIndex(Page::GENERAL_PAGE);
}


void	AccountGUI::btnPageSync(void) {
    _stack->setCurrentIndex(Page::SYNC_PAGE);
}

void	AccountGUI::btnWebApp(void) {
    QDesktopServices::openUrl(QUrl("http://webapp.woda-server.com/app_dev.php"));
}

//! \brief Button to click to disconnect to the server
void    AccountGUI::btnSignOut() {
    UserFolderManagement::getSingletonPtr()->deleteDirectory();
    RequestHttpAccount::getSingletonPtr()->logoutToServer();
}


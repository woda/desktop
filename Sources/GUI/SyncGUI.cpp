//! \file SyncGUI.cpp
//! \brief	implementation of the header SyncGUI for display the Sync Preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#include	"SyncGUI.hh"
#include	"page.hh"
#include    "Account.hh"

SyncGUI::SyncGUI(QStackedWidget * stack, QWidget * parent)
    : QWidget(parent), _stack(stack) {
  setupUi(this);
}

SyncGUI::~SyncGUI() {
}

void	SyncGUI::update() {
    if (!Account::getSingletonPtr()->isConnected()) {
        _stack->setCurrentIndex(Page::SIGNIN_PAGE);
    }
}


void	SyncGUI::closePreference(void) {
    _stack->setCurrentIndex(Page::DESTROY_PAGE);
}


void	SyncGUI::btnPageGeneral(void) {
    _stack->setCurrentIndex(Page::GENERAL_PAGE);
}


void	SyncGUI::btnPageAccount(void) {
    _stack->setCurrentIndex(Page::ACCOUNT_PAGE);
}

void	SyncGUI::btnWebApp(void) {
    QDesktopServices::openUrl(QUrl("http://webapp.woda-server.com/app_dev.php"));
}

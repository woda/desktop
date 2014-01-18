//! \file GeneralGUI.cpp
//! \brief	implementation of the header GeneralGUI for display the General Preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#include	"GeneralGUI.hh"
#include	"Page.hh"
#include    "Account.hh"
#include    "UserFolderManagement.hh"

GeneralGUI::GeneralGUI(QStackedWidget * stack, QWidget * parent)
    : QWidget(parent), _stack(stack) {
  setupUi(this);

  connect(this->comboBoxNotification, SIGNAL(currentIndexChanged(int)),
          this, SLOT(notificationPosition(int)));
}

GeneralGUI::~GeneralGUI() {
}

void	GeneralGUI::update() {
    if (!Account::getSingletonPtr()->isConnected()) {
        _stack->setCurrentIndex(Page::SIGNIN_PAGE);
    }
}

//void	GeneralGUI::BtnOK(void) {
//    QString login(this->lineEditLogin->text());
//    QString password(this->lineEditPassword->text());
//  if (Login::getInstance()->checkConnect(login, password)) {
//    _stack->setCurrentIndex(Page::TOURNEE_PAGE);
//  } else {
//      this->labelError->setText(Login::getInstance()->getError());
//      this->labelError->show();
//  }
//}

//void    GeneralGUI::clear(void) {
//    QString str("");
//    this->lineEditLogin->setText(str);
//    this->lineEditPassword->setText(str);
//    this->labelError->setText(str);
//    this->labelError->hide();
//}


void	GeneralGUI::closePreference(void) {
    _stack->setCurrentIndex(Page::DESTROY_PAGE);
}


void	GeneralGUI::btnPageAccount(void) {
    _stack->setCurrentIndex(Page::ACCOUNT_PAGE);
}


void	GeneralGUI::btnPageSync(void) {
    _stack->setCurrentIndex(Page::SYNC_PAGE);
}


void	GeneralGUI::btnWebApp(void) {
    QDesktopServices::openUrl(QUrl("http://kobhqlt.fr/wodajs/uptodate/#/"));
}

void    GeneralGUI::notificationPosition(int index) {
    Account::getSingletonPtr()->setCorner(index);
}

void	GeneralGUI::btnFolderLocation(void) {
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            UserFolderManagement::getSingletonPtr()->getCurrentDirectory(),
                                            QFileDialog::ShowDirsOnly |
                                            QFileDialog::DontResolveSymlinks);
    if (dir.isEmpty()) {
        return;
    }
    this->pushButtonLocation->setText(dir);
    UserFolderManagement::getSingletonPtr()->changeDirectory(dir);
}

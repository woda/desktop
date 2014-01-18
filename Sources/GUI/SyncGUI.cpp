//! \file SyncGUI.cpp
//! \brief	implementation of the header SyncGUI for display the Sync Preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#include	"SyncGUI.hh"
#include	"Page.hh"
#include    "SyncTreeWidgetGUI.hh"
#include    "Account.hh"
#include    "UserFolderManagement.hh"

SyncGUI::SyncGUI(QStackedWidget * stack, QWidget * parent)
    : QWidget(parent), _stack(stack),
      _vectorTreeWidgetItem(new QVector<QTreeWidgetItem *>()) {
  setupUi(this);
}

SyncGUI::~SyncGUI() {
}

void	SyncGUI::update() {
    if (!Account::getSingletonPtr()->isConnected()) {
        _stack->setCurrentIndex(Page::SIGNIN_PAGE);
    }
//    this->fillTreeWidgetWithFolder(UserFolderManagement::getSingletonPtr()->getCurrentDirectory(),
//                                   this->treeWidget);
    this->treeWidget = new SyncTreeWidgetGUI(this);
    this->treeWidget->show();
    this->treeWidget->move(50,120);
    this->treeWidget->setFixedHeight(181);
    this->treeWidget->setFixedWidth(421);
}


//void    SyncGUI::fillTreeWidgetWithFolder(QString strPath, QTreeWidget * parentWidget) {
//    QDir directory(strPath);

//    if (directory.exists(strPath)) {
//        Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
//            if (info.isDir()) {
//                QString str = info.absoluteFilePath().mid(strPath.length() + 1);
//                QTreeWidgetItem * item;
//                item = new QTreeWidgetItem(parentWidget);
//                item->setExpanded(true);
//                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
//                item->setCheckState(0, Qt::Unchecked);
//                item->setText(0, str);
//                item->setToolTip(0, info.absoluteFilePath());
//                this->fillTreeWidgetWithFolder(info.absoluteFilePath(), item);
//            } else {
//                QString str = info.absoluteFilePath().mid(strPath.length() + 1);
//                QTreeWidgetItem *item;
//                item = new QTreeWidgetItem(parentWidget);
//                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
//                item->setCheckState(0, Qt::Unchecked);
//                item->setText(0, str);
//                item->setToolTip(0, info.absoluteFilePath());
//            }
//        }
//    }
//}


//void    SyncGUI::fillTreeWidgetWithFolder(QString strPath, QTreeWidgetItem * parentWidget) {
//    QDir directory(strPath);

//    if (directory.exists(strPath)) {
//        Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
//            if (info.isDir()) {
//                QString str = info.absoluteFilePath().mid(strPath.length() + 1);
//                QTreeWidgetItem * item;
//                item = new QTreeWidgetItem(parentWidget);
//                item->setExpanded(true);
//                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
//                item->setCheckState(0, Qt::Unchecked);
//                item->setText(0, str);
//                item->setToolTip(0, info.absoluteFilePath());
//                this->fillTreeWidgetWithFolder(info.absoluteFilePath(), item);
//            } else {
//                QString str = info.absoluteFilePath().mid(strPath.length() + 1);
//                QTreeWidgetItem *item;
//                item = new QTreeWidgetItem(parentWidget);
//                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
//                item->setCheckState(0, Qt::Unchecked);
//                item->setText(0, str);
//                item->setToolTip(0, info.absoluteFilePath());
//            }
//        }
//    }
//}


//void    SyncGUI::mousePressEvent(QMouseEvent *event) {
//    qDebug() << "test33";
////    this->treeWidget->mousePressEvent(event);
//    QTreeView::mousePressEvent(event);
//    QModelIndex indexClicked = this->treeWidget->indexAt(event->pos());
//    if (indexClicked.isValid()) {
//        qDebug() << "test34";
//        QRect vrect = this->treeWidget->visualRect(indexClicked);
//        int itemIndentation = vrect.x() - this->treeWidget->visualRect(this->treeWidget->rootIndex()).x();
//        QRect rect = QRect(this->treeWidget->header()->sectionViewportPosition(0) + itemIndentation,
//                           vrect.y(), style()->pixelMetric(QStyle::PM_IndicatorWidth),
//                           vrect.height());
//        if(rect.contains(event->pos())) {
//            qDebug() << indexClicked.model()->data(indexClicked, Qt::ToolTipRole).toString();
////            this->treeWidget->mousePressEvent(event);
//            return;
//        } else {
////            QTreeWidget::mousePressEvent(event);
//        }
//    }
//}

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
    QDesktopServices::openUrl(QUrl("http://kobhqlt.fr/wodajs/uptodate/#/"));
}

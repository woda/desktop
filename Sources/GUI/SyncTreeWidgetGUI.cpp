//! \file SyncGUI.cpp
//! \brief	implementation of the header SyncGUI for display the Sync Preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#include	"SyncTreeWidgetGUI.hh"
#include    "UserFolderManagement.hh"
#include    "FolderDB.hh"

SyncTreeWidgetGUI::SyncTreeWidgetGUI(QWidget * parent)
    : QTreeWidget(parent), _vectorTreeWidgetItem(new QVector<QTreeWidgetItem *>()) {
    this->show();
    this->fillTreeWidgetWithFolder(UserFolderManagement::getSingletonPtr()->getCurrentDirectory(),
                                   this);
}

SyncTreeWidgetGUI::~SyncTreeWidgetGUI() {
}


void    SyncTreeWidgetGUI::fillTreeWidgetWithFolder(QString strPath, QTreeWidget * parentWidget) {
    QDir directory(strPath);
    FolderDB db;

    if (directory.exists(strPath)) {
        Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                QString str = info.absoluteFilePath().mid(strPath.length() + 1);
                QTreeWidgetItem * item;
                item = new QTreeWidgetItem(parentWidget);
                item->setExpanded(true);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                if (db.checkFolderSynchronizedWithFileSystem(info.absoluteFilePath())) {
                    item->setCheckState(0, Qt::Checked);
                } else {
                    item->setCheckState(0, Qt::Unchecked);
                }
                item->setText(0, str);
                item->setToolTip(0, info.absoluteFilePath());
                this->fillTreeWidgetWithFolder(info.absoluteFilePath(), item);
            }
        }
    }
}


void    SyncTreeWidgetGUI::fillTreeWidgetWithFolder(QString strPath, QTreeWidgetItem * parentWidget) {
    QDir directory(strPath);
    FolderDB db;

    if (directory.exists(strPath)) {
        Q_FOREACH(QFileInfo info, directory.entryInfoList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                QString str = info.absoluteFilePath().mid(strPath.length() + 1);
                QTreeWidgetItem * item;
                item = new QTreeWidgetItem(parentWidget);
                item->setExpanded(true);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                if (db.checkFolderSynchronizedWithFileSystem(info.absoluteFilePath())) {
                    item->setCheckState(0, Qt::Checked);
                } else {
                    item->setCheckState(0, Qt::Unchecked);
                }
                item->setText(0, str);
                item->setToolTip(0, info.absoluteFilePath());
                this->fillTreeWidgetWithFolder(info.absoluteFilePath(), item);
            }
        }
    }
}


void    SyncTreeWidgetGUI::mousePressEvent(QMouseEvent *event) {
    FolderDB db;
    QModelIndex indexClicked = indexAt(event->pos());
    if(indexClicked.isValid()) {
        QRect vrect = visualRect(indexClicked);
        int itemIndentation = vrect.x() - visualRect(rootIndex()).x();
        QRect rect = QRect(header()->sectionViewportPosition(0) + itemIndentation,
                           vrect.y(), style()->pixelMetric(QStyle::PM_IndicatorWidth),
                           vrect.height());
        if(rect.contains(event->pos())) {
            QString path = indexClicked.model()->data(indexClicked, Qt::ToolTipRole).toString();
            qDebug() << path;
            if (db.checkFolderSynchronizedWithFileSystem(path)) {
                db.insertFolder(path, 0);
            } else {
                db.insertFolder(path, 1);
            }
            QTreeWidget::mousePressEvent(event);
            return;
        } else {
            QTreeWidget::mousePressEvent(event);
        }
    }
}

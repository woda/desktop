//! \file SyncTreeWidgetGUI.hh
//! \brief	header SyncTreeWidgetGUI : Sync Tree Widget
//! \author Woda Corporation
//! \version 1.2
//! \date 2014-01


#ifndef				GUI_SYNCTREEWIDGETGUI_HH__
# define			GUI_SYNCTREEWIDGETGUI_HH__

# include			<QtGui>
# include			<string>

//! \class SyncTreeWidgetGUI SyncTreeWidgetGUI.hh
//! \brief Class for the Sync Tree Widget into Sync GUI
class				SyncTreeWidgetGUI : public QTreeWidget {
 private:
  QVector<QTreeWidgetItem *> * _vectorTreeWidgetItem;

 public:
  SyncTreeWidgetGUI(QWidget * parent = 0);
  ~SyncTreeWidgetGUI();
  void      fillTreeWidgetWithFolder(QString strPath,
                                     QTreeWidget * parentWidget);
  void      fillTreeWidgetWithFolder(QString strPath,
                                     QTreeWidgetItem * parentWidget);

 public slots:
  void      mousePressEvent(QMouseEvent *event);
};

#endif				// !GUI_SYNCTREEWIDGETGUI_HH__

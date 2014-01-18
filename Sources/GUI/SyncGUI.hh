//! \file SyncGUI.hh
//! \brief	header SyncGUI : Sync Preference Page
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07


#ifndef				GUI_SYNCGUI_HH__
# define			GUI_SYNCGUI_HH__

# include			<QtGui>
# include			<string>
# include			"ui_SyncGUI.h"
# include			"IGUI.hh"

//! \class SyncGUI SyncGUI.hh
//! \brief Class for the Sync Preference Page
class				SyncGUI : public QWidget,
                              private Ui::SyncGUI,
                              public IGUI {
 Q_OBJECT

 private:
  QStackedWidget *		_stack;
  QVector<QTreeWidgetItem *> * _vectorTreeWidgetItem;

 public:
  SyncGUI(QStackedWidget * stack, QWidget * parent = 0);
  virtual   ~SyncGUI();
  void      update();

// private:
//  void      fillTreeWidgetWithFolder(QString strPath,
//                                     QTreeWidget * parentWidget);
//  void      fillTreeWidgetWithFolder(QString strPath,
//                                     QTreeWidgetItem * parentWidget);

 public slots:
//  void      mousePressEvent(QMouseEvent *event);
  void      closePreference(void);
  void      btnPageGeneral(void);
  void      btnPageAccount(void);
  void      btnWebApp(void);
};

#endif				// !GUI_SYNCGUI_HH__

//! \file GeneralGUI.hh
//! \brief	header GeneralGUI : General Preference Page
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07


#ifndef				GUI_GENERALGUI_HH__
# define			GUI_GENERALGUI_HH__

# include			<QtGui>
# include			<string>
# include			"ui_GeneralGUI.h"
# include			"IGUI.hh"

//! \class GeneralGUI GeneralGUI.hh
//! \brief Class for the General Preference Page
class				GeneralGUI : public QWidget,
                                 private Ui::GeneralGUI,
                                 public IGUI {
 Q_OBJECT

 private:
  QStackedWidget *		_stack;

 public:
  GeneralGUI(QStackedWidget * stack, QWidget * parent = 0);
  virtual ~GeneralGUI();
  void	update();
//  void  clear(void);

 public slots:
  void	closePreference(void);
  void	btnPageAccount(void);
  void	btnPageSync(void);
  void	btnWebApp(void);
  void  btnFolderLocation(void);
  void  notificationPosition(int index);

//  void	BtnCancel(void);
//  void	BtnQuit(void);
};

#endif				// !GUI_GENERALGUI_HH__

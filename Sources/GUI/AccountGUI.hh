//! \file AccountGUI.hh
//! \brief	header AccountGUI : display the Account Preference
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#ifndef				GUI_ACCOUNTGUI_HH__
# define			GUI_ACCOUNTGUI_HH__

# include			<QtGui>
# include			<string>
# include			"ui_AccountGUI.h"
# include			"IGUI.hh"

//! \def TIMER_REFRESH
# define    TIMER_REFRESH_DISCONNECT   4000

//! \class AccountGUI AccountGUI.hh
//! \brief Class for the Account Preference Page
class				AccountGUI : public QWidget,
                                 private Ui::AccountGUI,
                                 public IGUI {
 Q_OBJECT

 private:
  QStackedWidget *		_stack;
  QTimer *              _timer;

 public:
  AccountGUI(QStackedWidget * stack, QWidget * parent = 0);
  virtual ~AccountGUI();
  void	update();

 public slots:
  void	closePreference(void);
  void	btnPageGeneral(void);
  void	btnPageSync(void);
  void	btnWebApp(void);
  void  btnSignOut(void);
  void  updateUserAccount(void);
};

#endif				// !GUI_ACCOUNTGUI_HH__

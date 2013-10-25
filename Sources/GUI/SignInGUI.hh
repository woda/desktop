//! \file SignInGUI.hh
//! \brief	header SignGUI : display the Sign In page
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07

#ifndef				GUI_SIGNINGUI_HH__
# define			GUI_SIGNINGUI_HH__

# include			<QtGui>
# include			<string>
# include			"ui_SignInGUI.h"
# include			"IGUI.hh"

//! \def TIMER_REFRESH
# define    TIMER_REFRESH   1000

//! \class SignInGUI SignInGUI.hh
//! \brief Class for the Sign In Page
class				SignInGUI : public QWidget,
                                private Ui::SignInGUI,
                                public IGUI {
 Q_OBJECT

 private:
  QStackedWidget *		_stack;
  QTimer *              _timer;

 public:
  SignInGUI(QStackedWidget * stack, QWidget * parent = 0);
  virtual ~SignInGUI();
  void	update();
  void  setUserFolder(void);

 public slots:
  void  updateUserAccount(void);
  void	closePreference(void);
  void	btnWebApp(void);
  void  btnSignIn(void);
};

#endif				// !GUI_ACCOUNTGUI_HH__

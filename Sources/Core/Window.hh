//! \file Window.hh
//! \brief	header Window : Window wich manages the interfaces
//! \author Woda Corporation
//! \version 1.3
//! \date 2013-01

#ifndef		INCLUDE_WINDOW_HH__
# define	INCLUDE_WINDOW_HH__

# include	<QWidget>
# include   "TrayIcon.hh"


//! \class Window Window.hh
//! \brief main Window who manage all the system
class		Window : public QWidget
{
  Q_OBJECT

public:
  Window(QWidget * parent = 0);
  ~Window();

public slots:
  void		closeEvent(QCloseEvent * event);

private:
  void      checkUserFolder();

private:
  TrayIcon * _trayIcon;
};

#endif		// !__WINDOW_HH__

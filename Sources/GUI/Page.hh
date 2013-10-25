//! \file Page.hh
//! \brief	header Page : Class for manage the other GUI
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-07


#ifndef		GUI_PAGE_HH__
# define	GUI_PAGE_HH__

# include	<QtGui>
# include	<string>

# define    HEIGHT_TITLE_BAR       21

//! \class Page Page.hh
//! \brief main class who manage the other GUI page
class		Page : public QWidget
{
  Q_OBJECT

private:
    QStackedWidget *    _stack;
    QVBoxLayout *       _layout;
    QPoint              _mpos;
public:
    static int          _idx;

public:
  Page(QWidget * parent = 0);
  ~Page();

public slots:
  void		update(int);
  void      mousePressEvent(QMouseEvent * event);
  void      mouseMoveEvent(QMouseEvent * event);

private:
  void		setBackground(int idx);
  void		setBackgroundImage(std::string str);

public:
  // ajouter ici un enum pour votre nouvelle page
enum
  {
    DESTROY_PAGE = 0,
    RELOAD_PAGE,
    GENERAL_PAGE,
    ACCOUNT_PAGE,
    SYNC_PAGE,
    SIGNIN_PAGE
  };
};

#endif		// !GUI_PAGE_HH__

//! \file ConfFile.cpp
//! \brief	implementation of the interface of Popup for display a popup in the corner
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef		POPUP_HH__
# define	POPUP_HH__

# include	<QLabel>
# include	<QTimer>
# include	<QWidget>
# include	<QTextEdit>
# include	<QMouseEvent>
# include	<QGridLayout>
# include	<QApplication>
# include	<QDesktopWidget>

class		Popup : public QWidget
{
  Q_OBJECT

  public:
  Popup(const int width, const int height);
  ~Popup(void);

  void		setTextColor(const QColor & c);
  void		setBackgroundColor(const QColor & c);
  void		setFrameColor(const QColor & c);

public slots:
  void		showUp(const QString& text, const int timeout = 10000);

protected:
  virtual void	paintEvent(QPaintEvent* event);
  virtual void	mousePressEvent(QMouseEvent* event);
  virtual void	mouseMoveEvent(QMouseEvent* event);
  virtual void	showAnimation(void);
  virtual void	stopAnimation(void);

protected slots:
  virtual void	hideAnimation(void);
    void		fadein(void);
      void		fadeout(void);

private:
  void		init(void);
  void		buildCache(void);
  void		setCorner(void);

private:
  int		_popupWidth;
  int		_popupHeight;
  int		_screenWidth;
  int		_screenHeight;

  QLabel	_text;
  QColor	_textColor;
  QColor	_backgroundColor;
  QColor	_frameColor;
  QGridLayout	_layout;
  QPixmap *	_cache;
  QTimer *	_hiddingTrigger;
  QTimer *	_fadein;
  QTimer *	_fadeout;
  qreal		_opacityAnimation;
};

#endif		// !POPUP_HH__

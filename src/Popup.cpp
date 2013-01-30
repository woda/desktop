//! \file ConfFile.cpp
//! \brief	implementation of the interface of Popup for display a popup in the corner
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#include	"Popup.hh"
#include	"ConfFile.hh"
#include	<QPainter>


//! \namespace
//! \brief Constant
namespace
{
  qreal INITIAL_OPACITY = 0.9;
  qreal HOVER_OPACITY = 0.9;
}


//! \fn Popup::Popup(const int width, const int height)
//! \param[in] width width of the popup
//! \param[in] height height of the popup
//! \brief		Constructor, initialize the timer, the interval, and slot
Popup::Popup(const int width, const int height)
  : _popupWidth(width), _popupHeight(height),
    _textColor("#CC6633"), _backgroundColor("#171722"),
    _frameColor("#B1B1CB"), _cache(NULL), _opacityAnimation(0.)
{
  init();
  this->_hiddingTrigger = new QTimer(this);
  this->_hiddingTrigger->setSingleShot(true);
  connect(this->_hiddingTrigger, SIGNAL(timeout()), SLOT(hideAnimation()));
  this->_fadein = new QTimer(this);
  this->_fadein->setInterval(25);
  this->_fadein->setSingleShot(false);
  connect(this->_fadein, SIGNAL(timeout()), this, SLOT(fadein()));
  this->_fadeout = new QTimer(this);
  this->_fadeout->setInterval(25);
  this->_fadeout->setSingleShot(false);
  connect(this->_fadeout, SIGNAL(timeout()), this, SLOT(fadeout()));
}


//! \fn Popup::~Popup(void)
//! \brief		Destructor
Popup::~Popup(void)
{
}


//! \fn void Popup::showUp(const QString& text, const int timeout)
//! \param[in] text text to display in the popup
//! \param[in] timeout timeout of the popup
//! \brief initialize the text and the interval of the popup
void		Popup::showUp(const QString& text, const int timeout)
{
  if (isVisible()) stopAnimation();

  setCorner();
  setWindowOpacity(INITIAL_OPACITY);
  this->_text.setText("<font color=" + this->_textColor.name() + '>' +
                      text + "</font>");
  this->_hiddingTrigger->setInterval(timeout);
  this->_hiddingTrigger->start();
  setWindowOpacity(this->_opacityAnimation);
  this->_fadein->start();
  showAnimation();
}


//! \fn void Popup::paintEvent(QPaintEvent* event)
//! \param[in] event event received in the slot
//! \brief draw the popup if the event is triggered
void		Popup::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event);

  if (this->_cache == NULL)
    {
      buildCache();
    }
  else
    {
      QPainter painter(this);
      painter.drawPixmap(0, 0, *this->_cache);
    }
}


//! \fn void Popup::mousePressEvent(QMouseEvent* event)
//! \param[in] event event received in the slot
//! \brief stop the animation of the popup if the popup is clicked
void		Popup::mousePressEvent(QMouseEvent* event)
{
  Q_UNUSED(event);
  stopAnimation();
}


//! \fn void Popup::mouseMoveEvent(QMouseEvent* event)
//! \param[in] event event received in the slot
//! \brief change the opacity if the mouse is over the popup
void		Popup::mouseMoveEvent(QMouseEvent* event)
{
  if (normalGeometry().contains(mapToGlobal(event->pos()), true))
    {
      setWindowOpacity(HOVER_OPACITY);
    }
  else
    {
      setWindowOpacity(INITIAL_OPACITY);
    }
}


//! \fn void Popup::fadein(void)
//! \brief animation fadein
void		Popup::fadein(void)
{
    if (isVisible() && this->_opacityAnimation < INITIAL_OPACITY)
	{
        this->_opacityAnimation += 0.05;
		setWindowOpacity(this->_opacityAnimation);
	}
	else
	{
        this->_fadein->stop();
	}
}


//! \fn void Popup::fadeout(void)
//! \brief animation fadeout
void		Popup::fadeout(void)
{
    if (isVisible() && this->_opacityAnimation > 0.)
    {
        this->_opacityAnimation -= 0.05;
        setWindowOpacity(this->_opacityAnimation);
    }
    else
    {
        this->_opacityAnimation = 0.;
        this->_fadeout->stop();
        hide();
    }
}


//! \fn void Popup::showAnimation(void)
//! \brief display the window popup
void		Popup::showAnimation(void)
{
  show();
}


//! \fn void Popup::stopAnimation(void)
//! \brief stop the animation and hide the popup
void		Popup::stopAnimation(void)
{
  this->_hiddingTrigger->stop();
  hide();
}


//! \fn void Popup::hideAnimation(void)
//! \brief begin the fadeout on the popup
void		Popup::hideAnimation(void)
{
    this->_fadeout->start();
}


//! \fn void Popup::init(void)
//! \brief initialize the geometric, layout, attribute
void		Popup::init(void)
{
  const QRect geo = QApplication::desktop()->screenGeometry(this);
  this->_screenWidth = geo.width();
  this->_screenHeight = geo.height();

  this->_text.setFrameShape(QFrame::NoFrame);
  this->_text.setAttribute(Qt::WA_TransparentForMouseEvents);
  this->_text.setWordWrap(true);

  this->_layout.addWidget(&this->_text);
  setLayout(&this->_layout);

  //  setGeometry(this->_screenWidth - this->_popupWidth,
  //              this->_screenHeight - this->_popupHeight,
  //              this->_popupWidth,
  //              this->_popupHeight);
  setLayout(&this->_layout);

  setMouseTracking(true);
  setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
}


//! \fn void Popup::buildCache(void)
//! \brief construct point by point the popup
void		Popup::buildCache(void)
{
  this->_cache = new QPixmap(size());
  this->_cache->fill(Qt::transparent);

  QPainter painter(this->_cache);

  // Window's background
  QPolygon background;

  background << QPoint(           0,            16)
             << QPoint(          16,             0)
             << QPoint(width() - 16,             0)
             << QPoint(width()     ,            16)
             << QPoint(width()     , height() - 16)
             << QPoint(width() - 16,      height())
             << QPoint(          16,      height())
             << QPoint(           0, height() - 16);

  painter.setPen  (QPen  (this->_backgroundColor));
  painter.setBrush(QBrush(this->_backgroundColor));

  painter.drawPolygon(background);

  // Window's frame
  QPolygon frame;

  frame << QPoint(           4,            20)
        << QPoint(          20,             4)
        << QPoint(width() - 20,             4)
        << QPoint(width() -  4,            20)
        << QPoint(width() -  4, height() - 20)
        << QPoint(width() - 20,  height() - 4)
        << QPoint(          20,  height() - 4)
        << QPoint(           4, height() - 20);

  painter.setPen(QPen(this->_frameColor));
  painter.setBrush(Qt::NoBrush);

  painter.drawPolygon(frame);
  update();
}


//! \fn void Popup::setTextColor(const QColor & c)
//! \param[in] c color choose for the text
//! \brief change the text color
void		Popup::setTextColor(const QColor & c)
{
  this->_textColor = c;
}


//! \fn void Popup::setBackgroundColor(const QColor & c)
//! \param[in] c color choose for the background
//! \brief change the background color
void		Popup::setBackgroundColor(const QColor & c)
{
  this->_backgroundColor = c;
}


//! \fn void Popup::setFrameColor(const QColor & c)
//! \param[in] c color choose for the frame
//! \brief change the frame color
void		Popup::setFrameColor(const QColor & c)
{
  this->_frameColor = c;
}


//! \fn void Popup::setCorner(void)
//! \brief search in wich corner draw the popup
void		Popup::setCorner(void)
{
  int corner = ConfFile::getSingletonPtr()->getValue(CONFFILE_CORNER).toInt();

  switch (corner)
    {
    case 1:
      setGeometry(0, 0, this->_popupWidth, this->_popupHeight);
      break;
    case 2:
      setGeometry(this->_screenWidth - this->_popupWidth, 0,
		  this->_popupWidth,
		  this->_popupHeight);
      break;
    case 3:
      setGeometry(0, this->_screenHeight - this->_popupHeight,
		  this->_popupWidth,
		  this->_popupHeight);
      break;
    default:
      setGeometry(this->_screenWidth - this->_popupWidth,
		  this->_screenHeight - this->_popupHeight,
		  this->_popupWidth,
		  this->_popupHeight);    
    }
}

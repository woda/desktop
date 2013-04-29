//! \file MyCustomActionPixmap.hh
//! \brief	header MyCustomActionPixmap : CustomAction for display a Pixmap in the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef			INCLUDE_MYCUSTOMACTIONPIXMAP_HH__
# define		INCLUDE_MYCUSTOMACTIONPIXMAP_HH__

# include		<QWidgetAction>
# include		<QLabel>
# include		<QString>

//! \class MyCustomActionPixmap MyCustomActionPixmap.hh
//! \brief class that inherits from QWidgetAction for display a pixmap in the tray icon.
class			MyCustomActionPixmap : public QWidgetAction
{
    Q_OBJECT
public:
  explicit		MyCustomActionPixmap(QWidget *parent, QString & path);
    
protected:
  virtual QWidget *	createWidget(QWidget *parent);

private:
  QString		_path;
  QLabel *		_label;
};

#endif			// !INCLUDE_MYCUSTOMACTIONPIXMAP_HH__

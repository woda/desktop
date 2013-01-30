//! \file ConfFile.cpp
//! \brief	implementation of the interface of CustomAction for display a Pixmap in the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef			MYCUSTOMACTIONPIXMAP_HH__
# define		MYCUSTOMACTIONPIXMAP_HH__

# include		<QWidgetAction>
# include		<QLabel>
# include		<QString>

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

#endif			// !MYCUSTOMACTIONPIXMAP_HH__

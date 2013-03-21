//! \file MyCustomActionLabel.hh
//! \brief	header MyCustonActionLabel : CustomAction for display a label in the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef			INCLUDE_MYCUSTOMACTIONLABEL_HH__
# define		INCLUDE_MYCUSTOMACTIONLABEL_HH__

# include		<QWidgetAction>
# include		<QLabel>
# include		<QString>

//! \class MyCustomActionLabel MyCustomActionLabel.hh
//! \brief class that inherits from QWidgetAction for display a label in the tray icon.
class			MyCustomActionLabel : public QWidgetAction
{
    Q_OBJECT
public:
  explicit		MyCustomActionLabel(QWidget * parent, QString str);
    
protected:
  virtual QWidget *	createWidget(QWidget *parent);

private:
  QString		_str;
  QLabel *		_label;
};

#endif			// !INCLUDE_MYCUSTOMACTIONLABEL_HH__

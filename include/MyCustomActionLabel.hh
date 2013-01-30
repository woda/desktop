//! \file ConfFile.cpp
//! \brief	implementation of the interface of CustomAction for display a label in the tray icon
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef			MYCUSTOMACTIONLABEL_HH__
# define		MYCUSTOMACTIONLABEL_HH__

# include		<QWidgetAction>
# include		<QLabel>
# include		<QString>

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

#endif			// !MYCUSTOMACTIONLABEL_HH__

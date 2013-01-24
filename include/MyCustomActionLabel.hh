/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

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

/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

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

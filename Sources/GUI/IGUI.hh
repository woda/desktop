//! \file IGUI.hh
//! \brief	header IGUI : interface for GUI class
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef		GUI_IGUI_HH__
# define	GUI_IGUI_HH__

//! \class IGUI IGUI.hh
//! \brief Interface for update the gui
class		IGUI
{
public:
  virtual ~IGUI() {}
  virtual void update() = 0;
};

#endif		// !GUI_IGUI_HH__

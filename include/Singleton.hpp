//! \file ConfFile.cpp
//! \brief	implementation of the interface of Singleton for call a class whithout instance her
//! \author Woda Corporation
//! \version 1.2
//! \date 2013-01

#ifndef		__SINGLETON_HPP__
# define	__SINGLETON_HPP__

# include	<string>

template	<class T>
class		Singleton
{
protected:
  Singleton() {}
  ~Singleton() {}

public:
  static T &	getSingleton()
  {
    if (mySingleton == NULL)
      mySingleton = new T;
    return *mySingleton;
  }

  static T &	getSingleton(const std::string &str)
  {
    if (mySingleton == NULL)
      mySingleton = new T(str);
    return *mySingleton;
  }

  static T *	getSingletonPtr(const std::string &str)
  {
    if (mySingleton == NULL)
      mySingleton = new T(str);
    return mySingleton;
  }

  static T &	getSingleton(std::string &str1, std::string &str2)
  {
    if (mySingleton == NULL)
      mySingleton = new T(str1, str2);
    return *mySingleton;
  }

  static T *	getSingletonPtr(std::string &str1, std::string &str2)
  {
    if (mySingleton == NULL)
      mySingleton = new T(str1, str2);
    return mySingleton;
  }

  static T *	getSingletonPtr()
  {
    if (mySingleton == NULL)
      mySingleton = new T;
    return mySingleton;
  }

  static bool	isExist()
  {
    if (mySingleton == NULL)
      return false;
    return true;
  }

  static void	del()
  {
    delete mySingleton;
    mySingleton = NULL;
  }

protected:
  static T *	mySingleton;
};

template <class T>
T * Singleton<T>::mySingleton = NULL;

#endif		// !__SINGLETON_HPP__

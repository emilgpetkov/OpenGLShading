#ifndef OGLUTILS_GLOBAL_H
#define OGLUTILS_GLOBAL_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	#  if defined( OGLUTILS_LIBRARY_STATIC )
	#    define OGLUTILSSHARED_EXPORT
	#  elif defined( OGLUTILS_LIBRARY )
	#    define OGLUTILSSHARED_EXPORT   __declspec(dllexport)
	#  else
	#    define OGLUTILSSHARED_EXPORT   __declspec(dllimport)
	#  endif
#else
	#  define OGLUTILSSHARED_EXPORT
#endif

//#if defined(OGLUTILS_LIBRARY)
//#  define OGLUTILSSHARED_EXPORT __declspec(dllexport)
//#else
//#  define OGLUTILSSHARED_EXPORT __declspec(dllimport)
//#endif

#endif // OGLUTILS_GLOBAL_H

#ifndef OPENGLSHADINGWINDOW_GLOBAL_H
#define OPENGLSHADINGWINDOW_GLOBAL_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	#  if defined( OPENGLSHADINGWINDOW_LIBRARY_STATIC )
	#    define OPENGLSHADINGWINDOWSHARED_EXPORT
	#  elif defined( OPENGLSHADINGWINDOW_LIBRARY )
	#    define OPENGLSHADINGWINDOWSHARED_EXPORT   __declspec(dllexport)
	#  else
	#    define OPENGLSHADINGWINDOWSHARED_EXPORT   __declspec(dllimport)
	#  endif
#else
	#  define OPENGLSHADINGWINDOWSHARED_EXPORT
#endif

#endif // OPENGLSHADINGWINDOW_GLOBAL_H

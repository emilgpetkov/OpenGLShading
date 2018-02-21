#ifndef OGLSHADER_GLOBAL_H
#define OGLSHADER_GLOBAL_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	#  if defined( OGLSHADER_LIBRARY_STATIC )
	#    define OGLSHADERSHARED_EXPORT
	#  elif defined( OGLSHADER_LIBRARY )
	#    define OGLSHADERSHARED_EXPORT   __declspec(dllexport)
	#  else
	#    define OGLSHADERSHARED_EXPORT   __declspec(dllimport)
	#  endif
#else
	#  define OGLSHADERSHARED_EXPORT
#endif

#endif // OGLSHADER_GLOBAL_H

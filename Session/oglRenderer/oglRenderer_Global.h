#ifndef OGLRENDERER_GLOBAL_H
#define OGLRENDERER_GLOBAL_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	#  if defined( OGLRENDERER_LIBRARY_STATIC )
	#    define OGLRENDERERSHARED_EXPORT
	#  elif defined( OGLRENDERER_LIBRARY )
	#    define OGLRENDERERSHARED_EXPORT   __declspec(dllexport)
	#  else
	#    define OGLRENDERERSHARED_EXPORT   __declspec(dllimport)
	#  endif
#else
	#  define OGLRENDERERSHARED_EXPORT
#endif

#endif // OGLRENDERER_GLOBAL_H

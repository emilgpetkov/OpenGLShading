#ifndef OGLGEOMETRY_GLOBAL_H
#define OGLGEOMETRY_GLOBAL_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	#  if defined( OGLGEOMETRY_LIBRARY_STATIC )
	#    define OGLGEOMETRYSHARED_EXPORT
	#  elif defined( OGLGEOMETRY_LIBRARY )
	#    define OGLGEOMETRYSHARED_EXPORT   __declspec(dllexport)
	#  else
	#    define OGLGEOMETRYSHARED_EXPORT   __declspec(dllimport)
	#  endif
#else
	#  define OGLGEOMETRYSHARED_EXPORT
#endif

//#if defined(OGLGEOMETRY_LIBRARY)
//#  define OGLGEOMETRYSHARED_EXPORT __declspec(dllexport)
//#else
//#  define OGLGEOMETRYSHARED_EXPORT __declspec(dllimport)
//#endif

#endif // OGLGEOMETRY_GLOBAL_H

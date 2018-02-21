#ifndef OGLGEOMUTILS_H
#define OGLGEOMUTILS_H

#include "oglUtils_Global.h"

namespace OglGeomUtils {

// Define a tolerance
struct OGLUTILSSHARED_EXPORT GeomTol
{
	GeomTol()
	{

	}

	~GeomTol()
	{

	}

	static double dTol;
};

// Some useful functions to compare doubles using a tolerance
bool OGLUTILSSHARED_EXPORT OglZero(const double &dVal, const double &dTol = GeomTol::dTol);
bool OGLUTILSSHARED_EXPORT OglEqual(const double &dValA, const double &dValB, const double &dTol = GeomTol::dTol);
bool OGLUTILSSHARED_EXPORT OglGreater(const double &dValA, const double &dValB, const double &dTol = GeomTol::dTol);
bool OGLUTILSSHARED_EXPORT OglGreaterEqual(const double &dValA, const double &dValB, const double &dTol = GeomTol::dTol);
bool OGLUTILSSHARED_EXPORT OglLess(const double &dValA, const double &dValB, const double &dTol = GeomTol::dTol);
bool OGLUTILSSHARED_EXPORT OglLessEqual(const double &dValA, const double &dValB, const double &dTol = GeomTol::dTol);
double OGLUTILSSHARED_EXPORT OglRadians(const double &deg);

} // namespace OglGeomUtils

#endif // OGLGEOMUTILS_H

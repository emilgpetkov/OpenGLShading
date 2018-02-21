#include <math.h>

#include "oglGeomUtils.h"

namespace OglGeomUtils {

double GeomTol::dTol = 1e-10;

bool OglZero(const double &dVal, const double &dTol)
{
	return fabs(dVal) - fabs(dTol) <= 0.0;
}

bool OglEqual(const double &dValA, const double &dValB, const double &dTol)
{
	return OglZero(fabs(dValA - dValB), dTol);
}

bool OglGreater(const double &dValA, const double &dValB, const double &dTol)
{
	return dValA - dValB > fabs(dTol);
}

bool OglGreaterEqual(const double &dValA, const double &dValB, const double &dTol)
{
	return (OglGreater(dValA, dValB, dTol) || OglEqual(dValA, dValB, dTol));
}

bool OglLess(const double &dValA, const double &dValB, const double &dTol)
{
	return dValA - dValB < fabs(dTol);
}

bool OglLessEqual(const double &dValA, const double &dValB, const double &dTol)
{
	return (OglLess(dValA, dValB, dTol) || OglEqual(dValA, dValB, dTol));
}

double OglRadians(const double &deg)
{
	return deg * M_PI / 180.0;
}

} // namespace OglGeomUtils

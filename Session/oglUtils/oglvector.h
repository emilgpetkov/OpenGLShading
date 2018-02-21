#ifndef OGLVECTOR_H
#define OGLVECTOR_H

#include "oglUtils_Global.h"
#include "oglGeomUtils.h"

namespace OglGeomUtils {

// Geometry vector class, 3-D, doubles
class OGLUTILSSHARED_EXPORT vec3d
{
public:
	// Public methods
	vec3d(); // Default c-tor
	vec3d(const double &x, const double &y, const double &z); // C-tor
	vec3d(const vec3d &v); // Copy c-tor
	~vec3d(); // D-tor

	// Some useful static constants
	static const vec3d kOrigin;
	static const vec3d kIdentity;
	static const vec3d kAxisX;
	static const vec3d kAxisY;
	static const vec3d kAxisZ;

	// Get/set coordinates
	double x() const;
	void x(const double &x);

	double y() const;
	void y(const double &y);

	double z() const;
	void z(const double &z);

	// Need to retrieve a pointer and an array of floats
	double *getAsPointer();
	void getAsFloat(float vec3f[3]) const;

	double lenght() const;
	vec3d crossProduct(const vec3d &v) const;
	double dotProduct(const vec3d &v) const;
	vec3d normal() const; // Renturns a copy of a normal vector to the current one
	vec3d &normalize(); // Normalizes the current vector and returns a refernce to it;
	bool isParallelTo(const vec3d &v) const;
	double angleTo(const vec3d &v) const;
	bool isPerpendicularTo(const vec3d &v) const;

	const double operator[](int i) const;
	double &operator[](int i);
	vec3d operator+(const vec3d &v) const;
	vec3d &operator+=(const vec3d &v);
	vec3d operator-(const vec3d &v) const;
	vec3d operator-() const;
	vec3d operator*(const double &scale) const;
	vec3d &operator*=(const double &scale);
	vec3d operator/(const double &scale) const;
	vec3d &operator=(const vec3d &v);
	bool operator==(const vec3d &v) const;

private:
	// Private data
	double vec[3];
};

} // namespace OglGeomUtils

#endif // OGLVECTOR_H

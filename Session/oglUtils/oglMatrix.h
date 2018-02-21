#ifndef OGLMATRIX_H
#define OGLMATRIX_H

#include "oglUtils_Global.h"

#include "oglvector.h"

namespace OglGeomUtils {

// Matrix of doubles used for 3D transformations
class OGLUTILSSHARED_EXPORT mat4d
{
public:
	// Public methods
	mat4d(); // Default c-tor
	mat4d(const double &m00, const double &m01, const double &m02, const double &m03,
		  const double &m10, const double &m11, const double &m12, const double &m13,
		  const double &m20, const double &m21, const double &m22, const double &m23,
		  const double &m30, const double &m31, const double &m32, const double &m33); // C-tor
	mat4d(const double &val); // C-tor, sets all of the components to the provided value
	mat4d(const mat4d &mIn); // Copy c-tor
	~mat4d(); // D-tor

	// A useful static const
	static const mat4d kIdentity;

	// Need to retrieve a pointer and an array of floats
	double *getAsPointer();
	void getAsFloat(float mat3f[16]) const;

	const double operator[](int i) const;
	double &operator[](int i);
	mat4d &operator=(const mat4d &m);
	mat4d operator*(const mat4d &m) const;
	vec3d operator*(const vec3d &vIn);
	mat4d operator+(const mat4d &mIn) const;
	bool operator==(const mat4d &mIn) const;

	// Need to multiply the matrix by a double
	mat4d multiplyByVal(const double &dVal) const;

	// Set to transformation
	mat4d &setToRotation(const double &dAngle, const vec3d &ptOrig, const vec3d &vAxis);
	mat4d &setToTranslation(const vec3d &vTransl);
	mat4d &setToScale(const vec3d &vScale);
	mat4d &setCoordinateSystem(const vec3d &ptOrig, const vec3d &axisU, const vec3d &axisV, const vec3d &axisW);
	mat4d &transpose();

	// Need to interpret two indices as a 1D array
	static int getMatIdx(int i, int j);

private:
	// Private data
	double mat[16];
};

// Get view and projection matrices
mat4d lookAt(const vec3d &ptViewPostion, const vec3d &ptViewTarget, const vec3d &vViewUp);
mat4d perspective(const double &dFOV, const double &dAspect, const double &dNear, const double &dFar);
mat4d ortho(const double &dLeft, const double &dRight,
			const double &dTop, const double &dBottom,
			const double &dNear, const double &dFar);

} // namespace OglGeomUtils

#endif // OGLMATRIX_H

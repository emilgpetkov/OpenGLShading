#include "oglMatrix.h"

#include <math.h>

namespace OglGeomUtils {

mat4d::mat4d()
{
	*this = kIdentity;
}

mat4d::mat4d(const double &m00, const double &m01, const double &m02, const double &m03,
			 const double &m10, const double &m11, const double &m12, const double &m13,
			 const double &m20, const double &m21, const double &m22, const double &m23,
			 const double &m30, const double &m31, const double &m32, const double &m33)
{
//	mat[0] = m00; mat[4] = m10; mat[8]  = m20; mat[12] = m30;
//	mat[1] = m01; mat[5] = m11; mat[9]  = m21; mat[13] = m31;
//	mat[2] = m02; mat[6] = m12; mat[10] = m22; mat[14] = m32;
//	mat[3] = m03; mat[7] = m13; mat[11] = m23; mat[15] = m33;

	mat[0] = m00; mat[4] = m01; mat[8]  = m02; mat[12] = m03;
	mat[1] = m10; mat[5] = m11; mat[9]  = m12; mat[13] = m13;
	mat[2] = m20; mat[6] = m21; mat[10] = m22; mat[14] = m23;
	mat[3] = m30; mat[7] = m31; mat[11] = m32; mat[15] = m33;
}

mat4d::mat4d(const double &val)
{
	for (int i = 0; i < 16; i++)
	{
		mat[i] = val;
	}
}

mat4d::mat4d(const mat4d &mIn)
{
	mat4d &m = *this;

	for (int i = 0; i < 16; i++)
	{
		m[i] = mIn[i];
	}
}

mat4d::mat4d(const glm::detail::tmat4x4<double, glm::defaultp> &mIn)
{
	mat4d &m = *this;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			typedef int (*F)(int, int); // Just for convenience
			F fnIdx = &mat4d::getMatIdx;

			m[fnIdx(i, j)] = static_cast<double>(mIn[j][i]);
		}
	}
}

mat4d::mat4d(const glm::detail::tmat4x4<float, glm::defaultp> &mIn)
{
	mat4d &m = *this;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			typedef int (*F)(int, int); // Just for convenience
			F fnIdx = &mat4d::getMatIdx;

			m[fnIdx(i, j)] = mIn[j][i];
		}
	}
}

mat4d::~mat4d()
{

}

double *mat4d::getAsPointer()
{
	return mat;
}

void mat4d::getAsFloat(float mat3f[16]) const
{
	for (int i = 0; i < 16; i++)
	{
		mat3f[i] = static_cast<float>(mat[i]);
	}
}

const double mat4d::operator[](int i) const
{
	return mat[i];
}

double &mat4d::operator[](int i)
{
	return mat[i];
}

const mat4d mat4d::kIdentity = mat4d(1.0, 0.0, 0.0, 0.0,
									 0.0, 1.0, 0.0, 0.0,
									 0.0, 0.0, 1.0, 0.0,
									 0.0, 0.0, 0.0, 1.0);

mat4d &mat4d::operator=(const OglGeomUtils::mat4d &mIn)
{
	for (int i = 0; i < 16; i++)
	{
		mat[i] = mIn[i];
	}

	return *this;
}

mat4d mat4d::operator*(const mat4d &m)
{
	mat4d mRes;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			double dRes = 0.0;

			for (int k = 0; k < 4; k++)
			{
				dRes += mat[getMatIdx(i, k)] * m[getMatIdx(k, j)];
			}

			mRes[getMatIdx(i, j)] = dRes;
		}
	}

	return mRes;
}

vec3d mat4d::operator*(const vec3d &vIn)
{
	double res[4];
	double v[4] = { vIn[0], vIn[1], vIn[2], 1.0 };

	for (int i = 0; i < 4; i++)
	{
		double dRes = 0.0;

		for (int j = 0; j < 4; j++)
		{
			dRes += mat[getMatIdx(i, j)] * v[j];
		}

		res[i] = dRes;
	}

	return vec3d (res[0], res[1], res[2]);
}

mat4d mat4d::operator+(const mat4d &mIn) const
{
	const mat4d &m = *this;
	mat4d mRes;

	for (int i = 0; i < 16; i++)
	{
		mRes[i] = m[i] + mIn[i];
	}

	return mRes;
}

bool mat4d::operator==(const mat4d &mIn) const
{
	const mat4d &m = *this;
	bool bRes = true;

	for (int i = 0; i < 16; i++)
	{
		bRes = bRes && OglEqual(m[i], mIn[i]);
	}

	return bRes;
}

mat4d mat4d::multiplyByVal(const double &dVal) const
{
	const mat4d &m = *this;
	mat4d mRes;

	for (int i = 0; i < 16; i++)
	{
		mRes[i] = m[i] * dVal;
	}

	return mRes;
}

mat4d &mat4d::setToRotation(const double &dAngle, const vec3d &ptOrig, const vec3d &vAxis)
{
	mat4d matS(0.0); // matS = vAxis x transpose(vAxis)
	const mat4d matI; // kIdentity
	mat4d &mR = *this;
	mat4d mTransl;

	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;

	matS[fnIdx(0, 1)] = vAxis.z();
	matS[fnIdx(0, 2)] = -vAxis.y();
	matS[fnIdx(1, 0)] = -vAxis.z();
	matS[fnIdx(1, 2)] = vAxis.x();
	matS[fnIdx(2, 0)] = vAxis.y();
	matS[fnIdx(2, 1)] = -vAxis.x();

	mTransl.setToTranslation(vec3d::kOrigin - ptOrig);

	double s = sin(dAngle);
	double c = 1.0 - cos(dAngle);
	const mat4d &matSsqr = matS * matS;
	const mat4d &matSbyS = matS.multiplyByVal(s);
	const mat4d &matSbyC = matSsqr.multiplyByVal(c);

	mR = matI + matSbyS + matSbyC;
	mR = mTransl * mR;
	return mR; //.transpose();
}

mat4d &mat4d::setToTranslation(const vec3d &vTransl)
{
	mat4d &m = *this;
	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;

	m[fnIdx(3, 0)] = vTransl[0];
	m[fnIdx(3, 1)] = vTransl[1];
	m[fnIdx(3, 2)] = vTransl[2];

	return m;
}

mat4d &mat4d::setToScale(const vec3d &vScale)
{
	mat4d &mRes = *this;
	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;

	mRes[fnIdx(0, 0)] *= vScale[0];
	mRes[fnIdx(1, 1)] *= vScale[1];
	mRes[fnIdx(2, 2)] *= vScale[2];
	mRes[fnIdx(3, 3)] *= 1.0;

	return mRes;
}

mat4d &mat4d::setCoordinateSystem(const vec3d &ptOrig, const vec3d &axisU, const vec3d &axisV, const vec3d &axisW)
{
	mat4d &m = *this;

	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;

	m[fnIdx(0, 0)] = axisU[0];
	m[fnIdx(1, 0)] = axisU[1];
	m[fnIdx(2, 0)] = axisU[2];

	m[fnIdx(0, 1)] = axisV[0];
	m[fnIdx(1, 1)] = axisV[1];
	m[fnIdx(2, 1)] = axisV[2];

	m[fnIdx(0, 2)] = axisW[0];
	m[fnIdx(1, 2)] = axisW[1];
	m[fnIdx(2, 2)] = axisW[2];

	m[fnIdx(3, 0)] = -ptOrig[0];
	m[fnIdx(3, 1)] = -ptOrig[1];
	m[fnIdx(3, 2)] = -ptOrig[2];

	return m;
}

mat4d &mat4d::transpose()
{
	mat4d &m = *this;
	mat4d mInit(*this);

	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[fnIdx(i, j)] = mInit[fnIdx(j, i)];
		}
	}

	return m;
}

int mat4d::getMatIdx(int i, int j)
{
	//const int c_nRows = 4;
	const int c_nCols = 4;

	return i * c_nCols + j;
}

mat4d lookAt(const vec3d &ptViewPostion, const vec3d &ptViewTarget, const vec3d &vViewUp)
{
	vec3d f = (ptViewTarget - ptViewPostion).normalize();
	vec3d s = f.crossProduct(vViewUp).normalize();
	vec3d u = s.normal().crossProduct(f).normalize();
	mat4d mRes, mTransl;
	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;

	mRes[fnIdx(0, 0)] = s.x();
	mRes[fnIdx(1, 0)] = s.y();
	mRes[fnIdx(2, 0)] = s.z();

	mRes[fnIdx(0, 1)] = u.x();
	mRes[fnIdx(1, 1)] = u.y();
	mRes[fnIdx(2, 1)] = u.z();

	mRes[fnIdx(0, 2)] = -f.x();
	mRes[fnIdx(0, 2)] = -f.y();
	mRes[fnIdx(0, 2)] = -f.z();

	mTransl.setToTranslation(ptViewPostion);
	mRes = mTransl * mRes;

//	mRes[fnIdx(0, 3)] = -left.dotProduct(ptViewPostion);
//	mRes[fnIdx(1, 3)] = -up.dotProduct(ptViewPostion);
//	mRes[fnIdx(2, 3)] = -forward.dotProduct(ptViewPostion);

	return mRes;
}

mat4d perspective(const double &dFOV, const double &dAspect, const double &dNear, const double &dFar)
{
	mat4d mRes(0.0);
	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;
	double dD = 1.0 / tan(OglRadians(dFOV / 2.0));

	mRes[fnIdx(0, 0)] = dD / dAspect;
	mRes[fnIdx(1, 1)] = dD;
	mRes[fnIdx(2, 2)] = (dNear + dFar) / (dNear - dFar);
	mRes[fnIdx(3, 2)] = (2.0 * dNear * dFar) / (dNear - dFar);
	mRes[fnIdx(2, 3)] = -1.0;

	return mRes;
}

mat4d ortho(const double &dLeft, const double &dRight, const double &dTop, const double &dBottom, const double &dNear, const double &dFar)
{
	mat4d mRes(0.0);
	typedef int (*F)(int, int); // Just for convenience
	F fnIdx = &mat4d::getMatIdx;

	mRes[fnIdx(0, 0)] = 2.0 / (dRight - dLeft);
	mRes[fnIdx(3, 0)] = -((dRight + dLeft) / (dRight - dLeft));
	mRes[fnIdx(1, 1)] = 2.0 / (dTop - dBottom);
	mRes[fnIdx(3, 1)] = -((dTop + dBottom) / (dTop - dBottom));
	mRes[fnIdx(2, 2)] = -2.0 / (dFar - dNear);
	mRes[fnIdx(3, 2)] = -((dFar + dNear) / (dFar - dNear));
	mRes[fnIdx(3, 3)] = 1.0;

	return mRes;
}

} // namespace OglGeomUtils

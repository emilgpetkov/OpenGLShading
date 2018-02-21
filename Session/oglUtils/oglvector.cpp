#include "oglvector.h"

#include <math.h>

namespace OglGeomUtils {

vec3d::vec3d() :
	vec{0.0, 0.0, 0.0}
{
}

vec3d::vec3d(const double &x, const double &y, const double &z) :
	vec{x, y, z}
{
}

vec3d::vec3d(const vec3d &v)
{
	vec3d &u = *this;
	u[0] = v[0];
	u[1] = v[1];
	u[2] = v[2];
}

vec3d::~vec3d()
{

}

const vec3d vec3d::kOrigin = vec3d(0.0, 0.0, 0.0);
const vec3d vec3d::kIdentity = vec3d(0.0, 0.0, 0.0);
const vec3d vec3d::kAxisX = vec3d(1.0, 0.0, 0.0);
const vec3d vec3d::kAxisY = vec3d(0.0, 1.0, 0.0);
const vec3d vec3d::kAxisZ = vec3d(0.0, 0.0, 1.0);

double vec3d::x() const
{
	return vec[0];
}

void vec3d::x(const double &x)
{
	vec[0] = x;
}

double vec3d::y() const
{
	return vec[1];
}

void vec3d::y(const double &y)
{
	vec[1] = y;
}

double vec3d::z() const
{
	return vec[2];
}

void vec3d::z(const double &z)
{
	vec[2] = z;
}

double *vec3d::getAsPointer()
{
	return vec;
}

void vec3d::getAsFloat(float vec3f[]) const
{
	vec3f[0] = static_cast<float>(vec[0]);
	vec3f[1] = static_cast<float>(vec[1]);
	vec3f[2] = static_cast<float>(vec[2]);
}

double vec3d::lenght() const
{
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

vec3d vec3d::crossProduct(const vec3d &v) const
{
	vec3d w;
	vec3d u = *this;

	w.x(u[1] * v[2] - u[2] * v[1]);
	w.y(u[2] * v[0] - u[0] * v[2]);
	w.z(u[0] * v[1] - u[1] * v[0]);

	return w;
}

double vec3d::dotProduct(const vec3d &v) const
{
	const vec3d &u = *this;
	double dRes = 0.0;

	for (int i = 0; i < 3; i++)
	{
		dRes += u[i] * v[i];
	}

	return dRes;
}

vec3d vec3d::normal() const
{
	vec3d vNorm(0.0, 0.0, 0.0);
	const vec3d &u = *this;
	double dLen = u.lenght();

	if (OglZero(dLen))
	{
		return vNorm;
	}

	vNorm = u / dLen;
	return vNorm;
}

vec3d &vec3d::normalize()
{
	vec3d &u = *this;
	double dLen = u.lenght();
	u = u / dLen;
	return u;
}

bool vec3d::isParallelTo(const vec3d &v) const
{
	return OglZero(this->crossProduct(v).lenght());
}

double vec3d::angleTo(const vec3d &v) const
{
	if (OglZero(this->lenght()) || OglZero(v.lenght()))
	{
		return 0.0;
	}

	return (this->dotProduct(v) / this->lenght());
}

bool vec3d::isPerpendicularTo(const vec3d &v) const
{
	return OglZero(this->dotProduct(v));
}

const double vec3d::operator[](int i) const
{
	return vec[i];
}

double &vec3d::operator[](int i)
{
	return vec[i];
}

vec3d vec3d::operator+(const vec3d &v) const
{
	const vec3d &u = *this;
	return vec3d(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

vec3d &vec3d::operator+=(const vec3d &v)
{
	vec3d &u = *this;
	u[0] += v[0]; u[1] += v[1]; u[2] += v[2];
	return u;
}

vec3d vec3d::operator-(const vec3d &v) const
{
	const vec3d &u = *this;
	return vec3d(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

vec3d vec3d::operator-() const
{
	const vec3d &u = *this;
	return vec3d(-u[0], -u[1], -u[2]);
}

vec3d vec3d::operator*(const double &scale) const
{
	const vec3d &u = *this;
	vec3d v;

	v.x(u[0] * scale);
	v.y(u[1] * scale);
	v.z(u[2] * scale);

	return v;
}

vec3d &vec3d::operator*=(const double &scale)
{
	vec3d &u = *this;
	u = u * scale;
}

vec3d vec3d::operator/(const double &scale) const
{
	const vec3d &u = *this;

	if (OglZero(scale))
	{
		return u;
	}

	vec3d v = u * (1.0 / scale);
	return v;
}

vec3d &vec3d::operator=(const vec3d &v)
{
	vec3d &u = *this;

	u.x(v[0]);
	u.y(v[1]);
	u.z(v[2]);

	return *this;
}

bool vec3d::operator==(const vec3d &v) const
{
	const vec3d &u = *this;

	return (u[0] == v[0] &&
			u[1] == v[1] &&
			u[2] == v[2]);
}

} // namespace OglGeomUtils

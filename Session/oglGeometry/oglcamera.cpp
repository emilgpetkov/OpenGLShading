#include "oglcamera.h"

// Class definition

OglCamera::OglCamera() :
	m_ptPosition(0.0, 0.0, 0.0),
	m_ptTarget(0.0, 0.0, 0.0),
	m_vUp(0.0, 0.0, 0.0),
	m_bPerspective(false),
	m_dFOV(0.0),
	m_dAspect(1.0),
	m_dNearPersp(0.0),
	m_dFarPersp(0.0),
	m_dLeft(0.0),
	m_dRight(0.0),
	m_dTop(0.0),
	m_dBottom(0.0),
	m_dNearOrtho(0.0),
	m_dFarOrtho(0.0)
{

}

OglCamera::OglCamera(const OglCamera &cam) :
	m_ptPosition(cam.getPosition()),
	m_ptTarget(cam.getTarget()),
	m_vUp(cam.getUpVector()),
	m_bPerspective(cam.getPerspective()),
	m_dFOV(cam.getFOV()),
	m_dAspect(cam.getAspect()),
	m_dNearPersp(cam.getNearDistancePersp()),
	m_dFarPersp(cam.getFarDistancePersp()),
	m_dNearOrtho(cam.getNearDistanceOrho()),
	m_dFarOrtho(cam.getFarDistanceOrtho())
{
	cam.getViewport(m_dLeft, m_dRight, m_dTop, m_dBottom);
}

OglCamera::~OglCamera()
{

}

void OglCamera::setUpVector(const vec3d &vUp)
{
	m_vUp = vUp;
}

vec3d OglCamera::getUpVector() const
{
	return m_vUp;
}

vec3d OglCamera::getLeftVector() const
{
	return m_vUp.crossProduct(getViewDir());
}

vec3d OglCamera::getViewDir() const
{
	return m_ptPosition - m_ptTarget;
}

vec3d OglCamera::getPosition() const
{
	return m_ptPosition;
}

void OglCamera::setPosition(const vec3d &ptPosition)
{
	m_ptPosition = ptPosition;
}

vec3d OglCamera::getTarget() const
{
	return m_ptTarget;
}

void OglCamera::setTarget(const vec3d &ptTarget)
{
	m_ptTarget = ptTarget;
}

bool OglCamera::getPerspective() const
{
	return m_bPerspective;
}

void OglCamera::setPerspective(bool bPerspective)
{
	m_bPerspective = bPerspective;
}

double OglCamera::getFOV() const
{
	return m_dFOV;
}

void OglCamera::setFOV(const double &dFOV)
{
	m_dFOV = dFOV;
}

double OglCamera::getAspect() const
{
	return m_dAspect;
}

void OglCamera::setAspect(const double &dAspect)
{
	m_dAspect = dAspect;
}

double OglCamera::getNearDistancePersp() const
{
	return m_dNearPersp;
}

void OglCamera::setNearDistancePersp(const double &dNear)
{
	m_dNearPersp = dNear;
}

double OglCamera::getFarDistancePersp() const
{
	return m_dFarPersp;
}

void OglCamera::setFarDistancePersp(const double &dFar)
{
	m_dFarPersp = dFar;
}

double OglCamera::getNearDistanceOrho() const
{
	return m_dNearOrtho;
}

void OglCamera::setNearDistanceOrtho(const double &dNear)
{
	m_dNearOrtho = dNear;
}

double OglCamera::getFarDistanceOrtho() const
{
	return m_dFarOrtho;
}

void OglCamera::setFarDistanceOrtho(const double &dFar)
{
	m_dFarOrtho = dFar;
}

void OglCamera::getViewport(double &dLeft, double &dRight, double &dTop, double &dBottom) const
{
	dLeft = m_dLeft;
	dRight = m_dRight;
	dTop = m_dTop;
	dBottom = m_dBottom;
}

void OglCamera::setViewport(const double &dLeft, const double &dRight, const double &dTop, const double &dBottom)
{
	m_dLeft = dLeft;
	m_dRight = dRight;
	m_dTop = dTop;
	m_dBottom = dBottom;
}

#ifndef OGLCAMERA_H
#define OGLCAMERA_H

#include "oglGeometry_Global.h"

#include "oglvector.h"
#include "oglMatrix.h"

using namespace OglGeomUtils;

// Class declaration
// OglCamera class is used to hold data needed to create the
// Model-View-Projection transformation
class OGLGEOMETRYSHARED_EXPORT OglCamera
{
public:
	// Public methods
	OglCamera(); // Default c-tor
	OglCamera(const OglCamera &cam); // Copy c-tor
	~OglCamera(); // D-tor

	// Getter/setter methods of the Up-vector
	vec3d getUpVector() const;
	void setUpVector(const vec3d &vUp);

	vec3d getLeftVector() const; // Get the Left-vector
	vec3d getViewDir() const; // Get the View-vector

	// Getter/setter methods of the camera's position
	vec3d getPosition() const;
	void setPosition(const vec3d &ptPosition);

	// Getter/setter methods of the camera's target
	vec3d getTarget() const;
	void setTarget(const vec3d &ptTarget);

	// Getter/setter methods of the perspective flag
	bool getPerspective() const;
	void setPerspective(bool bPerspective);

	// Getter/setter methods of the camera's Field of View
	double getFOV() const;
	void setFOV(const double &dFOV);

	// Getter/setter methods of the camera's aspect ratio
	double getAspect() const;
	void setAspect(const double &dAspect);

	// Getter/setter methods of the camera's Near distance when perspective is ON
	double getNearDistancePersp() const;
	void setNearDistancePersp(const double &dNear);

	// Getter/setter methods of the camera's Far distance when perspective is ON
	double getFarDistancePersp() const;
	void setFarDistancePersp(const double &dFar);

	// Getter/setter methods of the camera's Near distance when perspective is OFF, i.e. ortho
	double getNearDistanceOrho() const;
	void setNearDistanceOrtho(const double &dNear);

	// Getter/setter methods of the camera's Far distance when perspective is OFF, i.e. ortho
	double getFarDistanceOrtho() const;
	void setFarDistanceOrtho(const double &dFar);

	// Getter/setter methods of the viewport's position and size
	void getViewport(double &dLeft, double &dRight, double &dTop, double &dBottom) const;
	void setViewport(const double &dLeft, const double &dRight, const double &dTop, const double &dBottom);

private:
	// Private data
	vec3d m_ptPosition; // Camera's position
	vec3d m_ptTarget; // Camera's target
	vec3d m_vUp; // Camera's up-vector
	bool m_bPerspective; // Camera's perspective flag
	double m_dFOV; // Field of View
	double m_dAspect; // Aspect ratio
	double m_dNearPersp; // Near distance when perspective is ON
	double m_dFarPersp; // Far distance when perspective is ON
	double m_dLeft; // Viewport's Left parameter
	double m_dRight; // Viewport's Right parameter
	double m_dTop; // Viewport's Top parameter
	double m_dBottom; // Viewport's Bottom parameter
	double m_dNearOrtho; // Near distance when perspective is OFF, i.e. ortho
	double m_dFarOrtho; // Far distance when perspective is OFF, i.e. ortho
};

#endif // OGLCAMERA_H

#ifndef OGLRENDERER_H
#define OGLRENDERER_H

#include "oglRenderer_Global.h"
#include "oglGeomUtils.h"
#include "oglShader.h"
#include "oglcamera.h"
#include "oglSphere.h"

class OGLRENDERERSHARED_EXPORT OglRenderer
{
public:
	OglRenderer(); // C-tor
	OglRenderer(const OglRenderer &); // Copy c-tor sets default values of data
	~OglRenderer(); // D-tor

	// Setter/getter methods of view parameters
	void setView(const vec3d &position, const vec3d &target, const vec3d &upVector);
	void getView(vec3d &position, vec3d &target, vec3d &upVector) const;

	// Setter/getter methods of viewport's position and size
	void setViewport(const int &nX, const int &nY, const int &nWidth, const int &nHeight);
	void getViewport(int &nX, int &nY, int &nWidth, int &nHeight);

	// Turn the perspevtive On/Off
	void setIsPerspective(bool bIsPerspective);
	bool getIsPerspective() const;

	// Setter/getter methods of perspective parameters
	void setPerspective(const double &dFOV, const double &dAspect, const double &dNear, const double &dFar);
	void getPerspective(double &dFOV, double &dAspect, double &dNear, double &dFar);

	// Setter/getter methods of ortho parameters
	void setOrtho(const double &dLeft, const double &dRight,
				  const double &dTop, const double &dBottom,
				  const double &dNear, const double &dFar);
	void getOrtho(double &dLeft, double &dRight,
				  double &dTop, double &dBottom,
				  double &dNear, double &dFar);

	// Setter/getter methods of Level of Details
	void setLOD(const unsigned int &nLOD);
	unsigned int getLOD() const;

	// Set geometry and elements' data
	// Do NOT delete pData after passing it as an argument. Otherwise an unexpected behaviour may occur
	void setGeometry(float *pData, const unsigned int &nVertCount, const unsigned int &nComponentsPerVertex, const int &nFlags);
	void setElements(unsigned int *pData, const unsigned int &nElmCount);
	void doRender(); // Render
	void initialize(); // Initialize

protected:
	void renderFractals(const mat4d &mInitialTransf, unsigned int nLOD);

private:
	bool m_bIsInitialized; // Need to initialize?
	/*
	 * {3 * coords}, {3 * normals}, {3 * color}, {2 * texture coords}
	 * {x, y, z}, {nx, ny, nz}, {r, g, b}, {u, v}
	*/
	float *m_pVertexData; // Geometry vertex data
	unsigned int m_unVertsCount; // Count of elements' dat
	int m_nFlags; // Flags designating which vertex parameters are passed in the vertex data
	// Count of components per vertex, i.e. vertex coordinates plus all the corresponding data
	// set as bits-on in m_nFlags
	unsigned int m_unComponentsPerVertex;

	unsigned int *m_pElements; // Geometry elements' data
	unsigned int m_unElmsCount; // Count of elements' data

	OglShader *m_pShader; // Current shader class
	unsigned int m_unVao; // Vertex array object
	unsigned int m_unVbo; // Vertex buffer object
	unsigned int m_unEbo; // Elements buffer data

	OglCamera *m_pCamera; // Camera to hold view's parameters

	int m_nViewport[4]; // Array to hold the viewport's position and size

	unsigned int m_unLOD; // Level of detail
};

#endif // OGLRENDERER_H

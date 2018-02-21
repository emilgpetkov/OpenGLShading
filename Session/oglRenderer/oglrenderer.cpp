#include "oglrenderer.h"

#include <GL/gl.h>
#include "GL/glut.h"
#include "GL/glu.h"
#include "GL/glx.h"
#include "GLES3/gl3.h"
#include "GL/glext.h"

#include <math.h>

#include "oglMatrix.h"

OglRenderer::OglRenderer() :
	m_bIsInitialized(false),
	m_pVertexData(nullptr),
	m_unVertsCount(0u),
	m_unComponentsPerVertex(0u),
	m_nFlags(OglSpheref::vpNone),
	m_pElements(nullptr),
	m_unElmsCount(0),
	m_pShader(nullptr),
	m_unVao(0),
	m_unVbo(0),
	m_unEbo(0),
	m_pCamera(nullptr),
	m_nViewport{ 0 },
	m_unLOD(0)
{

}

OglRenderer::OglRenderer(const OglRenderer &) :
	m_bIsInitialized(false),
	m_pVertexData(nullptr),
	m_unVertsCount(0u),
	m_unComponentsPerVertex(0u),
	m_nFlags(OglSpheref::vpNone),
	m_pElements(nullptr),
	m_unElmsCount(0),
	m_pShader(nullptr),
	m_unVao(0),
	m_unVbo(0),
	m_unEbo(0),
	m_pCamera(nullptr),
	m_nViewport{ 0 },
	m_unLOD(0)
{
	/*do nothing*/
}

OglRenderer::~OglRenderer()
{
	// Free the previously allocated data and buffers
	if (m_pShader != nullptr)
	{
		delete m_pShader;
		m_pShader = nullptr;
	}

	if (m_unVao != 0)
	{
		glDeleteVertexArrays(1, &m_unVao);
	}

	if (m_unVbo != 0)
	{
		glDeleteBuffers(1, &m_unVbo);
	}

	if (m_unEbo != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_unEbo);
	}

	if (m_pCamera != nullptr)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

void OglRenderer::setView(const vec3d &position, const vec3d &target, const vec3d &upVector)
{
	// Set view parameters through the camera
	if (m_pCamera == nullptr)
	{
		m_pCamera = new OglCamera;
	}

	m_pCamera->setPosition(position);
	m_pCamera->setTarget(target);
	m_pCamera->setUpVector(upVector);
}

void OglRenderer::getView(vec3d &position, vec3d &target, vec3d &upVector) const
{
	// Get view parameters through the camera
	position = vec3d(0.0, 0.0, 0.0);
	target = vec3d(0.0, 0.0, 0.0);
	upVector = vec3d(0.0, 0.0, 0.0);

	if (m_pCamera == nullptr)
	{
		return;
	}

	position = m_pCamera->getPosition();
	target = m_pCamera->getTarget();
	upVector = m_pCamera->getUpVector();
}

void OglRenderer::setViewport(const int &nX, const int &nY, const int &nWidth, const int &nHeight)
{
	m_nViewport[0] = nX;
	m_nViewport[1] = nY;
	m_nViewport[2] = nWidth;
	m_nViewport[3] = nHeight;
}

void OglRenderer::getViewport(int &nX, int &nY, int &nWidth, int &nHeight)
{
	nX = m_nViewport[0];
	nY = m_nViewport[1];
	nWidth = m_nViewport[2];
	nHeight = m_nViewport[3];
}

void OglRenderer::setIsPerspective(bool bIsPerspective)
{
	if (m_pCamera == nullptr)
	{
		m_pCamera = new OglCamera;
	}

	m_pCamera->setPerspective(bIsPerspective);
}

bool OglRenderer::getIsPerspective() const
{
	if (m_pCamera == nullptr)
	{
		return false;
	}

	return m_pCamera->getPerspective();
}

void OglRenderer::setPerspective(const double &dFOV, const double &dAspect, const double &dNear, const double &dFar)
{
	if (m_pCamera == nullptr)
	{
		m_pCamera = new OglCamera;
	}

	m_pCamera->setFOV(dFOV);
	m_pCamera->setAspect(dAspect);
	m_pCamera->setNearDistancePersp(dNear);
	m_pCamera->setFarDistancePersp(dFar);
}

void OglRenderer::getPerspective(double &dFOV, double &dAspect, double &dNear, double &dFar)
{
	dFOV = 0.0;
	dAspect = 0.0;
	dNear = 0.0;
	dFar = 0.0;

	if (m_pCamera == nullptr)
	{
		return;
	}

	dFOV = m_pCamera->getFOV();
	dAspect = m_pCamera->getAspect();
	dNear = m_pCamera->getNearDistancePersp();
	dFar = m_pCamera->getFarDistancePersp();
}

void OglRenderer::setOrtho(const double &dLeft, const double &dRight, const double &dTop, const double &dBottom, const double &dNear, const double &dFar)
{
	if (m_pCamera == nullptr)
	{
		m_pCamera = new OglCamera;
	}

	m_pCamera->setViewport(dLeft, dRight, dTop, dBottom);
	m_pCamera->setNearDistanceOrtho(dNear);
	m_pCamera->setFarDistanceOrtho(dFar);
}

void OglRenderer::getOrtho(double &dLeft, double &dRight, double &dTop, double &dBottom, double &dNear, double &dFar)
{
	dLeft = 0.0;
	dRight = 0.0;
	dTop = 0.0;
	dBottom = 0.0;
	dNear = 0.0;
	dFar = 0.0;

	if (m_pCamera == nullptr)
	{
		return;
	}

	m_pCamera->getViewport(dLeft, dRight, dTop, dBottom);
	dNear = m_pCamera->getNearDistanceOrho();
	dFar = m_pCamera->getFarDistanceOrtho();
}

void OglRenderer::setLOD(const unsigned int &nLOD)
{
	m_unLOD = nLOD;
}

unsigned int OglRenderer::getLOD() const
{
	return m_unLOD;
}

void OglRenderer::doRender()
{
	// Do the actual rendering
	glClearColor(0.75f, 0.75f, 0.75f, 1.0); // Set color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer bits
	glEnable(GL_DEPTH_TEST); // Enable depth-testing

	// Set OpenGL viewport
	glViewport(m_nViewport[0], m_nViewport[1], m_nViewport[2], m_nViewport[3]);

	if (m_pShader == nullptr || ! m_bIsInitialized)
	{
		return;
	}

	// Use the current shader
	m_pShader->use();

	if (m_pCamera == nullptr)
	{
		return;
	}

	const vec3d &ptPos = m_pCamera->getPosition();
	const vec3d &ptTarget = m_pCamera->getTarget();

	// Get the view matrix
	mat4d matView = OglGeomUtils::lookAt(ptPos, ptTarget, m_pCamera->getUpVector());
	mat4d matProj;

	// Get projection parameters
	double dFOV = 0.0, dAspect = 0.0, dNearPersp = 0.0, dFarPersp = 0.0;
	getPerspective(dFOV, dAspect, dNearPersp, dFarPersp);

	double dLeft = 0.0, dRight = 0.0, dTop = 0.0, dBottom = 0.0;
	double dNearOrtho = 0.0, dFarOrtho = 0.0;
	getOrtho(dLeft, dRight, dTop, dBottom, dNearOrtho, dFarOrtho);

	// Get the projection matrix considering the perspective flag
	if (getIsPerspective())
	{
		matProj = OglGeomUtils::perspective(dFOV, dAspect, dNearPersp, dFarPersp);
	}
	else
	{
		matProj = OglGeomUtils::ortho(dLeft, dRight, dTop, dBottom, dNearOrtho, dFarOrtho);
	}

	// Set the shader's parameters
	// View Position
	float ptPosF[3];
	ptPos.getAsFloat(ptPosF);
	m_pShader->setVec3("viewPos", ptPosF);

	float fmatView[16] = { 0.0f }, fmatProj[16] = { 0.0f };
	matView.getAsFloat(fmatView);
	matProj.getAsFloat(fmatProj);

	// View and projection matrices
	m_pShader->setMat4("mProjection", fmatProj,  false);
	m_pShader->setMat4("mView", fmatView, false);

	// Draw the geometry
	{
//		double dTmpAng = OglRadians(45.0);
//		double dVerAng = OglRadians(-45.0);

//		vec3d vU(cos(dTmpAng) * cos(dVerAng), cos(dVerAng) * sin(dTmpAng), sin(dVerAng));
//		vec3d vV(vec3d::kAxisZ.crossProduct(vU).normal()), vW(vU.crossProduct(vV).normal());

		{
			// Bind the vertex array object
			glBindVertexArray(m_unVao);

			// Set initial transformation
			mat4d mTransf(mat4d::kIdentity);
			float matModelF[16];

			// Model matrix
			mTransf.getAsFloat(matModelF);
			m_pShader->setMat4("mModel", matModelF, false);

			// Draw the base sphere as quad strips
			glDrawElements(GL_QUAD_STRIP, m_unElmsCount, GL_UNSIGNED_INT, 0);

			// Render the fractals
			renderFractals(mTransf, m_unLOD);

			// Unbind the vertex array object
			glBindVertexArray(0);
		}
	}
}

void OglRenderer::initialize()
{
	if (m_bIsInitialized || m_pVertexData == nullptr || ! (m_nFlags & OglSpheref::vpCoords))
	{
		return;
	}

	// Create the shader class
	m_pShader = new OglShader();

	const unsigned int &unCPV = m_unComponentsPerVertex;
	int nAttribIndex = 0;
	int nAttribOffset = 0;

	// Generate and bind the vertex array, vertex buffer and element buffer
	glGenVertexArrays(1, &m_unVao);
	glGenBuffers(1, &m_unVbo);
	glGenBuffers(1, &m_unEbo);
	glBindVertexArray(m_unVao);

	// Bind the buffer data to the corresponding array buffer
	// Vertex data
	if (m_pVertexData != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_unVbo);
		glBufferData(GL_ARRAY_BUFFER, m_unVertsCount * unCPV * sizeof(float), m_pVertexData, GL_STATIC_DRAW);
	}

	// Elements' data
	if (m_pElements != nullptr)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_unElmsCount * sizeof(unsigned int), m_pElements, GL_STATIC_DRAW);
	}

	// Define how the vertex components are to be read by OpenGL, i.e.
	/*
	 * {3 * coords}, {3 * normals}, {3 * color}, {2 * texture coords}
	 * {x, y, z}, {nx, ny, nz}, {r, g, b}, {u, v}
	*/
	// The m_nFlags are used to check which component is provided by the vertex data

	{
		glVertexAttribPointer(nAttribIndex, 3, GL_FLOAT, GL_FALSE, unCPV * sizeof(float),
							  (void*)(nAttribOffset * sizeof(float)));
		glEnableVertexAttribArray(nAttribIndex);
		nAttribIndex += 1;
		nAttribOffset += 3;
	}

	if (m_nFlags & OglSpheref::vpNormals)
	{
		glVertexAttribPointer(nAttribIndex, 3, GL_FLOAT, GL_FALSE, unCPV * sizeof(float),
							  (void*)(nAttribOffset * sizeof(float)));
		glEnableVertexAttribArray(nAttribIndex);
		nAttribIndex += 1;
		nAttribOffset += 3;
	}

	if (m_nFlags & OglSpheref::vpColors)
	{
		glVertexAttribPointer(nAttribIndex, 3, GL_FLOAT, GL_FALSE, unCPV * sizeof(float),
							  (void*)(nAttribOffset * sizeof(float)));
		glEnableVertexAttribArray(nAttribIndex);
		nAttribIndex += 1;
		nAttribOffset += 3;
	}

	if (m_nFlags & OglSpheref::vpTextures)
	{
		glVertexAttribPointer(nAttribIndex, 2, GL_FLOAT, GL_FALSE, unCPV * sizeof(float),
							  (void*)(nAttribOffset * sizeof(float)));
		glEnableVertexAttribArray(nAttribIndex);
		nAttribIndex += 1;
		nAttribOffset += 2;
	}

	m_bIsInitialized = true; // Already initialized
}

void OglRenderer::renderFractals(const mat4d &mInitialTransf, unsigned int nLOD)
{
	// The method is called recursively for while nLOD > 0. Each sphere is assumed as base for its children.
	// In order that the latter are transformed correctly the base sphere's transformation is passed as mInitialTransf parameter.
	// Right after a sphere is drawn the method is called in order to draw the first sphere's child. As soon as it is drawn,
	// the method is called again to draw its first child, and so on. The first recursive call-chain breaks right after each first child
	// of each first sphere-child has been drawn. Then, briefly said, the recursive call-chains are executed for each branch from bottom to top, i.e.
	// starting from their leaves until the root is reached.

	// Need to draw in the first place?
	if (nLOD <= 0)
	{
		return;
	}

	double dDetAng = 2.0 * M_PI / 6.0;
	double dTmpAng = 0.0;
	double dMove = 1.0 + 1.0 / 3.0;

	{
		// Draw the spheres on the equator
		for (; dTmpAng <= 2.0 * M_PI; dTmpAng += dDetAng)
		{
			// Set local transformation in respect of the local coordinates of the base sphere
			mat4d mTransf(mat4d::kIdentity);
			mat4d mRot(mat4d::kIdentity);
			mat4d mTransl(mat4d::kIdentity);
			mat4d mScale;

			mTransl.setToTranslation(vec3d(dMove, 0.0, 0.0));
			mRot.setToRotation(dTmpAng, vec3d::kOrigin, vec3d::kAxisZ);
			mScale.setToScale(vec3d(1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0));

			// Additionally transform the local transormation by the initial transformation (mInitialTransf)
			mTransf = mInitialTransf * (mRot * mTransl * mScale);

			mat4d mFrac;
			mFrac.setToRotation(M_PI / 2.0, vec3d::kOrigin, -vec3d::kAxisY);
			mTransf = mTransf * mFrac;

			// Set the Model matrix to the shader
			float matModelF[16];
			mTransf.getAsFloat(matModelF);
			m_pShader->setMat4("mModel", matModelF, false);

			// Draw the current sphere
			glDrawElements(GL_QUAD_STRIP, m_unElmsCount, GL_UNSIGNED_INT, 0);

			// Call the method recursively
			renderFractals(mTransf, nLOD-1);
		}
	}

	{
		double dDetAng = 2.0 * M_PI / 3.0;
		double dTmpAng = 2.0 * M_PI / 12.0;
		double dMove = 1.0 + 1.0 / 3.0;
		double dVerAng = OglRadians(45.0);

		// Draw the spheres in the northern hemisphere
		for (; dTmpAng <= 2.0 * M_PI; dTmpAng += dDetAng)
		{
			// Set local transformation in respect of the local coordinates of the base sphere
			mat4d mTransf(mat4d::kIdentity);
			mat4d mRot(mat4d::kIdentity);
			mat4d mTransl(mat4d::kIdentity);
			mat4d mScale;

			vec3d vW(cos(dTmpAng) * cos(dVerAng), cos(dVerAng) * sin(dTmpAng), sin(dVerAng));
			vec3d vV(vec3d::kAxisZ.crossProduct(vW).normal()), vU(vW.crossProduct(vV).normal());

			mTransl.setToTranslation(vec3d(dMove, 0.0, 0.0));
			mRot.setCoordinateSystem(vec3d::kOrigin, vU, vV, vW);
			mScale.setToScale(vec3d(1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0));

			// Additionally transform the local transormation by the initial transformation (mInitialTransf)
			mTransf = mInitialTransf * (mRot * mTransl * mScale);

			mat4d mFrac;
			mFrac.setToRotation(M_PI / 2.0, vec3d::kOrigin, -vec3d::kAxisY);
			mTransf = mTransf * mFrac;

			// Set the Model matrix to the shader
			float matModelF[16];
			mTransf.getAsFloat(matModelF);
			m_pShader->setMat4("mModel", matModelF, false);

			// Draw the current sphere
			glDrawElements(GL_QUAD_STRIP, m_unElmsCount, GL_UNSIGNED_INT, 0);

			// Call the method recursively
			renderFractals(mTransf, nLOD-1);
		}
	}
}

void OglRenderer::setGeometry(float *pData, const unsigned int &nVertCount, const unsigned int &nComponentsPerVertex, const int &nFlags)
{
	// Set the geometry data as a reference
	m_pVertexData = pData;
	m_unVertsCount = nVertCount;
	m_unComponentsPerVertex = nComponentsPerVertex;
	m_nFlags = nFlags;
}

void OglRenderer::setElements(unsigned int *pData, const unsigned int &nElmCount)
{
	// Set the elements' data as a reference
	m_pElements = pData;
	m_unElmsCount = nElmCount;
}


#include "oglSphere.h"

#include <math.h>
#include <iostream>
#include <iomanip>

#include "oglGeomUtils.h"

using namespace std;

OglSpheref::OglSpheref() :
	m_dRadius(1.0),
	m_ptCenter(vec3d::kIdentity),
	m_pVertexData(nullptr),
	m_pElements(nullptr),
	m_unVertsCount(0u),
	m_unComponentsPerVertex(VertexParams::vpNone),
	m_unElmsCount(0u),
	m_unSmoothU(24u),
	m_unSmoothV(24u)
{

}

OglSpheref::OglSpheref(const OglSpheref &sphere) :
	m_dRadius(sphere.getRadius()),
	m_ptCenter(sphere.getCenter()),
	m_unSmoothU(sphere.getSmoothU()),
	m_unSmoothV(sphere.getSmoothV())
{
	// Clear the vertex data and the elements' data, if any is available
	// and reset the pointer
	if (m_pVertexData != nullptr)
	{
		delete[] m_pVertexData;
		m_pVertexData = nullptr;

		m_unVertsCount = 0u;
		m_unComponentsPerVertex = 0u;
		m_nFlags = OglSpheref::VertexParams::vpNone;
	}

	if (m_pElements != nullptr)
	{
		delete[] m_pElements;
		m_pElements = nullptr;
		m_unElmsCount = 0u;
	}

	// Get the vertex data as a pointer
	float *pData = nullptr;
	sphere.getVertexData(pData, m_unVertsCount, m_unComponentsPerVertex, m_nFlags);

	// Copy the data into the current object's vertex data
	if (pData != nullptr)
	{
		unsigned int nDataSize = m_unVertsCount * m_unComponentsPerVertex;
		m_pVertexData = new float[nDataSize];

		for (unsigned int i = 0u; i < nDataSize; i++)
		{
			m_pVertexData[i] = pData[i];
		}
	}

	// Get the elements' data as a pointer
	unsigned int *pElems = nullptr;
	sphere.getElements(pElems, m_unElmsCount);

	// Copy the elements' data into the current object's elements' data
	if (pElems != nullptr)
	{
		unsigned int nElemSize = m_unElmsCount;
		m_pElements = new unsigned int[nElemSize];

		for (unsigned int i = 0u; i < nElemSize; i++)
		{
			m_pElements[i] = pElems[i];
		}
	}
}

OglSpheref::~OglSpheref()
{
	// Clear the vertex data and the elements' data, if any is available
	// and reset the pointer
	if (m_pVertexData != nullptr)
	{
		delete[] m_pVertexData;
		m_pVertexData = nullptr;

		m_unVertsCount = 0u;
		m_unComponentsPerVertex = VertexParams::vpNone;
	}

	if (m_pElements != nullptr)
	{
		delete[] m_pElements;
		m_pElements = nullptr;
		m_unElmsCount = 0u;
	}
}

void OglSpheref::setCenter(const vec3d &ptCenter)
{
	m_ptCenter = ptCenter;
}

const vec3d &OglSpheref::getCenter() const
{
	return m_ptCenter;
}

void OglSpheref::setRadius(const double &dRadius)
{
	m_dRadius = dRadius;
}

double OglSpheref::getRadius() const
{
	return m_dRadius;
}

void OglSpheref::setSmoothU(const unsigned int &nSU)
{
	m_unSmoothU = nSU;
}

unsigned int OglSpheref::getSmoothU() const
{
	return m_unSmoothU;
}

void OglSpheref::setSmoothV(const unsigned int &nSV)
{
	m_unSmoothV = nSV;
}

unsigned int OglSpheref::getSmoothV() const
{
	return m_unSmoothV;
}

mat4d OglSpheref::getTransform() const
{
	mat4d mModel;
	mModel.setCoordinateSystem(m_ptCenter, vec3d::kAxisX, vec3d::kAxisY, vec3d::kAxisZ);
	return mModel;
}

void OglSpheref::generateVertexData(float *&pData, unsigned int &nVertCount, unsigned int &nComponentsPerVertex, int &snVertexFlags)
{
	// Clear the elements' data, if any is available
	// and reset the pointer
	if (m_pVertexData != nullptr)
	{
		delete[] m_pVertexData;
		m_pVertexData = nullptr;

		m_unVertsCount = 0u;
		m_unComponentsPerVertex = 0u;
		snVertexFlags = OglSpheref::VertexParams::vpNone;
	}

	// Generate sphere:
	// phi ~ [0; 2.0 * PI] -> horizontal angle, i.e. parallel to XY
	// psi ~ [-PI / 2.0; PI / 2.0] -> vertical angle, i.e. perpendicular to XY
	// The normals of each vertex is the unit vector of the center-to-point vector
	unsigned int unCountPhi = m_unSmoothU;
	unsigned int unCountPsi = m_unSmoothV;
	double phiMin = 0.0, psiMin = -M_PI_2;
	double phiMax = 2.0 * M_PI, psiMax = M_PI_2;
	double dtPhi = (phiMax - phiMin) / static_cast<double>(unCountPhi);
	double dtPsi = (psiMax - psiMin) / static_cast<double>(unCountPsi);
	double dTmpPhi = phiMin, dTmpPsi = psiMin;

	// Allocate memory for the vertex data
	m_unVertsCount = (unCountPhi + 1) * (unCountPsi + 1);
	m_nFlags = vpCoords | vpNormals; // We'll set the coordinates and the normals of the vertices
	m_unComponentsPerVertex = 6u; // We need six unsigned ints
	m_pVertexData = new float[m_unVertsCount * m_unComponentsPerVertex]; // The total amount of floats in the array

	unsigned int idx = 0u; // Set an index

	for (; OglLessEqual(dTmpPsi, psiMax); dTmpPsi += dtPsi)
	{
		// Iterate throughout the vertical angle range
		double dNz = sin(dTmpPsi); // z-Normal
		double dZ = m_dRadius * sin(dTmpPsi) + m_ptCenter.z(); // z-Coordinate

		// Set the temporary phi-angle
		dTmpPhi = phiMin;

		for (; OglLessEqual(dTmpPhi, phiMax); dTmpPhi += dtPhi, idx++)
		{
			// Iterate throughout the horizontal angle range
			double dNx = cos(dTmpPsi) * cos(dTmpPhi); // x-Normal
			double dNy = cos(dTmpPsi) * sin(dTmpPhi); // y-Normal
			double dX = m_dRadius * cos(dTmpPsi) * cos(dTmpPhi) + m_ptCenter.x(); // x-Coordinate
			double dY = m_dRadius * cos(dTmpPsi) * sin(dTmpPhi) + m_ptCenter.y(); // y-Coordinate

			// Set the coordinates and the normal of each vertex
			m_pVertexData[idx] = static_cast<float>(dX);
			m_pVertexData[++idx] = static_cast<float>(dY);
			m_pVertexData[++idx] = static_cast<float>(dZ);
			m_pVertexData[++idx] = static_cast<float>(dNx);
			m_pVertexData[++idx] = static_cast<float>(dNy);
			m_pVertexData[++idx] = static_cast<float>(dNz);
		}
	}

	// Output the generated data
	pData = m_pVertexData;
	nVertCount = m_unVertsCount;
	nComponentsPerVertex = m_unComponentsPerVertex;
	snVertexFlags = m_nFlags;
}

void OglSpheref::generateElements(unsigned int *&pElms, unsigned int &nElmCount)
{
	// Clear the elements' data, if any is available
	// and reset the pointer
	if (m_pElements != nullptr)
	{
		delete[] m_pElements;
		m_pElements = nullptr;
		m_unElmsCount = 0u;
	}

	// Allocate and set the elements' data. The sphere is going to be drawn as a quads stripe
	unsigned int unCountPhi = m_unSmoothU;
	unsigned int unCountPsi = m_unSmoothV;

	m_unElmsCount = 2 * (unCountPhi + 1) * (unCountPsi + 1);
	m_pElements = new unsigned int[m_unElmsCount];

	unsigned int idx = 0u;

	for (unsigned int i = 0u; i <= unCountPsi; i++)
	{
		for (unsigned int j = 0u; j <= unCountPhi; j++, idx++)
		{
			m_pElements[idx] = i * unCountPhi + j;
			m_pElements[++idx] = (i + 1) * unCountPhi + (j + 1);
		}
	}

	// Output the data
	pElms = m_pElements;
	nElmCount = m_unElmsCount;
}

void OglSpheref::getVertexData(float *&pData, unsigned int &nVertCount, unsigned int &nComponentsPerVertex, int &snVertexFlags) const
{
	// Get the data as a reference. NON-copy
	pData = m_pVertexData;
	nVertCount = m_unVertsCount;
	nComponentsPerVertex = m_unComponentsPerVertex;
	snVertexFlags = m_nFlags;
}

void OglSpheref::getElements(unsigned int *&pElms, unsigned int &nElmCount) const
{
	// Get the data as a reference. NON-copy
	pElms = m_pElements;
	nElmCount = m_unElmsCount;
}


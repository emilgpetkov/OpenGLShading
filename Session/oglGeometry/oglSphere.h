#ifndef OGLSPHERE_H
#define OGLSPHERE_H

#include "oglGeometry_Global.h"

#include "oglvector.h"
#include "oglMatrix.h"

using namespace OglGeomUtils;

// Class used to hold the data of the current geometry, the Sphere
class OGLGEOMETRYSHARED_EXPORT OglSpheref
{
public:
	// Public methods
	OglSpheref(); // Default c-tor
	OglSpheref(const OglSpheref &sphere); // Copy c-tor
	~OglSpheref(); // D-tor

	// Enum used to set flags which properties are passed to the vertex data
	enum VertexParams
	{
		vpNone     = 0x00000,
		vpCoords   = 0x00001,
		vpNormals  = 0x00004,
		vpColors   = 0x00008,
		vpTextures = 0x00010
	};

	// Setter/getter methods of the sphere's center
	void setCenter(const vec3d &ptCenter);
	const vec3d &getCenter() const;

	// Setter/getter methods of the sphere's radius
	void setRadius(const double &dRadius);
	double getRadius() const;

	// Setter/getter methods of the sphere's smoothness in U, i.e.
	// parallel to WCS XY
	void setSmoothU(const unsigned int &nSU);
	unsigned int getSmoothU() const;

	// Setter/getter methods of the sphere's smoothness in V, i.e.
	// perpendicular to WCS XY
	void setSmoothV(const unsigned int &nSV);
	unsigned int getSmoothV() const;

	// Retrieve the transformation matrix
	mat4d getTransform() const;

	// Generate the vertex data and elements' array
	void generateVertexData(float *&pData, unsigned int &nVertCount, unsigned int &nComponentsPerVertex, int &snVertexFlags);
	void generateElements(unsigned int *&pElms, unsigned int &nElmCount);

	// Get the vertex and the elements' data as references. NON-copy
	void getVertexData(float *&pData, unsigned int &nVertCount, unsigned int &nComponentsPerVertex, int &snVertexFlags) const;
	void getElements(unsigned int *&pElms, unsigned int &nElmCount) const;

private:
	// Private data
	double m_dRadius; // Sphere's radius
	vec3d m_ptCenter; // Sphere's center

	float *m_pVertexData; // Sphere's vertex data

	unsigned int m_unVertsCount; // Count of generated vertices
	int m_nFlags; // Flags designating which vertex parameters are passed in the vertex data
	// Count of components per vertex, i.e. vertex coordinates plus all the corresponding data
	// set as bits-on in m_nFlags
	unsigned int m_unComponentsPerVertex;

	unsigned int *m_pElements; // Sphere's element's data
	unsigned int m_unElmsCount; // Count of elements

	unsigned int m_unSmoothU; // Number of segments in U-direction, i.e. parallel to XY
	unsigned int m_unSmoothV; // Number of segments in V-direction, i.e. perpendicular to XY

};

#endif // OGLSPHERE_H

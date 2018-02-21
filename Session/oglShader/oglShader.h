#ifndef OGLSHADER_H
#define OGLSHADER_H

//#include "oglabstractshader.h"

#include "oglShader_Global.h"

class OGLSHADERSHARED_EXPORT OglShader
{
public:
	// Public methods
	OglShader(const char* csVertexShaderPath, const char* csFragmentShaderPath); // C-tor
	OglShader(); // Default c-tor
	OglShader(const OglShader &); // Copy c-tor sets default values of data
	~OglShader(); // D-tor

	void use() const;
	void setBool(const char *sName, bool bValue) const;
	void setInt(const char *sName, const int &nValue) const;
	void setFloat(const char *sName, const float &fValue) const;
	void setVec3(const char *sName, const float *vec) const;
	void setMat4(const char *sName, const float *mat, const bool bTranspose) const;

private:
	// Private data
	unsigned int m_unProgramID; // Shader program ID
};

#endif // OGLSHADER_H

#ifndef OGLABSTRACTSHADER_H
#define OGLABSTRACTSHADER_H

#include "oglShader_Global.h"

#include <string>

using namespace std;

class OGLSHADERSHARED_EXPORT OglAbstractShader
{
public:
	OglAbstractShader(const char*, const char*);
	virtual ~OglAbstractShader();

	virtual void use() const = 0;
	virtual void setBool(const string &sName, bool bValue) const = 0;
	virtual void setInt(const string &sName, const int &nValue) const = 0;
	virtual void setFloat(const string &sName, const float &fValue) const = 0;

private:
	unsigned int m_unProgramID; // Shader program ID
};

#endif // OGLABSTRACTSHADER_H

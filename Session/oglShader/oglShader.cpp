#include "oglShader.h"

#include <GL/gl.h>
#include "GL/glut.h"
#include "GL/glu.h"
#include "GL/glx.h"
#include "GLES3/gl3.h"
#include "GL/glext.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

OglShader::OglShader(const char *csVertexShaderPath, const char *csFragmentShaderPath) :
	m_unProgramID(0)
{
	// Please, see the default c-tor for comments
	ifstream fVertShader;
	fVertShader.open(csVertexShaderPath, ios_base::in);

	if (! fVertShader.is_open())
	{
		cout << "ERROR::SHADER::FILE_NOT_OPEN" << endl;
	}

	stringstream ssShader("");
	ssShader << fVertShader.rdbuf();
	fVertShader.close();

	string strVertShader = ssShader.str();
	const char *sVertShaderCode = strVertShader.c_str();
	unsigned int unVertShaderID = 0;
	int nSuccess = 0;
	const int c_nLogSize = 512;
	char sInfoLog[c_nLogSize];

	unVertShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(unVertShaderID, 1, &sVertShaderCode, NULL);
	glCompileShader(unVertShaderID);
	glGetShaderiv(unVertShaderID, GL_COMPILE_STATUS, &nSuccess);

	if (! nSuccess)
	{
		glGetShaderInfoLog(unVertShaderID, c_nLogSize, NULL, sInfoLog);
		cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << sInfoLog << endl;
	}

	ifstream fFragShader;
	fFragShader.open(csFragmentShaderPath, ios_base::in);

	if (! fFragShader.is_open())
	{
		cout << "ERROR::FRAGMENT::SHADER::FILE_NOT_OPEN" << endl;
	}

	ssShader.str("");
	ssShader << fFragShader.rdbuf();
	fVertShader.close();

	string strFragShader = ssShader.str();
	const char *sFragShaderCode = strFragShader.c_str();
	unsigned int unFragShaderID = 0;

	nSuccess = 0;
	unFragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(unFragShaderID, 1, &sFragShaderCode, NULL);
	glCompileShader(unFragShaderID);
	glGetShaderiv(unFragShaderID, GL_COMPILE_STATUS, &nSuccess);

	if (! nSuccess)
	{
		glGetShaderInfoLog(unFragShaderID, c_nLogSize, NULL, sInfoLog);
		cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << sInfoLog << endl;
	}

	m_unProgramID = glCreateProgram();
	glAttachShader(m_unProgramID, unVertShaderID);
	glAttachShader(m_unProgramID, unFragShaderID);
	glLinkProgram(m_unProgramID);
	glGetProgramiv(m_unProgramID, GL_LINK_STATUS, &nSuccess);

	if (! nSuccess)
	{
		glGetProgramInfoLog(m_unProgramID, c_nLogSize, NULL, sInfoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << sInfoLog << endl;
	}

	glDeleteShader(unVertShaderID);
	glDeleteShader(unFragShaderID);
}

OglShader::OglShader() :
	m_unProgramID(0)
{
	// The vertex and fragment shaders are embedded directly avoiding use of external files
	// Vertex shader reads the vertsx position and normals as layout in variables and
	// the transformation Model-to-View-to-Projection matrices,
	// sets the fragment position using gl_Position and
	// ouputs it together with the fragment's normal and the color, which is set
	// to correspond to the normal's direction

	const char *sVertShaderCode =
			"#version 330 core\n"
			"layout (location = 0) in vec3 vPos;\n"
			"layout (location = 1) in vec3 vNormal;\n"
			"uniform mat4 mProjection;\n"
			"uniform mat4 mView;\n"
			"uniform mat4 mModel;\n"
			"out vec3 FragPos;\n"
			"out vec3 v3Color;\n"
			"out vec3 v3Normal;\n"
			"\n"
			"void main()\n"
			"{\n"
				"\tFragPos = vec3(mModel * vec4(vPos, 1.0));\n"
				"\tv3Normal = vNormal;\n"
				"\tv3Color = v3Normal;\n"
				"\tgl_Position = mProjection * mView * vec4(FragPos, 1.0);\n"
			"}";

	// Fragment shader gets as an input parameter the color and outputs it respectively
	const char *sFragShaderCode =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 v3Color;\n"
		"\n"
		"void main()\n"
		"{\n"
			"\tFragColor = vec4(v3Color, 1.0);\n"
		"}";

	// Create and compile the vertex shader
	unsigned int unVertShaderID = 0;
	int nSuccess = 0;
	const int c_nLogSize = 512;
	char sInfoLog[c_nLogSize];

	unVertShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(unVertShaderID, 1, &sVertShaderCode, NULL);
	glCompileShader(unVertShaderID);
	glGetShaderiv(unVertShaderID, GL_COMPILE_STATUS, &nSuccess); // Check for errors

	if (! nSuccess)
	{
		glGetShaderInfoLog(unVertShaderID, c_nLogSize, NULL, sInfoLog);
		cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << sInfoLog << endl;
	}

	// Create and compile the fragment shader
	unsigned int unFragShaderID = 0;

	nSuccess = 0;
	unFragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(unFragShaderID, 1, &sFragShaderCode, NULL);
	glCompileShader(unFragShaderID);
	glGetShaderiv(unFragShaderID, GL_COMPILE_STATUS, &nSuccess); // Check for errors

	if (! nSuccess)
	{
		glGetShaderInfoLog(unFragShaderID, c_nLogSize, NULL, sInfoLog);
		cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << sInfoLog << endl;
	}

	// Create the shader program, attach each shader and link the program
	m_unProgramID = glCreateProgram();
	glAttachShader(m_unProgramID, unVertShaderID);
	glAttachShader(m_unProgramID, unFragShaderID);
	glLinkProgram(m_unProgramID);
	glGetProgramiv(m_unProgramID, GL_LINK_STATUS, &nSuccess); // Check for errors

	if (! nSuccess)
	{
		glGetProgramInfoLog(m_unProgramID, c_nLogSize, NULL, sInfoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << sInfoLog << endl;
	}

	// We no longer need the shaders, then free them
	glDeleteShader(unVertShaderID);
	glDeleteShader(unFragShaderID);
}

OglShader::OglShader(const OglShader &) :
	m_unProgramID(0)
{
	/*do nothing*/
}

OglShader::~OglShader()
{
	glDeleteProgram(m_unProgramID);
	m_unProgramID = 0;
}

void OglShader::use() const
{
	glUseProgram(m_unProgramID);
}

void OglShader::setBool(const char *sName, bool bValue) const
{
	glUniform1i(glGetUniformLocation(m_unProgramID, sName), static_cast<int>(bValue));
}

void OglShader::setInt(const char *sName, const int &nValue) const
{
	glUniform1i(glGetUniformLocation(m_unProgramID, sName), nValue);
}

void OglShader::setFloat(const char *sName, const float &fValue) const
{
	glUniform1f(glGetUniformLocation(m_unProgramID, sName), fValue);
}

void OglShader::setVec3(const char *sName, const float *vec) const
{
	glUniform3fv(glGetUniformLocation(m_unProgramID, sName), 1, vec);
}

void OglShader::setMat4(const char *sName, const float *mat, const bool bTranspose) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_unProgramID, sName), 1, bTranspose ? GL_TRUE : GL_FALSE, mat);
}

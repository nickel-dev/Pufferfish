//-----------------------------------------------------------------------------
// R_Shader.h by Steve Jones 
// Copyright (c) 2015-2019 Game Institute. All Rights Reserved.
//
// GLSL shader manager class
//-----------------------------------------------------------------------------
#ifndef __RENDER_SHADER_H_
#define __RENDER_SHADER_H_

#include "../base/base_inc.h"

using std::string;

class R_Shader
{
public:
	 R_Shader();
	 R_Shader(const char* path);
	~R_Shader();

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	// Only supports vertex and fragment (this series will only have those two)
	bool Load(const char* path);
	void Use();

	GLuint GetProgram() const;

	void SetUniform(const GLchar* name, const glm::vec2& v);
	void SetUniform(const GLchar* name, const glm::vec3& v);
	void SetUniform(const GLchar* name, const glm::vec4& v);
	void SetUniform(const GLchar* name, const F32* m);
	void SetUniform(const GLchar* name, const I32 m);

	// We are going to speed up looking for uniforms by keeping their locations in a map
	GLint GetUniformLocation(const GLchar* name);

private:

	string fileToString(const string& filename);
	void  checkCompileErrors(GLuint shader, ShaderType type);

	
	GLuint mHandle;
	std::map<string, GLint> mUniformLocations;
};
#endif // SHADER_H
#include <gtc\type_ptr.hpp>

#include "ForwardShader.hpp"
#include "..\Util\Error.hpp"

const std::string ForwardShader::WORLD_MATRIX_UNIFORM_NAME = "worldMatrix";
const std::string ForwardShader::VIEW_MATRIX_UNIFORM_NAME = "viewMatrix";
const std::string ForwardShader::PROJECTION_MATRIX_UNIFORM_NAME = "projectionMatrix";
const std::string ForwardShader::TEXTURE_MAP_UNIFORM_NAMES[4] = { "diffuseMap", "specularMap", "normalMap", "opacityMap" };

bool ForwardShader::create()
{
	if (!load("Shaders\\Forward.vs.glsl", "", "Shaders\\Forward.fs.glsl"))
		return false;

	if (!link())
		return false;

	glUseProgram(program);

	if (!getUniformLocation(WORLD_MATRIX_UNIFORM_NAME, worldMatrixUniformLocation))
		return false;

	if (!getUniformLocation(VIEW_MATRIX_UNIFORM_NAME, viewMatrixUniformLocation))
		return false;

	if (!getUniformLocation(PROJECTION_MATRIX_UNIFORM_NAME, projectionMatrixUniformLocation))
		return false;

	GLint textureMapUniformLocation;

	for (int i = 0; i < 4; ++i)
	{
		if (!getUniformLocation(TEXTURE_MAP_UNIFORM_NAMES[i], textureMapUniformLocation))
			return false;

		glUniform1i(textureMapUniformLocation, i);
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Error::report("Error", "Failed to load forward shader: " + Error::getOpenGLErrorString(error));
		return false;
	}

	return true;
}

void ForwardShader::setWorldViewProjectionUniforms(const glm::mat4 &worldMatrix, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
{
	glUniformMatrix4fv(worldMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(worldMatrix));
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}
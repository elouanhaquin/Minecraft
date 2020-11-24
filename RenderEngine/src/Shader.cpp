#include "stdafx.h"

#include <Shader.h>

using namespace RenderEngineNS;

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	: m_filePathVertex(vertexShader), m_filePathFragment(fragmentShader), m_rendererID(0)
{
	const std::string vertexShaderSource = Parse(vertexShader);
	const std::string fragmentShaderSource = Parse(fragmentShader);

	const unsigned int program = glCreateProgram();
	const unsigned int vs = Compile(GL_VERTEX_SHADER, vertexShaderSource);
	const unsigned int fs = Compile(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	(glDeleteShader(vs));
	(glDeleteShader(fs));

	m_rendererID = program;
}

Shader::~Shader()
{
	glDeleteProgram(m_rendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_rendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& p_name, const glm::mat4& p_mat)
{
	glUniformMatrix4fv(GetUniformLocation(p_name), 1, GL_FALSE, &p_mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	const int location = glGetUniformLocation(m_rendererID, name.c_str());
	//ASSERT(location != -1);

	m_uniformLocationCache[name] = location;

	return location;
}

std::string Shader::Parse(const std::string& filePath) const
{
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream stringstream;

	while (getline(stream, line))
	{
		stringstream << line << "\n";
	}

	return stringstream.str();
}

int Shader::Compile(const unsigned int type, const std::string& source) const
{
	const char* src = source.c_str();
	int result;

	const unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		auto* message = static_cast<char*>(alloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "Vertex" : "fragment") <<
			" shader \n";
		std::cout << message << "\n";

		glDeleteShader(id);

		return 0;
	}

	return id;
}

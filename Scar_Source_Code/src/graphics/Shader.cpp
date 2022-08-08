#include "graphics/Shader.h"
#include "glad/glad.h"
#include <fstream>
#include <sstream>
#include "core/Log.h"

namespace Scar::graphics {
    bool Shader::m_binded = false;

	Shader::Shader(const char* vs, const char* fs, const char* gs) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vs);
            fShaderFile.open(fs);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
            if (gs != nullptr)
            {
                gShaderFile.open(gs);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure& e)
        {
            SCAR_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: {} " ,e.what() );
            SCAR_ASSERT(false, "Shader error");
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if (gs != nullptr)
        {
            const char* gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (gs != nullptr)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (gs != nullptr)
            glDeleteShader(geometry);

	}

    Shader::~Shader() {
        glUseProgram(0);
        glDeleteProgram(ID);
    }

    void Shader::Bind() {
        glUseProgram(ID);
        m_binded = true;
    }

    void Shader::UnBind() {
        glUseProgram(0);
        m_binded = false;
    }

    void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                SCAR_ERROR("ERROR::SHADER_COMPILE_ERROR of type: {}", type ,"\n", infoLog , "\n -- --------------------------------------------------- -- ");
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                SCAR_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {}", type, "\n", infoLog, "\n -- --------------------------------------------------- -- ");
            }
        }
    }

    // utility uniform functions
   // ------------------------------------------------------------------------
    void Shader::SetBool(const std::string& name, bool value) const
    {
        SCAR_ASSERT(m_binded,"SHADER NOT BOUND");
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void Shader::SetInt(const std::string& name, int value) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::SetFloat(const std::string& name, float value) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void Shader::SetVec2(const std::string& name, float x, float y) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void Shader::SetVec3(const std::string& name, float x, float y, float z) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        SCAR_ASSERT(m_binded, "SHADER NOT BOUND");
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}
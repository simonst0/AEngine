#include "Shader.h"

ShaderProgram::ShaderProgram(const char *vertex_shader_src, const char *fragment_shader_src){
    VertexShader = LoadShader(GL_VERTEX_SHADER, vertex_shader_src);
    FragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragment_shader_src);

    ProgramHandle = glCreateProgram();

    if(ProgramHandle == 0)
    {
        log_debug("Could not create Program");
        return;
    }

    glAttachShader(ProgramHandle, FragmentShader);
    glAttachShader(ProgramHandle, VertexShader);
    BindShaderAttributeLocations();
    glLinkProgram(ProgramHandle);

    GLint ok = 0;
    glGetProgramiv(ProgramHandle, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint length = 0;
        glGetProgramiv(ProgramHandle, GL_INFO_LOG_LENGTH, &length);
        if(length > 1)
        {
            char* infoLog = (char*)malloc(sizeof(char) * length);
            glGetProgramInfoLog(ProgramHandle, length, nullptr, infoLog);
            log_error("Program linking of >>%s<< and >>%s<< failed with: >>%s<<",
                      vertex_shader_src, fragment_shader_src, infoLog);
            free(infoLog);
        }
        glDeleteProgram(ProgramHandle);
        return;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ShaderProgram::Initialize()
{
    LoadUniformLocations();
    BindShaderAttributeLocations();
}

GLuint ShaderProgram::LoadShader(GLenum shader_type, const char *shader_src) {
    log_debug("Making shader");
    GLuint Shader;
    GLint Compiled;
    Shader = glCreateShader(shader_type);

    if(Shader == 0)
    {
        log_debug("Could not Create Shader Graphics API Error");
        return 0;
    }

    glShaderSource(Shader, 1, &shader_src, nullptr);
    glCompileShader(Shader);

    glGetShaderiv(Shader, GL_COMPILE_STATUS, &Compiled);
    if (!Compiled) {
        GLint length = 0;
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &length);
        if(length > 1)
        {
            char* infoLog = (char*)malloc(sizeof(char) * length);
            glGetShaderInfoLog(Shader, length, nullptr, infoLog);
            log_error("Shader compilation of >>%s<< failed with: >>%s<<", shader_src, infoLog);
            free(infoLog);
        }
    }
    return Shader;
}

void ShaderProgram::BindShaderAttributeLocations()
{
    GLint count;
    glGetProgramiv(ProgramHandle, GL_ACTIVE_ATTRIBUTES, &count);

    GLint size;
    GLenum type;
    const GLsizei bufferSize = 32;
    GLchar name[bufferSize];
    GLsizei length;

    for (GLuint i = 0; i < count; i++)
    {
        glGetActiveAttrib(ProgramHandle, i, bufferSize, &length, &size, &type, name);
        std::string nameAsString = std::string(name, length);
        AttributeLocations.push_back(nameAsString);
        glBindAttribLocation(ProgramHandle, i, name);
        log_debug("AttributeLocation %d Type: %u Name: %s", i, type, name);
    }
}

void ShaderProgram::LoadUniformLocations()
{
    GLint count;
    glGetProgramiv(ProgramHandle, GL_ACTIVE_UNIFORMS, &count);

    GLint size;
    GLenum type;
    const GLsizei bufferSize = 32;
    GLchar name[bufferSize];
    GLsizei length;

    for (GLuint i = 0; i < count; i++)
    {
        glGetActiveUniform(ProgramHandle, i, bufferSize, &length, &size, &type, name);
        UniformLocations[std::string(name, length)] = i;
        log_debug("UniformLocation %d Type: %u Name: %s", i, type, name);
    }
}

GLint ShaderProgram::GetUniformLocation(const std::string& uniformName)
{
    if(UniformLocations.count(uniformName) >= 1)
        return UniformLocations[uniformName];
    log_debug("Could not find uniform location for %s", uniformName.c_str());
    return -1;
}

void ShaderProgram::DisableProgram()
{
    glUseProgram(0);
    for (int i = 0; i < AttributeLocations.size(); ++i)
        glDisableVertexAttribArray(i);
}

void ShaderProgram::EnableProgram() {
    glUseProgram(ProgramHandle);
    for (int i = 0; i < AttributeLocations.size(); ++i)
        glEnableVertexAttribArray(i);
}
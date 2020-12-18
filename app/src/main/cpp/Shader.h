#pragma  once

#include <string>
#include <GLES2/gl2.h>
#include <vector>
#include <unordered_map>
#include "Util.h"

class ShaderProgram
{
public:
    ShaderProgram(const char *vertex_shader_src, const char *fragment_shader_src);
    void EnableProgram();
    void DisableProgram();
    void Initialize();
    GLint GetUniformLocation(const std::string& uniformName);

    GLuint ProgramHandle;
    GLuint FragmentShader;
    GLuint VertexShader;

protected:
    void BindShaderAttributeLocations();
    void LoadUniformLocations();
    GLuint LoadShader(GLenum shader_type, const char* shader_src);
    std::unordered_map<std::string, GLint> UniformLocations;
    std::vector<std::string> AttributeLocations;
};

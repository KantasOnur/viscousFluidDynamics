#pragma once
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <unordered_map>

class Shader
{
protected:
    unsigned int id_;
private:
    unsigned int createShader(GLenum type, const std::string& sourcePath);
    void createProgram(const std::vector<unsigned int>& shaders);
    std::unordered_map<std::string, int> uniformToLocation_;
public:
    Shader(const std::string& shader, const bool& compute = false);
    ~Shader();
    void bind() const;
    void unbind() const;
    //void bindTexture() const;
    GLint getUniformLocation(const std::string& name);
    void setMatrix4f(const std::string& name, const glm::mat4& val);
    void setVec3f(const std::string& name, const glm::vec3& val);
    void setFloat1f(const std::string& name, const float& val);
    void setInt(const std::string& name, const int& val);
};



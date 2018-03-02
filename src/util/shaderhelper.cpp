#include "util/shaderhelper.hpp"

std::string shaderhelper::loadShader(const std::string & shaderFilename) {
    std::string appPath = pathhelper::getApplicationPath();
    std::string shaderPath = appPath + "/" + shaderFilename;

    std::string shaderCode;

    ifstream shaderStream(shaderPath.c_str(), ios::in);

    if (shaderStream.is_open()) {
        std::string Line;
        while (getline(shaderStream, Line)) {
            shaderCode += "\n" + Line;
        }
        shaderStream.close();
    } else {
        throw std::invalid_argument("Unable to open " + shaderPath);
    }

    return shaderCode;
}

GLuint shaderhelper::compileShader(const std::string & shaderFilename, GLenum shaderType) {
    std::string shaderCode = loadShader(shaderFilename);

    GLint compilationSuccess = GL_FALSE;
    int infoLogLength;
    GLuint shaderId = glCreateShader(shaderType);

    char const *sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, nullptr);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationSuccess);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> shaderErrorMessage((unsigned long) (infoLogLength + 1));
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, &shaderErrorMessage[0]);
        throw std::runtime_error(&shaderErrorMessage[0]);
    }

    return shaderId;
}

GLuint shaderhelper::createProgram(const std::string & vertexFilename, const std::string & fragmentFilename)
{
    GLuint vertexShaderId = compileShader(vertexFilename, GL_VERTEX_SHADER);
    GLuint fragmentShaderId = compileShader(fragmentFilename, GL_FRAGMENT_SHADER);

    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    GLint compilationSuccess = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(programId, GL_LINK_STATUS, &compilationSuccess);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        vector<char> programErrorMessage((unsigned long) (infoLogLength + 1));
        glGetProgramInfoLog(programId, infoLogLength, nullptr, &programErrorMessage[0]);
        throw std::runtime_error(&programErrorMessage[0]);
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

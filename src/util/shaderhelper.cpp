#include "util/shaderhelper.hpp"

string shaderhelper::loadShader(const string & shaderFilename) {
    unique_ptr<string> appPath = pathhelper::getApplicationPath();
    string shaderPath = *(appPath.get()) + "/" + shaderFilename;

    string shaderCode;

    ifstream shaderStream(shaderPath.c_str(), ios::in);

    if (shaderStream.is_open()) {
        string Line = "";
        while (getline(shaderStream, Line)) {
            shaderCode += "\n" + Line;
        }
        shaderStream.close();
    } else {
        throw string("Unable to open " + shaderFilename);
    }

    return shaderCode;
}

GLuint shaderhelper::compileShader(const string & shaderFilename, GLenum shaderType) {
    string shaderCode = loadShader(shaderFilename);

    // Compile shader
    GLint compilationSuccess = GL_FALSE;
    int infoLogLength;
    GLuint shaderId = glCreateShader(shaderType);

    char const *sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);

    // Check shader
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationSuccess);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> vertexShaderErrorMessage((unsigned long) (infoLogLength + 1));
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
    }

    return shaderId;
}

GLuint shaderhelper::createProgram(const string & vertexFilename, const string & fragmentFilename)
{
    // Compile shaders
    GLuint vertexShaderId = compileShader(vertexFilename, GL_VERTEX_SHADER);
    GLuint fragmentShaderId = compileShader(fragmentFilename, GL_FRAGMENT_SHADER);

    // Link the program
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
        glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);
        throw &programErrorMessage[0];
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

#include "util/shaderhelper.hpp"

GLuint shaderhelper::compileShader(const string & shaderFilename, GLenum shaderType) {
    LOG(INFO) << " - Loading shader: " << shaderFilename;
    unique_ptr<string> appPath = pathhelper::getApplicationPath();
    string shaderPath = *(appPath.get()) + "/" + shaderFilename;

    GLuint shaderId = glCreateShader(shaderType);

    string shaderCode;

    ifstream shaderStream(shaderPath.c_str(), ios::in);

    if (shaderStream.is_open()) {
        string Line = "";
        while (getline(shaderStream, Line)) {
            shaderCode += "\n" + Line;
        }
        shaderStream.close();
    }
    else {
        throw string("Unable to open " + shaderFilename);
    }

    // Compile shader
    LOG(INFO) << " - Compiling shader: " << shaderFilename;
    GLint compilationSuccess = GL_FALSE;
    int infoLogLength;

    char const *sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);

    // Check shader
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationSuccess);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        LOG(INFO) << " - Shader compilation error: ";
        LOG(INFO) << &vertexShaderErrorMessage[0];
    }

    return shaderId;
}

GLuint shaderhelper::createProgram(const string & vertexFilename, const string & fragmentFilename)
{
    LOG(INFO) << "Creating GLSL Program";

    // Compile shaders
    GLuint vertexShaderId = compileShader(vertexFilename, GL_VERTEX_SHADER);
    GLuint fragmentShaderId = compileShader(fragmentFilename, GL_FRAGMENT_SHADER);

    // Link the program
    LOG(INFO) << " - Linking GLSL Program";
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
        vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);
        throw &programErrorMessage[0];
    }

    LOG(INFO) << " - Cleaning up shaders";
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

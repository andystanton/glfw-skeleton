#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <GL/glew.h>

#include "util/shaderhelper.hpp"

using namespace std;

GLuint shaderhelper::compileShader(const string & shaderFilename, GLenum shaderType)
{
    unique_ptr<string> appPath = pathhelper::getApplicationPath();
    string shaderPath = *(appPath.get()) + "/" + shaderFilename;

    GLuint shaderId = glCreateShader(shaderType);

    // Read shader code form file
    string shaderCode;
    ifstream shaderStream(shaderPath.c_str(), ios::in);
    if (shaderStream.is_open())
    {
        string Line = "";
        while(getline(shaderStream, Line))
            shaderCode += "\n" + Line;
        shaderStream.close();
    } else
    {
        cerr << "Unable to open " << shaderFilename << endl;
        getchar();
        return 0;
    }

    GLint compilationSuccess = GL_FALSE;
    int infoLogLength;

    // Compile shader
    cout << "Compiling shader: " << shaderFilename << endl;
    char const * sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);

    // Check shader
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationSuccess);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        cerr << &vertexShaderErrorMessage[0] << endl;
    }

    return shaderId;
}

GLuint shaderhelper::loadShaderPair(const string & vertexFilename, const string & fragmentFilename)
{
    GLuint vertexShaderId = compileShader(vertexFilename, GL_VERTEX_SHADER);
    GLuint fragmentShaderId = compileShader(fragmentFilename, GL_FRAGMENT_SHADER);

    // Link the program
    cout << "Linking program" << endl;
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    GLint compilationSuccess = GL_FALSE;
    int infoLogLength;

    // Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &compilationSuccess);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);
        cerr << &programErrorMessage[0] << endl;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

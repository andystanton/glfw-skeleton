#include <GL/glew.h>

#include "util/shaderhelper.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::ios;

const string ok(" ... \033[1;32mOK\033[0m");
const string fail(" ... \033[1;31mFail\033[0m");

GLuint shaderhelper::compileShader(const string & shaderFilename, GLenum shaderType)
{
    cout << " - Loading shader: " << shaderFilename;
    unique_ptr<string> appPath = pathhelper::getApplicationPath();
    string shaderPath = * (appPath.get()) + "/" + shaderFilename;

    GLuint shaderId = glCreateShader(shaderType);

    string shaderCode;

    ifstream shaderStream(shaderPath.c_str(), ios::in);

    if (shaderStream.is_open())
    {
        string Line = "";
        while (getline(shaderStream, Line))
        {
            shaderCode += "\n" + Line;
        }
        shaderStream.close();
        cout << ok << endl;
    }
    else
    {
        cout << fail << endl;
        throw string("Unable to open " + shaderFilename);
        return 0;
    }

    // Compile shader
    cout << " - Compiling shader: " << shaderFilename;
    GLint compilationSuccess = GL_FALSE;
    int infoLogLength;

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
    cout << ok << endl;

    return shaderId;
}

GLuint shaderhelper::createProgram(const string & vertexFilename, const string & fragmentFilename)
{
    cout << "Creating GLSL Program" << endl;

    // Compile shaders
    GLuint vertexShaderId = compileShader(vertexFilename, GL_VERTEX_SHADER);
    GLuint fragmentShaderId = compileShader(fragmentFilename, GL_FRAGMENT_SHADER);

    // Link the program
    cout << " - Linking GLSL Program";
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
        cout << fail << endl;
        throw &programErrorMessage[0];
    }
    cout << ok << endl;

    cout << " - Cleaning up shaders";
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    cout << ok << endl;

    return programId;
}

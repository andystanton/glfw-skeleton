#pragma once

#include "util/pathhelper.hpp"

#include <GL/glew.h>

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::vector;
using std::ifstream;
using std::ios;

namespace shaderhelper
{
    std::string loadShader(const std::string & shaderFilename);
    GLuint compileShader(const std::string & shaderFilename, GLenum shaderType);
    GLuint createProgram(const std::string & vertexFileName, const std::string & fragmentFileName);
};

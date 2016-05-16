#pragma once

#include "util/pathhelper.hpp"

#include <GL/glew.h>

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "easylogging++.h"

using std::vector;
using std::ifstream;
using std::ios;

namespace shaderhelper
{
    GLuint compileShader(const string & shaderFilename, GLenum shaderType);
    GLuint createProgram(const string & vertexFileName, const string & fragmentFileName);
};

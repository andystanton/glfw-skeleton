#ifndef _SKELETON_SHADER
#define _SKELETON_SHADER

#include "util/pathhelper.hpp"

namespace shaderhelper {
    GLuint loadShader(const char * shaderFileName);
    GLuint loadShaderPair(const string & vertexFileName, const string & fragmentFileName);
};

#endif

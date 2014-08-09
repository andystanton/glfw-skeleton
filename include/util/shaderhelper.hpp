#ifndef _SKELETON_SHADER
#define _SKELETON_SHADER

#include "util/pathhelper.hpp"

namespace shaderhelper {
    GLuint compileShader(const string & shaderFilename, GLenum shaderType);
    GLuint loadShaderPair(const string & vertexFileName, const string & fragmentFileName);
};

#endif

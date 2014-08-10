#ifndef _SKELETON_SHADER_HELPER
#define _SKELETON_SHADER_HELPER

#include "util/pathhelper.hpp"

namespace shaderhelper {
    GLuint compileShader(const string & shaderFilename, GLenum shaderType);
    GLuint createProgram(const string & vertexFileName, const string & fragmentFileName);
};

#endif

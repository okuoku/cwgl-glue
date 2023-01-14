#include "glue-priv.h"

/* 6.1 Querying GL State */
/* 6.1.1 Simple Queries */
GL_APICALL void GL_APIENTRY
glGetBooleanv(GLenum value, GLboolean *data){
}

GL_APICALL void GL_APIENTRY
glGetIntegerv(GLenum value, GLint *data){
}

GL_APICALL void GL_APIENTRY
glGetFloatv(GLenum value, GLfloat *data){
}

GL_APICALL GLboolean GL_APIENTRY
glIsEnabled(GLenum value){
}

/* 6.1.3 Enumerated Queries */
GL_APICALL void GL_APIENTRY
glGetTexParameteriv(GLenum target, GLenum value, GLint *data){
}
GL_APICALL void GL_APIENTRY
glGetTexParameterfv(GLenum target, GLenum value, GLfloat *data){
}

GL_APICALL void GL_APIENTRY
glGetBufferParameteriv(GLenum target, GLenum value, GLint *data){
}

GL_APICALL void GL_APIENTRY
glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment,
                                      GLenum pname, GLint *params){
}

GL_APICALL void GL_APIENTRY
glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params){
}

/* 6.1.4 Texture Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsTexture(GLuint texture){
}

/* 6.1.5 String Queries */
GL_APICALL const GLubyte* GL_APIENTRY // the spec lacks const
glGetString(GLenum name){
}

/* 6.1.6 Buffer Object Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsBuffer(GLuint buffer){
}

/* 6.1.7 Framebuffer Object and Renderbuffer Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsFramebuffer(GLuint framebuffer){
}

GL_APICALL GLboolean GL_APIENTRY
glIsRenderbuffer(GLuint renderbuffer){
}

/* 6.1.8 Shader and Program Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsShader(GLuint shader){
}

GL_APICALL void GL_APIENTRY
glGetShaderiv(GLuint shader, GLenum pname, GLint *params){
}

GL_APICALL GLboolean GL_APIENTRY
glIsProgram(GLuint program){
}

GL_APICALL void GL_APIENTRY
glGetProgramiv(GLuint program, GLenum pname, GLint *params){
}

GL_APICALL void GL_APIENTRY
glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count,
                     GLuint *shaders){
}

GL_APICALL void GL_APIENTRY
glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length,
                   GLchar *infoLog){
}

GL_APICALL void GL_APIENTRY
glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length,
                    GLchar *infoLog){
}

GL_APICALL void GL_APIENTRY
glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length,
                  GLchar* source){
}

GL_APICALL void GL_APIENTRY
glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype,
                           GLint *range, GLint *precision){
}

GL_APICALL void GL_APIENTRY
glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params){
}

GL_APICALL void GL_APIENTRY
glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params){
}

GL_APICALL void GL_APIENTRY
glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer){
}

GL_APICALL void GL_APIENTRY
glGetUniformfv(GLuint program, GLint location, GLfloat *params){
}

GL_APICALL void GL_APIENTRY
glGetUniformiv(GLuint program, GLint location, GLint *params){
}



#include "glue-priv.h"

/* 3.4 Line Segments */
GL_APICALL void GL_APIENTRY
glLineWidth(GLfloat width){
}

/* 3.5 Polygons */
/* 3.5.1 Basic Polygon Rasterization */
GL_APICALL void GL_APIENTRY
glFrontFace(GLenum dir){
}

GL_APICALL void GL_APIENTRY
glCullFace(GLenum mode){
}

/* 3.5.2 Depth Offset */
GL_APICALL void GL_APIENTRY
glPolygonOffset(GLfloat factor, GLfloat units){
}

/* 3.6 Pixel Rectangles */
/* 3.6.1 Pixel Storage Modes */
GL_APICALL void GL_APIENTRY
glPixelStorei(GLenum pname, GLint param /* ??? */){
}

/* 3.7 Texturing */
GL_APICALL void GL_APIENTRY
glActiveTexture(GLenum texture){
}

/* 3.7.1 Texture Image Specification */
GL_APICALL void GL_APIENTRY
glTexImage2D(GLenum target, GLint level, GLint internalformat,
             GLsizei width, GLsizei height, GLint border,
             GLenum format, GLenum type, void *data){
}

/* 3.7.2 Alternate Texture Image Specification Commands */
GL_APICALL void GL_APIENTRY
glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat,
                 GLint x, GLint y, GLsizei width, GLsizei height, GLint border){
}

GL_APICALL void GL_APIENTRY
glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                GLsizei width, GLsizei height, GLenum format, GLenum type,
                void *data){
}

GL_APICALL void GL_APIENTRY
glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                    GLint x, GLint y, GLsizei width, GLsizei height){
}

/* 3.7.3 Compressed Texture Images */
GL_APICALL void GL_APIENTRY
glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat,
                       GLsizei width, GLsizei height, GLint border,
                       GLsizei imageSize, void *data){
}

GL_APICALL void GL_APIENTRY
glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                          GLint yoffset, GLsizei width, GLsizei height,
                          GLenum format, GLsizei imageSize, void *data){
}

/* 3.7.4 Texture Parameters */
GL_APICALL void GL_APIENTRY
glTexParameteri(GLenum target, GLenum pname, GLint param){
}

GL_APICALL void GL_APIENTRY
glTexParameterf(GLenum target, GLenum pname, GLfloat param){
}

GL_APICALL void GL_APIENTRY
glTexParameteriv(GLenum target, GLenum pname, const GLint* params){
}

GL_APICALL void GL_APIENTRY
glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params){
}

/* 3.7.11 Mipmap Generation */
GL_APICALL void GL_APIENTRY
glGenerateMipmap(GLenum target){
}

/* 3.7.13 Texture Objects */
GL_APICALL void GL_APIENTRY
glBindTexture(GLenum target, GLuint texture){
}

GL_APICALL void GL_APIENTRY
glDeleteTextures(GLsizei n, const GLuint *textures){
}

GL_APICALL void GL_APIENTRY
glGenTextures(GLsizei n, GLuint *textures){
}


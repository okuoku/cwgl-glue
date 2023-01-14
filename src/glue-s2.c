#include "glue-priv.h"
#include "glue-ctx.h"

/* 2.5 GL Errors */
GL_APICALL GLenum GL_APIENTRY
glGetError(void){
}

/* 2.7 Current Vertex State */
GL_APICALL void GL_APIENTRY
glVertexAttrib1f(GLuint index, GLfloat x){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib1f(ctx, index, x);
}
GL_APICALL void GL_APIENTRY
glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib2f(ctx, index, x, y);
}
GL_APICALL void GL_APIENTRY
glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib3f(ctx, index, x, y, z);
}
GL_APICALL void GL_APIENTRY
glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib4f(ctx, index, x, y, z, w);
}

GL_APICALL void GL_APIENTRY
glVertexAttrib1fv(GLuint index, const GLfloat* v){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib1f(ctx, index, v[0]);
}

GL_APICALL void GL_APIENTRY
glVertexAttrib2fv(GLuint index, const GLfloat* v){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib2f(ctx, index, v[0], v[1]);
}

GL_APICALL void GL_APIENTRY
glVertexAttrib3fv(GLuint index, const GLfloat* v){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib3f(ctx, index, v[0], v[1], v[2]);
}

GL_APICALL void GL_APIENTRY
glVertexAttrib4fv(GLuint index, const GLfloat* v){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_vertexAttrib4f(ctx, index, v[0], v[1], v[2], v[3]);
}

/* 2.8 Vertex Arrays */
GL_APICALL void GL_APIENTRY
glVertexAttribPointer(GLuint index, GLint size, GLenum type, 
                      GLboolean normalized, GLsizei stride,
                      const void *pointer){
}

GL_APICALL void GL_APIENTRY
glEnableVertexAttribArray(GLuint index){
}

GL_APICALL void GL_APIENTRY
glDisableVertexAttribArray(GLuint index){
}

GL_APICALL void GL_APIENTRY
glDrawArrays(GLenum mode, GLint first, GLsizei count){
}

GL_APICALL void GL_APIENTRY
glDrawElements(GLenum mode, GLsizei count, GLenum type,
               void* indices){
}

/* 2.9 Buffer Objects */
GL_APICALL void GL_APIENTRY
glBindBuffer(GLenum target, GLuint buffer){
}

GL_APICALL void GL_APIENTRY
glDeleteBuffers(GLsizei n, const GLuint *buffers){
}

GL_APICALL void GL_APIENTRY
glGenBuffers(GLsizei n, GLuint *buffers){
}

GL_APICALL void GL_APIENTRY
glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage){
}

GL_APICALL void GL_APIENTRY
glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size,
                const void *data){
}

/* 2.10 Vertex Shaders */
/* 2.10.1 Loading and Compiling Shader Source */
GL_APICALL GLuint GL_APIENTRY
glCreateShader(GLenum type){
}

GL_APICALL void GL_APIENTRY
glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string,
               const GLint *length){
}

GL_APICALL void GL_APIENTRY
glCompileShader(GLuint shader){
}

GL_APICALL void GL_APIENTRY
glReleaseShaderCompiler(void){
}

GL_APICALL void GL_APIENTRY
glDeleteShader(GLuint shader){
}

/* 2.10.2 Loading Shader Binaries */
GL_APICALL void GL_APIENTRY
glShaderBinary(GLsizei count, const GLuint *shaders,
               GLenum binaryformat, const void *binary, GLsizei length){
}

/* 2.10.3 Program Objects */
GL_APICALL GLuint GL_APIENTRY
glCreateProgram(void){
}

GL_APICALL void GL_APIENTRY
glAttachShader(GLuint program, GLuint shader){
}

GL_APICALL void GL_APIENTRY
glDetachShader(GLuint program, GLuint shader){
}

GL_APICALL void GL_APIENTRY
glLinkProgram(GLuint program){
}

GL_APICALL void GL_APIENTRY
glUseProgram(GLuint program){
}

GL_APICALL void GL_APIENTRY
glDeleteProgram(GLuint program){
}

/* 2.10.4 Shader Variables */
GL_APICALL void GL_APIENTRY
glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize,
                  GLsizei *length, GLint *size, GLenum *type,
                  char *name){
}

GL_APICALL GLint GL_APIENTRY
glGetAttribLocation(GLuint program, const char *name){
}

GL_APICALL void GL_APIENTRY
glBindAttribLocation(GLuint program, GLuint index, const char *name){
}

GL_APICALL GLint GL_APIENTRY
glGetUniformLocation(GLuint program, const char *name){
}

GL_APICALL void GL_APIENTRY
glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize,
                   GLsizei *length, GLint *size, GLenum *type,
                   char *name){
}

GL_APICALL void GL_APIENTRY
glUniform1i(GLint location, GLint x){
}

GL_APICALL void GL_APIENTRY
glUniform2i(GLint location, GLint x, GLint y){
}

GL_APICALL void GL_APIENTRY
glUniform3i(GLint location, GLint x, GLint y, GLint z){
}

GL_APICALL void GL_APIENTRY
glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w){
}

GL_APICALL void GL_APIENTRY
glUniform1f(GLint location, GLfloat x){
}

GL_APICALL void GL_APIENTRY
glUniform2f(GLint location, GLfloat x, GLfloat y){
}

GL_APICALL void GL_APIENTRY
glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z){
}

GL_APICALL void GL_APIENTRY
glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
}

GL_APICALL void GL_APIENTRY
glUniform1iv(GLint location, GLsizei count, const GLint* v){
}

GL_APICALL void GL_APIENTRY
glUniform2iv(GLint location, GLsizei count, const GLint* v){
}

GL_APICALL void GL_APIENTRY
glUniform3iv(GLint location, GLsizei count, const GLint* v){
}

GL_APICALL void GL_APIENTRY
glUniform4iv(GLint location, GLsizei count, const GLint* v){
}

GL_APICALL void GL_APIENTRY
glUniform1fv(GLint location, GLsizei count, const GLfloat* v){
}

GL_APICALL void GL_APIENTRY
glUniform2fv(GLint location, GLsizei count, const GLfloat* v){
}

GL_APICALL void GL_APIENTRY
glUniform3fv(GLint location, GLsizei count, const GLfloat* v){
}

GL_APICALL void GL_APIENTRY
glUniform4fv(GLint location, GLsizei count, const GLfloat* v){
}

GL_APICALL void GL_APIENTRY
glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
}

GL_APICALL void GL_APIENTRY
glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
}

GL_APICALL void GL_APIENTRY
glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
}

/* 2.10.5 Shader Execution */
GL_APICALL void GL_APIENTRY
glValidateProgram(GLuint program){
}

/* 2.12 Coordinate Transformations */
/* 2.12.1 Controlling the Viewport */
GL_APICALL void GL_APIENTRY
glDepthRangef(GLclampf n, GLclampf f){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_depthRange(ctx, n, f);
}

GL_APICALL void GL_APIENTRY
glViewport(GLint x, GLint y, GLsizei w, GLsizei h){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_viewport(ctx, x, y, w, h);
}


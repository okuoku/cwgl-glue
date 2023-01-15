#include "glue-priv.h"
#include "glue-ctx.h"
#include <stdlib.h>
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string.h>

/* 2.5 GL Errors */
GL_APICALL GLenum GL_APIENTRY
glGetError(void){
    // FIXME:
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
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glEnableVertexAttribArray(GLuint index){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glDisableVertexAttribArray(GLuint index){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glDrawArrays(GLenum mode, GLint first, GLsizei count){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glDrawElements(GLenum mode, GLsizei count, GLenum type,
               void* indices){
    // FIXME:
}

/* 2.9 Buffer Objects */
GL_APICALL void GL_APIENTRY
glBindBuffer(GLenum target, GLuint buffer){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Buffer_t* buf;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(! buffer){
        buf = 0;
    }else{
        ptr = glue_get(glue, OBJ_BUFFER, buffer);
        if(! ptr){
            abort(); // unknown
            return;
        }else{
            buf = ptr->buffer;
        }
    }
    cwgl_bindBuffer(ctx, (cwgl_enum_t) target, buf);
    // FIXME: Track binding here
}

GL_APICALL void GL_APIENTRY
glDeleteBuffers(GLsizei n, const GLuint *buffers){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0;x != n; x++){
        if(buffers[x]){
            ptr = glue_get(glue, OBJ_BUFFER, buffers[x]);
            if(! ptr){
                abort(); // unknown
                return;
            }
            cwgl_deleteBuffer(ctx, ptr->buffer);
            (void) glue_del(glue, OBJ_BUFFER, buffers[x]);
            // FIXME: Track binding here
        }
    }

}

GL_APICALL void GL_APIENTRY
glGenBuffers(GLsizei n, GLuint *buffers){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0; x != n; x++){
        ptr.buffer = cwgl_createBuffer(ctx);
        buffers[x] = glue_put(glue, OBJ_BUFFER, &ptr);
    }
}

GL_APICALL void GL_APIENTRY
glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_bufferData(ctx, (cwgl_enum_t) target, size, data, (cwgl_enum_t) usage);
}

GL_APICALL void GL_APIENTRY
glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size,
                const void *data){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_bufferSubData(ctx, (cwgl_enum_t) target, offset, data, size);
}

/* 2.10 Vertex Shaders */
/* 2.10.1 Loading and Compiling Shader Source */
GL_APICALL GLuint GL_APIENTRY
glCreateShader(GLenum type){
    GLuint r;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr.shader = cwgl_createShader(ctx, (cwgl_enum_t) type);
    r = glue_put(glue, OBJ_SHADER, &ptr);

    return r;
}

GL_APICALL void GL_APIENTRY
glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string,
               const GLint *length){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Shader_t* sh;
    size_t x,y,srctotal;
    char* temp;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(! shader){
        abort(); // error
    }else{
        ptr = glue_get(glue, OBJ_SHADER, shader);
        if(! ptr){
            abort(); // unknown
            return;
        }
        sh = ptr->shader;
    }

    /* pass1: Get total length */
    srctotal = 0;
    if(! length){
        x = 0;
        while(string[x]){
            srctotal += strlen(string[x]);
            x++;
        }
    }else{
        x = 0;
        while(string[x]){
            srctotal += length[x];
            x++;
        }
    }
    temp = malloc(srctotal + 1);
    if(! temp){
        abort();
    }

    /* pass2: Copy to temporary buffer */
    if(! length){
        x = 0;
        temp[0] = 0;
        while(string[x]){
            (void) strcat(temp, string[x]);
            x++;
        }
    }else{
        x = 0;
        y = 0;
        while(string[x]){
            memcpy(&temp[y], string[x], length[x]);
            y += length[x];
            x++;
        }
        temp[y] = 0;
    }

    cwgl_shaderSource(ctx, sh, temp, srctotal);
    free(temp);

}

GL_APICALL void GL_APIENTRY
glCompileShader(GLuint shader){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Shader_t* sh;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(! shader){
        abort(); // error
    }else{
        ptr = glue_get(glue, OBJ_SHADER, shader);
        if(! ptr){
            abort(); // unknown
            return;
        }
        sh = ptr->shader;
    }

    cwgl_compileShader(ctx, sh);
}

GL_APICALL void GL_APIENTRY
glReleaseShaderCompiler(void){
    /* Do nothing */
}

GL_APICALL void GL_APIENTRY
glDeleteShader(GLuint shader){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();
    ptr = glue_get(glue, OBJ_SHADER, shader);
    if(! ptr){
        abort(); // error
    }
    cwgl_deleteShader(ctx, ptr->shader);
    (void) glue_del(glue, OBJ_SHADER, shader);
}

/* 2.10.2 Loading Shader Binaries */
GL_APICALL void GL_APIENTRY
glShaderBinary(GLsizei count, const GLuint *shaders,
               GLenum binaryformat, const void *binary, GLsizei length){
    abort();
}

/* 2.10.3 Program Objects */
GL_APICALL GLuint GL_APIENTRY
glCreateProgram(void){
    GLuint r;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr.program = cwgl_createProgram(ctx);
    r = glue_put(glue, OBJ_PROGRAM, &ptr);

    return r;
}

GL_APICALL void GL_APIENTRY
glAttachShader(GLuint program, GLuint shader){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Shader_t* sh;
    cwgl_Program_t* prg;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(shader){
        ptr = glue_get(glue, OBJ_SHADER, shader);
        sh = ptr->shader;
    }else{
        sh = 0;
    }
    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }
    prg = ptr->program;

    cwgl_attachShader(ctx, prg, sh);
}

GL_APICALL void GL_APIENTRY
glDetachShader(GLuint program, GLuint shader){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Shader_t* sh;
    cwgl_Program_t* prg;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr = glue_get(glue, OBJ_SHADER, shader);
    if(! ptr){
        abort(); // error
    }
    sh = ptr->shader;
    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }
    prg = ptr->program;

    cwgl_attachShader(ctx, prg, sh);
}

GL_APICALL void GL_APIENTRY
glLinkProgram(GLuint program){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Program_t* prg;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }
    prg = ptr->program;

    cwgl_linkProgram(ctx, prg);
}

GL_APICALL void GL_APIENTRY
glUseProgram(GLuint program){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Program_t* prg;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }
    prg = ptr->program;

    cwgl_useProgram(ctx, prg);
}

GL_APICALL void GL_APIENTRY
glDeleteProgram(GLuint program){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();
    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }
    cwgl_deleteProgram(ctx, ptr->program);
    (void) glue_del(glue, OBJ_PROGRAM, program);
}

/* 2.10.4 Shader Variables */
GL_APICALL void GL_APIENTRY
glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize,
                  GLsizei *length, GLint *size, GLenum *type,
                  char *name){
    // FIXME:
}

GL_APICALL GLint GL_APIENTRY
glGetAttribLocation(GLuint program, const char *name){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glBindAttribLocation(GLuint program, GLuint index, const char *name){
    // FIXME:
}

GL_APICALL GLint GL_APIENTRY
glGetUniformLocation(GLuint program, const char *name){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize,
                   GLsizei *length, GLint *size, GLenum *type,
                   char *name){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform1i(GLint location, GLint x){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform2i(GLint location, GLint x, GLint y){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform3i(GLint location, GLint x, GLint y, GLint z){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform1f(GLint location, GLfloat x){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform2f(GLint location, GLfloat x, GLfloat y){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform1iv(GLint location, GLsizei count, const GLint* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform2iv(GLint location, GLsizei count, const GLint* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform3iv(GLint location, GLsizei count, const GLint* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform4iv(GLint location, GLsizei count, const GLint* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform1fv(GLint location, GLsizei count, const GLfloat* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform2fv(GLint location, GLsizei count, const GLfloat* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform3fv(GLint location, GLsizei count, const GLfloat* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniform4fv(GLint location, GLsizei count, const GLfloat* v){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
    // FIXME:
}

/* 2.10.5 Shader Execution */
GL_APICALL void GL_APIENTRY
glValidateProgram(GLuint program){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Program_t* prg;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }
    prg = ptr->program;

    cwgl_validateProgram(ctx, prg);
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


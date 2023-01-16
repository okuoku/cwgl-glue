#define CWGL_DECL_ENUMS

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "glue-priv.h"
#include "glue-ctx.h"
#include <stdlib.h>
#include <string.h>

/* 2.5 GL Errors */
GL_APICALL GLenum GL_APIENTRY
glGetError(void){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    return cwgl_getError(ctx);
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
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(index >= GLUE_MAX_VERTEX_ATTRIBUTES){
        abort(); // overflow
    }

    if(glue->current_array_buffer){
        if((uintptr_t) pointer > UINT32_MAX){
            abort(); // overflow
        }
        /* Buffer bound. clear va_state pass args to cwgl */
        glue->va_state[index].use_client_array = 0;
        cwgl_vertexAttribPointer(ctx, index, size, (cwgl_enum_t) type,
                                 normalized, stride, (uint32_t) pointer);
    }else{
        /* Unbound. Just record args to cache */
        glue->va_state[index].use_client_array = 1;
        glue->va_state[index].client_array_size = size;
        glue->va_state[index].client_array_type = (cwgl_enum_t) type;
        glue->va_state[index].client_array_normalized = normalized;
        glue->va_state[index].client_array_stride = stride;
        glue->va_state[index].client_array_ptr = pointer;
    }
}

GL_APICALL void GL_APIENTRY
glEnableVertexAttribArray(GLuint index){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(index >= GLUE_MAX_VERTEX_ATTRIBUTES){
        abort(); // overflow
    }

    cwgl_enableVertexAttribArray(ctx, index);
    glue->va_state[index].enable = 1;
}

GL_APICALL void GL_APIENTRY
glDisableVertexAttribArray(GLuint index){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(index >= GLUE_MAX_VERTEX_ATTRIBUTES){
        abort(); // overflow
    }

    cwgl_disableVertexAttribArray(ctx, index);
    glue->va_state[index].enable = 0;
}

static int 
elementsize(cwgl_enum_t type){
    switch(type){
        case BYTE:
        case UNSIGNED_BYTE:
            return 1;
        case SHORT:
        case UNSIGNED_SHORT:
        //case HALF_FLOAT:
            return 2;
        case INT:
        case UNSIGNED_INT:
        case FLOAT:
            return 4;
        default:
            abort(); // unknown type
            return 0;
    }
}

static int /* realized? */
realize_proxy_buffers(glue_ctx_t* glue, size_t count){
    glue_va_state_t* state;
    int required = 0;
    char* temp = 0;
    void* buf;
    int i;
    size_t elemsize;
    size_t bufsize;
    size_t x;
    for(i = 0; i!= GLUE_MAX_VERTEX_ATTRIBUTES; i++){
        state = &glue->va_state[i];
        if(state->enable && state->use_client_array){
            required = 1;
            break;
        }
    }
    if(! required){
        return 0;
    }
    for(i = 0; i!= GLUE_MAX_VERTEX_ATTRIBUTES; i++){
        state = &glue->va_state[i];
        if(state->enable && state->use_client_array){
            elemsize = elementsize(state->client_array_type) *
                state->client_array_size;
            bufsize = elemsize * count;
            if(state->client_array_stride != elemsize){
                temp = malloc(bufsize);
                if(! temp){
                    abort(); // NOMEM
                }
                /* Gather elements */
                for(x = 0; x != count; x++){
                    memcpy(temp + (elemsize * x),
                           (char*)state->client_array_ptr +
                           (state->client_array_stride * elemsize * x),
                           elemsize);
                }
                buf = temp;
            }else{
                /* Directly use client buffer */
                buf = (void*)state->client_array_ptr;
            }

            /* Upload to GPU */
            state->proxy_buffer = cwgl_createBuffer(glue->ctx);
            cwgl_bindBuffer(glue->ctx, ARRAY_BUFFER, state->proxy_buffer);
            cwgl_bufferData(glue->ctx, ARRAY_BUFFER, 
                            bufsize, buf, STREAM_DRAW);

            /* Update binding */
            cwgl_vertexAttribPointer(glue->ctx, i, 
                                     state->client_array_size,
                                     state->client_array_type,
                                     state->client_array_normalized,
                                     0 /* stride */,
                                     0 /* offset */);
            cwgl_enableVertexAttribArray(glue->ctx, i);
        }
    }

    if(temp){
        free(temp);
    }

    return 1;
}

static void
teardown_proxy_buffers(glue_ctx_t* glue){
    int i;
    glue_va_state_t* state;
    for(i = 0; i!= GLUE_MAX_VERTEX_ATTRIBUTES; i++){
        state = &glue->va_state[i];
        if(state->proxy_buffer){
            cwgl_deleteBuffer(glue->ctx, state->proxy_buffer);
            cwgl_Buffer_release(glue->ctx, state->proxy_buffer);
        }
    }

    cwgl_bindBuffer(glue->ctx, ARRAY_BUFFER,
                    glue->current_array_buffer_obj);
}

GL_APICALL void GL_APIENTRY
glDrawArrays(GLenum mode, GLint first, GLsizei count){
    int realized;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(count < 0){
        abort(); // overflow
    }

    realized = realize_proxy_buffers(glue, count);

    cwgl_drawArrays(ctx, (cwgl_enum_t) mode, first, count);

    if(realized){
        teardown_proxy_buffers(glue);
    }
}

GL_APICALL void GL_APIENTRY
glDrawElements(GLenum mode, GLsizei count, GLenum type,
               void* indices){
    int i;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_va_state_t* state;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(count < 0){
        abort(); // overflow
    }
    if(! glue->current_element_array_buffer){
        abort(); // Not implemented
    }

    for(i = 0; i!= GLUE_MAX_VERTEX_ATTRIBUTES; i++){
        state = &glue->va_state[i];
        if(state->enable && state->use_client_array){
            abort(); // Not implemented
        }
    }

    cwgl_drawElements(ctx, (cwgl_enum_t) mode, count, (cwgl_enum_t) type,
                      (uint32_t)(uintptr_t) indices);
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
    if((cwgl_enum_t) target == ARRAY_BUFFER){
        glue->current_array_buffer = buffer;
        glue->current_array_buffer_obj = buf;
    }
    if((cwgl_enum_t) target == ELEMENT_ARRAY_BUFFER){
        glue->current_element_array_buffer = buffer;
    }
    cwgl_bindBuffer(ctx, (cwgl_enum_t) target, buf);

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
            if(glue->current_array_buffer == buffers[x]){
                glue->current_array_buffer = 0;
                glue->current_array_buffer_obj = 0;
            }
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
    int i;
    size_t y,srctotal;
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
        for(i = 0; i != count; i++){
            srctotal += strlen(string[i]);
        }
    }else{
        for(i = 0; i != count; i++){
            srctotal += length[i];
        }
    }
    temp = malloc(srctotal + 1);
    if(! temp){
        abort();
    }

    /* pass2: Copy to temporary buffer */
    if(! length){
        temp[0] = 0;
        for(i = 0; i != count; i++){
            (void) strcat(temp, string[i]);
        }
    }else{
        y = 0;
        for(i = 0; i != count; i++){
            memcpy(&temp[y], string[i], length[i]);
            y += length[i];
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

    glue_clear_uniform_cache(glue, program);
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

    if(! program){
        prg = 0;
    }else{
        ptr = glue_get(glue, OBJ_PROGRAM, program);
        if(! ptr){
            abort(); // error
        }
        prg = ptr->program;
    }

    cwgl_useProgram(ctx, prg);
    glue->current_program = program;
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
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Program_t* prg;

    int32_t out_size;
    int32_t out_type;
    size_t namesize;
    cwgl_string_t* out_name;
    cwgl_query_result_t r;

    if(bufSize < 0){
        abort();
    }

    ctx = glue_current_ctx();
    glue = glue_current_glue();
    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }

    prg = ptr->program;
    r = cwgl_getActiveAttrib(ctx, prg, index,
                             &out_size, &out_type, &out_name);

    if(r != CWGL_QR_SUCCESS){
        if(r == CWGL_QR_GLERROR){
            return;
        }
        abort();
    }

    *size = out_size;
    *type = (GLenum) (unsigned int) out_type;
    namesize = cwgl_string_size(ctx, out_name);
    if(namesize == 0){
        if(bufSize > 0){
            name[0] = 0;
        }
        if(length){
            *length = 0;
        }
    }else{
        if((unsigned)bufSize <= namesize){
            namesize = bufSize - 1;
        }
        (void)cwgl_string_read(ctx, out_name, name, bufSize);
        name[namesize] = 0;
        if(length){
            *length = namesize;
        }
    }
    cwgl_string_release(ctx, out_name);
}

GL_APICALL GLint GL_APIENTRY
glGetAttribLocation(GLuint program, const char *name){
    GLint r;
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
    r = cwgl_getAttribLocation(ctx, prg, name);
    return r;
}

GL_APICALL void GL_APIENTRY
glBindAttribLocation(GLuint program, GLuint index, const char *name){
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
    cwgl_bindAttribLocation(ctx, prg, index, name);
    return;
}

GL_APICALL GLint GL_APIENTRY
glGetUniformLocation(GLuint program, const char *name){
    int x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Program_t* prg;
    cwgl_UniformLocation_t* loc;
    glue_program_uniform_cache_t* cache;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }
    prg = ptr->program;

    /* First, search for cached uniform location */
    for(x = 0; x != GLUE_MAX_UNIFORMS; x++){
        cache = &glue->obj[program].uniform_cache[x];
        if (!cache->name) {
            continue;
        }
        if(! strcmp(cache->name, name)){
            return x;
        }
    }

    /* Allocate UniformLocation */
    loc = cwgl_getUniformLocation(ctx, prg, name);
    if(! loc){
        return (GLint) -1;
    }
    for(x = 0; x != GLUE_MAX_UNIFORMS; x++){
        cache = &glue->obj[program].uniform_cache[x];
        if(! cache->obj){
            cache->obj = loc;
            cache->name = _strdup(name);
            return x;
        }
    }

    abort(); // overflow
}

GL_APICALL void GL_APIENTRY
glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize,
                   GLsizei *length, GLint *size, GLenum *type,
                   char *name){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Program_t* prg;

    int32_t out_size;
    int32_t out_type;
    size_t namesize;
    cwgl_string_t* out_name;
    cwgl_query_result_t r;

    if(bufSize < 0){
        abort();
    }

    ctx = glue_current_ctx();
    glue = glue_current_glue();
    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }

    prg = ptr->program;
    r = cwgl_getActiveUniform(ctx, prg, index,
                              &out_size, &out_type, &out_name);

    if(r != CWGL_QR_SUCCESS){
        if(r == CWGL_QR_GLERROR){
            return;
        }
        abort();
    }

    *size = out_size;
    *type = (GLenum) (unsigned int) out_type;
    namesize = cwgl_string_size(ctx, out_name);
    if(namesize == 0){
        if(bufSize > 0){
            name[0] = 0;
        }
        if(length){
            *length = 0;
        }
    }else{
        if((unsigned)bufSize <= namesize){
            namesize = bufSize - 1;
        }
        (void)cwgl_string_read(ctx, out_name, name, bufSize);
        name[namesize] = 0;
        if(length){
            *length = namesize;
        }
    }
    cwgl_string_release(ctx, out_name);
}

static cwgl_UniformLocation_t*
uniformlocation(glue_ctx_t* glue, GLint location){
    unsigned int program = glue->current_program;
    cwgl_UniformLocation_t* loc;
    if(location >= GLUE_MAX_UNIFORMS){
        abort();
    }
    if(! program){
        abort();
    }
    if(program >= glue->objs){
        abort();
    }
    if(glue->obj[program].type != OBJ_PROGRAM){
        abort();
    }

    loc = glue->obj[program].uniform_cache[location].obj;
    if(! loc){
        abort();
    }

    return loc;
}

GL_APICALL void GL_APIENTRY
glUniform1i(GLint location, GLint x){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform1i(ctx, loc, x);
}

GL_APICALL void GL_APIENTRY
glUniform2i(GLint location, GLint x, GLint y){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform2i(ctx, loc, x, y);
}

GL_APICALL void GL_APIENTRY
glUniform3i(GLint location, GLint x, GLint y, GLint z){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform3i(ctx, loc, x, y, z);
}

GL_APICALL void GL_APIENTRY
glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform4i(ctx, loc, x, y, z, w);
}

GL_APICALL void GL_APIENTRY
glUniform1f(GLint location, GLfloat x){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform1f(ctx, loc, x);
}

GL_APICALL void GL_APIENTRY
glUniform2f(GLint location, GLfloat x, GLfloat y){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform2f(ctx, loc, x, y);
}

GL_APICALL void GL_APIENTRY
glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform3f(ctx, loc, x, y, z);
}

GL_APICALL void GL_APIENTRY
glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform4f(ctx, loc, x, y, z, w);
}

GL_APICALL void GL_APIENTRY
glUniform1iv(GLint location, GLsizei count, const GLint* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform1iv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniform2iv(GLint location, GLsizei count, const GLint* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform2iv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniform3iv(GLint location, GLsizei count, const GLint* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform3iv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniform4iv(GLint location, GLsizei count, const GLint* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform4iv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniform1fv(GLint location, GLsizei count, const GLfloat* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform1fv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniform2fv(GLint location, GLsizei count, const GLfloat* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform2fv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniform3fv(GLint location, GLsizei count, const GLfloat* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform3fv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniform4fv(GLint location, GLsizei count, const GLfloat* v){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniform4fv(ctx, loc, v, count);
}

GL_APICALL void GL_APIENTRY
glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniformMatrix2fv(ctx, loc, transpose, value, count);
}

GL_APICALL void GL_APIENTRY
glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniformMatrix3fv(ctx, loc, transpose, value, count);
}

GL_APICALL void GL_APIENTRY
glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                   const GLfloat *value){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    cwgl_UniformLocation_t* loc;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    loc = uniformlocation(glue, location);
    cwgl_uniformMatrix4fv(ctx, loc, transpose, value, count);
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


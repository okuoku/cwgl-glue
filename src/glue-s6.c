#define CWGL_DECL_ENUMS

#include "glue-priv.h"
#include "glue-ctx.h"
#include <stdlib.h>

#define TYPE_BOOL4 ((cwgl_query_result_t) 0x1001)
#define TYPE_Ia ((cwgl_query_result_t) 0x1002)
#define TYPE_STR ((cwgl_query_result_t) 0x1003)

static cwgl_query_result_t
getenumtype(cwgl_enum_t num){
    switch(num){
        case BLEND:
        case CULL_FACE:
        case DEPTH_TEST:
        case DEPTH_WRITEMASK:
        case DITHER:
        case POLYGON_OFFSET_FILL:
        case SAMPLE_ALPHA_TO_COVERAGE:
        case SAMPLE_COVERAGE:
        case SAMPLE_COVERAGE_INVERT:
        case SCISSOR_TEST:
        case STENCIL_TEST:
        case UNPACK_FLIP_Y_WEBGL:
        case UNPACK_PREMULTIPLY_ALPHA_WEBGL:
        case DELETE_STATUS:
        case LINK_STATUS:
        case VALIDATE_STATUS:
        //case DELETE_STATUS:
        case COMPILE_STATUS:
        case VERTEX_ATTRIB_ARRAY_ENABLED:
        case VERTEX_ATTRIB_ARRAY_NORMALIZED:
            return CWGL_QR_TYPE_BOOL;
        case COLOR_WRITEMASK:
            return TYPE_BOOL4; // FIXME: Add B4 type
        case MAX_VIEWPORT_DIMS:
            return CWGL_QR_TYPE_I2;
        case SCISSOR_BOX:
        case VIEWPORT:
            return CWGL_QR_TYPE_I4;
        case COMPRESSED_TEXTURE_FORMATS:
            return TYPE_Ia; // FIXME: Add I* type
        case RENDERER:
        case VENDOR:
        case VERSION:
        case SHADING_LANGUAGE_VERSION:
            return TYPE_STR; // FIXME: Add String type
        case DEPTH_CLEAR_VALUE:
        case LINE_WIDTH:
        case POLYGON_OFFSET_FACTOR:
        case POLYGON_OFFSET_UNITS:
        case SAMPLE_COVERAGE_VALUE:
            return CWGL_QR_TYPE_F1; 
        case ALIASED_LINE_WIDTH_RANGE:
        case ALIASED_POINT_SIZE_RANGE:
        case DEPTH_RANGE:
            return CWGL_QR_TYPE_F2;
        case BLEND_COLOR:
        case COLOR_CLEAR_VALUE:
        //case SCISSOR_BOX:
        case CURRENT_VERTEX_ATTRIB:
            return CWGL_QR_TYPE_F4;
        case ARRAY_BUFFER_BINDING:
        case ELEMENT_ARRAY_BUFFER_BINDING:
        case VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
            return CWGL_QR_TYPE_BUFFER;
        case CURRENT_PROGRAM:
            return CWGL_QR_TYPE_PROGRAM;
        case FRAMEBUFFER_BINDING:
            return CWGL_QR_TYPE_FRAMEBUFFER;
        case RENDERBUFFER_BINDING:
            return CWGL_QR_TYPE_RENDERBUFFER;
        case TEXTURE_BINDING_2D:
        case TEXTURE_BINDING_CUBE_MAP:
            return CWGL_QR_TYPE_TEXTURE;

        case ACTIVE_TEXTURE:
        case ALPHA_BITS:
        case BLEND_DST_ALPHA:
        case BLEND_DST_RGB:
        case BLEND_EQUATION_ALPHA:
        case BLEND_EQUATION_RGB:
        case BLEND_SRC_ALPHA:
        case BLEND_SRC_RGB:
        case BLUE_BITS:
        case CULL_FACE_MODE:
        case DEPTH_BITS:
        case DEPTH_FUNC:
        case FRONT_FACE:
        case GENERATE_MIPMAP_HINT:
        case GREEN_BITS:
        case IMPLEMENTATION_COLOR_READ_FORMAT:
        case IMPLEMENTATION_COLOR_READ_TYPE:
        case MAX_COMBINED_TEXTURE_IMAGE_UNITS:
        case MAX_CUBE_MAP_TEXTURE_SIZE:
        case MAX_FRAGMENT_UNIFORM_VECTORS:
        case MAX_RENDERBUFFER_SIZE:
        case MAX_TEXTURE_IMAGE_UNITS:
        case MAX_TEXTURE_SIZE:
        case MAX_VARYING_VECTORS:
        case MAX_VERTEX_ATTRIBS:
        case MAX_VERTEX_TEXTURE_IMAGE_UNITS:
        case MAX_VERTEX_UNIFORM_VECTORS:
        case PACK_ALIGNMENT:
        case RED_BITS:
        case SAMPLE_BUFFERS:
        case SAMPLES:
        case STENCIL_BACK_FAIL:
        case STENCIL_BACK_FUNC:
        case STENCIL_BACK_PASS_DEPTH_FAIL:
        case STENCIL_BACK_PASS_DEPTH_PASS:
        case STENCIL_BACK_REF:
        case STENCIL_BACK_VALUE_MASK:
        case STENCIL_BACK_WRITEMASK:
        case STENCIL_BITS:
        case STENCIL_CLEAR_VALUE:
        case STENCIL_FAIL:
        case STENCIL_FUNC:
        case STENCIL_PASS_DEPTH_FAIL:
        case STENCIL_PASS_DEPTH_PASS:
        case STENCIL_REF:
        case STENCIL_VALUE_MASK:
        case STENCIL_WRITEMASK:
        case SUBPIXEL_BITS:
        case UNPACK_ALIGNMENT:
        case UNPACK_COLORSPACE_CONVERSION_WEBGL:
        case FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE:
        case FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL:
        case FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE:
        case RENDERBUFFER_WIDTH:
        case RENDERBUFFER_HEIGHT:
        case RENDERBUFFER_INTERNAL_FORMAT:
        case RENDERBUFFER_RED_SIZE:
        case RENDERBUFFER_GREEN_SIZE:
        case RENDERBUFFER_BLUE_SIZE:
        case RENDERBUFFER_ALPHA_SIZE:
        case RENDERBUFFER_DEPTH_SIZE:
        case RENDERBUFFER_STENCIL_SIZE:
        case TEXTURE_MAG_FILTER:
        case TEXTURE_MIN_FILTER:
        case TEXTURE_WRAP_S:
        case TEXTURE_WRAP_T:
        case ATTACHED_SHADERS:
        case ACTIVE_ATTRIBUTES:
        case ACTIVE_UNIFORMS:
        case SHADER_TYPE:
        case VERTEX_ATTRIB_ARRAY_SIZE:
        case VERTEX_ATTRIB_ARRAY_STRIDE:
        case VERTEX_ATTRIB_ARRAY_TYPE:
            return CWGL_QR_TYPE_I1;
        default:
            printf("Unknown enum type %x\n", num);
            return CWGL_QR_TYPE_I1;
    }
}

/* 6.1 Querying GL State */
/* 6.1.1 Simple Queries */
GL_APICALL void GL_APIENTRY
glGetBooleanv(GLenum value, GLboolean *data){
    cwgl_ctx_t* ctx;
    cwgl_query_result_t type;
    int32_t buf[4];
    ctx = glue_current_ctx();
    type = getenumtype(value);

    if(type == TYPE_BOOL4){
        cwgl_getParameter_b4(ctx, value, 
                             &buf[0], &buf[1], &buf[2], &buf[3]);
        data[0] = buf[0];
        data[1] = buf[1];
        data[2] = buf[2];
        data[3] = buf[3];
    }else{
        cwgl_getParameter_b1(ctx, value, buf);
        data[0] = buf[0];
    }
}

GL_APICALL void GL_APIENTRY
glGetIntegerv(GLenum value, GLint *data){
    cwgl_ctx_t* ctx;
    cwgl_query_result_t type;
    ctx = glue_current_ctx();
    type = getenumtype(value);

    // Overrides
    if(value == GL_NUM_COMPRESSED_TEXTURE_FORMATS){
        data[0] = 0;
        return;
    }

    if(value == GL_NUM_SHADER_BINARY_FORMATS){
        data[0] = 0;
        return;
    }

    if(value == GL_MAX_VERTEX_ATTRIBS){
        data[0] = 32;
        return;
    }

    switch(type){
        case CWGL_QR_TYPE_I4:
            cwgl_getParameter_i4(ctx, value,
                                 &data[0], &data[1], &data[2], &data[3]);
            return;
        case CWGL_QR_TYPE_I2:
            cwgl_getParameter_i2(ctx, value, &data[0], &data[1]);
            return;
        default:
            cwgl_getParameter_i1(ctx, value, data);
            return;
    }

}

GL_APICALL void GL_APIENTRY
glGetFloatv(GLenum value, GLfloat *data){
    cwgl_ctx_t* ctx;
    cwgl_query_result_t type;
    ctx = glue_current_ctx();
    type = getenumtype(value);

    switch(type){
        case CWGL_QR_TYPE_F4:
            cwgl_getParameter_f4(ctx, value,
                                 &data[0], &data[1], &data[2], &data[3]);
            return;
        case CWGL_QR_TYPE_F2:
            cwgl_getParameter_f2(ctx, value, &data[0], &data[1]);
            return;
        default:
            cwgl_getParameter_f1(ctx, value, data);
            return;
    }
}

GL_APICALL GLboolean GL_APIENTRY
glIsEnabled(GLenum value){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    return cwgl_isEnabled(ctx, value);
}

/* 6.1.3 Enumerated Queries */
GL_APICALL void GL_APIENTRY
glGetTexParameteriv(GLenum target, GLenum value, GLint *data){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_getTexParameter_i1(ctx, (cwgl_enum_t) target,
                            (cwgl_enum_t) value,
                            data);

}

GL_APICALL void GL_APIENTRY
glGetTexParameterfv(GLenum target, GLenum value, GLfloat *data){
    abort(); // None?
}

GL_APICALL void GL_APIENTRY
glGetBufferParameteriv(GLenum target, GLenum value, GLint *data){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_getBufferParameter_i1(ctx, (cwgl_enum_t) target,
                               (cwgl_enum_t) value, data);

}

GL_APICALL void GL_APIENTRY
glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment,
                                      GLenum pname, GLint *params){
    cwgl_ctx_t* ctx;
    cwgl_query_result_t type;
    ctx = glue_current_ctx();
    type = getenumtype(pname);

    switch(type){
        case CWGL_QR_TYPE_RENDERBUFFER:
        case CWGL_QR_TYPE_TEXTURE:
            abort(); // unimpl
            return;
        default:
            cwgl_getFramebufferAttachmentParameter_i1(ctx,
                                                      (cwgl_enum_t) target,
                                                      (cwgl_enum_t) attachment,
                                                      (cwgl_enum_t) pname,
                                                      params);
            return;
    }
}

GL_APICALL void GL_APIENTRY
glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_getRenderbufferParameter_i1(ctx, (cwgl_enum_t) target,
                                     (cwgl_enum_t) pname,
                                     params);

}

/* 6.1.4 Texture Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsTexture(GLuint texture){
    glue_ctx_t* glue;
    glue = glue_current_glue();

    if(texture >= glue->objs){
        return 0;
    }else if(glue->obj[texture].type == OBJ_TEXTURE){
        return 1;
    }else{
        return 0;
    }
}

/* 6.1.5 String Queries */
GL_APICALL const GLubyte* GL_APIENTRY // the spec lacks const
glGetString(GLenum name){
    switch(name){
        case GL_EXTENSIONS:
            return "";
        case GL_VENDOR:
            return "cwgl";
        case GL_RENDERER:
            return "cwgl";
        case GL_VERSION:
            return "OpenGL ES 2.0";
        case GL_SHADING_LANGUAGE_VERSION:
            return "OpenGL ES GLSL ES 1.00";
        default:
            abort();
            return "";
    }
}

/* 6.1.6 Buffer Object Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsBuffer(GLuint buffer){
    glue_ctx_t* glue;
    glue = glue_current_glue();

    if(buffer >= glue->objs){
        return 0;
    }else if(glue->obj[buffer].type == OBJ_BUFFER){
        return 1;
    }else{
        return 0;
    }
}

/* 6.1.7 Framebuffer Object and Renderbuffer Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsFramebuffer(GLuint framebuffer){
    glue_ctx_t* glue;
    glue = glue_current_glue();

    if(framebuffer >= glue->objs){
        return 0;
    }else if(glue->obj[framebuffer].type == OBJ_FRAMEBUFFER){
        return 1;
    }else{
        return 0;
    }
}

GL_APICALL GLboolean GL_APIENTRY
glIsRenderbuffer(GLuint renderbuffer){
    glue_ctx_t* glue;
    glue = glue_current_glue();

    if(renderbuffer >= glue->objs){
        return 0;
    }else if(glue->obj[renderbuffer].type == OBJ_RENDERBUFFER){
        return 1;
    }else{
        return 0;
    }
}

/* 6.1.8 Shader and Program Queries */
GL_APICALL GLboolean GL_APIENTRY
glIsShader(GLuint shader){
    glue_ctx_t* glue;
    glue = glue_current_glue();

    if(shader >= glue->objs){
        return 0;
    }else if(glue->obj[shader].type == OBJ_SHADER){
        return 1;
    }else{
        return 0;
    }
}

GL_APICALL void GL_APIENTRY
glGetShaderiv(GLuint shader, GLenum pname, GLint *params){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr = glue_get(glue, OBJ_SHADER, shader);
    if(! ptr){
        abort(); //error
    }

    cwgl_getShaderParameter_i1(ctx, ptr->shader, (cwgl_enum_t) pname,
                               params);
}

GL_APICALL GLboolean GL_APIENTRY
glIsProgram(GLuint program){
    glue_ctx_t* glue;
    glue = glue_current_glue();

    if(program >= glue->objs){
        return 0;
    }else if(glue->obj[program].type == OBJ_PROGRAM){
        return 1;
    }else{
        return 0;
    }
}

GL_APICALL void GL_APIENTRY
glGetProgramiv(GLuint program, GLenum pname, GLint *params){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); //error
    }

    cwgl_getProgramParameter_i1(ctx, ptr->program, (cwgl_enum_t) pname,
                               params);
}

GL_APICALL void GL_APIENTRY
glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count,
                     GLuint *shaders){
    abort(); // unimpl
}

GL_APICALL void GL_APIENTRY
glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length,
                   GLchar *infoLog){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_string_t* str;
    size_t strsize;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(bufSize < 0){
        abort(); // error
    }

    ptr = glue_get(glue, OBJ_SHADER, shader);
    if(! ptr){
        abort(); // error
    }

    str = cwgl_getShaderInfoLog(ctx, ptr->shader);
    if(str){
        strsize = cwgl_string_size(ctx, str);
        if(strsize == 0){
            if(bufSize > 0){
                infoLog[0] = 0;
            }
            if(length){
                *length = 0;
            }
        }else{
            if((unsigned)bufSize <= strsize){
                strsize = bufSize - 1;
            }
            (void)cwgl_string_read(ctx, str, infoLog, bufSize);
            infoLog[strsize] = 0;
            if(length){
                *length = strsize;
            }
        }
        cwgl_string_release(ctx, str);
    }else{
        abort();
    }
}

GL_APICALL void GL_APIENTRY
glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length,
                    GLchar *infoLog){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_string_t* str;
    size_t strsize;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(bufSize < 0){
        abort(); // error
    }

    ptr = glue_get(glue, OBJ_PROGRAM, program);
    if(! ptr){
        abort(); // error
    }

    str = cwgl_getProgramInfoLog(ctx, ptr->program);
    if(str){
        strsize = cwgl_string_size(ctx, str);
        if(strsize == 0){
            if(bufSize > 0){
                infoLog[0] = 0;
            }
            if(length){
                *length = 0;
            }
        }else{
            if((unsigned)bufSize <= strsize){
                strsize = bufSize - 1;
            }
            (void)cwgl_string_read(ctx, str, infoLog, bufSize);
            infoLog[strsize] = 0;
            if(length){
                *length = strsize;
            }
        }
        cwgl_string_release(ctx, str);
    }else{
        abort();
    }

}

GL_APICALL void GL_APIENTRY
glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length,
                  GLchar* source){
    abort(); // unimpl
}

GL_APICALL void GL_APIENTRY
glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype,
                           GLint *range, GLint *precision){
    // FIXME: temp. Return highp existence for now
    range[0] = range[1] = 127;
    precision[0] = 32;
}

GL_APICALL void GL_APIENTRY
glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params){
    abort(); // unimpl
}

GL_APICALL void GL_APIENTRY
glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params){
    abort(); // unimpl
}

GL_APICALL void GL_APIENTRY
glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer){
    abort(); // unimpl
}

GL_APICALL void GL_APIENTRY
glGetUniformfv(GLuint program, GLint location, GLfloat *params){
    abort(); // unimpl
}

GL_APICALL void GL_APIENTRY
glGetUniformiv(GLuint program, GLint location, GLint *params){
    abort(); // unimpl
}



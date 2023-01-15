#include "glue-priv.h"
#include "glue-ctx.h"
#include <stdlib.h>

/* 3.4 Line Segments */
GL_APICALL void GL_APIENTRY
glLineWidth(GLfloat width){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_lineWidth(ctx, width);
}

/* 3.5 Polygons */
/* 3.5.1 Basic Polygon Rasterization */
GL_APICALL void GL_APIENTRY
glFrontFace(GLenum dir){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_frontFace(ctx, (cwgl_enum_t) dir);
}

GL_APICALL void GL_APIENTRY
glCullFace(GLenum mode){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_cullFace(ctx, (cwgl_enum_t) mode);
}

/* 3.5.2 Depth Offset */
GL_APICALL void GL_APIENTRY
glPolygonOffset(GLfloat factor, GLfloat units){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_polygonOffset(ctx, factor, units);
}

/* 3.6 Pixel Rectangles */
/* 3.6.1 Pixel Storage Modes */
GL_APICALL void GL_APIENTRY
glPixelStorei(GLenum pname, GLint param /* ??? */){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_pixelStorei(ctx, (cwgl_enum_t) pname, param);
}

/* 3.7 Texturing */
GL_APICALL void GL_APIENTRY
glActiveTexture(GLenum texture){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_activeTexture(ctx, (cwgl_enum_t) texture);
}

/* 3.7.1 Texture Image Specification */
GL_APICALL void GL_APIENTRY
glTexImage2D(GLenum target, GLint level, GLint internalformat,
             GLsizei width, GLsizei height, GLint border,
             GLenum format, GLenum type, void *data){
    // FIXME:
}

/* 3.7.2 Alternate Texture Image Specification Commands */
GL_APICALL void GL_APIENTRY
glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat,
                 GLint x, GLint y, GLsizei width, GLsizei height, GLint border){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_copyTexImage2D(ctx, (cwgl_enum_t) target, level,
                        (cwgl_enum_t) internalformat, 
                        x, y, width, height, border);

}

GL_APICALL void GL_APIENTRY
glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                GLsizei width, GLsizei height, GLenum format, GLenum type,
                void *data){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                    GLint x, GLint y, GLsizei width, GLsizei height){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_copyTexSubImage2D(ctx, (cwgl_enum_t) target, level, xoffset, yoffset, 
                           x, y, width, height);
}

/* 3.7.3 Compressed Texture Images */
GL_APICALL void GL_APIENTRY
glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat,
                       GLsizei width, GLsizei height, GLint border,
                       GLsizei imageSize, void *data){
    // FIXME:
}

GL_APICALL void GL_APIENTRY
glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                          GLint yoffset, GLsizei width, GLsizei height,
                          GLenum format, GLsizei imageSize, void *data){
    // FIXME:
}

/* 3.7.4 Texture Parameters */
GL_APICALL void GL_APIENTRY
glTexParameteri(GLenum target, GLenum pname, GLint param){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_texParameteri(ctx, (cwgl_enum_t) target, (cwgl_enum_t) pname, param);
}

GL_APICALL void GL_APIENTRY
glTexParameterf(GLenum target, GLenum pname, GLfloat param){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_texParameterf(ctx, (cwgl_enum_t) target, (cwgl_enum_t) pname, param);
}

GL_APICALL void GL_APIENTRY
glTexParameteriv(GLenum target, GLenum pname, const GLint* params){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_texParameteri(ctx, (cwgl_enum_t) target, (cwgl_enum_t) pname, 
                       params[0]);
}

GL_APICALL void GL_APIENTRY
glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_texParameterf(ctx, (cwgl_enum_t) target, (cwgl_enum_t) pname, 
                       params[0]);
}

/* 3.7.11 Mipmap Generation */
GL_APICALL void GL_APIENTRY
glGenerateMipmap(GLenum target){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_generateMipmap(ctx, (cwgl_enum_t) target);
}

/* 3.7.13 Texture Objects */
GL_APICALL void GL_APIENTRY
glBindTexture(GLenum target, GLuint texture){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Texture_t* tex;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(! texture){
        tex = 0;
    }else{
        ptr = glue_get(glue, OBJ_TEXTURE, texture);
        if(! ptr){
            abort(); // unknown
            return;
        }else{
            tex = ptr->texture;
        }
    }

    cwgl_bindTexture(ctx, (cwgl_enum_t) target, tex);

}

GL_APICALL void GL_APIENTRY
glDeleteTextures(GLsizei n, const GLuint *textures){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0;x != n; x++){
        if(textures[x]){
            ptr = glue_get(glue, OBJ_TEXTURE, textures[x]);
            if(! ptr){
                abort(); // unknown
                return;
            }
            cwgl_deleteTexture(ctx, ptr->texture);
            (void) glue_del(glue, OBJ_TEXTURE, textures[x]);
        }
    }
}

GL_APICALL void GL_APIENTRY
glGenTextures(GLsizei n, GLuint *textures){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0; x != n; x++){
        ptr.texture = cwgl_createTexture(ctx);
        textures[x] = glue_put(glue, OBJ_TEXTURE, &ptr);
    }
}

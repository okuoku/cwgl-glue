#define CWGL_DECL_ENUMS

#include "glue-priv.h"
#include "glue-ctx.h"
#include <stdlib.h>

/* 4.1 Per-Fragment Operations */
/* 4.1.2 Scissor Test */
GL_APICALL void GL_APIENTRY
glScissor(GLint left, GLint bottom, GLsizei width, GLsizei height){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_scissor(ctx, left, bottom, width, height);
}

/* 4.1.3 Multisample Fragment Operations */
GL_APICALL void GL_APIENTRY
glSampleCoverage(GLclampf value, GLboolean invert){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_sampleCoverage(ctx, value, invert);
}

/* 4.1.4 Stencil Test */
GL_APICALL void GL_APIENTRY
glStencilFunc(GLenum func, GLint ref, GLuint mask){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    cwgl_stencilFunc(ctx, (cwgl_enum_t) func, ref, mask);
}

GL_APICALL void GL_APIENTRY
glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_stencilFuncSeparate(ctx, (cwgl_enum_t) face, (cwgl_enum_t) func,
                             ref, mask);
}

GL_APICALL void GL_APIENTRY
glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_stencilOp(ctx, (cwgl_enum_t) sfail, (cwgl_enum_t) dpfail,
                   (cwgl_enum_t) dppass);
}

GL_APICALL void GL_APIENTRY
glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_stencilOpSeparate(ctx, (cwgl_enum_t) face, (cwgl_enum_t) sfail,
                           (cwgl_enum_t) dpfail, (cwgl_enum_t) dppass);
}

/* 4.1.5 Depth Buffer Test */
GL_APICALL void GL_APIENTRY
glDepthFunc(GLenum func){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_depthFunc(ctx, (cwgl_enum_t) func);
}

/* 4.1.6 Blending */
GL_APICALL void GL_APIENTRY
glBlendEquation(GLenum mode){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_blendEquation(ctx, (cwgl_enum_t) mode);
}

GL_APICALL void GL_APIENTRY
glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_blendEquationSeparate(ctx, (cwgl_enum_t) modeRGB,
                               (cwgl_enum_t) modeAlpha);
}

GL_APICALL void GL_APIENTRY
glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha,
                    GLenum dstAlpha){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_blendFuncSeparate(ctx, (cwgl_enum_t) srcRGB, (cwgl_enum_t) dstRGB,
                           (cwgl_enum_t) srcAlpha, (cwgl_enum_t) dstAlpha);
}

GL_APICALL void GL_APIENTRY
glBlendFunc(GLenum src, GLenum dst){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_blendFunc(ctx, (cwgl_enum_t) src, (cwgl_enum_t) dst);
}

GL_APICALL void GL_APIENTRY
glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_blendColor(ctx, red, green, blue, alpha);
}

/* 4.2 Whole Framebuffer Operations */
/* 4.2.2 Fine Control of BUffer Updates */
GL_APICALL void GL_APIENTRY
glColorMask(GLboolean r, GLboolean g, GLboolean b, GLboolean a){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_colorMask(ctx, r, g, b, a);
}

GL_APICALL void GL_APIENTRY
glDepthMask(GLboolean mask){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_depthMask(ctx, mask);
}

GL_APICALL void GL_APIENTRY
glStencilMask(GLuint mask){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_stencilMask(ctx, mask);
}

GL_APICALL void GL_APIENTRY
glStencilMaskSeparate(GLenum face, GLuint mask){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_stencilMaskSeparate(ctx, (cwgl_enum_t) face, mask);
}

/* 4.2.3 Clearing the BUffers */
GL_APICALL void GL_APIENTRY
glClear(GLbitfield buf){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_clear(ctx, buf);
}

GL_APICALL void GL_APIENTRY
glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_clearColor(ctx, r, g, b, a);
}

GL_APICALL void GL_APIENTRY
glClearDepthf(GLclampf d){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_clearDepth(ctx, d);
}

GL_APICALL void GL_APIENTRY
glClearStencil(GLint s){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_clearStencil(ctx, s);
}

/* 4.3 Reading Pixels */
/* 4.3.1 Reading Pixels */

static int
pixelelemsize(cwgl_enum_t type){
    switch(type){
        case UNSIGNED_BYTE:
            return 1;
        case UNSIGNED_INT:
        case INT:
        case FLOAT:
            return 4;
        default:
            abort();
            return 0;
    }
}

GL_APICALL void GL_APIENTRY
glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, 
             GLenum format, GLenum type, void *data){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();
    // FIXME: Consider glPixelStorei setting
    const int elemsize = pixelelemsize((cwgl_enum_t) type);
    const size_t datasize = width * height * elemsize * 4; // FIXME: Align??

    cwgl_readPixels(ctx, x, y, width, height, format, type, data, datasize);
}

/* 4.4 Framebuffer Objects */
/* 4.4.1 Binding and Managing Framebuffer Objects */
GL_APICALL void GL_APIENTRY
glBindFramebuffer(GLenum target, GLuint framebuffer){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Framebuffer_t* fb;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(! framebuffer){
        fb = 0;
    }else{
        ptr = glue_get(glue, OBJ_FRAMEBUFFER, framebuffer);
        if(! ptr){
            abort(); // unknown
            return;
        }else{
            fb = ptr->framebuffer;
        }
    }
    cwgl_bindFramebuffer(ctx, (cwgl_enum_t) target, fb);
}

GL_APICALL void GL_APIENTRY
glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0;x != n; x++){
        if(framebuffers[x]){
            ptr = glue_get(glue, OBJ_FRAMEBUFFER, framebuffers[x]);
            if(! ptr){
                abort(); // unknown
                return;
            }
            cwgl_deleteFramebuffer(ctx, ptr->framebuffer);
            (void) glue_del(glue, OBJ_FRAMEBUFFER, framebuffers[x]);
        }
    }
}

GL_APICALL void GL_APIENTRY
glGenFramebuffers(GLsizei n, GLuint *framebuffers){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0; x != n; x++){
        ptr.framebuffer = cwgl_createFramebuffer(ctx);
        framebuffers[x] = glue_put(glue, OBJ_FRAMEBUFFER, &ptr);
    }
}

/* 4.4.3 Renderbuffer Objects */
GL_APICALL void GL_APIENTRY
glBindRenderbuffer(GLenum target, GLuint renderbuffer){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Renderbuffer_t* rb;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(! renderbuffer){
        rb = 0;
    }else{
        ptr = glue_get(glue, OBJ_RENDERBUFFER, renderbuffer);
        if(! ptr){
            abort(); // unknown
            return;
        }else{
            rb = ptr->renderbuffer;
        }
    }
    cwgl_bindRenderbuffer(ctx, (cwgl_enum_t) target, rb);
}

GL_APICALL void GL_APIENTRY
glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0;x != n; x++){
        if(renderbuffers[x]){
            ptr = glue_get(glue, OBJ_RENDERBUFFER, renderbuffers[x]);
            if(! ptr){
                abort(); // unknown
                return;
            }
            cwgl_deleteRenderbuffer(ctx, ptr->renderbuffer);
            (void) glue_del(glue, OBJ_RENDERBUFFER, renderbuffers[x]);
        }
    }
}

GL_APICALL void GL_APIENTRY
glGenRenderbuffers(GLsizei n, GLuint *renderbuffers){
    GLsizei x;
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t ptr;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    for(x = 0; x != n; x++){
        ptr.renderbuffer = cwgl_createRenderbuffer(ctx);
        renderbuffers[x] = glue_put(glue, OBJ_RENDERBUFFER, &ptr);
    }
}

GL_APICALL void GL_APIENTRY
glRenderbufferStorage(GLenum target, GLenum internalformat,
                      GLsizei width, GLsizei height){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_renderbufferStorage(ctx, (cwgl_enum_t) target, 
                             (cwgl_enum_t) internalformat,
                             width, height);
}

GL_APICALL void GL_APIENTRY
glFramebufferRenderbuffer(GLenum target, GLenum attachment,
                          GLenum renderbuffertarget, GLuint renderbuffer){
    cwgl_ctx_t* ctx;
    glue_ctx_t* glue;
    glue_obj_ptr_t* ptr;
    cwgl_Renderbuffer_t* rb;
    ctx = glue_current_ctx();
    glue = glue_current_glue();

    if(! renderbuffer){
        rb = 0;
    }else{
        ptr = glue_get(glue, OBJ_RENDERBUFFER, renderbuffer);
        if(! ptr){
            abort(); // unknown
            return;
        }else{
            rb = ptr->renderbuffer;
        }
    }

    cwgl_framebufferRenderbuffer(ctx, (cwgl_enum_t) target,
                                 (cwgl_enum_t) attachment,
                                 (cwgl_enum_t) renderbuffertarget,
                                 rb);
}

GL_APICALL void GL_APIENTRY
glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget,
                       GLuint texture, GLint level){
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

    cwgl_framebufferTexture2D(ctx, (cwgl_enum_t) target,
                              (cwgl_enum_t) attachment,
                              (cwgl_enum_t) textarget,
                              tex, level);

}

/* 4.4.5 Framebuffer Completeness */
GL_APICALL GLenum GL_APIENTRY
glCheckFramebufferStatus(GLenum target){
    cwgl_ctx_t* ctx;
    cwgl_enum_t r;
    ctx = glue_current_ctx();
    
    r = cwgl_checkFramebufferStatus(ctx, (cwgl_enum_t) target);
    return (GLenum) r;
}




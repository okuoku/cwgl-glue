#include "glue-priv.h"
#include "glue-ctx.h"

/* 5.1 Flush and Finish */
GL_APICALL void GL_APIENTRY
glFlush(void){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_flush(ctx);
}

GL_APICALL void GL_APIENTRY
glFinish(void){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_finish(ctx);
}

/* 5.2 Hints */
GL_APICALL void GL_APIENTRY
glHint(GLenum target, GLenum hint){
    cwgl_ctx_t* ctx;
    ctx = glue_current_ctx();

    cwgl_hint(ctx, (cwgl_enum_t) target, (cwgl_enum_t) hint);
}



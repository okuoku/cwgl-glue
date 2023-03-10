#include "yfrm.h"
#include "glue-ctx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int yfrm_initialized = 0;

/* Global contexts */
static glue_ctx_t* glue_ctx = 0;

static void
obj_setnone(glue_ctx_t* ctx, size_t objid){
    ctx->obj[objid].type = OBJ_FREE;
    ctx->obj[objid].ptr.__invalid = 0;
    memset(ctx->obj[objid].uniform_cache, 0,
           sizeof(glue_program_uniform_cache_t));
}

size_t
glue_put(glue_ctx_t* ctx, glue_obj_type_t type, glue_obj_ptr_t* ptr){
    size_t x,y;
    /* First, search for OBJ_FREE slot */
    for(x = 1 /* Don't check zero */; x != ctx->objs; x++){
        if(ctx->obj[x].type == OBJ_FREE){
            break;
        }
    }
    if(x == ctx->objs){
        /* Expand by 2x and use (previous) last entry */
        ctx->obj = realloc(ctx->obj, sizeof(glue_obj_slot_t) * x * 2);
        if (!ctx->obj) {
            abort();
        }
        ctx->objs = x * 2;
        for(y = x; y!= ctx->objs; y++){
            obj_setnone(ctx, y);
        }
    }
    ctx->obj[x].type = type;
    ctx->obj[x].ptr = *ptr;
    memset(ctx->obj[x].uniform_cache, 0, sizeof(ctx->obj[x].uniform_cache));
    return x;
}

glue_obj_ptr_t*
glue_get(glue_ctx_t* ctx, glue_obj_type_t type, size_t objid){
    glue_obj_slot_t* obj;
    if(objid >= ctx->objs){
        return 0;
    }
    obj = &ctx->obj[objid];
    if(obj->type != type){
        return 0;
    }
    return &obj->ptr;
}

void 
glue_clear_uniform_cache(glue_ctx_t* ctx, size_t program){
    size_t x;
    cwgl_ctx_t* cwgl;
    glue_obj_slot_t* obj;
    obj = &ctx->obj[program];
    cwgl = glue_current_ctx1(ctx);
    for(x = 0; x != GLUE_MAX_UNIFORMS; x++){
        if(obj->uniform_cache[x].obj){
            cwgl_UniformLocation_release(cwgl, 
                                         obj->uniform_cache[x].obj);
            free(obj->uniform_cache[x].name);
            obj->uniform_cache[x].obj = 0;
            obj->uniform_cache[x].name = 0;
        }
    }
}

int /* bool */
glue_del(glue_ctx_t* ctx, glue_obj_type_t type, size_t objid){
    cwgl_ctx_t* cwgl;
    glue_obj_slot_t* obj;
    if(objid >= ctx->objs){
        return 0;
    }
    obj = &ctx->obj[objid];
    if(obj->type != type){
        return 0;
    }
    cwgl = glue_current_ctx1(ctx);
    switch(obj->type){
        case OBJ_ZERO:
        case OBJ_FREE:
            return 0;
        case OBJ_BUFFER:
            cwgl_Buffer_release(cwgl, obj->ptr.buffer);
            break;
        case OBJ_SHADER:
            cwgl_Shader_release(cwgl, obj->ptr.shader);
            break;
        case OBJ_PROGRAM:
            glue_clear_uniform_cache(ctx, objid);
            cwgl_Program_release(cwgl, obj->ptr.program);
            break;
        case OBJ_TEXTURE:
            cwgl_Texture_release(cwgl, obj->ptr.texture);
            break;
        case OBJ_FRAMEBUFFER:
            cwgl_Framebuffer_release(cwgl, obj->ptr.framebuffer);
            break;
        case OBJ_RENDERBUFFER:
            cwgl_Renderbuffer_release(cwgl, obj->ptr.renderbuffer);
            break;
    }
    obj_setnone(ctx, objid);
    return 1;
}


glue_ctx_t*
glue_current_glue(void){
    return glue_ctx;
}

cwgl_ctx_t*
glue_current_ctx1(glue_ctx_t* glue){
    cwgl_ctx_t* ctx;
    ctx = glue_ctx->private__cwgl_ctx;
    glue = glue_current_glue();
    if(! glue->in_frame){
        yfrm_frame_begin0(ctx);
        glue->in_frame = 1;
    }
    return ctx;
}

cwgl_ctx_t*
glue_current_ctx(void){
    return glue_current_ctx1(glue_current_glue());
}


void
glue_init(int width, int height){
    int i;
    // FIXME: Implement thread handling
    cwgl_ctx_t* current_cwgl_ctx;
    if(! yfrm_initialized){
        (void)yfrm_init();
        yfrm_initialized = 1;
    }
    if(! glue_ctx){
        glue_ctx = malloc(sizeof(glue_ctx_t));
        if(! glue_ctx){
            abort();
        }
        current_cwgl_ctx = 0;
    }else{
        free(glue_ctx->obj);
        current_cwgl_ctx = glue_ctx->private__cwgl_ctx;
    }
    memset(glue_ctx, 0, sizeof(glue_ctx_t));
    glue_ctx->objs = 100;
    glue_ctx->obj = malloc(sizeof(glue_obj_slot_t) * 100);
    if(! glue_ctx->obj){
        abort();
    }
    for(i=0; i!= glue_ctx->objs; i++){
        obj_setnone(glue_ctx, i);
    }
    glue_ctx->obj[0].type = OBJ_ZERO;
    if(! current_cwgl_ctx){
        current_cwgl_ctx = yfrm_cwgl_ctx_create(width, height, 0, 0);
        glue_ctx->private__cwgl_ctx = current_cwgl_ctx;
    }else{
        glue_ctx->private__cwgl_ctx = yfrm_cwgl_ctx_reset0(current_cwgl_ctx);
    }

    glue_ctx->in_frame = 0;
}

void
glue_endframe(glue_ctx_t* ctx){
    yfrm_frame_end0(ctx->private__cwgl_ctx);
    ctx->in_frame = 0;
}


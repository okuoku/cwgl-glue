#include "yfrm.h"
#include "glue-ctx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int yfrm_initialized = 0;

/* Global contexts */
static cwgl_ctx_t* cwgl_ctx = 0;
static glue_ctx_t* glue_ctx = 0;

size_t
glue_put(glue_obj_ptr_t* ptr){
}

void
glue_del(size_t objid){
}

void
glue_reset(glue_ctx_t* ctx){
}

cwgl_ctx_t*
glue_current_ctx(void){
    return cwgl_ctx;
}

static void
obj_setnone(glue_ctx_t* ctx, size_t objid){
    ctx->obj[objid].type = OBJ_FREE;
    ctx->obj[objid].ptr.__invalid = 0;
    memset(ctx->obj[objid].uniform_cache, 0,
           sizeof(glue_program_uniform_cache_t));
}

glue_ctx_t*
glue_init(int width, int height){
    int i;
    if(! yfrm_initialized){
        (void)yfrm_init();
        yfrm_initialized = 1;
    }
    if(! cwgl_ctx){
        cwgl_ctx = yfrm_cwgl_ctx_create(width, height, 0, 0);
    }
    if(! glue_ctx){
        glue_ctx = malloc(sizeof(glue_ctx_t));
        memset(glue_ctx, 0, sizeof(glue_ctx_t));
        glue_ctx->ctx = cwgl_ctx;
        glue_ctx->objs = 100;
        for(i=0; i!= glue_ctx->objs; i++){
            obj_setnone(glue_ctx, i);
        }
        glue_ctx->obj[0].type = OBJ_ZERO;
    }
}


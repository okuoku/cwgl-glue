#define CWGL_DECL_ENUMS

#include "yfrm.h"
#include "glue-priv.h"
#include "glue-ctx.h"

#include <stdio.h>

// FIXME: ONLY for gl4es now

/* 3.1 Errors */
// eglGetError

/* 3.2 Initialization */
// eglGetPlatformDisplay

CWGL_GLUE_EXPORT_EGL EGLDisplay KHRONOS_APIENTRY
eglGetDisplay(EGLNativeDisplayType display_id){
    /* Do nothing */
    return 0;
}

CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY
eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor){
    /* Do nothing */
    return 1;
}

// eglTerminate

/* 3.3 EGL Queries */
// eglQueryString

/* 3.4 Configuration Management */
/* 3.4.1 Querying Configurations */
// eglGetConfigs
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY
eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list,
                EGLConfig *configs, EGLint config_size,
                EGLint *num_config){
    /* Do nothing */
    return 1;
}

/* 3.4.3 Querying Configuration Attributes */
// eglGetConfigAttrib

/* 3.5 Rendering Surfaces */
/* 3.5.1 Creating On-Screen Rendering Surfaces */
// eglCreatePlatformWindowSurface
CWGL_GLUE_EXPORT_EGL EGLSurface KHRONOS_APIENTRY
eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
                       EGLNativeWindowType win,
                       const EGLint *attrib_list){
    /* Do nothing */
    return 0;
}

/* 3.5.2 Creating Off-Screen Rendering Surfaces */
// eglCreatePbufferSurface

/* 3.5.3 Binding Off-Screen Rendering Surfaces To Client Buffers */
// eglCreatePbufferFromClientBuffer

/* 3.5.4 Creating Native Pixmap Rendering Surfaces */
// eglCreatePlatformPixmapSurface
// eglCreatePixmapSurface

/* 3.5.5 Destroying Rendering Surfaces */
// eglDestroySurface

/* 3.5.6 Surface Attributes */
// eglSurfaceAttrib
// eglQuerySurface

/* 3.6 Rendering to Textures */
/* 3.6.1 Binding a Surface to a OpenGL ES Texture */
// eglBindTexImage
/* 3.6.2 Releasing a Surface from an OpenGL ES Texture */
// eglReleaseTexImage

/* 3.7 Rendering Contexts */
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY
eglBindAPI(EGLenum api){
    /* Do nothing */
    return 0;
}
// eglQueryAPI

static glue_ctx_t* my_ctx = 0;

/* 3.7.1 Creating Rendering Contexts */
CWGL_GLUE_EXPORT_EGL EGLContext  KHRONOS_APIENTRY
eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context,
                 const EGLint *attrib_list){
    int i;
    if(my_ctx){
        /* TENTATIVE: Disable critical states */
        for(i=0;i!=GLUE_MAX_VERTEX_ATTRIBUTES;i++){
            cwgl_disableVertexAttribArray(my_ctx->ctx, i);
        }
        cwgl_bindBuffer(my_ctx->ctx, ELEMENT_ARRAY_BUFFER, 0);
        cwgl_bindBuffer(my_ctx->ctx, ARRAY_BUFFER, 0);

        /* Setup rasterizer */
        cwgl_viewport(my_ctx->ctx, 0, 0, 1280, 720);
        cwgl_scissor(my_ctx->ctx, 0, 0, 1280, 720);
    }else{
        my_ctx = glue_init(1280, 720);
        yfrm_frame_begin0(my_ctx->ctx);
    }
    return 0;
}

/* 3.7.2 Destroying Rendering Contexts */
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY
eglDestroyContext(EGLDisplay dpy, EGLContext ctx){
    /* Do nothing */
    return 1;
}

/* 3.7.3 Binding Contexts and Drawables */
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY
eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read,
               EGLContext ctx){
    /* Do nothing */
    return 1;
}

/* 3.7.4 Context Queries */
// eglGetCurrentContext
// eglGetCurrentSurface
// eglGetCurrentDisplay
// eglQueryContext

/* 3.8 Synchronization Primitives */
// eglWaitClient
// eglWaitGL
// eglWaitNative
/* 3.8.1 Sync Objects */
// eglCreateSync
/* 3.8.1.3 Waiting For Sync Objects */
// eglClientWaitSync
// eglWaitSync
/* 3.8.1.4 Querying Sync Object Attributes */
// eglGetSyncAttrib
// eglDestroySync

/* 3.9 EGLImage Specification and Management */
// eglCreateImage

/* 3.9.1 Lifetime and Usage of EGLImages */
// eglDestroyImage

/* 3.10 Posting the Color Buffer */
/* 3.10.1 Posting to a Window */
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY
eglSwapBuffers(EGLDisplay dpy, EGLSurface surface){
    yfrm_frame_end0(my_ctx->ctx);
    yfrm_frame_begin0(my_ctx->ctx);
    return 1;
}

/* 3.10.2 Copying to a Native Pixmap */
// eglCopyBuffers
/* 3.10.3 Posting Semantics */
// eglSwapInterval

/* 3.11 Obtaining Function Pointers */
void* glue_lookup(const char* name);
CWGL_GLUE_EXPORT_EGL void* KHRONOS_APIENTRY
eglGetProcAddress(const char *procname){
    void* p;

    p = glue_lookup(procname);
    if(p){
        printf("proc: %s = %p\n", procname, p);
    }else{
        printf("proc: %s NOT FOUND\n", procname);
    }
    return p;
}

/* 3.12 Releasing Thread State */
// eglReleaseThread

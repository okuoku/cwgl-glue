#include "glue-priv.h"
#include "glue-funclist.h"
#include <string.h>

CWGL_GLUE_EXPORT_EGL EGLDisplay KHRONOS_APIENTRY eglGetDisplay(EGLNativeDisplayType display_id);
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
CWGL_GLUE_EXPORT_EGL EGLSurface KHRONOS_APIENTRY eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY eglBindAPI(EGLenum api);
CWGL_GLUE_EXPORT_EGL EGLContext  KHRONOS_APIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
CWGL_GLUE_EXPORT_EGL EGLBoolean KHRONOS_APIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
CWGL_GLUE_EXPORT_EGL void* KHRONOS_APIENTRY eglGetProcAddress(const char *procname);

void*
glue_lookup(const char* name){
#define ITR_CHECK(func) \
    if(!strcmp(name, #func)){ \
        return func; \
    }
FUNC_LIST(ITR_CHECK);
    return 0;
}



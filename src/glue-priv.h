#include <stdint.h>
//FIXME: Merge it with egl.h ??
typedef void* EGLDisplay;
typedef void* EGLConfig;
typedef void* EGLSurface;
typedef void* EGLContext;
typedef unsigned int EGLBoolean;
typedef int32_t EGLint;
typedef unsigned int EGLenum;

// Yuniframe specific
typedef uintptr_t EGLNativeDisplayType;
typedef uintptr_t EGLNativeWindowType;

#define CWGL_GLUE_EXPORT_EGL __declspec(dllexport)

//#include <EGL/egl.h>
#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>

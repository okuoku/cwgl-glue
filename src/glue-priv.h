#include <stdint.h>
//FIXME: Merge it with egl.h ??
typedef void* EGLConfig;
typedef void* EGLSurface;
typedef void* EGLContext;
typedef int32_t EGLint;

#define CWGL_GLUE_EXPORT_EGL __declspec(dllexport)

//#include <EGL/egl.h>
#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>

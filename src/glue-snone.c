#include "glue-priv.h"
#include "glue-ctx.h"
#include "cwgl.h"

GL_APICALL void GL_APIENTRY
glEnable(GLenum cap){
    cwgl_enable(glue_current_ctx(), (cwgl_enum_t) cap);
}

GL_APICALL void GL_APIENTRY
glDisable(GLenum cap){
    cwgl_disable(glue_current_ctx(), (cwgl_enum_t) cap);
}

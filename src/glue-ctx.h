#include "cwgl.h"

enum glue_obj_type_e {
    OBJ_ZERO,
    OBJ_FREE,
    OBJ_BUFFER,
    OBJ_SHADER,
    OBJ_PROGRAM,
    OBJ_TEXTURE,
    OBJ_FRAMEBUFFER,
    OBJ_RENDERBUFFER
};
typedef enum glue_obj_type_e glue_obj_type_t;

struct glue_obj_slot_s;
union glue_obj_ptr_u {
    struct glue_obj_slot_s* __invalid;
    cwgl_Buffer_t* buffer;
    cwgl_Shader_t* shader;
    cwgl_Program_t* program;
    cwgl_Texture_t* texture;
    cwgl_Framebuffer_t* framebuffer;
    cwgl_Renderbuffer_t* renderbuffer;
};
typedef union glue_obj_ptr_u glue_obj_ptr_t;

#define GLUE_MAX_UNIFORMS 32
struct glue_program_uniform_cache_s {
    unsigned int location;
    cwgl_UniformLocation_t* obj;
    char* name;
};
typedef struct glue_program_uniform_cache_s glue_program_uniform_cache_t;

struct glue_obj_slot_s {
    glue_obj_type_t type;
    glue_obj_ptr_t ptr;
    glue_program_uniform_cache_t uniform_cache[GLUE_MAX_UNIFORMS];
};
typedef struct glue_obj_slot_s glue_obj_slot_t;

#define GLUE_MAX_VERTEX_ATTRIBUTES 32
struct glue_va_state_s {
    int active;
    int use_client_array;
    uintptr_t client_array_ptr_start;
    uintptr_t client_array_ptr_size;
    cwgl_Buffer_t* proxy_buffer;
};
typedef struct glue_va_state_s glue_va_state_t;

struct glue_ctx_s {
    cwgl_ctx_t* ctx;
    size_t objs;
    glue_obj_slot_t* obj;
    glue_va_state_t va_state[GLUE_MAX_VERTEX_ATTRIBUTES];
};
typedef struct glue_ctx_s glue_ctx_t;

cwgl_ctx_t* glue_current_ctx(void);
glue_ctx_t* glue_init(int width, int height);

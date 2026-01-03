#pragma once 

#include "class_linker.h"
#include "object.h"
#include "opcodes.h"

#include <pthread.h>

typedef enum{
    EJOT_U8,
    EJOT_U16,
    EJOT_U32,
    EJOT_U64,
}jvm_opcode_argtype_t;

typedef struct{
    unsigned nargs;
    jvm_opcode_argtype_t* arg_types;

    jvm_error_t (*opcode_fn)(jvm_opcode_t opcode, jvm_frame_t* frame, classlinker_class_t* cur_class, unsigned nargs, void* args[]);
}jvm_opcode_executor_t;
extern __thread jvm_thread_t* jvm_current_thread;

void jvm_lock(jvm_instance_t* jvm);
void jvm_unlock(jvm_instance_t* jvm);

jvm_error_t jvm_bytecode_executor(jvm_frame_t* frame);
                            


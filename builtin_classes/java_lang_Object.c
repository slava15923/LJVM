#include "../jvm.h"
#include "../object.h"
#include "../class_linker.h"

static jvm_error_t object_clinit(jvm_frame_t* frame){
    return JVM_OK;
}
static jvm_error_t object_init(jvm_frame_t* frame){
    return JVM_OK;
}
static jvm_error_t object_finalize(jvm_frame_t* frame){
    return JVM_OK;
}

static jvm_error_t object_clone(jvm_frame_t* frame){
    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    objectmanager_object_t* argument = *(void**)frame->locals[1].value;

    uint16_t return_sp = frame->previous_frame->stack.sp++;
    frame->previous_frame->stack.stack[return_sp].type = EJVT_REFERENCE;
    *(void**)frame->previous_frame->stack.stack[return_sp].value = objectmanager_object_clone(frame, argument);

    return JVM_OK;
}

static uint32_t h31_hash(const char* s, size_t len)
{
    uint32_t h = 0;
    while (len) {
        h = 31 * h + *s++;
        --len;
    }
    return h;
}

static jvm_error_t object_equals(jvm_frame_t* frame){
    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    objectmanager_object_t* compare_to = *(void**)frame->locals[1].value;

    jvm_value_t return_value = {
        .type = EJVT_BOOL,
        .value = {0},
    };

    *(uint32_t*)frame->previous_frame->stack.stack[frame->previous_frame->stack.sp++].value = self == compare_to;

    return JVM_OK;
}

static jvm_error_t object_hashcode(jvm_frame_t* frame){
    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    jvm_value_t hashcode = {0};

    TODO("Proper hashing. (Count only non reference fields!)");

    hashcode.type = EJVT_INT;
    *(uint32_t*)hashcode.value = h31_hash((char*)self, self->size); //

    frame->previous_frame->stack.stack[frame->previous_frame->stack.sp++] = hashcode;

    return JVM_OK;
}

classlinker_normalclass_t java_lang_Object_info = {
    .methods_count = 6,
    .methods = (classlinker_method_t[]){
        {
            .name = "<clinit>",
            .raw_description = "()V",
            .fn = object_clinit,
            .flags = ACC_STATIC | ACC_NATIVE,
        },
        {
            .name = "<init>",
            .raw_description = "()V",
            .fn = object_init,
            .flags = ACC_NATIVE,
        },
        {
            .name = "clone",
            .raw_description = "(Ljava/lang/Object;)V",
            .frame_descriptor.arguments_count = 1,
            .fn = object_clone,
            .flags = ACC_NATIVE,
        },
        {
            .name = "finalize",
            .raw_description = "()V",
            .flags = ACC_NATIVE,
            .fn = object_finalize,
        },
        {
            .name = "equals",
            .raw_description = "(Ljava/lang/Object;)Z",
            .frame_descriptor.arguments_count = 1,
            .fn = object_equals,
            .flags = ACC_NATIVE,
        },
        {
            .name = "hashCode",
            .raw_description = "()I",
            .fn = object_hashcode,
            .flags = ACC_NATIVE,
        }

    },
};

extern classlinker_class_t java_lang_Clonable;
classlinker_class_t java_lang_Object = {
    .this_name = "java/lang/Object",
    .info = &java_lang_Object_info,
    .implements_count = 1,
    .implements = (classlinker_class_t*[]){&java_lang_Clonable},
};

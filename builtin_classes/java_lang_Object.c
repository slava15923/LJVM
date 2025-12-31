#include "../jvm.h"
#include "../jvm_internal.h"
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

static jvm_error_t object_equals(jvm_frame_t* frame){
    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    objectmanager_object_t* compare_to = *(void**)frame->locals[1].value;

    jvm_value_t return_value = {
        .type = EJVT_BOOL,
        .value = {0},
    };

    *(uint32_t*)return_value.value = self == compare_to;
    frame->previous_frame->stack.stack[frame->previous_frame->stack.sp++] = return_value;

    return JVM_OK;
}
static jvm_error_t object_hashcode(jvm_frame_t* frame){
    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    jvm_value_t hashcode = {0};

    hashcode.type = EJVT_INT;
    *(uint32_t*)hashcode.value = objectmanager_hash(self);

    frame->previous_frame->stack.stack[frame->previous_frame->stack.sp++] = hashcode;

    return JVM_OK;
}

static jvm_error_t object_toString(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    jvm_value_t* retvalue = &frame->previous_frame->stack.stack[frame->previous_frame->stack.sp++];

    retvalue->type = EJVT_REFERENCE;
    *(void**)retvalue->value = objectmanager_new_class_object(frame, classlinker_find_class(frame->jvm->linker, "java/lang/String"));
    objectmanager_object_t* string = *(void**)retvalue->value;

    FAIL_SET_JUMP(string,err,JVM_OOM,exit);

    char Cto_string[256] = {0};
    snprintf(Cto_string,sizeof(Cto_string) - 1,"%s@%zu\n",objectmanager_get_class_object_info(self)->class->this_name,(size_t)objectmanager_hash(self));

    classlinker_method_t* init = objectmanager_class_object_get_method(frame, objectmanager_get_class_object_info(string), "<init>", "(*)V");

    jvm_value_t args[] = {{EJVT_REFERENCE},{EJVT_NATIVEPTR}};
    *(void**)args[0].value = string;
    *(void**)args[1].value = Cto_string;

    err = jvm_invoke(frame->jvm,frame,init,2,args);

exit:
    return err;
}

classlinker_normalclass_t java_lang_Object_info = {
    .methods_count = 7,
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
        },
        {
            .name = "toString",
            .raw_description = "()Ljava/lang/String;",
            .fn = object_toString,
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

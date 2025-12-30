#include "../jvm.h"
#include "../jvm_internal.h"
#include "../object.h"
#include "../class_linker.h"

extern classlinker_class_t java_lang_Object;

static jvm_error_t throwable_clinit(jvm_frame_t* frame){
    return JVM_OK;
}

static jvm_error_t throwable_init(jvm_frame_t* frame){
    return JVM_OK;
}

static jvm_error_t throwable_init_msg(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    objectmanager_object_t* message = *(void**)frame->locals[1].value;

    FAIL_SET_JUMP(self,err,JVM_OPPARAM_INVALID,exit);
    FAIL_SET_JUMP(message,err,JVM_OPPARAM_INVALID,exit);

    FAIL_SET_JUMP(objectmanager_class_object_is_compatible_to(
        objectmanager_get_class_object_info(message), classlinker_find_class(frame->jvm->linker,"java/lang/String")),
                        err,JVM_OPPARAM_INVALID,exit);

    classlinker_field_t* field = objectmanager_class_object_get_field(frame, objectmanager_get_class_object_info(self), "exception_message");
    FAIL_SET_JUMP(field,err,JVM_NOTFOUND,exit);

    field->value.type = EJVT_REFERENCE;
    *(void**)field->value.value = objectmanager_object_clone(frame, message);

    FAIL_SET_JUMP(*(void**)field->value.value,err,JVM_OOM,exit);

exit:
    return err;
}

static jvm_error_t throwable_toString(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    FAIL_SET_JUMP(self,err,JVM_OPPARAM_INVALID,exit);

    jvm_value_t* return_value = &frame->previous_frame->stack.stack[frame->previous_frame->stack.sp++];

    TODO("Java string to C string conversion and proper print in throwable toString()");

    char exception_string[256] = {0};
    snprintf(exception_string,sizeof(exception_string) - 1,"%s",frame->method->class->this_name);

    return_value->type = EJVT_REFERENCE;
    *(void**)return_value->value = objectmanager_new_class_object(frame,classlinker_find_class(frame->jvm->linker,"java/lang/String")); 
    FAIL_SET_JUMP(*(void**)return_value->value, err, JVM_OOM,exit);

    jvm_value_t init_args[] = {{EJVT_REFERENCE},{EJVT_NATIVEPTR}};
    *(void**)init_args[0].value = *(void**)return_value->value;
    *(void**)init_args[1].value = exception_string;

    err = jvm_invoke(frame->jvm,frame,
                objectmanager_class_object_get_method(frame,objectmanager_get_class_object_info(*(void**)return_value->value),
                                "<init>","(*)V"),2,init_args);


exit:
    return err;
}

static jvm_error_t throwable_getMessage(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    classlinker_field_t* field = objectmanager_class_object_get_field(frame, objectmanager_get_class_object_info(self), "exception_message");
    FAIL_SET_JUMP(field,err,JVM_NOTFOUND,exit);

    jvm_value_t* return_value = &frame->previous_frame->stack.stack[frame->previous_frame->stack.sp++];

    *return_value = field->value;

exit:
    return err;
}

static jvm_error_t throwable_printStackTrace(jvm_frame_t* frame){

    fprintf(stderr,"Exception stack trace! Exception: %s\n",frame->method->class->this_name);

    for(jvm_frame_t* cur = frame; cur; cur = frame->previous_frame){
        fprintf(stderr,"from: %s/%s():%zd\n",cur->method->class->this_name,cur->method->name,(ssize_t)cur->pc);
    }

    return JVM_OK;
}

classlinker_normalclass_t java_lang_Throwable_info = {
    .methods_count = 6,
    .methods = (classlinker_method_t[]){
        {
            .name = "<clinit>",
            .raw_description = "()V",
            .fn = throwable_clinit,
            .flags = ACC_STATIC | ACC_NATIVE,
        },
        {
            .name = "<init>",
            .raw_description = "()V",
            .fn = throwable_init,
            .flags = ACC_NATIVE,
        },
        {
            .name = "<init>",
            .raw_description = "(Ljava/lang/String;)V",
            .fn = throwable_init_msg,
            .flags = ACC_NATIVE,
        },
        {
            .name = "toString",
            .raw_description = "()Ljava/lang/String;",
            .fn = throwable_toString,
            .flags = ACC_NATIVE,
        },
        {
            .name = "getMessage",
            .raw_description = "()Ljava/lang/String;",
            .fn = throwable_getMessage,
            .flags = ACC_NATIVE,
        },
        {
            .name = "printStackTrace",
            .raw_description = "()V",
            .fn = throwable_printStackTrace,
            .flags = ACC_NATIVE,
        }        
    },
    .fields_count = 1,
    .fields = (classlinker_field_t[]){
        {
            .name = "exception_message",
            .value.type = EJVT_REFERENCE,
        }
    }
};

classlinker_class_t java_lang_Throwable = {
    .this_name = "java/lang/Throwable",
    .generation = 1,
    .parent = &java_lang_Object,
    .info = &java_lang_Throwable_info,
};
#include "../jvm.h"
#include "../object.h"
#include "../class_linker.h"

#include <fcntl.h>
#include <unistd.h>

extern classlinker_class_t java_lang_Object;

static jvm_error_t outputstream_clinit(jvm_frame_t* frame){
    return JVM_OK;
}
static jvm_error_t outputstream_init(jvm_frame_t* frame){
    return JVM_OK;
}

static jvm_error_t outputstream_wfd_init(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    int32_t fd = *(int32_t*)frame->locals[1].value;

    classlinker_field_t* field_fd = objectmanager_class_object_get_field(frame,objectmanager_get_class_object_info(self), "fd");
    FAIL_SET_JUMP(field_fd,err,JVM_NOTFOUND,exit);

    field_fd->value.type = EJVT_INT;
    *(int32_t*)field_fd->value.value = fd; 

exit:
    return err;
}
static jvm_error_t outputstream_close(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;

    classlinker_field_t* field_fd = objectmanager_class_object_get_field(frame,objectmanager_get_class_object_info(self), "fd");
    FAIL_SET_JUMP(field_fd,err,JVM_NOTFOUND,exit);

    int32_t fd = *(int32_t*)field_fd->value.value;
    FAIL_SET_JUMP(fd >= 0,err,JVM_UNKNOWN,exit);

    close(fd);

    *(int32_t*)field_fd->value.value = 0;

exit:
    return err;
}
static jvm_error_t outputstream_flush(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;

    classlinker_field_t* field_fd = objectmanager_class_object_get_field(frame,objectmanager_get_class_object_info(self), "fd");
    FAIL_SET_JUMP(field_fd,err,JVM_NOTFOUND,exit);

    int32_t fd = *(int32_t*)field_fd->value.value;
    FAIL_SET_JUMP(fd >= 0,err,JVM_UNKNOWN,exit);

    fsync(fd);

exit:
    return err;
}

static jvm_error_t outputstream_writebytes(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;

    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    objectmanager_object_t* bytes = *(void**)frame->locals[1].value;

    objectmanager_array_object_t* bytes_array = objectmanager_get_array_object_info(bytes);
    uint8_t Cbytes[bytes_array->count];

    FAIL_SET_JUMP(bytes_array,err,JVM_UNKNOWN,exit);

    classlinker_field_t* field_fd = objectmanager_class_object_get_field(frame,objectmanager_get_class_object_info(self), "fd");
    FAIL_SET_JUMP(field_fd,err,JVM_NOTFOUND,exit);

    int32_t fd = *(int32_t*)field_fd->value.value;
    FAIL_SET_JUMP(fd >= 0,err,JVM_UNKNOWN,exit);

    for(unsigned i = 0; i < bytes_array->count; i++){
        Cbytes[i] = *(uint8_t*)bytes_array->elements[i].value;
    }
    write(fd,Cbytes,bytes_array->count);

exit:
    return err;
}

classlinker_normalclass_t java_io_OutputStream_info = {
    .methods_count = 6,
    .methods = (classlinker_method_t[]){
        {
            .name = "<clinit>",
            .raw_description = "()V",
            .fn = outputstream_clinit,
            .flags = ACC_STATIC | ACC_NATIVE,
        },
        {
            .name = "<init>",
            .raw_description = "()V",
            .fn = outputstream_init,
            .flags = ACC_NATIVE,
        },
        {
            .name = "<init>",
            .raw_description = "(I)V", //Secret custom FD output init :)
            .frame_descriptor.arguments_count = 1,
            .fn = outputstream_wfd_init,
            .flags = ACC_NATIVE,
        },
        {
            .name = "close",
            .raw_description = "()V", //Secret custom FD function!
            .fn = outputstream_close,
            .flags = ACC_NATIVE,
        },
        {
            .name = "flush",
            .raw_description = "()V", //Secret custom FD function!
            .fn = outputstream_close,
            .flags = ACC_NATIVE,
        },
        {
            .name = "write",
            .raw_description = "([B)V", //Secret custom FD function!
            .frame_descriptor.arguments_count = 1,
            .fn = outputstream_writebytes,
            .flags = ACC_NATIVE,
        },
    },
    .fields_count = 1,
    .fields = (classlinker_field_t[]){
        {
            .name = "fd",
            .value.type = EJVT_INT,
        },
    },
};

classlinker_class_t java_io_OutputStream = {
    .this_name = "java/io/OutputStream",
    .parent = &java_lang_Object,
    .generation = 1,
    .info = &java_io_OutputStream_info,
};
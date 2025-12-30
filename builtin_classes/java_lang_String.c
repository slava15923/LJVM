#include "../jvm.h"
#include "../object.h"
#include "../class_linker.h"

static jvm_error_t string_clinit(jvm_frame_t* frame){
    return JVM_OK;
}

static jvm_error_t string_native_utf8_init(jvm_frame_t* frame){
    jvm_error_t err = JVM_OK;
    
    objectmanager_object_t* self = *(void**)frame->locals[0].value;
    char* native_utf8 = *(void**)frame->locals[1].value;

    jvm_value_t UTF8_string = {EJVT_REFERENCE};
    
    objectmanager_object_t* UTF8_array = objectmanager_new_array_object(frame, EJVT_BYTE, strlen(native_utf8));
    FAIL_SET_JUMP(UTF8_array,err,JVM_OOM,exit);

    objectmanager_array_object_t* array_itself = objectmanager_get_array_object_info(UTF8_array);
    for(unsigned i = 0; i < array_itself->count; i++){
        *(char*)array_itself->elements[i].value = native_utf8[i];
    }

    classlinker_field_t* field = objectmanager_class_object_get_field(frame,objectmanager_get_class_object_info(self), "UTF8_string");
    FAIL_SET_JUMP(field,err,JVM_NOTFOUND,exit);

    field->value.type = EJVT_REFERENCE;
    *(void**)field->value.value = UTF8_array;

exit:
    return err;
}

classlinker_normalclass_t java_lang_String_info = {
    .methods_count = 2,
    .methods = (classlinker_method_t[]){
        {
            .name = "<clinit>",
            .raw_description = "()V",
            .fn = string_clinit,
            .flags = ACC_STATIC | ACC_NATIVE,
        },
        {
            .name = "<init>",
            .raw_description = "(*)V",
            .fn = string_native_utf8_init,
            .frame_descriptor.arguments_count = 1,
            .flags = ACC_NATIVE,
        }
    },
    .fields_count = 1,
    .fields = (classlinker_field_t[]){
        {
            .name = "UTF8_string",
            },
    }
};

extern classlinker_class_t java_lang_Object;
classlinker_class_t java_lang_String = {
    .this_name = "java/lang/String",
    .parent = &java_lang_Object,
    .info = &java_lang_String_info,
    .generation = 1,
};
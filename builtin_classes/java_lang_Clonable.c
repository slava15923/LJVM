#include "../jvm.h"
#include "../object.h"
#include "../class_linker.h"

static jvm_error_t clonable_clinit(jvm_frame_t* frame){
    return JVM_OK;
}

extern classlinker_class_t java_lang_Object;
classlinker_normalclass_t java_lang_Clonable_info = {
    .methods_count = 1,
    .methods = (classlinker_method_t[]){
        {
            .name = "<clinit>",
            .raw_description = "()V",
            .flags = ACC_NATIVE | ACC_STATIC,
            .fn = clonable_clinit,
        },
    },
};
classlinker_class_t java_lang_Clonable = {
    .this_name = "java/lang/Cloneable",
    .generation = 1,
    .parent = &java_lang_Object,
    .info = &java_lang_Clonable_info,
};
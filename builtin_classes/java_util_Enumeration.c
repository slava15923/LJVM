#include "../class_linker.h"

extern classlinker_class_t java_lang_Object;

classlinker_normalclass_t Enumeration_info = {
    .methods_count = 2,
    .methods = (classlinker_method_t[]){
        {
            .name = "hasMoreElements",
            .raw_description = "()Z",
            .flags = ACC_NATIVE,
        },
        {
            .name = "nextElement",
            .raw_description = "()Ljava/lang/Object;",
            .flags = ACC_NATIVE,
        }
    },
};

classlinker_class_t java_util_Enumeration = {
    .this_name = "java/util/Enumeration",
    .parent = &java_lang_Object,
    .generation = 1,
    .info = &Enumeration_info,
};
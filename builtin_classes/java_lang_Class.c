#include "../jvm.h"
#include "../object.h"
#include "../class_linker.h"

extern classlinker_class_t java_lang_Object;

classlinker_normalclass_t java_lang_Class_info = {
};

classlinker_class_t java_lang_Class = {
    .this_name = "java/lang/Class",
    .info = &java_lang_Class_info,
    .parent = &java_lang_Object,
    .generation = 1,
};
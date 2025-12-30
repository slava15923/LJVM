#include "../jvm.h"
#include "../class_linker.h"

extern classlinker_class_t java_lang_RuntimeException;

classlinker_normalclass_t java_lang_NullPointerException_info = {
};

classlinker_class_t java_lang_NullPointerException = {
    .this_name = "java/lang/NullPointerException",
    .parent = &java_lang_RuntimeException,
    .generation = 4,
    .info = &java_lang_NullPointerException_info, 
};
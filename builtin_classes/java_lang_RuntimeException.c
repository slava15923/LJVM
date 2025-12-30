#include "../jvm.h"
#include "../class_linker.h"

extern classlinker_class_t java_lang_Exception;

classlinker_normalclass_t java_lang_RuntimeException_info = {
};

classlinker_class_t java_lang_RuntimeException = {
    .this_name = "java/lang/RuntimeException",
    .parent = &java_lang_Exception,
    .generation = 3,
    .info = &java_lang_RuntimeException_info, 
};
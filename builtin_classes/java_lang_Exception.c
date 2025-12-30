#include "../jvm.h"
#include "../class_linker.h"

extern classlinker_class_t java_lang_Throwable;

classlinker_normalclass_t java_lang_Exception_info = {

};

classlinker_class_t java_lang_Exception = {
    .this_name = "java/lang/Exception",
    .parent = &java_lang_Throwable,
    .generation = 2,
    .info = &java_lang_Exception_info,
};
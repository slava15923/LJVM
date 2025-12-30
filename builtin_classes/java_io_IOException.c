#include "../jvm.h"
#include "../class_linker.h"

extern classlinker_class_t java_lang_Exception;

classlinker_normalclass_t java_io_IOException_info = {
};

classlinker_class_t java_io_IOException = {
    .this_name = "java/io/IOException",
    .parent = &java_lang_Exception,
    .generation = 3,
    .info = &java_io_IOException_info,
};
#include "object.h"
#include "class_linker.h"
#include "class_loader.h"
#include "jvm.h"

jvm_error_t objectmanager_init_heap(jvm_frame_t* frame, uint32_t heap_size){
    INIT_LIST_HEAD(&frame->jvm->heap.object_list);

    return JVM_OK;
}

objectmanager_object_t* objectmanager_new_class_object(jvm_frame_t* frame,
                                                       classlinker_class_t* class){

    TODO("Implement GC based memory manager! Using malloc() stub for now");

    objectmanager_object_t* new = malloc(sizeof(*new));
    assert(new);

    INIT_LIST_HEAD(&new->list);
    list_add(&new->list,&frame->jvm->heap.object_list);

    new->type = EJOMOT_CLASS;
    new->data = malloc(sizeof(objectmanager_class_object_t));
    assert(new->data);

    objectmanager_class_object_t* class_object = new->data;
    class_object->class = class;
    class_object->fields = calloc(class->generation + 1, sizeof(*class_object->fields));

    for(classlinker_class_t* cur = class; cur; cur = cur->parent){
        classlinker_normalclass_t* class_info = cur->info;
        class_object->fields[cur->generation] = calloc(class_info->fields_count,
                                            sizeof(*class_object->fields[0]));

        for(unsigned i = 0; i < class_info->fields_count; i++){
            class_object->fields[cur->generation][i] = class_info->fields[i];
            class_object->fields[cur->generation][i].name = \
                        strdup(class_object->fields[cur->generation][i].name);
        }
    }

    new->jvm = frame->jvm;

    return new;
}

objectmanager_object_t* objectmanager_new_array_object(jvm_frame_t* frame, jvm_value_type_t type,
                                                       size_t size){
    TODO("GC based memory manager for arrays. Using malloc() for now");
    objectmanager_object_t* new = malloc(sizeof(*new));

    INIT_LIST_HEAD(&new->list);
    list_add(&new->list,&frame->jvm->heap.object_list);

    new->type = EJOMOT_ARRAY;
    new->data = calloc(1,sizeof(objectmanager_array_object_t));

    objectmanager_array_object_t* array_object = new->data;
    objectmanager_object_t* JLObject = objectmanager_new_class_object(frame, classlinker_find_class(frame->jvm->linker,"java/lang/Object"));
    assert(JLObject);

    array_object->JLObject = JLObject;
    array_object->count = size;
    array_object->elements = calloc(size,sizeof(*array_object->elements));

    for(unsigned i = 0; i < size; i++){
        array_object->elements[i].type = type;
        memset(array_object->elements[i].value,0,sizeof(array_object->elements[i].value));
    }

    new->jvm = frame->jvm;

    return new;
}

objectmanager_class_object_t* objectmanager_get_class_object_info(objectmanager_object_t* object){
    if(object->type == EJOMOT_CLASS){
        return object->data;
    }
    return ((objectmanager_array_object_t*)object->data)->JLObject->data;
    
}

objectmanager_array_object_t* objectmanager_get_array_object_info(objectmanager_object_t* object){
    if(object->type == EJOMOT_ARRAY){
        return object->data;
    }
    return NULL;
}

classlinker_field_t* objectmanager_class_object_get_field(jvm_frame_t* frame, objectmanager_class_object_t* class_object,
                                                          char* name){
    classlinker_field_t* found = NULL;
    for(classlinker_class_t* cur = class_object->class; cur; cur = cur->parent){
        classlinker_normalclass_t* class_info = cur->info;
        for(unsigned i = 0; i < class_info->fields_count; i++){            
            if(strcmp(class_object->fields[cur->generation][i].name, name) == 0){

                if((class_object->fields[cur->generation][i].flags & ACC_PRIVATE) == ACC_PRIVATE){
                    if(cur == frame->method->class)
                        return &class_object->fields[cur->generation][i];
                    else continue;
                } else return &class_object->fields[cur->generation][i];
            }
        }
    }
    return NULL;
}

classlinker_method_t* objectmanager_class_object_get_method(jvm_frame_t* frame, objectmanager_class_object_t* object,
                                                            char* name, char* description){

    return classlinker_find_method(frame, object->class,name,description);
}

objectmanager_object_t* objectmanager_object_clone(jvm_frame_t* frame, objectmanager_object_t* object){
    objectmanager_object_t* new_object = NULL;
    switch(object->type){
        case EJOMOT_CLASS:{
            objectmanager_class_object_t* old_class_object = object->data;
            new_object = objectmanager_new_class_object(frame,old_class_object->class);
            if(new_object == NULL){
                TODO("OOM exception!");
                assert(new_object);
            }

            objectmanager_class_object_t* new_class_object = new_object->data;
            for(classlinker_class_t* cur = old_class_object->class; cur; cur = cur->parent){
                classlinker_normalclass_t* class_info = cur->info;
                memcpy(new_class_object->fields[cur->generation],old_class_object->fields[cur->generation],class_info->fields_count * sizeof(old_class_object->fields[0][0]));
            }
        }
        break;

        case EJOMOT_ARRAY:{
            objectmanager_array_object_t* old_array_object = object->data;
            new_object = objectmanager_new_array_object(frame,old_array_object->elements[0].type, old_array_object->count);
            if(new_object == NULL){
                TODO("OOM exception!");
                assert(new_object);
            }

            objectmanager_array_object_t* new_array_object = new_object->data;
            memcpy(new_array_object->elements,old_array_object->elements,sizeof(old_array_object->elements[0]) * old_array_object->count);
        }
        break;
    }
    return new_object;
}

bool objectmanager_class_object_is_compatible_to(objectmanager_class_object_t* class_object, classlinker_class_t* class){
    return classlinker_is_classes_compatible(class_object->class,class);
}
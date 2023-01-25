#include "Loader.h"
#include "Debug.h"
#ifndef __APPLE__
#include <link.h>
#endif
#include <dlfcn.h>
#include <stdlib.h>

namespace iris {
namespace rt {

Loader::Loader() {
  handle_ = NULL;
  handle_ext_ = NULL;
  iris_get_kernel_names = NULL;
  iris_set_kernel_ptr_with_obj = NULL;
}

Loader::~Loader() {
  if (handle_) if (dlclose(handle_) != 0) _error("%s", dlerror());
  if (handle_ext_) if (dlclose(handle_ext_) != 0) _error("%s", dlerror());
}

int Loader::Load() {
  if (!library()) return IRIS_SUCCESS;
  if (LoadHandle() != IRIS_SUCCESS) return IRIS_ERROR;
  return LoadFunctions();
}

int Loader::LoadExtHandle(const char *libname) {
  handle_ext_ = dlopen(libname, RTLD_GLOBAL | RTLD_NOW);
  if (handle_ext_) {
#if 0
    struct link_map *map;
    dlinfo(handle_ext_, RTLD_DI_LINKMAP, &map);
    _trace("shared library path[%s]", realpath(map->l_name, NULL));
#endif
  } else {
    _trace("%s", dlerror());
    return IRIS_ERROR;
  }
  return IRIS_SUCCESS;
}

int Loader::LoadHandle() {
  if (library_precheck() && dlsym(RTLD_DEFAULT, library_precheck())) {
    handle_ = RTLD_DEFAULT;
    return IRIS_SUCCESS;
  }
  handle_ = dlopen(library(), RTLD_GLOBAL | RTLD_NOW);
  if (handle_) {
#if 0
    struct link_map *map;
    dlinfo(handle_, RTLD_DI_LINKMAP, &map);
    _trace("shared library path[%s]", realpath(map->l_name, NULL));
#endif
  } else {
    _trace("%s", dlerror());
    return IRIS_ERROR;
  }
  return IRIS_SUCCESS;
}

int Loader::LoadFunctions() {
    LOADFUNC_OPTIONAL(iris_get_kernel_names);
    LOADFUNC_OPTIONAL(iris_set_kernel_ptr_with_obj);
    return IRIS_SUCCESS;
}

bool Loader::IsFunctionExists(const char *kernel_name) {
    __iris_kernel_ptr kptr;
    kptr = (__iris_kernel_ptr) dlsym(handle_, kernel_name);
    if (kptr == NULL) return false;
    return true;
}

int Loader::SetKernelPtr(void *obj, char *kernel_name)
{
    if (iris_set_kernel_ptr_with_obj) {
        __iris_kernel_ptr kptr;
        kptr = (__iris_kernel_ptr) dlsym(handle_, kernel_name);
        iris_set_kernel_ptr_with_obj(obj, kptr);
        if (kptr != NULL) return IRIS_SUCCESS;
    }
    return IRIS_ERROR;
}

} /* namespace rt */
} /* namespace iris */


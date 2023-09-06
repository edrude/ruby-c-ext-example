#include "ruby.h"
#include <dlfcn.h>

VALUE Example = Qnil;

// Wrapper function to call the 'product' function from the shared library
VALUE method_product(VALUE self, VALUE a, VALUE b) {
    void *handle;
    int (*product_func)(int, int);
    int result;

    handle = dlopen("./example.so", RTLD_LAZY);
    if (!handle) {
        rb_raise(rb_eRuntimeError, "Could not open example.so: %s", dlerror());
        return Qnil;
    }

    *(void **)(&product_func) = dlsym(handle, "product");
    if (!product_func) {
        rb_raise(rb_eRuntimeError, "Could not find 'product' function: %s", dlerror());
        dlclose(handle);
        return Qnil;
    }

    result = product_func(NUM2INT(a), NUM2INT(b));

    dlclose(handle);

    return INT2NUM(result);
}

void Init_example() {
    Example = rb_define_module("Example");
    rb_define_singleton_method(Example, "product", method_product, 2);
}


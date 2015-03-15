#include <str>
#include <auto_str>
#include <option>

static
void
process_str_err(misc_str_error err) {
    switch (err) {
        case null_ptr: printf("null_ptr\n"); break;
        case out_of_bounds: printf("out_of_bounds\n"); break;
        case max_length: printf("max_length\n"); break;
    }
}

static void
test_len() {
    $str_result(size_t) res = Str.len("hello world");

    printf("len: ");
    if (res.is == Err) {
        process_str_err(res.err.val);
    } else {
        printf("%zu\n", res.ok.val);
    }
}

static void
test_get() {
    $str_result(char) res;

    // Should succeed
    res = Str.get("hello world", 3);
    printf("get: ");
    if (res.is == Err) {
        process_str_err(res.err.val);
    } else {
        printf("%c\n", res.ok.val);
    }

    // SHould fail
    res = Str.get("hello world", 77);
    printf("get: ");
    if (res.is == Err) {
        process_str_err(res.err.val);
    } else {
        printf("%c\n", res.ok.val);
    }
}

static void
test_make() {
    $option(str) s = Str.make(10, '*');
    switch (s.is) {
        case Some: printf("make: %s\n", s.some.val); break;
        case None: printf("make: None\n"); break;
    }
    Str.drop(s.some.val);
}

static void
test_copy() {
    $option(str) s = Str.copy("hello world");
    switch (s.is) {
        case Some: printf("s_copy is %s\n", s.some.val); break;
        case None: printf("s is None\n"); break;
    }
    Str.drop(s.some.val);
}

static char
init_fn(int i) {
    return (char)(i + 42);
}

static void
test_init() {
    $option(str) s = Str.init(20, &init_fn);
    switch (s.is) {
        case Some: printf("s_init is %s\n", s.some.val); break;
        case None: printf("s is None\n"); break;
    }
    Str.drop(s.some.val);
}

static char
map_fn(char c) {
    return c + 1;
}

static void
test_map() {
    $option(str) s = Str.map(&map_fn, "abcdefg");
    switch (s.is) {
        case Some: printf("s_map is %s\n", s.some.val); break;
        case None: printf("s is None\n"); break;
    }
    Str.drop(s.some.val);
}

static char
mapi_fn(int i, char c) {
    return c + 1 + i;
}

static void
test_mapi() {
    $option(str) s = Str.mapi(&mapi_fn, "abcdefg");
    switch (s.is) {
        case Some: printf("s_map is %s\n", s.some.val); break;
        case None: printf("s is None\n"); break;
    }
    Str.drop(s.some.val);
}

static void
test_fill() {
    $option(str) s = Str.make(10, '*');
    Str.fill(s.some.val, 2, 3, '.');
    printf("fill: %s\n", s.some.val);
    Str.drop(s.some.val);
}

void test_func_1(char c) {
    printf("%c", c);
}

static void
test_iter() {
    $option(str) s = Str.make(10, '*');
    printf("iter: ");
    Str.iter(s.some.val, &test_func_1);
    printf("\n");
    Str.drop(s.some.val);
}

void test_func_2(size_t i, char c) {
    printf("[%zu:%c]", i, c);
}

static void
test_iteri() {
    $option(str) s = Str.make(10, '*');
    printf("iteri: ");
    Str.iteri(s.some.val, &test_func_2);
    printf("\n");
    Str.drop(s.some.val);
}

static void
test_index() {
    $option(str) s = Str.make(10, '*');
    $option(size_t) pos = Str.index(s.some.val, '0');
    switch (pos.is) {
        case Some: printf("index: %zu\n", pos.some.val); break;
        case None: printf("index: None\n"); break;
    }
    Str.drop(s.some.val);
}

static void
test_rindex() {
    $option(str) s = Str.make(10, '*');
    $option(size_t) pos = Str.rindex(s.some.val, '*');
    switch (pos.is) {
        case Some: printf("rindex: %zu\n", pos.some.val); break;
        case None: printf("rindex: None\n"); break;
    }
    Str.drop(s.some.val);
}

static void
test_auto_str_make() {
    auto_str s = Str.make(10, '*').some.val;
    if (s == nullptr) {
        printf("a_s is nullptr\n");
    }
}

void
test_str() {
    test_len();
    test_get();
    test_make();
    test_copy();
    test_init();
    test_map();
    test_mapi();
    test_fill();
    test_iter();
    test_iteri();
    test_index();
    test_rindex();

    test_auto_str_make();
}

int
main() {
    test_str();

    return 0;
}
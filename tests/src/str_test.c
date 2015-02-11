#include <str>
#include <auto_str>
#include <option>

static void
test_len() {
    printf("Str.len('hello world'): %zu\n", Str.len("hello world"));
}

static void
test_get() {
    $option(char) t = Str.get("hello world", 3);
    switch (t.is) {
        case Some: printf("t is %c\n", t.some.val); break;
        case None: printf("t is None\n"); break;
    }

    $option(char) u = Str.get("hello world", 77);
    switch (u.is) {
        case Some: printf("u is %d\n", u.some.val); break;
        case None: printf("u is None\n"); break;
    }
}

static void
test_make() {
    $option(str) s = Str.make(10, '*');
    switch (s.is) {
        case Some: printf("s is %s\n", s.some.val); break;
        case None: printf("s is None\n"); break;
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

    test_auto_str_make();
}

int
main() {
    test_str();

    return 0;
}
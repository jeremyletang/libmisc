#include <str>
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
        case None: printf("t is None\n");
    }

    $option(char) u = Str.get("hello world", 77);
    switch (u.is) {
        case Some: printf("u is %d\n", u.some.val); break;
        case None: printf("u is None\n");
    }
}

void
test_str() {
    test_len();
    test_get();
}

#import <str>
#import <option>

void
test_println() {
    Str.println("hello world");
}

void
test_len() {
    printf("Str.len('hello world'): %u\n", Str.len("hello world"));
}

void
test_get() {
    char_option t = Str.get("hello world", 3);
    switch (t.is) {
        case Some: printf("t is %c\n", t.some.val); break;
        case None: printf("t is None\n");
    }

    char_option u = Str.get("hello world", 77);
    switch (u.is) {
        case Some: printf("u is %d\n", u.some.val); break;
        case None: printf("u is None\n");
    }
}

int
main() {
    test_println();
    test_len();
    test_get();
    return 0;
}

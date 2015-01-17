#import <str>

int
println(char* str) {
    return printf("%s\n", str);
}

int
print(char* str) {
    return printf("%s\n", str);
}

unsigned
len(char* str) {
    char *str_ = str;
    while (*str_ != 0) { str_ += 1; }
    return str_ - str;
}

char_option
get(char* str, unsigned pos) {
    char_option res;

    if (len(str) < pos) {
        res.is = None;
    } else {
        res.some.is = Some;
        res.some.val = str[pos];
    }

    return res;
}

const str_mod Str = {
    .println = println,
    .print = print,
    .len = len,
    .get = get
};

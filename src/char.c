#import <char>
#import <option>

int
code(char c) {
    return (int)c;
}

char_option
chr(int c) {
    char_option res;

    if (c < 0 || c > 127) {
        res.is = None;
    } else {
        res.some.is = Some;
        res.some.val = (char)c;
    }

    return res;
}

char*
escaped(char c) {
    return 0;
}

char
lowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        c += 32;
    }

    return c;
}

char
uppercase(char c) {
    if (c >= 'a' && c <= 'z') {
        c -= 32;
    }

    return c;
}

int
compare(char c1, char c2) {
    int res = 0;

    if (c1 < c2) { res = -1; }
    else if (c1 > c2) { res = 1; }

    return res;
}

bool
is_alpha(char c) {
    if (is_uppercase(c) || is_lowercase(c)) {
        return true;
    }
    return false;
}

bool
is_num(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

bool
is_alphanum(char c) {
    if (is_num(c) || is_alpha(c)) {
        return true;
    }
    return false;
}

bool
is_uppercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

bool
is_lowercase(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    return false;
}

const char_mod Char = {
    .code = code,
    .chr = chr,
    .escaped = escaped,
    .is_alpha = is_alpha,
    .is_num = is_num,
    .is_alphanum = is_alphanum,
    .is_uppercase = is_uppercase,
    .is_lowercase = is_lowercase,
    .lowercase = lowercase,
    .uppercase = uppercase,
    .compare = compare
};

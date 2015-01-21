// The MIT License (MIT)
//
// Copyright (c) 2015 Jeremy Letang
// Copyright (c) 2015 Valentin Trinque
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <char>
#include <option>

bool is_uppercase(char c);
bool is_lowercase(char c);

int
code(char c) {
    return (int)c;
}

option(char)
chr(int c) {
    option(char) res;

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


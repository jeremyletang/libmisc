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

#include <str>

#include <stdlib.h>
#include <stdio.h>

// private function

void
priv_iter_len(str s, char (*f)(char), size_t len) {
    while (len != 0) {
        s[len] = f(s[len]);
        len -= 1;
    }
}

void
priv_iter(str s, char (*f)(char)) {
    str s_it = s;

    while (s_it != 0) {
        *s_it = f(*s_it);
        s_it++;
    }
}

// api function

int
println(str s) {
    return printf("%s\n", s);
}

size_t
len(const str s) {
    str it_s = s;

    while (*it_s != 0) { it_s += 1; }
    return it_s - s;
}


$option(char)
get(str s, unsigned pos) {
    $option(char) res;

    if (len(s) < pos) {
        res.is = None;
    } else {
        res.some.is = Some;
        res.some.val = s[pos];
    }
    return res;
}

$option(str)
create(size_t size) {
    $option(str) res;
    str s = malloc(sizeof(char) * (size + 1));

    if (s == nullptr) {
        res.is = None;
    } else {
        s[size] = 0;
        res.some.is = Some;
        res.some.val = s;
    }

    return res;
}

// str
// create_unsafe(size_t size) {
//     return malloc(sizeof(char) * (size + 1));
// }

$option(str)
make(size_t size, char c) {
    $option(str) res = create(size);

    switch (res.is) {
        case Some: {
            str s_it = res.some.val;
            while (s_it != res.some.val + size) {
                *s_it = c;
                s_it += 1;
            }
            break;
        }
        case None: break;
    }

    return res;
}

void
drop(str s) {
    free(s);
    s = nullptr;
}

const str_mod Str = {
    .len = len,
    .get = get,
    .create = create,
    .make = make,
    .drop = drop
};


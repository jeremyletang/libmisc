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

void
priv_iter_len(str s, char (*f)(char), size_t len) {
    for (uint i = 0; i < len; i++) {
        s[i] = f(s[i]);
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
get(str s, size_t pos) {
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

$option(str)
copy(str s) {
    size_t size = len(s);
    $option(str) s_copy = create(size);

    switch (s_copy.is) {
        case Some: {
            str s_copy_it = s_copy.some.val;
            str s_it = s;
            while (*s_it != 0) {
                *s_copy_it = *s_it;
                s_it += 1;
                s_copy_it += 1;
            }
            break;
        }
        case None: break;
    }

    return s_copy;
}

$option(str)
init(size_t size, char(*fn)(int)) {
    $option(str) s_init = create(size);

    switch (s_init.is) {
        case Some: {
            uint it = 0;
            while (it != size) {
                s_init.some.val[it] = fn(it);
                it += 1;
            }
            break;
        }
        case None: break;
    }

    return s_init;
}

$option(str)
map(char(*fn)(char), str s) {
    size_t size = len(s);
    $option(str) s_map = create(size);

    switch (s_map.is) {
        case Some: {
            uint it = 0;
            while (it != size) {
                s_map.some.val[it] = fn(s[it]);
                it += 1;
            }
            break;
        }
        case None: break;
    }

    return s_map;
}

$option(str)
mapi(char(*fn)(int, char), str s) {
    size_t size = len(s);
    $option(str) s_map = create(size);

    switch (s_map.is) {
        case Some: {
            uint it = 0;
            while (it != size) {
                s_map.some.val[it] = fn(it, s[it]);
                it += 1;
            }
            break;
        }
        case None: break;
    }

    return s_map;
}

bool
fill(str s, size_t start, size_t l, char c) {
    size_t size = len(s);
    if (start >= size || l + start >= size) {
        return false;
    }
    for (size_t i = start; i < start + l; i++) {
        s[i] = c;
    }
    return true;
}

void
iter(str s, void (*f)(char)) {
    size_t size = len(s);
    for (size_t i = 0; i < size; i++) {
        f(s[i]);
    }
}

void
iteri(str s, void (*f)(size_t, char)) {
    size_t size = len(s);
    for (size_t i = 0; i < size; i++) {
        f(i, s[i]);
    }
}

$option(size_t)
index_from(const str s, size_t index, char c) {
    $option(size_t) res;
    res.is = None;
    size_t size = len(s);
    size_t i = index + 1;
    while (i < size && res.is == None) {
        if (s[i] == c) {
            res.some.is = Some;
            res.some.val = i;
        }
        i += 1;
    }
    return res;
}

$option(size_t)
rindex_from(const str s, size_t rindex, char c) {
    $option(size_t) res;
    res.is = None;
    size_t size = len(s);
    size_t ri = rindex - 1;
    if (rindex > 0 && ri < size) {
        while (ri != 0 && res.is == None) {
            if (s[ri] == c) {
                res.some.is = Some;
                res.some.val = ri;
            }
            ri -= 1;
        }
    }
    return res;
}

$option(size_t)
index_(const str s, char c) {
    return index_from(s, -1, c);
}

$option(size_t)
rindex_(const str s, char c) {
    return rindex_from(s, len(s), c);
}

const str_mod Str = {
    .len = len,
    .get = get,
    .create = create,
    .make = make,
    .drop = drop,
    .copy = copy,
    .init = init,
    .map = map,
    .mapi = mapi,
    .fill = fill,
    .iter = iter,
    .iteri = iteri,
    .index_from = index_from,
    .rindex_from = rindex_from,
    .index = index_,
    .rindex = rindex_
};


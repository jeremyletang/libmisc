// <libmisc> -*- C -*-
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

#include <io>

static io_stream
cin() {
    io_stream ios = {
        .type = console_stream,
        .stream = stdin,
        .socket_fd = -1
    };
    return ios;
}

static io_stream
cout() {
    io_stream ios = {
        .type = console_stream,
        .stream = stdout,
        .socket_fd = -1
    };
    return ios;
}

static io_stream
cerr() {
    io_stream ios = {
        .type = console_stream,
        .stream = stderr,
        .socket_fd = -1
    };
    return ios;
}

static io_stream
file(const str path, const str rights) {
    io_stream ios = {
        .type = file_stream,
        .stream = fopen(path, rights),
        .socket_fd = -1
    };
    return ios;
}

static int
close(io_stream ios) {
    int res = 0;

    switch (ios.type) {
        case file_stream:
        case console_stream: res = fclose(ios.stream); break;
        case socket_stream: break; // todo
        default: break;
    }

    return res;
}

const io_mod IO = {
    .cin = cin,
    .cout = cout,
    .cerr = cerr,
    .file = file,
    .close = close
};

#!/bin/sh

LD_PRELOAD='lib/libtbbmalloc_proxy.so.2 lib/libtbbmalloc.so.2' LD_LIBRARY_PATH=lib ./FamousServer "$@"


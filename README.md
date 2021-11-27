## ll.c: A simple implementation of reversing a singly linked list

## Building and Testing

To build the code, all you'll need is `make` and `gcc`. To build and test from scratch, simply type `make test`.

All tests within `test.c` will be run. This file has a simple main function and is linked with the ll.c source at build time.

There's also a simple GitHub Action workflow file included, which will automatically check out and build the code by running `make test`.

## Modifying

To add new functionality, simply edit ll.h with your prototypes, and ll.c with your implementations. Then, to add tests, write test code in `test.c` and execute it with `make test`

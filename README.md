# libasm — libc functions in x86-64 assembly

A small static library that reimplements six standard C functions in **x86-64 assembly** (NASM, Intel syntax), as part of the 42 curriculum. Each function follows the **System V AMD64 calling convention**, so it can be called from C like the original.

| Function | Prototype | Notes |
|---|---|---|
| `ft_strlen` | `size_t ft_strlen(const char *s)` | |
| `ft_strcpy` | `char *ft_strcpy(char *dst, const char *src)` | returns `dst` |
| `ft_strcmp` | `int ft_strcmp(const char *s1, const char *s2)` | compares as unsigned bytes |
| `ft_write` | `ssize_t ft_write(int fd, const void *buf, size_t count)` | direct `write` syscall, sets `errno` on failure |
| `ft_read` | `ssize_t ft_read(int fd, void *buf, size_t count)` | direct `read` syscall, sets `errno` on failure |
| `ft_strdup` | `char *ft_strdup(const char *s)` | calls `malloc`, reuses `ft_strlen` and `ft_strcpy` |

## Build & test

Requires `nasm` and `gcc` on Linux x86-64.

```bash
make          # builds libasm.a and the test program, then runs the tests
make test     # only builds test.out
make fclean   # removes everything that was built
```

The test program (`tests.c`) checks each function against the libc version with `assert`, including edge cases: empty strings, invalid file descriptors (`EBADF`), `NULL` buffers (`EFAULT`), zero-byte reads and reading from a file. One test reads from standard input, so it asks you to type a line.

Use the library in your own code:

```c
#include <stdio.h>

size_t ft_strlen(const char *s);

int main(void)
{
    printf("%zu\n", ft_strlen("hello"));
    return 0;
}
```

```bash
gcc main.c -L. -lasm -o main
```

## Implementation notes

- **System calls**: `ft_write` and `ft_read` put the syscall number in `rax` and use the `syscall` instruction directly. On failure, Linux returns `-errno` in `rax`. The code negates it, stores it through `__errno_location()` and returns `-1`, exactly like libc.
- **Calling C from assembly**: `ft_strdup` and the error paths call `malloc` and `__errno_location` through the PLT (`wrt ..plt`), so the library links into position-independent executables.
- **Stack alignment**: `ft_strdup` saves its argument with a `push` before calling other functions, which also keeps the stack 16-byte aligned as the ABI requires.

## Project structure

```
.
├── Makefile
├── ft_strlen.s  ft_strcpy.s  ft_strcmp.s
├── ft_write.s   ft_read.s    ft_strdup.s
└── tests.c      # test suite
```

## Tech

x86-64 assembly · NASM · System V AMD64 ABI · Linux syscalls

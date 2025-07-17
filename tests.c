#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

extern size_t ft_strlen(const char *str);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);

void test_strlen() {
    assert(ft_strlen("") == strlen(""));
    assert(ft_strlen("a") == strlen("a"));
    assert(ft_strlen("Hello") == strlen("Hello"));
    assert(ft_strlen("Lorem ipsum dolor sit amet.") == strlen("Lorem ipsum dolor sit amet."));
    printf("[PASS] ft_strlen\n");
}

void test_strcpy() {
    char dest1[100];
    char dest2[100];
    const char *src = "Hello Assembly!";

    char *ret = ft_strcpy(dest1, src);
    strcpy(dest2, src);

    assert(strcmp(dest1, dest2) == 0);
    assert(ret == dest1);

    ft_strcpy(dest1, "");
    assert(strcmp(dest1, "") == 0);

    printf("[PASS] ft_strcpy\n");
}

void test_strcmp() {
    assert(ft_strcmp("hello", "hello") == 0);
    assert(ft_strcmp("", "") == 0);
    assert(ft_strcmp("a", "") > 0);
    assert(ft_strcmp("", "a") < 0);
    assert(ft_strcmp("abc", "abd") < 0);
    assert(ft_strcmp("abcd", "abc") > 0);
    assert(ft_strcmp("abc", "Abc") > 0);
    assert(ft_strcmp("ABC", "abc") < 0);
    assert(ft_strcmp("abc\0xyz", "abc") == 0);
    assert(ft_strcmp("helloo", "hello") > 0);
    assert(ft_strcmp("hello", "helloo") < 0);

    printf("[PASS] ft_strcmp\n");
}

void test_stdout_write() {
    ssize_t ret = ft_write(1, "Hello, world!\n", 14);
    assert(ret == 14);
    printf("[PASS] STDOUT write\n");
}

void test_invalid_fd_write() {
    errno = 0;
    ssize_t ret = ft_write(-1, "fail", 4);
    assert(ret == -1);
    assert(errno == EBADF);
    printf("[PASS] Invalid FD sets errno = EBADF\n");
}

void test_file_write() {
    int fd = open("test_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    assert(fd != -1);

    const char *msg = "Writing to a file.\n";
    ssize_t ret = ft_write(fd, msg, strlen(msg));
    assert(ret == (ssize_t)strlen(msg));

    close(fd);
    printf("[PASS] File write\n");
}

void test_null_buffer() {
    errno = 0;
    ssize_t ret = ft_write(1, NULL, 5);
    assert(ret == -1);
    assert(errno == EFAULT);
    printf("[PASS] NULL buffer sets errno = EFAULT\n");
}

void test_write() {
    test_stdout_write();
    test_invalid_fd_write();
    test_file_write();
    test_null_buffer();
    printf("[PASS] ft_write group\n");
}

void test_read_file() {
    char buffer[100] = {0};
    int fd = open("test_input.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    assert(fd != -1);
    write(fd, "Hello, ft_read!\n", 16);
    close(fd);

    fd = open("test_input.txt", O_RDONLY);
    assert(fd != -1);

    ssize_t bytes = ft_read(fd, buffer, sizeof(buffer));
    assert(bytes > 0);
    assert(strncmp(buffer, "Hello, ft_read!", 15) == 0);

    close(fd);
    printf("[PASS] File read\n");
}

void test_read_stdin() {
    char buffer[100] = {0};

    printf("Type something and press Enter: ");
    fflush(stdout);
    ssize_t bytes = ft_read(0, buffer, 100);
    assert(bytes > 0);
    printf("[PASS] STDIN read: %.*s", (int)bytes, buffer);
}

void test_invalid_fd_read() {
    char buffer[10];
    errno = 0;

    ssize_t bytes = ft_read(-1, buffer, 10);
    assert(bytes == -1);
    assert(errno == EBADF);

    printf("[PASS] Invalid FD sets errno = EBADF\n");
}

void test_zero_bytes() {
    char buffer[10] = {0};
    ssize_t bytes = ft_read(0, buffer, 0);
    assert(bytes == 0);
    printf("[PASS] Zero-byte read returns 0\n");
}

void test_read() {
    test_read_file();
    test_invalid_fd_read();
    test_zero_bytes();
    test_read_stdin();
    printf("[PASS] ft_read group\n");
}

void test_basic_string() {
    const char *s = "Hello, World!";
    char *dup = ft_strdup(s);

    assert(dup != NULL);
    assert(strcmp(dup, s) == 0);
    assert(dup != s);
    free(dup);
    printf("[PASS] Basic string duplication\n");
}

void test_empty_string() {
    const char *s = "";
    char *dup = ft_strdup(s);

    assert(dup != NULL);
    assert(strcmp(dup, s) == 0);
    assert(dup != s);
    free(dup);
    printf("[PASS] Empty string\n");
}

void test_long_string() {
    const char *s = "This is a very long string used to test ft_strdup in Assembly.";
    char *dup = ft_strdup(s);

    assert(dup != NULL);
    assert(strcmp(dup, s) == 0);
    assert(dup != s);
    free(dup);
    printf("[PASS] Long string\n");
}

void test_non_printable_chars() {
    const char *s = "abc\n\t123";
    char *dup = ft_strdup(s);

    assert(dup != NULL);
    assert(strcmp(dup, s) == 0);
    assert(dup != s);
    free(dup);
    printf("[PASS] String with non-printable characters\n");
}

void test_strdup() {
    test_basic_string();
    test_empty_string();
    test_long_string();
    test_non_printable_chars();
    printf("[PASS] ft_strdup group\n");
}

int main() {
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    return 0;
}

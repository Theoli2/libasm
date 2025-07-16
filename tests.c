#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

extern size_t ft_strlen(const char *str);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);

void test_strcmp() {
    // Equal strings
    assert(ft_strcmp("hello", "hello") == 0);
    assert(ft_strcmp("", "") == 0);

    // Different lengths
    assert(ft_strcmp("a", "") > 0);
    assert(ft_strcmp("", "a") < 0);

    // Alphabetical comparison
    assert(ft_strcmp("abc", "abd") < 0);
    assert(ft_strcmp("abcd", "abc") > 0);

    // Uppercase vs lowercase
    assert(ft_strcmp("abc", "Abc") > 0);
    assert(ft_strcmp("ABC", "abc") < 0);

    // Embedded null
    assert(ft_strcmp("abc\0xyz", "abc") == 0);

    // Longer string difference
    assert(ft_strcmp("helloo", "hello") > 0);
    assert(ft_strcmp("hello", "helloo") < 0);

    printf("✅ All ft_strcmp tests passed!\n");
}

void test_strlen() {
    assert(ft_strlen("") == strlen(""));
    assert(ft_strlen("a") == strlen("a"));
    assert(ft_strlen("Hello") == strlen("Hello"));
    assert(ft_strlen("Lorem ipsum dolor sit amet.") == strlen("Lorem ipsum dolor sit amet."));
    printf("ft_strlen tests passed ✅\n");
}

void test_strcpy() {
    char dest1[100];
    char dest2[100];

    const char *src = "Hello Assembly!";

    // Call your ft_strcpy
    char *ret = ft_strcpy(dest1, src);
    // Compare with standard strcpy
    strcpy(dest2, src);

    // Check if the copied string is the same
    assert(strcmp(dest1, dest2) == 0);

    // Check if the return value is the destination pointer
    assert(ret == dest1);

    // Test with empty string
    ft_strcpy(dest1, "");
    assert(strcmp(dest1, "") == 0);

    printf("ft_strcpy tests passed ✅\n");
}

int main() {
    test_strlen();
    test_strcpy();
    test_strcmp();
    return 0;
}
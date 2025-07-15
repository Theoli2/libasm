#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

extern size_t ft_strlen(const char *str);
extern char *ft_strcpy(char *dest, const char *src);

void test_strlen() {
    assert(ft_strlen("") == strlen(""));
    assert(ft_strlen("a") == strlen("a"));
    assert(ft_strlen("Hello") == strlen("Hello"));
    assert(ft_strlen("Lorem ipsum dolor sit amet.") == strlen("Lorem ipsum dolor sit amet."));
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

}

int main() {
    test_strlen();
    test_strcpy();
    return 0;
}
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C"{
    void writeInteger(int x) {
        printf("%d", x);
    }

    void writeByte(char x) {
        printf("%d", (int)x);
    }

    void writeChar(char x) {
        printf("%c", x);
    }

    void writeString(const char* x) {
        printf("%s", x);
    }

    int readInteger() {
        int x;
        scanf("%d", &x);
        return x;
    }

    char readByte() {
        int x;
        scanf("%d", &x);
        return (char) x;
    }

    char readChar() {
        char x;
        scanf("%c", &x);
        return x;
    }

    void readString(int n, char *x){
        fgets(x, n, stdin);

        int len = 0;
        while (x[len] != '\0') {
            len++;
        }
        if (len > 0 && x[len - 1] == '\n') {
            x[len - 1] = '\0';
        }
    }

    int extend (char c) {
        return (int) c;
    }

    char shrink (int i) {
        
        i = i % 256;
        return (char) i;
    }  

    char* strcat(char* dest, char* src) {
        char* d = dest;
        while (*d) d++;
        while (*src) {
            *d = *src;
            d++;
            src++;
        }
        *d = 0;
        return dest;
    }

    int strlen(char* s) {
        int i = 0;
        while (*s) {
            i++;
            s++;
        }
        return i;
    }

    int strcmp(char* s1, char* s2) {
        while (*s1 && *s2) {
            if (*s1 != *s2) {
                return *s1 - *s2;
            }
            s1++;
            s2++;
        }
        return 0;
    }

    void strcpy(char* dest, char* src) {
        while (*src) {
            *dest = *src;
            dest++;
            src++;
        }
        *dest = 0;
    }
}


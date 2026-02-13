#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Encrypt(char *plaintext,char *key);
char *Decrypt(char *ciphertext,char *key);

int main() {
    char *plaintext = "Hello World";
    char *key = "1234567890";
    char *ciphertext = Encrypt(plaintext,key);
    printf("%s\n",ciphertext);

    printf("%s\n",Decrypt(ciphertext,key));
    system("pause");
    return 0;
}

char *Encrypt(char *plaintext,char *key) {
    int key_len = strlen(key);
    char *ciphertext = (char*)malloc(strlen(plaintext));
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = plaintext[i]^key[i%key_len];
    }
    return ciphertext;
}
char *Decrypt(char *ciphertext,char *key) {
    return Encrypt(ciphertext,key);
}
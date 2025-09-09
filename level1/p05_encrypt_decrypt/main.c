#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONG 1000

void Encryption(char* str, int len, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0; i<len; i++) {
        str[i] = str[i] ^ key[i % keyLen];
    }
}

int main() {
    const char key[] = "xiafancheng";
    char w_key[100];
    char *message = (char*)malloc(LONG * sizeof(char));
    if (message == NULL) {
        printf("内存分配失败");
        return 1;
    }
    printf("请输入要加密的字符串: ");
    fgets(message, LONG, stdin);
    message[strcspn(message, "\n")] = '\0';
    int len = strlen(message);  
    printf("原始：%s\n", message);
    Encryption(message, len, key);  
    printf("加密:");
    for (int i = 0; i<len; i++)
    {
        printf(" 0x%02x", message[i]);




        
    }
    printf("\n");
    printf("请输入密钥: ");
    fgets(w_key, sizeof(w_key), stdin); 
    w_key[strcspn(w_key, "\n")] = '\0';
    if (strcmp(w_key, key) != 0) {
        printf("密钥错误无法解密\n");
    } else {
        Encryption(message, len, w_key); 
        printf("解密：%s\n", message);
    }
    free(message);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define IOError() do { perror(""); exit(1); } while(0)

int main(int argc, char** argv){
    if (argc != 3){
        printf("Extract file contents to OUTPUT and print the last 16 bytes\n./extract INPUT OUTPUT");
        return 0;
    }

    FILE* fr = fopen(argv[1], "rb");
    if (!fr) { IOError(); }
    fseek(fr, 0, SEEK_END);
    size_t size = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    // just assume the file is super large in my use case
    size -= 16;

    FILE* fw = fopen(argv[2], "wb");
    if (!fw) { IOError(); }

    for (size_t i = 0; i < size; i++){
        char byte;
        if (!fread(&byte, 1, 1, fr)){
            if (ferror(fr)){
                IOError();
            }
        }
        if (!fwrite(&byte, 1, 1, fw)){
            if (ferror(fw)){
                IOError();
            }
        }
    }

    unsigned char last[16];
    if (fread(last, 1, 16, fr) != 16){
        if (ferror(fr)){
            IOError();
        }
    }
    for (int i = 0; i < 16; i++){
        if (last[i] < 10){
            printf("0%x", last[i]);
        }else{
            printf("%x", last[i]);
        }
    }
}

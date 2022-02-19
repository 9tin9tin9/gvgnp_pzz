#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define IOError() do { perror(""); exit(1); } while(0)

#define BIT_OPERATION ^

int main(int argc, char** argv){
    if (argc != 3) {
        printf("./unencrypt INPUT OUTPUT\n");
        return 0;
    }
    FILE* fr = fopen(argv[1], "rb");
    if (!fr) { IOError(); }
    fseek(fr, 0, SEEK_SET);

    FILE* fw = fopen(argv[2], "wb");
    if (!fw) { IOError(); }

    // read padding byte to find 0x00000000
    // assume 4 bytes at offset 0x7FC is 0x00000000
    uint32_t null_bytes;
    fseek(fr, 0x7FC, SEEK_SET);
    fread(&null_bytes, 4, 1, fr);
    fseek(fr, 0, SEEK_SET);

    uint32_t bytes;
    while(fread(&bytes, sizeof(bytes), 1, fr)){
        bytes = bytes BIT_OPERATION null_bytes;
        fwrite(&bytes, sizeof(bytes), 1, fw);
    }
    fclose(fr);
    fclose(fw);
    return 0;
}

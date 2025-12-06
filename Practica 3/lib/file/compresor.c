#include "compresor.h"
void compress(unsigned char *bytes, long long num_elements,  char *codigo[256]){

    long long size=0;
    for(long long i = 0; i < num_elements; i++){
        char *temp = codigo[bytes[i]];
        int j=0;
        while(temp[j++] != '\0') size++;     
    }

    size = (size + 7) / 8;

    int count_bit = 0, code_pos = 0;
    unsigned char tmp_byte = 0;
    unsigned char *compress = malloc(size * sizeof(unsigned char));

    size = 0;
    
    for(long long i = 0; i < num_elements; i++){
        char *hoffman = codigo[bytes[i]];

        while(hoffman[code_pos] != '\0'){
            if(hoffman[code_pos] == '1')
                tmp_byte |= (1 << (7-count_bit));
            code_pos++;
            count_bit++;

            if(count_bit == 8){
                compress[size++] = tmp_byte;
                count_bit = 0;
                tmp_byte = 0;
            }
        }
        code_pos = 0;
    }
    if(count_bit>0)
        compress[size++] = tmp_byte;

    FILE * file = fopen("prueba.dat", "wb");
    if(file == NULL){
        printf("Error al crear el archivo");
        exit(1); 
    }

    long long written = fwrite(compress, sizeof(unsigned char), size, file);
    if (written != size) {
        printf("Error al escribir el archivo\n");
        fclose(file);
        exit(1);
    }

    fflush(file);
    fclose(file);
}


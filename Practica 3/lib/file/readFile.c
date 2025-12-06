#include "readFile.h"

readFile readF(char *name){
    FILE * file = fopen(name, "rb");
    if(file == NULL){
        printf("Error al abrir el archivo");
        fclose(file);
        exit(1);
    }

    readFile rf = {0};

    fseek(file, 0, SEEK_END);
    rf.num_elements = ftell(file);
    rewind(file);

    rf.bytes = malloc(sizeof(unsigned char) * rf.num_elements);
    if(rf.bytes == NULL){
        printf("Error al reservar memoria");
        exit(1);
    }

    fread(rf.bytes, sizeof(char), rf.num_elements, file);

    fclose(file);

    for(int i = 0; i < rf.num_elements; i++){
        rf.frecuencias[rf.bytes[i]]++;
    }
    
    return rf;
}


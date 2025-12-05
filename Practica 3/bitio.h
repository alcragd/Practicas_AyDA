#ifndef BITIO_H
#define BITIO_H

#include <stdio.h>
#include <stdint.h>

// Bit writer
typedef struct {
    FILE *f;
    uint8_t buffer;   // buffer de bits (acumulador)
    int bit_count;    // cuántos bits hay en buffer (0..7)
} BitWriter;

BitWriter *bw_create(FILE *f);
void bw_write_bit(BitWriter *bw, int bit); // bit = 0 o 1
void bw_write_bits(BitWriter *bw, uint64_t bits, int nbits); // escribe nbits (msb first)
void bw_flush(BitWriter *bw);
void bw_destroy(BitWriter *bw);

// Bit reader
typedef struct {
    FILE *f;
    uint8_t buffer;
    int bit_count; // cuántos bits quedan en buffer (0..7)
    int eof;
} BitReader;

BitReader *br_create(FILE *f);
int br_read_bit(BitReader *br); // devuelve 0/1, o -1 si EOF y no quedan bits
void br_destroy(BitReader *br);

#endif

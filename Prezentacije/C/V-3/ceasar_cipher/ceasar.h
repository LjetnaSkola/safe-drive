#ifndef CEASAR_H_
#define CEASAR_H_
#include <stdint.h>

void encryptCeasar(const char* in, char* out, int_fast16_t shift);
void decryptCeasar(const char* in, char* out, int_fast16_t shift);


#endif /* CEASAR_H_ */

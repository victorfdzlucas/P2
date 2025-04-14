#include <stdio.h>
#include <stdint.h>
#include "fic_wave.h"

FILE *abre_wave(const char *ficWave, float *fm) {
    FILE *fpWave = fopen(ficWave, "r");
    if (fpWave == NULL) return NULL;

    // num de canales (offset 22, tamaño 2 bytes)
    if (fseek(fpWave, 22, SEEK_SET) != 0) {
        fclose(fpWave);
        return NULL;
    }

    uint16_t num_channels;
    if (fread(&num_channels, sizeof(num_channels), 1, fpWave) != 1) {
        fclose(fpWave);
        return NULL;
    }

    
if (num_channels != 1) { // Verificar si es mono
        printf("vemos que la señal no es mono");
    if (num_channels == 2) {
    printf("La señal es estéreo.\n");
    }
        fclose(fpWave);
        return NULL;
    }

    // frec. de muestreo (offset 24, tamaño 4 bytes)
    if (fseek(fpWave, 24, SEEK_SET) != 0) {
        fclose(fpWave);
        return NULL;
    }

    uint32_t sample_rate;
    if (fread(&sample_rate, sizeof(sample_rate), 1, fpWave) != 1) {
        fclose(fpWave);
        return NULL;
    }

    *fm = (float)sample_rate; // Asignamos la frecuencia de muestreo

    // Movemos el puntero al inicio de los datos (offset 44)
    if (fseek(fpWave, 44, SEEK_SET) != 0) {
        fclose(fpWave);
        return NULL;
    }

    return fpWave;
}

size_t lee_wave(void *x, size_t size, size_t nmemb, FILE *fpWave) {
    return fread(x, size, nmemb, fpWave);
}

void cierra_wave(FILE *fpWave) {
    if (fpWave) fclose(fpWave);
}

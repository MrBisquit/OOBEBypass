#include <internal/internal.h>

int SaveState(int* page) {
    OOBEBYPASSCONFIG config = {
        *page
    };

    FILE* file = fopen("C:\\Temp\\oobe_bypass.cfg", "wb");
    if(file == NULL)
        return 0;

    if(fwrite(&config, sizeof(OOBEBYPASSCONFIG), 1, file) == 0)
        return 0;

    return 1;
}

int LoadState(int* page) {
    OOBEBYPASSCONFIG config;

    FILE* file = fopen("C:\\Temp\\oobe_bypass.cfg", "rb");
    if(file == NULL)
        return 0;

    if(fread(&config, sizeof(OOBEBYPASSCONFIG), 1, file) == 0)
        return 0;

    *page = config.stage;

    return 1;
}
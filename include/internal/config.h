/*
    This is the configuration file that contains flags so that the program
    does not lose its place in the process, or any information provided.
*/

typedef struct OOBEBYPASSCONFIG {
    int stage;
} OOBEBYPASSCONFIG;

int SaveState(int* page);
int LoadState(int* page);
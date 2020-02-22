#include <stdio.h>
#include <stdlib.h>
#include "TGrafo.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
        executa(argv[1], argv[2]);
    else
        printf("./compilar.sh entrada saida\n");
    return 0;
}

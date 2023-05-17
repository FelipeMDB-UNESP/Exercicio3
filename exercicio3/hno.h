#ifndef HNO_H
#define HNO_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hcliente.h"

typedef struct no{

    Cliente cliente;
    struct no* proximo;
    struct no* anterior;
} No;

#endif /* HNO_H */

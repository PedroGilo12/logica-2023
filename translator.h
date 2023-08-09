//
// Created by Pedro on 07/08/2023.
//

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char * OR_SENTENCES[11] = {
        " ou ",
        " ou entao ",
        " ou ainda ",
        " ou mesmo ",
        " ora ",
        " quer ",
        " caso ",
        " seja ",
        " senão ",
        " se ",
        " ou seja ",
};


char * AND_SENTENCES[11] = {
        " e ",
        "e tambem",
        "e ainda",
        "e mesmo",
        "tambem",
        "bem como",
        "alem disso",
        "ademais",
        "ainda",
        ",",
        "mais",
};

char * NOT_SENTENCES[10] = {
        " nao ",
        "nem",
        "nem mesmo",
        "nem tampouco",
        "nada",
        "nenhum",
        "ninguém",
        "jamais",
        "tampouco",
        "porém",
};

/**
 * @brief Função para procurar uma substring dentro de uma string.
 *
 * @param str String alvo
 * @param sub Substring à ser procurada na string alvo
 *
 * @return [int] indice do primeiro caracter da substring caso encontre
 *         -1 em caso de substring inexistente
 */
int translator_search_substring(const char * str, const char *sub);




#endif /* TRANSLATOR_H */

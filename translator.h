//
// Created by Pedro on 07/08/2023.
//

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#define AND "^"
#define OR "v"
#define NOT "~"
#define THEN "->"

/**
 * @brief Lista de simbolos proposicionais
 */
char *proposicionals_simbols[13] = {"M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "X", "Y", "Z"};

/**
 * @brief
 */
typedef struct logic_sentences {
    char *simbol;
    char *equivalent_string;

    void (*func)(char *);
} logic_sentences_t;

/**
 * @brief
 */
typedef struct node_founded_string {
    logic_sentences_t *data;
    int index;
    struct node_founded_string *next;
} node_founded_string_t;

/**
 * @brief
 */
typedef struct node {
    logic_sentences_t *data;
    struct node *next;
} node_t;


/**
 * @brief
 */
typedef struct list_logic_conectives {
    int len;
    logic_sentences_t *logic_conectives;
} list_logic_conective_t;

/**
 * @brief lista de sentenças logicas padrão
 */
logic_sentences_t default_list[] = {{AND,  " e "},
                                    {THEN, ", entao "},
                                    {AND,  " junto com "},
                                    {AND,  " mais "},
                                    {THEN, " logo "},
                                    {THEN, " sendo assim "},
                                    {NOT,  "nao "},
                                    {OR,   " ou "},
                                    {OR,   " alternativamente "},
                                    {OR,   " caso contrario "},
                                    {OR,   " em alternativa "},
                                    {OR,   " senão "},
                                    {AND,  ","}};

/**
 * @brief lista de sentenças logicas padrão
 */
list_logic_conective_t list_default_conectives = {
        .logic_conectives = default_list,
        .len = 13,
};

/**
 * @brief Função para procurar uma substring dentro de uma string.
 *
 * @param str String alvo
 * @param sub Substring à ser procurada na string alvo
 */
int translator_search_substring(const char *str, const char *sub);

/**
 * @brief Insere uma sentença logicas em uma lista encadeada ordenadamente
 *
 * @param head Topo da lista.
 * @param data Item a ser inserido.
 * @param index Index de ordenação do item.
 */
void tr_insert_ordered(node_founded_string_t **head, logic_sentences_t *data, int index);

/**
 * @brief Divide uma string em duas substrings.
 *
 * @param inputString String de entrada.
 * @param index Índice de divisão da string.
 * @param firstHalf Ponteiro para a substring 1.
 * @param secondHalf Ponteiro para substring 2.
 * @param len_conective Tamanho do conectivo.
 */
void tr_split_string(const char *inputString, int index, char **firstHalf, char **secondHalf, int len_conective);

/**
 * @brief Procura uma substring dentro de uma string.
 *
 * @param str String de entrada.
 * @param sub Substring procurada.
 * @return Indice do primeiro caracter da substring ou -1 caso não ache a substring.
 */
int tr_search_substring(const char *str, const char *sub);

/**
 * @brief Escreve no terminal os conectivos logicos presentes na lista encadeada.
 * @param head Topo da lista.
 */
void tr_print_linked_list(node_founded_string_t *head);

#endif /* TRANSLATOR_H */

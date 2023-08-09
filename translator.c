/**
 * @file    translator.c
 *
 * @author  Pedro Henrique Vieira Giló (phvg@ic.ufal.br)
 *          Pedro Henrique Balbino Rocha (phbr@ic.ufal.br)
 *          Caio Oliveira França dos Anjos (cofa@ic.ufal.br
 *
 * @brief
 *
 */

#include "translator.h"

#define MAX_STACK_SIZE 10

typedef struct {
    char * data;
    struct node * next;
} node ;

typedef struct {
    node * top;
} stack ;

stack* create_stack() {
    stack *new_stack = (stack*) malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}

int is_empty(stack *Stack) {
    return Stack->top == NULL;
}

void push(stack *stack, char * data)
{
    node *new_top = (node*) malloc(sizeof(node));
    new_top->data = data;
    new_top->next = stack->top;
    stack->top = new_top;
}

char *pop(stack *Stack) {
    if (is_empty(Stack)) {
        return NULL;
    }

    node *current = Stack->top;
    char *data = current->data;
    Stack->top = current->next;
    free(current);

    return data;
}

typedef struct {
    char * name;
    char **dictionary;
    int len_dict;
    int index_dict;

    void (*func)(char *);
} conective;

const conective OR = {
        .name = "v",
        .dictionary = OR_SENTENCES,
        .len_dict = 11,
        .index_dict = 10,
        .func = NULL
};

const conective AND = {
        .name = "^",
        .dictionary = AND_SENTENCES,
        .len_dict = 11,
        .index_dict = 10,
        .func = NULL
};

const conective NOT = {
        .name = "~",
        .dictionary = NOT_SENTENCES,
        .len_dict = 10,
        .index_dict = 9,
        .func = NULL
};

char *test_string = "paulo disse a verdade, lucas mentiu e joao nao disse a verdade";

void tr_split_string(const char *inputString, int index, char **firstHalf, char **secondHalf, int len_conective) {
    int strLength = strlen(inputString);
    if (index < 0 || index >= strLength) {
        *firstHalf = NULL;
        *secondHalf = NULL;
        return;
    }

    *firstHalf = (char *) malloc(index + 1);
    *secondHalf = (char *) malloc(strLength - index);

    strncpy(*firstHalf, inputString, index);
    (*firstHalf)[index] = '\0';

    strcpy(*secondHalf, inputString + index + len_conective);

}

int tr_search_substring(const char *str, const char *sub) {
    int i, j;

    int str_len = strlen(str);
    int sub_len = strlen(sub);

    for (i = 0; i <= str_len - sub_len; i++) {
        for (j = 0; j < sub_len; j++) {
            if (str[i + j] != sub[j]) {
                break;
            }
        }
        if (j == sub_len) {
            return i;
        }
    }

    return -1;
}

stack * sentence_queue;

int tr_translator_str(const conective sub, const char *str) {

    int index = -1;
    int len_dict = sub.len_dict;

    char *first_str;
    char *second_str;

    int end;

    for (int i = 0; i < len_dict; i++) {

        //printf("Procurando: %s \n", sub.dictionary[i]);

        index = tr_search_substring(str, sub.dictionary[i]);

         //printf("Retorno do indice: %d \n", index);

        if (index == -1) {
            continue;
        }

        tr_split_string(str, index, &first_str, &second_str, strlen(sub.dictionary[i]));

        printf("\nSTRING PAI: %s\n", str);

        //printf("STRING1: %s \n", first_str);
        end = tr_translator_str(sub, first_str);

        if(!end) {
            if(!is_empty(sentence_queue)) {
                push(sentence_queue, (char *)sub.name);
            }
            push(sentence_queue, first_str);
        }

        //printf("STRING2: %s \n", second_str);
        end = tr_translator_str(sub, second_str);

        if(!end) {
            push(sentence_queue, (char *)sub.name);
            push(sentence_queue, second_str);
        }

        printf("Retorno\n\n");

        return 1;
    }

    return 0;
}


int main() {

    printf("Start...\n");

    sentence_queue = create_stack();

    tr_translator_str(AND, test_string);

    while(1) {

        char *str = pop(sentence_queue);

        if(str == NULL) {
            break;
        }

        printf("Pop: %s\n", str);
    }




    return 0;
}
/**
 * @file    evaluator.c
 *
 * @author  Pedro Henrique Vieira Giló (phvg@ic.ufal.br)
 *          Pedro Henrique Balbino Rocha (phbr@ic.ufal.br)
 *          Caio Oliveira França dos Anjos (cofa@ic.ufal.br
 *
 * @brief
 *
 */

#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

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

    int (*func)(int, int);
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

void tr_insert_ordered(node_founded_string_t **head, logic_sentences_t *data, int index) {
    node_founded_string_t *new_node = (node_founded_string_t *) malloc(sizeof(node_founded_string_t));
    new_node->data = data;
    new_node->index = index;
    new_node->next = NULL;

    if (*head == NULL || index < (*head)->index) {
        new_node->next = *head;
        *head = new_node;
    } else {
        node_founded_string_t *current = *head;
        while (current->next != NULL && current->next->index <= index) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

typedef struct letra {
    char *character;
    unsigned long int valor;
} letra_t;

letra_t letras[] = {{"a", 0b0101010101010101},
                    {"b", 0b0011001100110011},
                    {"c", 0b0000111100001111},
                    {"d", 0b0000000011111111}};


int ev_operation_and(int a, int b) {
    return a & b;
}

int ev_operation_or(int a, int b) {
    return a | b;
}

int ev_operation_not(int a, int b) {
    return !a;
}

logic_sentences_t ev_and = {
        .simbol = "^",
        .equivalent_string = " ^ ",
        .func = ev_operation_and,
};

logic_sentences_t ev_or = {
        .simbol = "v",
        .equivalent_string = " v ",
        .func = ev_operation_or,
};

logic_sentences_t ev_not = {
        .simbol = "~",
        .equivalent_string = " ~ ",
        .func = ev_operation_not,
};

logic_sentences_t ev_default_conectives[3];

list_logic_conective_t ev_operations_list = {
        .logic_conectives = ev_default_conectives,
        .len = 3,
};

struct ev_linked_list {
    node_founded_string_t *head;
    int len;
} self = {
        .head = NULL,
        .len = 1,
};

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


void ev_extract_list_str(const list_logic_conective_t sub, const char *str, int previous_index) {
    int index = -1;
    int len_dict = sub.len;

    char *first_str;
    char *second_str;

    for (int i = 0; i < len_dict; i++) {
        index = tr_search_substring(str, sub.logic_conectives[i].equivalent_string);

        if (index == -1) {
            continue;
        }

        tr_split_string(str, index, &first_str, &second_str, strlen(sub.logic_conectives[i].equivalent_string));

        tr_insert_ordered(&self.head, &sub.logic_conectives[i], previous_index + index);
        self.len++;

        ev_extract_list_str(sub, first_str, previous_index);
        ev_extract_list_str(sub, second_str, previous_index + index);

        return;

    }
    return;
}

void printBinaryWithPadding(int num, int len) {
    for (int i = pow(2, len) - 1; i >= 0; i--) {  // Sempre imprime 4 bits
        int bit = (num >> i) & 1;   // Obtém o i-ésimo bit
        printf("%d", bit);
    }
    printf("\n");
}

struct bin_node {
    int bin;
    struct bin_node *next;
};

void insert(struct bin_node **head, int data) {
    struct bin_node *newNode = (struct bin_node *) malloc(sizeof(struct bin_node));
    newNode->bin = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct bin_node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

int removeFirst(struct bin_node **head) {
    if (*head == NULL) {
        return -1;
    }

    struct bin_node *temp = *head;
    int data = temp->bin;

    *head = (*head)->next;
    free(temp);

    return data;
}

void printList(struct bin_node *head) {
    printf("Lista Encadeada:\n");
    while (head != NULL) {
        printf("%d -> ", head->bin);
        head = head->next;
    }
    printf("NULL\n");
}

int execute(struct bin_node *list, node_founded_string_t *ev_head, int len) {

    node_founded_string_t *current = ev_head;
    int s;

    while (list->next != NULL) {
        int a = removeFirst(&list);
        int b = removeFirst(&list);

        s = current->data->func(a, b);

        insert(&list, s);

        printBinaryWithPadding(a, len);
        printBinaryWithPadding(b, len);
        printBinaryWithPadding(s, len);
        printf("\n");
        current = ev_head->next;
    }

    return s;
}

void procurar_letra(const char *string, const letra_t *letras, int letras_count, struct bin_node** list) {
    int string_length = strlen(string);

    for (int i = 0; i < string_length; i++) {
        for (int j = 0; j < letras_count; j++) {
            if (string[i] == '~') {
                for(int h = 0; h < letras_count; h++) {
                    if (string[i+1] == *letras[h].character) {
                        int a = ~letras[h].valor&0xFFFF;
                        insert(list, a);

                        i += 2;
                        break;
                    }
                }

            } else if (string[i] == *letras[j].character) {
                insert(list, letras[j].valor);
                break;
            }
        }
    }
}


int main() {

    char *input_str;
    int resultado = 0;
    int tam;

    printf("So serao aceitas variaveis: a, b, c, d\ne conectivos: v, ^, ~\nExemplo:\n\n     a ^ ~a\n\n");

    printf("Digite sua sentenca: \n");

    scanf("%m[^\n]", &input_str);

    printf("Sua string: %s\n", input_str);

    struct bin_node *list = NULL;

    ev_default_conectives[0] = ev_and;
    ev_default_conectives[1] = ev_or;
    ev_default_conectives[2] = ev_not;

    ev_extract_list_str(ev_operations_list, input_str, 0);

    int letras_count = sizeof(letras) / sizeof(letras[0]);
    procurar_letra(input_str, letras, letras_count, &list);

    resultado = execute(list, self.head, self.len);

    tam = (int) pow(2, self.len);

    tam = tam|~tam;

    if(resultado == 0) {
        printf("Contradicao\n");
    } else if ((0xFFFF&resultado) == 0xFFFF) {
        printf("Tautologia\n");
    } else {
        printf("Satisfativel\n");
    }

    return 0;
}
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

node_founded_string_t *head = NULL;

void tr_print_linked_list(node_founded_string_t *head) {
    node_founded_string_t *current = head;

    int index = 0;

    if(current == NULL) {
        printf("P\n");
        return;
    }

    if (current->data->simbol == NOT) {
        printf("%s", current->data->simbol);
        current = current->next;
    }

    printf("%s", proposicionals_simbols[index]);

    while (current != NULL) {
        if (current->next == NULL) {
            goto segmentation_fault_bypass;
        }
        if (current->next->data->simbol == NOT) {
            index++;
            printf(" %s ", current->data->simbol);
            printf("%s", current->next->data->simbol);
            printf("%s ", proposicionals_simbols[index]);
            current = current->next->next;
        } else {
            segmentation_fault_bypass:
            index++;
            printf(" %s ", current->data->simbol);
            printf("%s", proposicionals_simbols[index]);
            current = current->next;
        }
    }

    printf("\n");
}


void tr_translator_str(const list_logic_conective_t sub, const char *str, int previous_index) {
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

/*        printf("###############\nReparticao na substring: %s\n\n1- %s\n2- %s\nindice: %d\n##############\n",
               sub.logic_conectives[i].equivalent_string, first_str, second_str, previous_index+index);*/

        tr_insert_ordered(&head, &sub.logic_conectives[i], previous_index + index);

        tr_translator_str(sub, first_str, previous_index);
        tr_translator_str(sub, second_str, previous_index + index);

        return;

    }
    return;
}


int main() {

    char *input_str = NULL;

    printf("Digite sua sentenca: \n");

    scanf("%m[^\n]", &input_str);

    printf("Sua string: %s\n", input_str);

    printf("Sua sentenca traduzida: \n");
    tr_translator_str(list_default_conectives, input_str, 0);

    tr_print_linked_list(head);

    printf("\n");


    return 0;
}
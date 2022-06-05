// Trabalho Semestral de Pesquisa e Classificação de Dados
// Implementação de uma Trie que sirva como DNS
// Alunos: Vinicius Bertuol e Gabriel Luiz Scariot
// Link do Trabalho no Github: https://github.com/VBertuol/TrabalhoSemestralPCD

#include <stdio.h>
#include <stdlib.h>
#define URL 100

typedef struct Trie {
    int booleanTerminal;
    char IP [15];
    struct Trie * pointerArray [26];
}Trie;

Trie * newRoot() {
    int i;
    Trie * newTrie = (Trie *)malloc(sizeof(Trie));
    for(i = 0; i < 26; i++) {
        newTrie->booleanTerminal = 0;
        newTrie->pointerArray[i] = NULL;
    }
    return newTrie;
}

Trie * newLetter (Trie * myTrie, char a) {
    int char_to_int = a - 97;
    if (myTrie->pointerArray[char_to_int] == NULL) {
        Trie * newTrie = newRoot();
        myTrie->pointerArray[char_to_int] = newTrie;
        printf("%d  ", newTrie);
        return newTrie; 
    }
    else {
        printf("%d  ", myTrie->pointerArray[char_to_int]);
        return myTrie->pointerArray[char_to_int];
    }
}

void verify (Trie * myTrie) {
    Trie * auxTrie = newRoot();
    auxTrie = myTrie;
    int i = 0;
    int char_to_int;
    char url [URL];
    for(i = 0; i< URL; i++) {
        scanf("%c", url[i]);
        if (url[i] == '\0') break;
    }
    if (url[0] == "*") return;
    for (; i >= 0; i--) {
        char_to_int = url[i];
        if (url[i] == ".");
        if (auxTrie->booleanTerminal == 1) {
            printf ("%s", auxTrie->IP);
            break;;
        }
        if (auxTrie->pointerArray[char_to_int] != NULL) {
            auxTrie = auxTrie->pointerArray[char_to_int];
        }
        if (auxTrie->pointerArray[char_to_int] == NULL) {
            printf("nao encontrado.\n");
            break;;
        }
    }
    verify(myTrie);
}

int main () { 
    Trie * myTrie = newRoot();
    char character;
    char url [URL];
    FILE * dnsFILE = fopen("dns.txt", "r");
    while (!feof(dnsFILE)) {
        Trie * auxTrie1 = newRoot();
        fscanf(dnsFILE,"%c", &character);
        printf("%c ", character);
        auxTrie1 = newLetter(myTrie, character);
        while (character != ' ') {
            fscanf(dnsFILE,"%c", &character);
            if (character >= 97 && character <=122) {
                printf("%c ", character);
                auxTrie1 = newLetter(auxTrie1, character);
            }
        }
        fscanf(dnsFILE,"%s\n", &auxTrie1->IP[0]);
        auxTrie1->booleanTerminal = 1;
        printf(" %d %s\n", auxTrie1->booleanTerminal, auxTrie1->IP);
        free(auxTrie1);
    }
    verify(myTrie);
    return 0;
}
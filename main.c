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
        newTrie->pointerArray[i] = NULL;
    }
    return newTrie;
}

Trie * newLetter (Trie * myTrie, char a) {
    int char_to_int = a - 97;
    if (myTrie->pointerArray[char_to_int] == NULL) {
        Trie * newTrie = newRoot();
        myTrie->pointerArray[char_to_int] = newTrie;
        return newTrie; 
    }
    else {
        return myTrie->pointerArray[char_to_int];
    }
}

Trie * verify (Trie * myTrie, char character) {
    int char_to_int = character - 97;
    if (myTrie->pointerArray[char_to_int]->booleanTerminal == 1) {
        printf ("%s", myTrie->pointerArray[char_to_int]->IP);
        return myTrie;
    }
    if (myTrie->pointerArray[char_to_int] != NULL) {
        Trie * auxTrie = newRoot();
        auxTrie = myTrie->pointerArray[char_to_int];
        return auxTrie;
    }
    if (myTrie->pointerArray[char_to_int] == NULL) {
        printf("nao encontrado.\n");
        return myTrie;
    }
}

int main () { 
    
    Trie * myTrie = newRoot();
    char character;
    char url [URL];

    FILE * dnsFILE = fopen("dns.txt", "r");
   
    while (!feof(dnsFILE)) {
        Trie * auxTrie1 = newRoot();
        fscanf(dnsFILE,"%c", &character);
        auxTrie1 = newLetter(myTrie, character);
        while (character != ' ') {
            fscanf(dnsFILE,"%c", &character);
            if (character >= 97 && character <=122) {
                auxTrie1 = newLetter(auxTrie1, character);
            }
        }
        fscanf(dnsFILE,"%s", &auxTrie1->IP[0]);
        fscanf(dnsFILE,"%c", &character);
        auxTrie1->booleanTerminal = 1;
        free(auxTrie1);
    }

    while (character != '*') {
        Trie * auxTrie1 = newRoot();
        Trie * auxTrie2 = newRoot();
        scanf("%c", &character);
        if (character == '*') return 0;
        auxTrie1 = verify(myTrie, character);
        while (character != '\0') {
            scanf("%c", &character);
            if (character >= 97 && character <=122) {
                auxTrie2 = auxTrie1;
                auxTrie1 = verify(auxTrie1, character);
                if (auxTrie1 == auxTrie2) break;
            }
        }
        free(auxTrie1);
        free(auxTrie2);
        scanf("%c", &character);
    }
    return 0;
}
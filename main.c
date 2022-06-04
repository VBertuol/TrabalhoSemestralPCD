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
    printf (" %c %d\n", a, char_to_int);
    if (myTrie->pointerArray[char_to_int] == NULL) {
        Trie * newTrie = newRoot();
        myTrie->pointerArray[char_to_int] = newTrie;
        return newTrie; 
    }
    else {
        return myTrie->pointerArray[char_to_int];
    }
}

Trie * search (Trie * myTrie, char url) {
            int char_to_int = url - 97;
            if (myTrie->booleanTerminal == 1) {
                printf("%s", myTrie->IP);
                return NULL;
            }
            if (myTrie->pointerArray[char_to_int] != NULL) {
                myTrie = myTrie->pointerArray[char_to_int];
                printf("\n %c %d", url, char_to_int);
                printf("%d", myTrie->booleanTerminal);
                return myTrie;
            }
            else {
                printf("endereco nao encontrado.");
                return NULL;
            }
}

int main () {
    
    Trie * myTrie = newRoot();
    char character;
    char url;

    FILE * dnsFILE = fopen("dns.txt", "r");

    while (!feof(dnsFILE)) {
        Trie * auxTrie1 = newRoot();
        fscanf(dnsFILE,"%c", &character);
        auxTrie1 = newLetter(myTrie, character);
        while (character != ' ') {
            fscanf(dnsFILE,"%c", &character);
            if (character == '.') printf(" .\n");
            if (character >= 97 && character <=122) {
                auxTrie1 = newLetter(auxTrie1, character);
            }
        }
        auxTrie1->booleanTerminal = 1;
        printf(" ");
        fscanf(dnsFILE, "%s", &auxTrie1->IP);
        printf("%s ", auxTrie1->IP);

        free(auxTrie1);
        fscanf(dnsFILE,"%c", &character);
    }

    while (url != '*') {
        int i;
        Trie * myNewTrie = myTrie;
        for (i = 0; i < URL; i++) {
            scanf("%c", &url);
            if (url == '*' || myNewTrie == NULL) break;
            if (url >= 97 && url <=122 && (myNewTrie != NULL)) {
                myNewTrie = search(myNewTrie, url);
            }
        }
        free(myNewTrie);
    }
    return 0;
}
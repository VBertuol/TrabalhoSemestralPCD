// Trabalho Semestral de Pesquisa e Classificação de Dados
// Implementação de uma Trie que sirva como DNS
// Alunos: Vinicius Bertuol e Gabriel Luiz Scariot
// Link do Trabalho no Github: https://github.com/VBertuol/TrabalhoSemestralPCD

#include <stdio.h>
#include <stdlib.h>
#define URL 100

// Estrutura de um nodo da Trie, um "booleano" que diz que o nodo é terminal ou não, uma string para representar o IP caso exista
// e um vetor de ponteiros para 26 nodos inicialmente nulos que correponde aos 26 possiveis filhos, cada um representando uma das
// letras do alfabeto

typedef struct Trie {
    int booleanTerminal;
    char IP [15];
    struct Trie * pointerArray [26];
}Trie;

// Função que cria um novo nodo alocado dinamicamente, setando "terminal" = false e todos os filhos como nulos

Trie * newNode() {
    int i;
    Trie * newTrie = (Trie *)malloc(sizeof(Trie));
    newTrie->booleanTerminal = 0;
    for(i = 0; i < 26; i++) {
        newTrie->pointerArray[i] = NULL;
    }
    return newTrie;
}

// Função que recebe um nodo e um caractere a ser inserido na Trie, se o caractere for um '.', não faz nada, se for um novo caractere chama a função
// que cria novo nodo e retorna o novo nodo, caso o caractere ja esteja alocado retorna sua posição

Trie * newLetter (Trie * myTrie, char a) {
    int char_to_int = a - 97;
    if (a == '.') {
        return myTrie;
    }
    if (myTrie->pointerArray[char_to_int] == NULL) {
        Trie * newTrie = newNode();
        myTrie->pointerArray[char_to_int] = newTrie;
        return newTrie; 
    }
    else {
        return myTrie->pointerArray[char_to_int];
    }
}

//Função que verifica se a posição do caractere passado existe dentro da Trie ou não, se existe retorna sua posição, se não existe retorna nulo

Trie * verify (Trie * myTrie, char a) {
    int char_to_int = a - 97;
    if (a == '.') {
        return myTrie;
    }
    if (myTrie->pointerArray[char_to_int] == NULL) {
        return NULL;
    }
    else {
        return myTrie->pointerArray[char_to_int];
    }
}

//Função que limpa a variável do tipo string de 100 posições usada para guardar URLs, a "Limpeza" é feita colocando o caractere '$' em todas as posições

void clearURL (char * url) {
    int i;
    for (i = 0; i < URL; i++) {
        url[i] = '$';
    }
    return;
}

// Função chamada ao fim da execução do programa para descalocar recursivamente toda a memória utilizada pelos nodos da Trie
// Seu funcionamento é parecido com o percurso pós-order de uma BST, vai descendo até as folhas, libera elas e volta liberando até a raiz

void clearMemory (Trie * myTrie) {
    int i;
    for(i = 0; i<26;i++) {
        if (myTrie->pointerArray[i] != NULL) {
            clearMemory(myTrie->pointerArray[i]);
        }
    }
    free(myTrie);
    return;
}

int main () { 
    
    // Declaração de variáveis usadas na função main()

    Trie * myTrie = newNode();
    char character;
    char url [URL];
    int i;

    // Abre o Arquivo dns.txt

    FILE * dnsFILE = fopen("dns.txt", "r");
   
    // Leitura de todos os dados presentes no arquivo dns.txt, url letra por letra enviando para a função newLetter() 
    // e no fim o IP inteiro como string, além de mudar o booleano de terminal como verdadeiro quando necessário

    while (!feof(dnsFILE)) {
        clearURL(url);
        Trie * auxTrie1 = myTrie;
        for (i = 0; i < URL; i++) {
            fscanf(dnsFILE, "%c", &url[i]);
            if (url[i] == ' ') break;
        }
        for (i = URL - 1; i >= 0; i--) {
            if (url[i] != '$' && (url[i] != ' ')) {
                auxTrie1 = newLetter(auxTrie1, url[i]);
            }
        }
        auxTrie1->booleanTerminal = 1;
        fscanf(dnsFILE,"%s", &auxTrie1->IP[0]);
        fscanf(dnsFILE,"%c", &character);
    }
        
    // Leitura do teclado do usuário letra por letra armazenando na string de 100 posições 'url' até que haja um "new line", 
    // caracterizando assim como o fechamento de uma URL

    while (character != '*' ) {
        clearURL(url);
        Trie * auxTrie1 = myTrie;
        for (i = 0; i < URL; i++) {
            scanf("%c", &character);
            if (character == '*') break;
            if (character >= 97 && character <= 122) {
                url[i] = character;
            }
            if (character == 10) {
                break;
            }
        }
        if (character == '*') break;

    // Verificação letra a letra a URL armazenada, mandando para a função verify(), caso volte como nulo ou então a URL acabe sem achar um terminal
    // imprime que o endereço não foi encontrado, caso contrário imprime o IP correspondente ao URL

        for (i = URL - 1; i >= 0; i--) {
            if (url[i] != '$') {
                auxTrie1 = verify(auxTrie1, url[i]);
                if (auxTrie1 == NULL) {
                    printf("endereco nao encontrado.\n");
                    break;
                }
                else {
                    if (auxTrie1->booleanTerminal == 1) {
                        printf ("%s\n", auxTrie1->IP);
                        break;
                    }
                    if (auxTrie1->booleanTerminal == 0 && i == 0) {
                        printf("endereco nao encontrado.\n");
                        break;
                    }
                }
            }
        }
    }
    
    clearMemory(myTrie);

    return 0;
}
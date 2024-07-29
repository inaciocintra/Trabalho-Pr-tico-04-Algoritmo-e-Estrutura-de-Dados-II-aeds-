#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FILE_PATH "/tmp/characters.csv"
// C:/Users/glauc/Downloads/tp4-aeds2/tp04/characters.csv
#define INITIAL_STRING_CAPACITY 32
#define INITIAL_ARRAY_CAPACITY 5

typedef struct {
    char *id;
    char *name;
    char **alternateNames;
    int alternateNamesCount;
    char *house;
    char *ancestry;
    char *species;
    char *patronus;
    bool isHogwartsStaff;
    bool isHogwartsStudent;
    char *actorName;
    bool isAlive;
    char **alternateActors;
    int alternateActorsCount;
    char *dateOfBirth;
    int yearOfBirth;
    char *eyeColour;
    char *gender;
    char *hairColour;
    bool isWizard;
} Character;

void free_string_array(char **array, int length);
void free_character(Character *character);

char *read_string(int *i, const char *csvLine) {
    int maxSize = strlen(csvLine);
    if (*i >= maxSize) 
        return NULL; 

    int capacity = INITIAL_STRING_CAPACITY;
    char *str = (char *)malloc(capacity * sizeof(char));
    if (str == NULL) {
        perror("Memory allocation error in string");
        return NULL;
    }

    int pos = 0; 
    while (*i < maxSize && csvLine[*i] != ';') 
    {
        if (pos >= capacity-1) {
            capacity *= 2;
            char *temp = (char *)realloc(str, capacity * sizeof(char));
            if (temp == NULL) {
                perror("Error when resizing string");
                free(str); 
                return NULL;
            }
            str = temp;
        }
        str[pos++] = csvLine[(*i)++];
    }

    str[pos] = '\0'; 
    (*i)++;
    return str;
}

char **read_multivalued(int *i, const char *csvLine, int *arrayCount) {
    int maxSize = strlen(csvLine);
    if (*i >= maxSize-1 || csvLine[*i] != '[') 
        return NULL;

    (*i)++; // jump '['

    int arrayCapacity = INITIAL_ARRAY_CAPACITY;
    char **array = (char **)malloc(arrayCapacity * sizeof(char *)); 
    if (array == NULL) {
        perror("Memory allocation error in string array");
        return NULL;
    }

    int pos = 0;
    while (*i < maxSize && csvLine[*i] != ']')
    {
        if (pos >= arrayCapacity) {
            arrayCapacity *= 2; 
            char **temp = (char **)realloc(array, arrayCapacity * sizeof(char *)); 
            if (temp == NULL) {
                perror("Error when resizing string array");
                free_string_array(array, pos);
                return NULL;
            }
            array = temp; 
        }

        int strCapacity = INITIAL_STRING_CAPACITY;
        char *tempStr = (char *)malloc(strCapacity * sizeof(char));
        if (tempStr == NULL) {
            perror("Memory allocation error in string");
            free_string_array(array, pos);
            return NULL;
        }

        int j = 0;
        while (*i < maxSize && csvLine[*i] != ',' && csvLine[*i] != ']')
        {
            if (j >= strCapacity - 1) { 
                strCapacity *= 2;
                char *tempStr2 = (char *)realloc(tempStr, strCapacity * sizeof(char));
                if (tempStr2 == NULL) {
                    perror("Memory reallocation error in string");
                    free_string_array(array, pos);
                    free(tempStr);
                    return NULL;
                }
                tempStr = tempStr2; 
            }
            if (csvLine[*i] != '\'') 
                tempStr[j++] = csvLine[*i];
            
            (*i)++;
        }

        tempStr[j] = '\0'; 
        array[pos++] = tempStr;

        if (csvLine[*i] == ',') 
            (*i)++; 
    }
    (*i) += 2; // jump ']' and ';'
    *arrayCount = pos; 
    return array;
}

bool read_boolean(int *i, const char *csvLine) {
    bool predicate = false;
    char* wordRead = read_string(i, csvLine);

    if (wordRead != NULL) {
        if (wordRead[0] == 'V')
            predicate = true;
        free(wordRead);
    }

    return predicate; 
}

int read_integer(int *i, const char *csvLine){
    char* wordRead = read_string(i, csvLine);
    if(wordRead == NULL)
        return -1;
    return atoi(wordRead);
}

Character* csvLine_mapper(char *csvLine) {
    Character* character = (Character*)malloc(sizeof(Character));
    if (character == NULL) {
        perror("Memory allocation error in Character struct");
        return NULL;
    }

    int i = 0;

    character->id = read_string(&i, csvLine);
    character->name = read_string(&i, csvLine);

    int alternateNamesCount = 0;
    character->alternateNames = read_multivalued(&i, csvLine, &alternateNamesCount);
    character->alternateNamesCount = alternateNamesCount;

    character->house = read_string(&i, csvLine);
    character->ancestry = read_string(&i, csvLine);
    character->species = read_string(&i, csvLine);
    character->patronus = read_string(&i, csvLine);
    character->isHogwartsStaff = read_boolean(&i, csvLine);
    character->isHogwartsStudent = read_boolean(&i, csvLine);
    character->actorName = read_string(&i, csvLine);
    character->isAlive = read_boolean(&i, csvLine);

    int alternateActorsCount = 0;
    character->alternateActors = read_multivalued(&i, csvLine, &alternateActorsCount);
    character->alternateActorsCount = alternateActorsCount;

    character->dateOfBirth = read_string(&i, csvLine);
    character->yearOfBirth = read_integer(&i, csvLine);
    character->eyeColour = read_string(&i, csvLine);
    character->gender = read_string(&i, csvLine);
    character->hairColour = read_string(&i, csvLine);
    character->isWizard = read_boolean(&i, csvLine);
    
    return character; 
}

void print_string_array(char **array, int count) {
    printf("{");
    for (int i = 0; i < count; i++) {
        printf("%s", array[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("}");
}

void print_character(Character *character) {
    if (character == NULL) {
        printf("Character struct is NULL.\n");
        return;
    }

    printf("[");
    printf("%s", character->id ? character->id : " "); 
    printf(" ## %s", character->name ? character->name : " ");

    printf(" ## ");
    if (character->alternateNames) 
        print_string_array(character->alternateNames, character->alternateNamesCount);
    else 
        printf(" {}");

    printf(" ## %s", character->house ? character->house : " "); 
    printf(" ## %s", character->ancestry ? character->ancestry : " "); 
    printf(" ## %s", character->species ? character->species : " "); 
    printf(" ## %s", character->patronus ? character->patronus : " "); 
    printf(" ## %s", character->isHogwartsStaff ? "true" : "false"); 
    printf(" ## %s", character->isHogwartsStudent ? "true" : "false"); 
    printf(" ## %s", character->actorName ? character->actorName : " ");
    printf(" ## %s", character->isAlive ? "true" : "false"); 
    printf(" ## %s", character->dateOfBirth ? character->dateOfBirth : " "); 
    printf(" ## %d", character->yearOfBirth); 
    printf(" ## %s", character->eyeColour ? character->eyeColour : " ");
    printf(" ## %s", character->gender ? character->gender : " ");
    printf(" ## %s", character->hairColour ? character->hairColour : " "); 
    printf(" ## %s", character->isWizard ? "true" : "false");

    printf("]\n");
}


typedef struct No {
    Character* character;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;


typedef struct ArvoreAVL {
    No* raiz;
    void (*inserir)(struct ArvoreAVL*, Character*);
    bool (*pesquisar)(struct ArvoreAVL*, char*);
} ArvoreAVL;



// Função para obter a altura de um nó
int altura(No* n) {
    if (n == NULL) {
        return 0;
    }
    return n->altura;
}

// Função para obter o valor máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
No* criarNo(Character *character) {
    No* no = (No*)malloc(sizeof(No));
    no->character = character;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; // Novo nó é inicialmente adicionado como folha
    return no;
}

// Função para rotacionar à direita
No* rotacionarDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    // Retorna nova raiz
    return x;
}

// Função para rotacionar à esquerda
No* rotacionarEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    // Retorna nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int obterFatorBalanceamento(No* n) {
    if (n == NULL) {
        return 0;
    }
    return altura(n->esquerda) - altura(n->direita);
}

// Função para inserir um nó na árvore AVL
No* inserirNo(No *no, Character *character) {
    // 1. Inserir normalmente na árvore binária de busca
    if (no == NULL) {
        return criarNo(character);
    }

    if (strcmp(character->name, no->character->name) < 0) {
        no->esquerda = inserirNo(no->esquerda, character);
    } else if (strcmp(character->name, no->character->name) > 0) {
        no->direita = inserirNo(no->direita, character);
    } else { // Chave duplicada não é permitida na árvore AVL
        return no;
    }

    // 2. Atualizar a altura deste ancestral nó
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    // 3. Obter o fator de balanceamento deste ancestral nó para verificar se este nó ficou desbalanceado
    int balance = obterFatorBalanceamento(no);

    // Se o nó ficar desbalanceado, há 4 casos

    // Caso Esquerda-Esquerda
    if (balance > 1 && strcmp(character->name, no->esquerda->character->name) < 0) {
        return rotacionarDireita(no);
    }

    // Caso Direita-Direita
    if (balance < -1 && strcmp(character->name, no->direita->character->name) > 0) {
        return rotacionarEsquerda(no);
    }

    // Caso Esquerda-Direita
    if (balance > 1 && strcmp(character->name, no->esquerda->character->name) > 0) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && strcmp(character->name, no->direita->character->name) < 0) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    // Retornar o ponteiro do nó (inalterado)
    return no;
}

// Função para inicializar uma árvore AVL
ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL* arvore = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
    return arvore;
}

// Função para buscar um nó na árvore AVL
bool pesquisar(No *i, char* name) {
    if (i == NULL) {
    return false;
    }

    if (strcmp(i->character->name, name) == 0) {
        return true;
    }

    if (strcmp(name, i->character->name) < 0) {
    printf("esq ");
    return pesquisar(i->esquerda, name);
    }

    else if (strcmp(name, i->character->name) > 0){
    printf("dir ");
    return pesquisar(i->direita, name);
    }
}

// Função para inserir um Character na árvore AVL (método de classe)
void inserirNaArvore(ArvoreAVL* arvore, Character *character) {
    arvore->raiz = inserirNo(arvore->raiz, character);
}

// Função para pesquisar um Character na árvore AVL (método de classe)
bool pesquisarNaArvore(ArvoreAVL* arvore, char* nomepersonagem) {
    return pesquisar(arvore->raiz, nomepersonagem);
}





// Função principal que lê o arquivo CSV, processa cada linha, ordena e imprime personagens
int main(void) {
    
    ArvoreAVL* arvore = criarArvoreAVL();
    int characterCount = 0;
    
    char line[256];
    char codigo[37];
    char nomepersonagem[50];
    scanf("%s",codigo);   

    // Lê a linha de cabeçalho (ignorada neste exemplo)
    while (codigo[0]!='F' && codigo[1]!='I' && codigo[2]!='M')
    {
      FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        perror("File not found exception.");
        return 1;
        fgets(line, sizeof(line), file);

    }  
    while (fgets(line, sizeof(line), file)) {
        
        // Mapeia a linha CSV para um objeto Character
        Character *character = csvLine_mapper(line);

        if (strcmp(codigo, character->id) == 0) {
            // Adiciona o personagem na árvore AVL
            arvore->raiz = inserirNo(arvore->raiz, character);
        } else {
            free_character(character); // Libera a memória se o personagem não for adicionado
        }
        }
    //le dnv
    scanf("%s",codigo);
    // Fecha o arquivo após a leitura
    fclose(file);
    }
    


    while ( scanf(" %[^\r\n]", nomepersonagem))
    {
       
        if (strncmp(nomepersonagem, "FIM", 3) == 0) {
            break; // Sair do loop se a entrada for "FIM"
        }
    bool resp = true;
    printf("%s => raiz ",nomepersonagem);
    resp = pesquisar(arvore->raiz, nomepersonagem);
    
    if(resp){
    printf("SIM\n");
    }
    else{
    printf("NAO\n");
    }
    //le dnv
    
    
    

    // Libera a memória alocada para personagens
    /*for (int i = 0; i < characterCount; i++) {
        free_character(characterArray[i]);
    }*/

   

}
    return 0;
}

// Função para liberar um array de strings
void free_string_array(char **array, int length) {
    if (array == NULL)
        return;

    // Libera cada string do array
    for (int i = 0; i < length; i++) {
        free(array[i]);
    }

    // Libera o próprio array de strings
    free(array);
}

// Função para liberar um objeto Character
void free_character(Character *character) {
    if (character == NULL)
        return;

    // Libera as strings do objeto Character
    free(character->id);
    free(character->name);
    free(character->house);
    free(character->ancestry);
    free(character->species);
    free(character->patronus);
    free(character->actorName);
    free(character->dateOfBirth);
    free(character->eyeColour);
    free(character->gender);
    free(character->hairColour);

    // Libera as listas de strings do objeto Character
    if (character->alternateNames)
        free_string_array(character->alternateNames, character->alternateNamesCount);
    if (character->alternateActors)
        free_string_array(character->alternateActors, character->alternateActorsCount);

    // Libera o próprio objeto Character
    free(character);
}


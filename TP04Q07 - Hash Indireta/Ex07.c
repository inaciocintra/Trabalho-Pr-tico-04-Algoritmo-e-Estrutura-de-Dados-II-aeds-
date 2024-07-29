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
    Character *character;
    struct No *proximo;
} No;

typedef struct ListaEncadeada {
    No *cabeca;
} ListaEncadeada;

typedef struct TabelaHash {
    ListaEncadeada *tabela;
    int tamanho;
} TabelaHash;


No* criarNo(Character *character) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->character = character;
    novoNo->proximo = NULL;
    return novoNo;
}

ListaEncadeada* criarListaEncadeada() {
    ListaEncadeada *lista = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
    lista->cabeca = NULL;
    return lista;
}

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash *tabelaHash = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabelaHash->tamanho = tamanho;
    tabelaHash->tabela = (ListaEncadeada*)malloc(tamanho * sizeof(ListaEncadeada));
    for (int i = 0; i < tamanho; i++) {
        tabelaHash->tabela[i] = *criarListaEncadeada();
    }
    return tabelaHash;
}

int h(char *nome, int tamanhoTabela) {
    int valorHash = 0;
    int somaAscii = 0;
    for (int i = 0; i < strlen(nome); i++) {
        somaAscii += nome[i];
    }
    valorHash = (somaAscii) % tamanhoTabela;
    return valorHash;
}

int h2(Character *character, int tamanhoTabela){
    int valordoHash = 0;
    int resultadoAscii = 0;
    char nome[30];
    strcpy(nome,character->name);
    for (int i = 0; i < strlen(nome); i++) {
        resultadoAscii += nome[i];
    }
    valordoHash = (resultadoAscii) % tamanhoTabela;
    return valordoHash;
}

void inserir(TabelaHash *tabelaHash, Character *character) {
    int indice = h(character->name, tabelaHash->tamanho);
    No *novoNo = criarNo(character);

    // Inserir no início da lista encadeada
    novoNo->proximo = tabelaHash->tabela[indice].cabeca;
    tabelaHash->tabela[indice].cabeca = novoNo;
}

int pesquisar(TabelaHash *tabelaHash, char *nome) {
    bool cond = false;
    int resp = -1;
    int indice = h(nome, tabelaHash->tamanho);
    No *atual = tabelaHash->tabela[indice].cabeca;

    while (atual != NULL) {
        if (strcmp(atual->character->name, nome) == 0) {
            cond = true;
            resp = indice;
            return resp;
        }
        atual = atual->proximo;
    }
    return resp;
}

// Função principal que lê o arquivo CSV, processa cada linha, ordena e imprime personagens
int main(void) {
    
    // ArvoreAVL* arvore = criarArvoreAVL();
    TabelaHash *tabelinha = criarTabelaHash(21);
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
            //adiciona o personagem tabela
            inserir(tabelinha,character);
        } else {
            free_character(character); // Libera a memória se o personagem não for adicionado
        }
        }
    //le dnv
    scanf("%s",codigo);
    // Fecha o arquivo após a leitura
    fclose(file);
    }
    


    while (scanf(" %[^\r\n]", nomepersonagem))
    {
       
        if (strncmp(nomepersonagem, "FIM", 3) == 0) {
            break; // Sair do loop se a entrada for "FIM"
        }
    int resp = -1;
    printf("%s",nomepersonagem);
    resp = pesquisar(tabelinha, nomepersonagem);
    
    if(resp != -1){
    printf(" (pos: %d) SIM\n",resp);
    }
    else{
    printf(" NAO\n");
    }
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


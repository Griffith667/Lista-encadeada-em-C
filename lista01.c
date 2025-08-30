#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
  char nome[60];
  float nota1;
  float nota2;
  int nota3;
  struct Aluno *next;
}Aluno;

int length = 0;

void menu();
void insertStart( Aluno **sPtr, char nome[], float n1, float n2, float n3 );
void insertEnd( Aluno **sPtr, char nome[], float n1, float n2, float n3 );
void insertAny( Aluno **sPtr, char nome[], float n1, float n2, float n3, int lugar );
void Delete( Aluno **sPtr, char nome[] );
void printList( Aluno *currentPtr );

int main(void)
{
  int escolha, lugar;
  float x, y, z;
  char nome[60];

  Aluno *startPtr = NULL;

  menu();
  printf("? ");
  scanf("%d", &escolha);

  while ( escolha != 5 ) {
    switch ( escolha ) {
      case 1: 
        printf("Insira o nome do aluno: ");
        while (getchar() != '\n');
        fgets( nome, 60, stdin );
        nome[strcspn(nome, "\n")] = '\0';

        printf("Insira três notas: ");
        scanf(" %f%f%f", &x, &y, &z);
        printf("\n");
        insertStart(&startPtr, nome, x, y, z);
        printList(startPtr);
        break;
      case 2:
        printf("Insira o nome do aluno: ");
        while (getchar() != '\n');
        fgets( nome, 60, stdin );
        nome[strcspn(nome, "\n")] = '\0';

        printf("Insira três notas: ");
        scanf(" %f%f%f", &x, &y, &z);
        printf("\n");
        insertEnd(&startPtr, nome, x, y, z);
        printList(startPtr);
        break;
      case 3:
        printf("Insira o nome do aluno: ");
        while (getchar() != '\n');
        fgets( nome, 60, stdin );
        nome[strcspn(nome, "\n")] = '\0';

        printf("Insira três notas: ");
        scanf(" %f%f%f", &x, &y, &z);
        printf("\n");
        while (getchar() != '\n');
        printf("comprimento atual da lista: %d\n", length);
        printf("Número do lugar(0 para inserir no início): ");
        scanf("%d", &lugar);

        insertAny(&startPtr, nome, x, y, z, lugar);
        printList(startPtr);
        break;
      case 4:
        if ( startPtr == NULL ) {
          printf("Lista vazia.\n");
          break;
        }
        printf("Digite o nome do aluno a ser removido: ");
        while (getchar() != '\n');
        fgets(nome, 60, stdin);
        nome[strcspn(nome, "\n")] = '\0';
        Delete(&startPtr, nome);

        printf("\n");
        printList(startPtr);
        break;
      default:
        printf("Opção inválida.\n\n");
        break;
    }
    printf("? ");
    scanf("%d", &escolha);
  }

  printf("Programa finalizado.\n");
  return 0;
}

void menu(){
  printf("1. Para inserir no começo.\n");
  printf("2. Para inserir no final.\n");
  printf("3. Para inserir em um lugar específico.\n");
  printf("4. Para remover elemento da lista.\n");
  printf("5. Para finalizar o programa.\n\n");
}

void insertStart( Aluno **sPtr, char nome[], float n1, float n2, float n3 ){
  Aluno *newPtr = malloc(sizeof(Aluno)); // aloca memória do tamanho da struct Aluno para um ponteiro que aponta para Aluno 

  if ( newPtr != NULL ){            // se houver espaço
    strcpy(newPtr->nome, nome); // função que copia string 
    newPtr->nota1 = n1;         // 
    newPtr->nota2 = n2;         //  
    newPtr->nota3 = n3;         // coloca o nome e as notas nos campos 

    newPtr->next = *sPtr;  // O próximo do novo ponteiro é a coisa apontada pelo ponteiro startPtr
    *sPtr = newPtr; // O startPtr agora aponta para o novo nó
    length++; // contador de elementos da lista incrementado
  }
  else {
    printf("Sem memória disponível.\n\n");
  }
}

void printList( Aluno *currentPtr ){
  while ( currentPtr != NULL ) {
    printf("Nome do aluno: %s\nNota 1: %.1f\nNota 2: %.1f\nNota 3: %.1f\n\n", currentPtr->nome, currentPtr->nota1, 
           currentPtr->nota2, currentPtr->nota3);
    currentPtr = currentPtr->next;
  }
}

void insertEnd( Aluno **sPtr, char nome[], float n1, float n2, float n3 ){
  Aluno *newPtr = malloc(sizeof(Aluno)); 

  if ( newPtr != NULL ){ // se houver espaço
    strcpy(newPtr->nome, nome);
    newPtr->nota1 = n1;
    newPtr->nota2 = n2;
    newPtr->nota3 = n3;

    newPtr->next = NULL; // O próximo do novo nó é NULL

    Aluno *auxiliar = *sPtr; // Ponteiro para struct Aluno que aponta para o primeiro elemento da lista

    while ( auxiliar->next != NULL ) {  // loop para encontrar o atual último elemento da lista
      auxiliar = auxiliar->next;
    }
    auxiliar->next = newPtr; // O novo nó agora vira o último

    length++;
  }
  else {
    printf("Sem memória disponível\n\n");
  }
}

void insertAny( Aluno **sPtr, char nome[], float n1, float n2, float n3, int lugar ){
  Aluno *newPtr = malloc(sizeof(Aluno));

  if ( newPtr != NULL ) {
    strcpy(newPtr->nome, nome);
    newPtr->nota1 = n1;
    newPtr->nota2 = n2;
    newPtr->nota3 = n3;

    if ( lugar > length || lugar < 0 ) {  // Não pode ser inserido em lugares inexistentes 
      printf("Valor inválido.\n\n");
    }
    else {
      if ( lugar == 0 ){ // Se o lugar for zero, é a mesma coisa que colocar no início
        newPtr->next = *sPtr;
        *sPtr = newPtr;
      }
      else {
        Aluno *auxiliar = *sPtr;
        int i = 0;

        while ( i != lugar - 1 ) { // localiza o elemento anterior do que será substituído
          auxiliar = auxiliar->next;
          i++;
        }
        newPtr->next = auxiliar->next; // coloca o elemento a ser substituído como próximo do novo elemento
        auxiliar->next = newPtr; // coloca o novo elemento no lugar do elemento selecionado
      }
      length++;
    }
  }
  else {
    printf("Sem memória disponível\n\n");
  }
}

void Delete( Aluno **sPtr, char nome[] ){ 
  Aluno *currentPtr;
  Aluno *previousPtr;
  Aluno *tempPtr;

  if ( strcmp((*sPtr)->nome, nome) == 0 ) { // se o aluno a ser removido da lista for o primeiro (strcmp retorna 0 se as strings forem iguais)
    tempPtr = *sPtr; // o primeiro elemento apontado por sPtr vai pra temp 
    *sPtr = (*sPtr)->next; // o próximo elemento vira o primeiro
    free(tempPtr); // libera memória
    length--; // diminui o contador de elementos da lista
  }
  else {
    previousPtr = *sPtr; // anterior é o primeiro elemento
    currentPtr = (*sPtr)->next; // elemento atual é o próximo do primeiro

    while ( currentPtr != NULL && strcmp(currentPtr->nome, nome) != 0 ) { // enquanto o atual não for NULL e o nome do atual for diferente do nome passado pelo usuário
      previousPtr = currentPtr;       //
      currentPtr = currentPtr->next;  // caminha a lista colocando o atual no anterior, e o próximo do atual no atual 
    }                                 //

    if ( currentPtr != NULL ) {
      tempPtr = currentPtr;
      previousPtr->next = currentPtr->next; // coloca o próximo do atual no lugar dele
      free(tempPtr);
    }
    length--;
  }
}

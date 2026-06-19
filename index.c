#include <stdio.h> //biblioteca para entrada e saida de dados
#include <stdlib.h> //biblioteca para chamadas no sistema e gerenciamento de memória

#define TAM_ISBN 30
#define TAM_TITULO 50
#define TAM_AUTOR 50
#define TAM_PUBLICADOR 50
#define TAM_CATEGORIA 30
#define TAM_LOCALIZACAO 20

typedef struct {
  char isbn[TAM_ISBN];
  char titulo[TAM_TITULO];
  char autor[TAM_AUTOR];
  char publicador[TAM_PUBLICADOR];
  char categoria[TAM_CATEGORIA];
  int anoPublicacao;
  int quantidadeDisponivel;
  int totalCopias;
  char localizacao[TAM_LOCALIZACAO];
} Livro;

void menuInicial() {
  printf("\
╔════════════════════════════════════════════════╗\n\
║ Bem vindo ao sistema de gestão de bibliotecas  ║\n\
╠════════════════════════════════════════════════╣\n\
║ 1. Entrar como administrador                   ║\n\
║ 2. Entrar como bibliotecário                   ║\n\
║ 3. Entrar como leitor                          ║\n\
╚════════════════════════════════════════════════╝\
  ");
}

int main() {
  menuInicial();


  printf("\n\nObrigado por usar sistema de gestao de bibliotecas!");

  return 0;
}
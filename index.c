#include <stdio.h> //biblioteca para entrada e saida de dados
#include <stdlib.h> //biblioteca para chamadas no sistema e gerenciamento de memória

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
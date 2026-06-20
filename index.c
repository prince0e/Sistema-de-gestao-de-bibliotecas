#include <stdio.h> //biblioteca para entrada e saida de dados
#include <stdlib.h> //biblioteca para chamadas no sistema e gerenciamento de memória

//Macros para definir os tamanhos dos campos do struct Livro
#define TAM_ISBN 30
#define TAM_TITULO 50
#define TAM_AUTOR 50
#define TAM_PUBLICADOR 50
#define TAM_CATEGORIA 30
#define TAM_LOCALIZACAO 20

//Macros para definir os tamanhos dos campos do struct Usuario
#define TAM_ID 20
#define TAM_NOME 50
#define TAM_EMAIL 50
#define TAM_SENHA 20


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

typedef struct {
	char id[TAM_ID];
	char nome[TAM_NOME];
	char email[TAM_EMAIL];
	char senha[TAM_SENHA];
} Usuario;

Usuario* encontrarUsuarioPeloId() {
	char id[TAM_ID];
	printf("Digite o ID:");
	fgets()
}

void menuInicial() {
	printf("\
╔════════════════════════════════════════════════╗\n\
║ Bem vindo ao sistema de gestão de bibliotecas  ║\n\
╚════════════════════════════════════════════════╝\
		");
}

int main() {
	menuInicial();


	printf("\n\nObrigado por usar sistema de gestao de bibliotecas!");

	return 0;
}
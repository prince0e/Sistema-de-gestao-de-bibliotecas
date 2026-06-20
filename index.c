// sistema_biblioteca.h - Arquivo de cabeçalho principal
#ifndef SISTEMA_BIBLIOTECA_H
#define SISTEMA_BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Constantes para livros
#define MAX_ISBN 30
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_EDITORA 50
#define MAX_CATEGORIA 30
#define MAX_LOCALIZACAO 20

//Constantes para usuários
#define MAX_ID 20
#define MAX_NOME 50
#define MAX_EMAIL 50
#define MAX_TELEFONE 15

//Outras constantes
#define MAX_LIVROS 1000
#define MAX_USUARIOS 500
#define MAX_EMPRESTIMOS 1000
#define MAX_RESERVAS 200
#define MULTA_POR_DIA 50
#define DIAS_DE_EMPRESTIMO 14
#define MAX_RENOVACOES 2
#define MAX_EMPRESTIMOS_POR_USUARIO 5

// Estrutura de data
typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

// Estrutura de livro
typedef struct {
	char isbn[MAX_ISBN];
	char titulo[MAX_TITULO];
	char autor[MAX_AUTOR];
	char editora[MAX_EDITORA];
	char categoria[MAX_CATEGORIA];
	int anoPublicacao;
	int totalCopias;
	int copiasDisponiveis;
	char localizacao[MAX_LOCALIZACAO];
	int estaAtivo; // 1 se ativo, 0 se excluído
} Livro;

// Estrutura de usuário
typedef struct {
	char id[MAX_ID];
	char nome[MAX_NOME];
	char email[MAX_EMAIL];
	char telefone[MAX_TELEFONE];
	char papel[14]; // "admin", "bibliotecario", "leitor"
	int contadorEmprestimos;
	char historicoEmprestimos[50][MAX_ISBN]; // Armazena ISBNs dos livros emprestados
	int estaAtivo;
	float multasTotais;
} Usuario;

// Estrutura de empréstimo
typedef struct {
	int idEmprestimo;
	char idUsuario[MAX_ID];
	char isbn[MAX_ISBN];
	Data dataEmprestimo;
	Data dataVencimento;
	Data dataDevolucao;
	int foiDevolvido;
	int renovacoesUtilizadas;
	float valorMulta;
	int estaAtivo;
} Emprestimo;

// Estrutura de reserva
typedef struct {
	int idReserva;
	char idUsuario[MAX_ID];
	char isbn[MAX_ISBN];
	Data dataReserva;
	int estaAtivo;
	int foiAtendida;
} Reserva;

// Declarações de funções para Gerenciamento de Livros
void inicializarLivros(Livro livros[], int *contador);
int adicionarLivro(Livro livros[], int *contador);
int atualizarLivro(Livro livros[], int contador);
int excluirLivro(Livro livros[], int contador);
void exibirLivro(const Livro *livro);
void exibirTodosLivros(const Livro livros[], int contador);
int encontrarLivroPorISBN(const Livro livros[], int contador, const char *isbn);
void pesquisarLivros(const Livro livros[], int contador);

// Declarações de funções para Gerenciamento de Usuários
void inicializarUsuarios(Usuario usuarios[], int *contador);
int registrarUsuario(Usuario usuarios[], int *contador, const char *papel);
int atualizarUsuario(Usuario usuarios[], int contador);
int excluirUsuario(Usuario usuarios[], int contador);
void exibirUsuario(const Usuario *usuario);
void exibirTodosUsuarios(const Usuario usuarios[], int contador);
int encontrarUsuarioPorId(const Usuario usuarios[], int contador, const char *id);
Usuario* autenticarUsuario(Usuario usuarios[], int contador);

// Declarações de funções para Operações de Empréstimo
void inicializarEmprestimos(Emprestimo emprestimos[], int *contador);
int emprestarLivro(Emprestimo emprestimos[], int *contadorEmprestimos, Livro livros[], int contadorLivros,
	Usuario usuarios[], int contadorUsuarios, Reserva reservas[], int *contadorReservas);
int devolverLivro(Emprestimo emprestimos[], int contadorEmprestimos, Livro livros[], int contadorLivros,
	Usuario usuarios[], int contadorUsuarios);
int renovarLivro(Emprestimo emprestimos[], int contadorEmprestimos, Livro livros[], int contadorLivros);
void calcularMulta(Emprestimo *emprestimo);
void exibirEmprestimosAtivos(const Emprestimo emprestimos[], int contador, const Livro livros[], int contadorLivros);
void exibirEmprestimosUsuario(const Emprestimo emprestimos[], int contador, const char *idUsuario,
	const Livro livros[], int contadorLivros);

// Declarações de funções para Reservas
void inicializarReservas(Reserva reservas[], int *contador);
int fazerReserva(Reserva reservas[], int *contador, const char *idUsuario,
	const Livro livros[], int contadorLivros);
void visualizarReservas(const Reserva reservas[], int contador, const char *idUsuario,
	const Livro livros[], int contadorLivros);

// Declarações de funções para Relatórios
void gerarRelatorioMaisEmprestados(const Emprestimo emprestimos[], int contadorEmprestimos,
	const Livro livros[], int contadorLivros);
void gerarRelatorioLivrosDisponiveis(const Livro livros[], int contador);
void gerarRelatorioLivrosAtrasados(const Emprestimo emprestimos[], int contadorEmprestimos,
	const Livro livros[], int contadorLivros);
void gerarRelatorioMultas(const Emprestimo emprestimos[], int contadorEmprestimos, const Usuario usuarios[], int contadorUsuarios);
void gerarEstatisticasUso(const Emprestimo emprestimos[], int contadorEmprestimos);

// Funções utilitárias
Data obterDataAtual();
int diasEntre(Data d1, Data d2);
int ehDataValida(Data d);
int compararDatas(Data d1, Data d2);
void limparBufferEntrada();
void paraMinusculas(char *str);
void imprimirSeparador();
void pausarTela();

// Funções de menu
void menuAdmin(Usuario *usuarioAtual, Livro livros[], int *contadorLivros, Usuario usuarios[], int *contadorUsuarios,
	Emprestimo emprestimos[], int *contadorEmprestimos, Reserva reservas[], int *contadorReservas);
void menuBibliotecario(Usuario *usuarioAtual, Livro livros[], int *contadorLivros, Usuario usuarios[], int *contadorUsuarios,
	Emprestimo emprestimos[], int *contadorEmprestimos, Reserva reservas[], int *contadorReservas);
void menuLeitor(Usuario *usuarioAtual, Livro livros[], int contadorLivros, Emprestimo emprestimos[], int contadorEmprestimos,
	Reserva reservas[], int *contadorReservas);

#endif

// sistema_biblioteca.c - Arquivo de implementação principal
//#include "sistema_biblioteca.h"

// ==================== FUNÇÕES UTILITÁRIAS ====================

Data obterDataAtual() {
	Data hoje;
	time_t t = time(NULL);
	struct tm *tm_info = localtime(&t);

	hoje.dia = tm_info->tm_mday;
	hoje.mes = tm_info->tm_mon + 1;
	hoje.ano = tm_info->tm_year + 1900;

	return hoje;
}

int diasEntre(Data d1, Data d2) {
	// Converte datas para dias desde a época para comparação
	struct tm data1 = {
		0
	},
	data2 = {
		0
	};

	data1.tm_mday = d1.dia;
	data1.tm_mon = d1.mes - 1;
	data1.tm_year = d1.ano - 1900;

	data2.tm_mday = d2.dia;
	data2.tm_mon = d2.mes - 1;
	data2.tm_year = d2.ano - 1900;

	time_t tempo1 = mktime(&data1);
	time_t tempo2 = mktime(&data2);

	double diferenca = difftime(tempo2, tempo1);
	return (int)(diferenca / (60 * 60 * 24));
}

int ehDataValida(Data d) {
	if (d.ano < 1900 || d.ano > 2100) return 0;
	if (d.mes < 1 || d.mes > 12) return 0;
	if (d.dia < 1) return 0;

	int diasNoMes[] = {
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};

	// Ajuste para ano bissexto
	if ((d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0))
	diasNoMes[1] = 29;

	if (d.dia > diasNoMes[d.mes - 1]) return 0;

	return 1;
}

int compararDatas(Data d1, Data d2) {
	if (d1.ano != d2.ano) return d1.ano - d2.ano;
	if (d1.mes != d2.mes) return d1.mes - d2.mes;
	return d1.dia - d2.dia;
}

void limparBufferEntrada() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void paraMinusculas(char *str) {
	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
}

void imprimirSeparador() {
	printf("\n========================================\n");
}

void pausarTela() {
	printf("\nPressione Enter para continuar...");
	limparBufferEntrada();
	printf("\n");
}

// ==================== GERENCIAMENTO DE LIVROS ====================

void inicializarLivros(Livro livros[], int *contador) {
	*contador = 0;
	// Adiciona alguns livros de exemplo
	Livro livrosExemplo[] = {
		{
			"978-0-7475-3269-9",
			"Harry Potter e a Pedra Filosofal",
			"J.K. Rowling",
			"Bloomsbury",
			"Fantasia",
			1997,
			5,
			5,
			"A1-Prateleira1",
			1
		},
		{
			"978-0-316-76948-0",
			"O Apanhador no Campo de Centeio",
			"J.D. Salinger",
			"Little, Brown",
			"Ficção",
			1951,
			3,
			3,
			"A1-Prateleira2",
			1
		},
		{
			"978-0-06-112008-4",
			"O Sol é para Todos",
			"Harper Lee",
			"J.B. Lippincott",
			"Ficção",
			1960,
			4,
			4,
			"A2-Prateleira1",
			1
		},
		{
			"978-1-4516-4553-3",
			"A Arte da Programação de Computadores",
			"Donald Knuth",
			"Addison-Wesley",
			"Tecnologia",
			1968,
			2,
			2,
			"B1-Prateleira1",
			1
		},
		{
			"978-0-306-40615-7",
			"O Gene Egoísta",
			"Richard Dawkins",
			"Oxford University Press",
			"Ciência",
			1976,
			3,
			3,
			"B2-Prateleira1",
			1
		}
	};

	for (int i = 0; i < 5; i++) {
		livros[(*contador)++] = livrosExemplo[i];
	}
}

int adicionarLivro(Livro livros[], int *contador) {
	if (*contador >= MAX_LIVROS) {
		printf("Erro: Limite máximo de livros atingido!\n");
		return 0;
	}

	Livro novoLivro;
	printf("\n--- Adicionar Novo Livro ---\n");

	printf("Digite o ISBN (13 dígitos): ");
	fgets(novoLivro.isbn, MAX_ISBN, stdin);
	novoLivro.isbn[strcspn(novoLivro.isbn, "\n")] = 0;

	// Verifica ISBN duplicado
	if (encontrarLivroPorISBN(livros, *contador, novoLivro.isbn) != -1) {
		printf("Erro: Já existe um livro com este ISBN!\n");
		return 0;
	}

	printf("Digite o Título: ");
	fgets(novoLivro.titulo, MAX_TITULO, stdin);
	novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = 0;

	printf("Digite o(s) Autor(es): ");
	fgets(novoLivro.autor, MAX_AUTOR, stdin);
	novoLivro.autor[strcspn(novoLivro.autor, "\n")] = 0;

	printf("Digite a Editora: ");
	fgets(novoLivro.editora, MAX_EDITORA, stdin);
	novoLivro.editora[strcspn(novoLivro.editora, "\n")] = 0;

	printf("Digite a Categoria/Gênero: ");
	fgets(novoLivro.categoria, MAX_CATEGORIA, stdin);
	novoLivro.categoria[strcspn(novoLivro.categoria, "\n")] = 0;

	printf("Digite o Ano de Publicação: ");
	scanf("%d", &novoLivro.anoPublicacao);
	limparBufferEntrada();

	printf("Digite o Total de Cópias: ");
	scanf("%d", &novoLivro.totalCopias);
	limparBufferEntrada();
	novoLivro.copiasDisponiveis = novoLivro.totalCopias;

	printf("Digite a Localização Física (ex: A1-Prateleira3): ");
	fgets(novoLivro.localizacao, MAX_LOCALIZACAO, stdin);
	novoLivro.localizacao[strcspn(novoLivro.localizacao, "\n")] = 0;

	novoLivro.estaAtivo = 1;

	livros[*contador] = novoLivro;
	(*contador)++;

	printf("Livro adicionado com sucesso!\n");
	return 1;
}

int atualizarLivro(Livro livros[], int contador) {
	char isbn[MAX_ISBN];
	printf("\n--- Atualizar Informações do Livro ---\n");
	printf("Digite o ISBN do livro a ser atualizado: ");
	fgets(isbn, MAX_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	int indice = encontrarLivroPorISBN(livros, contador, isbn);
	if (indice == -1) {
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	printf("\nDetalhes Atuais do Livro:\n");
	exibirLivro(&livros[indice]);

	printf("\nDigite as novas informações (pressione Enter para manter o valor atual):\n");

	char entrada[MAX_TITULO];

	printf("Novo Título [%s]: ", livros[indice].titulo);
	fgets(entrada, MAX_TITULO, stdin);
	if (strlen(entrada) > 1) {
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livros[indice].titulo, entrada);
	}

	printf("Novo Autor [%s]: ", livros[indice].autor);
	fgets(entrada, MAX_AUTOR, stdin);
	if (strlen(entrada) > 1) {
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livros[indice].autor, entrada);
	}

	printf("Nova Editora [%s]: ", livros[indice].editora);
	fgets(entrada, MAX_EDITORA, stdin);
	if (strlen(entrada) > 1) {
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livros[indice].editora, entrada);
	}

	printf("Nova Categoria [%s]: ", livros[indice].categoria);
	fgets(entrada, MAX_CATEGORIA, stdin);
	if (strlen(entrada) > 1) {
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livros[indice].categoria, entrada);
	}

	printf("Nova Localização [%s]: ", livros[indice].localizacao);
	fgets(entrada, MAX_LOCALIZACAO, stdin);
	if (strlen(entrada) > 1) {
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livros[indice].localizacao, entrada);
	}

	printf("Novo Total de Cópias [%d]: ", livros[indice].totalCopias);
	fgets(entrada, 10, stdin);
	if (strlen(entrada) > 1) {
		int novoTotal = atoi(entrada);
		if (novoTotal >= livros[indice].totalCopias - livros[indice].copiasDisponiveis) {
			int emprestados = livros[indice].totalCopias - livros[indice].copiasDisponiveis;
			livros[indice].totalCopias = novoTotal;
			livros[indice].copiasDisponiveis = novoTotal - emprestados;
		} else {
			printf("Erro: Não é possível reduzir as cópias abaixo da quantidade atualmente emprestada!\n");
		}
	}

	printf("Livro atualizado com sucesso!\n");
	return 1;
}

int excluirLivro(Livro livros[], int contador) {
	char isbn[MAX_ISBN];
	printf("\n--- Excluir Livro ---\n");
	printf("Digite o ISBN do livro a ser excluído: ");
	fgets(isbn, MAX_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	int indice = encontrarLivroPorISBN(livros, contador, isbn);
	if (indice == -1) {
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	// Verifica se o livro está emprestado atualmente
	if (livros[indice].copiasDisponiveis < livros[indice].totalCopias) {
		printf("Erro: Não é possível excluir um livro que está emprestado!\n");
		return 0;
	}

	livros[indice].estaAtivo = 0;
	printf("Livro excluído com sucesso!\n");
	return 1;
}

void exibirLivro(const Livro *livro) {
	printf("\nISBN: %s\n", livro->isbn);
	printf("Título: %s\n", livro->titulo);
	printf("Autor(es): %s\n", livro->autor);
	printf("Editora: %s\n", livro->editora);
	printf("Categoria: %s\n", livro->categoria);
	printf("Ano de Publicação: %d\n", livro->anoPublicacao);
	printf("Cópias Disponíveis: %d/%d\n", livro->copiasDisponiveis, livro->totalCopias);
	printf("Localização: %s\n", livro->localizacao);
}

void exibirTodosLivros(const Livro livros[], int contador) {
	if (contador == 0) {
		printf("\nNão há livros na biblioteca.\n");
		return;
	}

	printf("\n--- Catálogo da Biblioteca ---\n");
	printf("%-15s %-30s %-20s %-10s %s\n", "ISBN", "Título", "Autor", "Disponíveis", "Localização");
	imprimirSeparador();

	for (int i = 0; i < contador; i++) {
		if (livros[i].estaAtivo) {
			printf("%-15s %-30s %-20s %d/%-9d %s\n",
				livros[i].isbn, livros[i].titulo, livros[i].autor,
				livros[i].copiasDisponiveis, livros[i].totalCopias, livros[i].localizacao);
		}
	}
}

int encontrarLivroPorISBN(const Livro livros[], int contador, const char *isbn) {
	for (int i = 0; i < contador; i++) {
		if (livros[i].estaAtivo && strcmp(livros[i].isbn, isbn) == 0) {
			return i;
		}
	}
	return -1;
}

void pesquisarLivros(const Livro livros[], int contador) {
	int opcao;
	printf("\n\
--- Pesquisar Livros ---\n\
1. Pesquisar por Título\n\
2. Pesquisar por Autor\n\
3. Pesquisar por ISBN\n\
4. Pesquisar por Categoria\n\
Digite a opção: \
		");
	scanf("%d", &opcao);
	limparBufferEntrada();

	char termoBusca[MAX_TITULO];
	int encontrados = 0;

	switch(opcao) {
		case 1:
		printf("Digite o título para pesquisar: ");
		fgets(termoBusca, MAX_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;
		paraMinusculas(termoBusca);

		printf("\nResultados da Pesquisa:\n");
		for (int i = 0; i < contador; i++) {
			if (livros[i].estaAtivo) {
				char tituloCopia[MAX_TITULO];
				strcpy(tituloCopia, livros[i].titulo);
				paraMinusculas(tituloCopia);
				if (strstr(tituloCopia, termoBusca) != NULL) {
					exibirLivro(&livros[i]);
					encontrados = 1;
				}
			}
		}
		break;

		case 2:
		printf("Digite o autor para pesquisar: ");
		fgets(termoBusca, MAX_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;
		paraMinusculas(termoBusca);

		printf("\nResultados da Pesquisa:\n");
		for (int i = 0; i < contador; i++) {
			if (livros[i].estaAtivo) {
				char autorCopia[MAX_AUTOR];
				strcpy(autorCopia, livros[i].autor);
				paraMinusculas(autorCopia);
				if (strstr(autorCopia, termoBusca) != NULL) {
					exibirLivro(&livros[i]);
					encontrados = 1;
				}
			}
		}
		break;

		case 3:
		printf("Digite o ISBN: ");
		fgets(termoBusca, MAX_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;

		printf("\nResultado da Pesquisa:\n");
		for (int i = 0; i < contador; i++) {
			if (livros[i].estaAtivo && strcmp(livros[i].isbn, termoBusca) == 0) {
				exibirLivro(&livros[i]);
				encontrados = 1;
				break;
			}
		}
		break;

		case 4:
		printf("Digite a categoria para filtrar: ");
		fgets(termoBusca, MAX_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;
		paraMinusculas(termoBusca);

		printf("\nLivros na categoria '%s':\n", termoBusca);
		for (int i = 0; i < contador; i++) {
			if (livros[i].estaAtivo) {
				char catCopia[MAX_CATEGORIA];
				strcpy(catCopia, livros[i].categoria);
				paraMinusculas(catCopia);
				if (strstr(catCopia, termoBusca) != NULL) {
					exibirLivro(&livros[i]);
					encontrados = 1;
				}
			}
		}
		break;

		default:
		printf("Opção inválida!\n");
		return;
	}

	if (!encontrados) {
		printf("Nenhum livro encontrado com os critérios de pesquisa.\n");
	}
}

//GERENCIAMENTO DE USUÁRIOS

void inicializarUsuarios(Usuario usuarios[], int *contador) {
	*contador = 0;

	// Adiciona usuário administrador padrão
	Usuario admin = {
		"ADMIN001",
		"Administrador do Sistema",
		"admin@biblioteca.com",
		"123-456-7890",
		"admin",
		0,
		{
			""
		},
		1,
		0.0
	};
	usuarios[(*contador)++] = admin;

	// Adiciona bibliotecário padrão
	Usuario bibliotecario = {
		"BIB001",
		"João Bibliotecário",
		"joao@biblioteca.com",
		"123-456-7891",
		"bibliotecario",
		0,
		{
			""
		},
		1,
		0.0
	};
	usuarios[(*contador)++] = bibliotecario;

	// Adiciona leitores de exemplo
	Usuario leitor1 = {
		"LEIT001",
		"Alice Leitora",
		"alice@email.com",
		"123-456-7892",
		"leitor",
		0,
		{
			""
		},
		1,
		0.0
	};
	usuarios[(*contador)++] = leitor1;

	Usuario leitor2 = {
		"LEIT002",
		"Bob Leitor",
		"bob@email.com",
		"123-456-7893",
		"leitor",
		0,
		{
			""
		},
		1,
		0.0
	};
	usuarios[(*contador)++] = leitor2;
}

int registrarUsuario(Usuario usuarios[], int *contador, const char *papel) {
	if (*contador >= MAX_USUARIOS) {
		printf("Erro: Limite máximo de usuários atingido!\n");
		return 0;
	}

	Usuario novoUsuario;
	printf("\n--- Registrar Novo Usuário ---\n");

	printf("Digite o ID: ");
	fgets(novoUsuario.id, MAX_ID, stdin);
	novoUsuario.id[strcspn(novoUsuario.id, "\n")] = 0;

	if (encontrarUsuarioPorId(usuarios, *contador, novoUsuario.id) != -1) {
		printf("Erro: ID de usuário já existe!\n");
		return 0;
	}

	printf("Digite o Nome: ");
	fgets(novoUsuario.nome, MAX_NOME, stdin);
	novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0;

	printf("Digite o Email: ");
	fgets(novoUsuario.email, MAX_EMAIL, stdin);
	novoUsuario.email[strcspn(novoUsuario.email, "\n")] = 0;

	printf("Digite o Telefone: ");
	fgets(novoUsuario.telefone, MAX_TELEFONE, stdin);
	novoUsuario.telefone[strcspn(novoUsuario.telefone, "\n")] = 0;

	strcpy(novoUsuario.papel, papel);
	novoUsuario.contadorEmprestimos = 0;
	novoUsuario.estaAtivo = 1;
	novoUsuario.multasTotais = 0.0;

	usuarios[*contador] = novoUsuario;
	(*contador)++;

	printf("Usuário registrado com sucesso!\n");
	return 1;
}

void exibirUsuario(const Usuario *usuario) {
	printf("\nID do Usuário: %s\n", usuario->id);
	printf("Nome: %s\n", usuario->nome);
	printf("Email: %s\n", usuario->email);
	printf("Telefone: %s\n", usuario->telefone);
	printf("Papel: %s\n", usuario->papel);
	printf("Empréstimos Ativos: %d\n", usuario->contadorEmprestimos);
	printf("Multas Totais: R$%.2f\n", usuario->multasTotais);
}

//Função para encontrar usuário pelo ID
int encontrarUsuarioPorId(const Usuario usuarios[], int contador, const char *id) {
	for (int i = 0; i < contador; i++) {
		if (usuarios[i].estaAtivo && strcmp(usuarios[i].id, id) == 0) {
			return i;
		}
	}
	return -1;
}

Usuario* autenticarUsuario(Usuario usuarios[], int contador) {
	char idUsuario[MAX_ID];
	printf("\n--- Login no Sistema da Biblioteca ---\n");
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, MAX_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	int indice = encontrarUsuarioPorId(usuarios, contador, idUsuario);
	if (indice != -1) {
		printf("Bem-vindo, %s!\n", usuarios[indice].nome);
		return &usuarios[indice];
	}

	printf("Erro: Usuário não encontrado!\n");
	return NULL;
}

//OPERAÇÕES DE EMPRÉSTIMO

void inicializarEmprestimos(Emprestimo emprestimos[], int *contador) {
	*contador = 0;
}

int emprestarLivro(Emprestimo emprestimos[], int *contadorEmprestimos, Livro livros[], int contadorLivros,
	Usuario usuarios[], int contadorUsuarios, Reserva reservas[], int *contadorReservas) {
	if (*contadorEmprestimos >= MAX_EMPRESTIMOS) {
		printf("Erro: Limite máximo de empréstimos atingido!\n");
		return 0;
	}

	printf("\n--- Emprestar Livro ---\n");

	char idUsuario[MAX_ID];
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, MAX_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	int indiceUsuario = encontrarUsuarioPorId(usuarios, contadorUsuarios, idUsuario);
	if (indiceUsuario == -1) {
		printf("Erro: Usuário não encontrado!\n");
		return 0;
	}

	if (usuarios[indiceUsuario].contadorEmprestimos >= MAX_EMPRESTIMOS_POR_USUARIO) {
		printf("Erro: Usuário atingiu o limite máximo de empréstimos (%d)!\n", MAX_EMPRESTIMOS_POR_USUARIO);
		return 0;
	}

	char isbn[MAX_ISBN];
	printf("Digite o ISBN do Livro: ");
	fgets(isbn, MAX_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, isbn);
	if (indiceLivro == -1) {
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	if (livros[indiceLivro].copiasDisponiveis <= 0) {
		printf("Livro está atualmente indisponível.\n");
		printf("Deseja fazer uma reserva? (1=Sim, 0=Não): ");
		int opcao;
		scanf("%d", &opcao);
		limparBufferEntrada();
		if (opcao == 1) {
			fazerReserva(reservas, contadorReservas, idUsuario, livros, contadorLivros);
		}
		return 0;
	}

	// Cria registro de empréstimo
	Emprestimo novoEmprestimo;
	novoEmprestimo.idEmprestimo = *contadorEmprestimos + 1;
	strcpy(novoEmprestimo.idUsuario, idUsuario);
	strcpy(novoEmprestimo.isbn, isbn);
	novoEmprestimo.dataEmprestimo = obterDataAtual();

	// Define data de vencimento (14 dias a partir da data de empréstimo)
	novoEmprestimo.dataVencimento = novoEmprestimo.dataEmprestimo;
	novoEmprestimo.dataVencimento.dia += DIAS_DE_EMPRESTIMO;

	// Ajusta para estouro de mês
	int diasNoMes[] = {
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};
	if ((novoEmprestimo.dataVencimento.ano % 4 == 0 && novoEmprestimo.dataVencimento.ano % 100 != 0) ||
		(novoEmprestimo.dataVencimento.ano % 400 == 0))
	diasNoMes[1] = 29;

	if (novoEmprestimo.dataVencimento.dia > diasNoMes[novoEmprestimo.dataVencimento.mes - 1]) {
		novoEmprestimo.dataVencimento.dia -= diasNoMes[novoEmprestimo.dataVencimento.mes - 1];
		novoEmprestimo.dataVencimento.mes++;
		if (novoEmprestimo.dataVencimento.mes > 12) {
			novoEmprestimo.dataVencimento.mes = 1;
			novoEmprestimo.dataVencimento.ano++;
		}
	}

	novoEmprestimo.foiDevolvido = 0;
	novoEmprestimo.renovacoesUtilizadas = 0;
	novoEmprestimo.valorMulta = 0.0;
	novoEmprestimo.estaAtivo = 1;

	// Atualiza disponibilidade do livro
	livros[indiceLivro].copiasDisponiveis--;

	// Atualiza contador de empréstimos e histórico do usuário
	usuarios[indiceUsuario].contadorEmprestimos++;
	for (int i = 0; i < 50; i++) {
		if (strlen(usuarios[indiceUsuario].historicoEmprestimos[i]) == 0) {
			strcpy(usuarios[indiceUsuario].historicoEmprestimos[i], isbn);
			break;
		}
	}

	emprestimos[*contadorEmprestimos] = novoEmprestimo;
	(*contadorEmprestimos)++;

	printf("Livro emprestado com sucesso!\n");
	printf("Data de Vencimento: %02d/%02d/%d\n", novoEmprestimo.dataVencimento.dia,
		novoEmprestimo.dataVencimento.mes, novoEmprestimo.dataVencimento.ano);

	// Verifica se o usuário tinha uma reserva para este livro
	for (int i = 0; i < *contadorReservas; i++) {
		if (reservas[i].estaAtivo && !reservas[i].foiAtendida &&
			strcmp(reservas[i].idUsuario, idUsuario) == 0 &&
			strcmp(reservas[i].isbn, isbn) == 0) {
			reservas[i].foiAtendida = 1;
			printf("Sua reserva para este livro foi atendida.\n");
			break;
		}
	}

	return 1;
}

//Função para devolver livro
int devolverLivro(Emprestimo emprestimos[], int contadorEmprestimos, Livro livros[], int contadorLivros,
	Usuario usuarios[], int contadorUsuarios) {
	printf("\n--- Devolver Livro ---\n");

	char idUsuario[MAX_ID];
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, MAX_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	char isbn[MAX_ISBN];
	printf("Digite o ISBN do Livro: ");
	fgets(isbn, MAX_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	// Encontra empréstimo ativo
	int indiceEmprestimo = -1;
	for (int i = 0; i < contadorEmprestimos; i++) {
		if (emprestimos[i].estaAtivo && !emprestimos[i].foiDevolvido &&
			strcmp(emprestimos[i].idUsuario, idUsuario) == 0 &&
			strcmp(emprestimos[i].isbn, isbn) == 0) {
			indiceEmprestimo = i;
			break;
		}
	}

	if (indiceEmprestimo == -1) {
		printf("Erro: Nenhum empréstimo ativo encontrado para este usuário e livro.\n");
		return 0;
	}

	emprestimos[indiceEmprestimo].dataDevolucao = obterDataAtual();
	emprestimos[indiceEmprestimo].foiDevolvido = 1;

	// Calcula multa se estiver atrasado
	calcularMulta(&emprestimos[indiceEmprestimo]);

	// Atualiza disponibilidade do livro
	int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, isbn);
	if (indiceLivro != -1) {
		livros[indiceLivro].copiasDisponiveis++;
	}

	// Atualiza contador de empréstimos do usuário
	int indiceUsuario = encontrarUsuarioPorId(usuarios, contadorUsuarios, idUsuario);
	if (indiceUsuario != -1) {
		usuarios[indiceUsuario].contadorEmprestimos--;
		if (emprestimos[indiceEmprestimo].valorMulta > 0) {
			usuarios[indiceUsuario].multasTotais += emprestimos[indiceEmprestimo].valorMulta;
		}
	}

	printf("Livro devolvido com sucesso!\n");
	if (emprestimos[indiceEmprestimo].valorMulta > 0) {
		printf("Multa aplicada: R$%.2f\n", emprestimos[indiceEmprestimo].valorMulta);
	}

	return 1;
}

int renovarLivro(Emprestimo emprestimos[], int contadorEmprestimos, Livro livros[], int contadorLivros) {
	printf("\n--- Renovar Livro ---\n");

	char idUsuario[MAX_ID];
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, MAX_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	char isbn[MAX_ISBN];
	printf("Digite o ISBN do Livro: ");
	fgets(isbn, MAX_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	// Encontra empréstimo ativo
	int indiceEmprestimo = -1;
	for (int i = 0; i < contadorEmprestimos; i++) {
		if (emprestimos[i].estaAtivo && !emprestimos[i].foiDevolvido &&
			strcmp(emprestimos[i].idUsuario, idUsuario) == 0 &&
			strcmp(emprestimos[i].isbn, isbn) == 0) {
			indiceEmprestimo = i;
			break;
		}
	}

	if (indiceEmprestimo == -1) {
		printf("Erro: Nenhum empréstimo ativo encontrado para este usuário e livro.\n");
		return 0;
	}

	if (emprestimos[indiceEmprestimo].renovacoesUtilizadas >= MAX_RENOVACOES) {
		printf("Erro: Número máximo de renovações atingido para este livro!\n");
		return 0;
	}

	// Verifica se está atrasado
	Data hoje = obterDataAtual();
	if (compararDatas(hoje, emprestimos[indiceEmprestimo].dataVencimento) > 0) {
		printf("Erro: Não é possível renovar um livro atrasado. Devolva-o primeiro.\n");
		return 0;
	}

	// Verifica se o livro tem reservas
	// (Simplificado - em um sistema real, verificaria a tabela de reservas)

	// Renova o empréstimo
	emprestimos[indiceEmprestimo].dataVencimento.dia += DIAS_DE_EMPRESTIMO;
	emprestimos[indiceEmprestimo].renovacoesUtilizadas++;

	// Ajusta para estouro de mês (lógica similar à de empréstimo)
	int diasNoMes[] = {
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};
	if ((emprestimos[indiceEmprestimo].dataVencimento.ano % 4 == 0 && emprestimos[indiceEmprestimo].dataVencimento.ano % 100 != 0) ||
		(emprestimos[indiceEmprestimo].dataVencimento.ano % 400 == 0))
	diasNoMes[1] = 29;

	if (emprestimos[indiceEmprestimo].dataVencimento.dia > diasNoMes[emprestimos[indiceEmprestimo].dataVencimento.mes - 1]) {
		emprestimos[indiceEmprestimo].dataVencimento.dia -= diasNoMes[emprestimos[indiceEmprestimo].dataVencimento.mes - 1];
		emprestimos[indiceEmprestimo].dataVencimento.mes++;
		if (emprestimos[indiceEmprestimo].dataVencimento.mes > 12) {
			emprestimos[indiceEmprestimo].dataVencimento.mes = 1;
			emprestimos[indiceEmprestimo].dataVencimento.ano++;
		}
	}

	printf("Livro renovado com sucesso!\n");
	printf("Nova Data de Vencimento: %02d/%02d/%d\n", emprestimos[indiceEmprestimo].dataVencimento.dia,
		emprestimos[indiceEmprestimo].dataVencimento.mes, emprestimos[indiceEmprestimo].dataVencimento.ano);
	printf("Renovações utilizadas: %d/%d\n", emprestimos[indiceEmprestimo].renovacoesUtilizadas, MAX_RENOVACOES);

	return 1;
}

void calcularMulta(Emprestimo *emprestimo) {
	Data hoje = emprestimo->dataDevolucao;
	int diasAtraso = diasEntre(emprestimo->dataVencimento, hoje);

	if (diasAtraso > 0) {
		emprestimo->valorMulta = diasAtraso * MULTA_POR_DIA;
	} else {
		emprestimo->valorMulta = 0.0;
	}
}

void exibirEmprestimosAtivos(const Emprestimo emprestimos[], int contador, const Livro livros[], int contadorLivros) {
	printf("\n--- Empréstimos Ativos ---\n");
	int encontrados = 0;

	for (int i = 0; i < contador; i++) {
		if (emprestimos[i].estaAtivo && !emprestimos[i].foiDevolvido) {
			int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, emprestimos[i].isbn);
			if (indiceLivro != -1) {
				printf("\nID do Empréstimo: %d\n", emprestimos[i].idEmprestimo);
				printf("Usuário: %s\n", emprestimos[i].idUsuario);
				printf("Livro: %s\n", livros[indiceLivro].titulo);
				printf("Emprestado em: %02d/%02d/%d\n", emprestimos[i].dataEmprestimo.dia,
					emprestimos[i].dataEmprestimo.mes, emprestimos[i].dataEmprestimo.ano);
				printf("Vencimento: %02d/%02d/%d\n", emprestimos[i].dataVencimento.dia,
					emprestimos[i].dataVencimento.mes, emprestimos[i].dataVencimento.ano);
				printf("Renovações: %d/%d\n", emprestimos[i].renovacoesUtilizadas, MAX_RENOVACOES);

				Data hoje = obterDataAtual();
				int diasRestantes = diasEntre(hoje, emprestimos[i].dataVencimento);
				if (diasRestantes < 0) {
					printf("Status: ATRASADO por %d dias\n", -diasRestantes);
				} else {
					printf("Status: %d dias restantes\n", diasRestantes);
				}
				encontrados = 1;
			}
		}
	}

	if (!encontrados) {
		printf("Nenhum empréstimo ativo.\n");
	}
}

void exibirEmprestimosUsuario(const Emprestimo emprestimos[], int contador, const char *idUsuario,
	const Livro livros[], int contadorLivros) {
	printf("\n--- Seus Empréstimos ---\n");
	int encontrados = 0;

	for (int i = 0; i < contador; i++) {
		if (emprestimos[i].estaAtivo && strcmp(emprestimos[i].idUsuario, idUsuario) == 0 && !emprestimos[i].foiDevolvido) {
			int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, emprestimos[i].isbn);
			if (indiceLivro != -1) {
				printf("\nLivro: %s\n", livros[indiceLivro].titulo);
				printf("Emprestado em: %02d/%02d/%d\n", emprestimos[i].dataEmprestimo.dia,
					emprestimos[i].dataEmprestimo.mes, emprestimos[i].dataEmprestimo.ano);
				printf("Vencimento: %02d/%02d/%d\n", emprestimos[i].dataVencimento.dia,
					emprestimos[i].dataVencimento.mes, emprestimos[i].dataVencimento.ano);

				Data hoje = obterDataAtual();
				int diasRestantes = diasEntre(hoje, emprestimos[i].dataVencimento);
				if (diasRestantes < 0) {
					printf("Status: ATRASADO por %d dias - Devolva imediatamente!\n", -diasRestantes);
				} else {
					printf("Status: %d dias restantes\n", diasRestantes);
				}
				encontrados = 1;
			}
		}
	}

	if (!encontrados) {
		printf("Nenhum empréstimo ativo.\n");
	}
}

// ==================== SISTEMA DE RESERVAS ====================

void inicializarReservas(Reserva reservas[], int *contador) {
	*contador = 0;
}

int fazerReserva(Reserva reservas[], int *contador, const char *idUsuario,
	const Livro livros[], int contadorLivros) {
	if (*contador >= MAX_RESERVAS) {
		printf("Erro: Limite máximo de reservas atingido!\n");
		return 0;
	}

	char isbn[MAX_ISBN];
	printf("Digite o ISBN do livro para reservar: ");
	fgets(isbn, MAX_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, isbn);
	if (indiceLivro == -1) {
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	if (livros[indiceLivro].copiasDisponiveis > 0) {
		printf("Este livro está atualmente disponível. Não é necessário reservar.\n");
		return 0;
	}

	// Verifica se o usuário já tem uma reserva para este livro
	for (int i = 0; i < *contador; i++) {
		if (reservas[i].estaAtivo && !reservas[i].foiAtendida &&
			strcmp(reservas[i].idUsuario, idUsuario) == 0 &&
			strcmp(reservas[i].isbn, isbn) == 0) {
			printf("Você já tem uma reserva ativa para este livro.\n");
			return 0;
		}
	}

	Reserva novaReserva;
	novaReserva.idReserva = *contador + 1;
	strcpy(novaReserva.idUsuario, idUsuario);
	strcpy(novaReserva.isbn, isbn);
	novaReserva.dataReserva = obterDataAtual();
	novaReserva.estaAtivo = 1;
	novaReserva.foiAtendida = 0;

	reservas[*contador] = novaReserva;
	(*contador)++;

	printf("Reserva feita com sucesso!\n");
	printf("Você será notificado quando o livro estiver disponível.\n");
	return 1;
}

void visualizarReservas(const Reserva reservas[], int contador, const char *idUsuario,
	const Livro livros[], int contadorLivros) {
	printf("\n--- Suas Reservas ---\n");
	int encontrados = 0;

	for (int i = 0; i < contador; i++) {
		if (reservas[i].estaAtivo && strcmp(reservas[i].idUsuario, idUsuario) == 0) {
			int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, reservas[i].isbn);
			if (indiceLivro != -1) {
				printf("\nID da Reserva: %d\n", reservas[i].idReserva);
				printf("Livro: %s\n", livros[indiceLivro].titulo);
				printf("Data: %02d/%02d/%d\n", reservas[i].dataReserva.dia,
					reservas[i].dataReserva.mes, reservas[i].dataReserva.ano);
				printf("Status: %s\n", reservas[i].foiAtendida ? "Atendida": "Pendente");
				encontrados = 1;
			}
		}
	}

	if (!encontrados) {
		printf("Nenhuma reserva encontrada.\n");
	}
}

// GERAÇÃO DE RELATÓRIOS

void gerarRelatorioMaisEmprestados(const Emprestimo emprestimos[], int contadorEmprestimos,
	const Livro livros[], int contadorLivros) {
	printf("\n=== RELATÓRIO DE LIVROS MAIS EMPRESTADOS ===\n");

	// Cria array para contar empréstimos
	typedef struct {
		char isbn[MAX_ISBN];
		int contagem;
	} ContagemEmprestimo;

	ContagemEmprestimo contagens[MAX_LIVROS];
	int contagemUnica = 0;

	// Conta empréstimos por livro
	for (int i = 0; i < contadorEmprestimos; i++) {
		if (emprestimos[i].estaAtivo) {
			int encontrado = 0;
			for (int j = 0; j < contagemUnica; j++) {
				if (strcmp(contagens[j].isbn, emprestimos[i].isbn) == 0) {
					contagens[j].contagem++;
					encontrado = 1;
					break;
				}
			}
			if (!encontrado) {
				strcpy(contagens[contagemUnica].isbn, emprestimos[i].isbn);
				contagens[contagemUnica].contagem = 1;
				contagemUnica++;
			}
		}
	}

	// Ordena por contagem (decrescente)
	for (int i = 0; i < contagemUnica - 1; i++) {
		for (int j = i + 1; j < contagemUnica; j++) {
			if (contagens[j].contagem > contagens[i].contagem) {
				ContagemEmprestimo temp = contagens[i];
				contagens[i] = contagens[j];
				contagens[j] = temp;
			}
		}
	}

	// Exibe os 10 primeiros
	printf("%-5s %-30s %-20s %s\n", "Rank", "Título", "Autor", "Vezes Emprestado");
	imprimirSeparador();

	int limite = contagemUnica < 10 ? contagemUnica: 10;
	for (int i = 0; i < limite; i++) {
		int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, contagens[i].isbn);
		if (indiceLivro != -1) {
			printf("%-5d %-30s %-20s %d\n", i + 1, livros[indiceLivro].titulo,
				livros[indiceLivro].autor, contagens[i].contagem);
		}
	}
}

void gerarRelatorioLivrosDisponiveis(const Livro livros[], int contador) {
	printf("\n=== RELATÓRIO DE LIVROS DISPONÍVEIS ===\n");
	int encontrados = 0;

	printf("%-30s %-20s %-10s %s\n", "Título", "Autor", "Disponíveis", "Localização");
	imprimirSeparador();

	for (int i = 0; i < contador; i++) {
		if (livros[i].estaAtivo && livros[i].copiasDisponiveis > 0) {
			printf("%-30s %-20s %d/%-9d %s\n", livros[i].titulo, livros[i].autor,
				livros[i].copiasDisponiveis, livros[i].totalCopias, livros[i].localizacao);
			encontrados = 1;
		}
	}

	if (!encontrados) {
		printf("Nenhum livro disponível.\n");
	}
}

void gerarRelatorioLivrosAtrasados(const Emprestimo emprestimos[], int contadorEmprestimos,
	const Livro livros[], int contadorLivros) {
	printf("\n=== RELATÓRIO DE LIVROS ATRASADOS ===\n");
	Data hoje = obterDataAtual();
	int encontrados = 0;

	printf("%-30s %-20s %-15s %s\n", "Título", "Usuário", "Vencimento", "Dias Atraso");
	imprimirSeparador();

	for (int i = 0; i < contadorEmprestimos; i++) {
		if (emprestimos[i].estaAtivo && !emprestimos[i].foiDevolvido) {
			int diasAtraso = diasEntre(emprestimos[i].dataVencimento, hoje);
			if (diasAtraso > 0) {
				int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, emprestimos[i].isbn);
				if (indiceLivro != -1) {
					printf("%-30s %-20s %02d/%02d/%d %13d\n",
						livros[indiceLivro].titulo, emprestimos[i].idUsuario,
						emprestimos[i].dataVencimento.dia, emprestimos[i].dataVencimento.mes,
						emprestimos[i].dataVencimento.ano, diasAtraso);
					encontrados = 1;
				}
			}
		}
	}

	if (!encontrados) {
		printf("Nenhum livro atrasado.\n");
	}
}

void gerarRelatorioMultas(const Emprestimo emprestimos[], int contadorEmprestimos, const Usuario usuarios[], int contadorUsuarios) {
	printf("\n=== RELATÓRIO DE MULTAS ===\n");
	float totalMultas = 0.0;
	int encontrados = 0;

	// Calcula multas de empréstimos ativos em atraso
	Data hoje = obterDataAtual();

	printf("%-20s %-30s %-15s %s\n", "ID do Usuário", "Nome", "Pendente", "Multas Totais");
	imprimirSeparador();

	for (int i = 0; i < contadorUsuarios; i++) {
		if (usuarios[i].estaAtivo) {
			float multaUsuario = usuarios[i].multasTotais;

			// Adiciona multas de empréstimos atuais em atraso
			for (int j = 0; j < contadorEmprestimos; j++) {
				if (emprestimos[j].estaAtivo && !emprestimos[j].foiDevolvido &&
					strcmp(emprestimos[j].idUsuario, usuarios[i].id) == 0) {
					int diasAtraso = diasEntre(emprestimos[j].dataVencimento, hoje);
					if (diasAtraso > 0) {
						multaUsuario += diasAtraso * MULTA_POR_DIA;
					}
				}
			}

			if (multaUsuario > 0) {
				printf("%-20s %-30s R$%-14.2f R$%.2f\n",
					usuarios[i].id, usuarios[i].nome, multaUsuario, usuarios[i].multasTotais);
				totalMultas += multaUsuario;
				encontrados = 1;
			}
		}
	}

	if (!encontrados) {
		printf("Nenhuma multa a relatar.\n");
	} else {
		printf("\nTotal de Multas Pendentes: R$%.2f\n", totalMultas);
	}
}

void gerarEstatisticasUso(const Emprestimo emprestimos[], int contadorEmprestimos) {
	printf("\n=== ESTATÍSTICAS DE USO ===\n");

	int emprestimosAtivos = 0;
	int emprestimosDevolvidos = 0;
	int emprestimosAtrasados = 0;
	Data hoje = obterDataAtual();

	for (int i = 0; i < contadorEmprestimos; i++) {
		if (emprestimos[i].estaAtivo) {
			if (emprestimos[i].foiDevolvido) {
				emprestimosDevolvidos++;
			} else {
				emprestimosAtivos++;
				if (diasEntre(emprestimos[i].dataVencimento, hoje) > 0) {
					emprestimosAtrasados++;
				}
			}
		}
	}

	printf("Total de Empréstimos: %d\n", contadorEmprestimos);
	printf("Empréstimos Ativos: %d\n", emprestimosAtivos);
	printf("Empréstimos Devolvidos: %d\n", emprestimosDevolvidos);
	printf("Empréstimos Atrasados: %d\n", emprestimosAtrasados);
	printf("Taxa de Devolução: %.2f%%\n", contadorEmprestimos > 0 ?
		((float)emprestimosDevolvidos / contadorEmprestimos * 100): 0);
}

// ==================== SISTEMA DE MENU ====================

void menuAdmin(Usuario *usuarioAtual, Livro livros[], int *contadorLivros, Usuario usuarios[], int *contadorUsuarios,
	Emprestimo emprestimos[], int *contadorEmprestimos, Reserva reservas[], int *contadorReservas) {
	int opcao;

	do {
		printf("\n╔════════════════════════════════════╗\n\
║     MENU DO ADMINISTRADOR         ║\n\
╠════════════════════════════════════╣\n\
║ 1. Gerenciar Livros               ║\n\
║ 2. Gerenciar Usuários             ║\n\
║ 3. Visualizar Todos os Empréstimos║\n\
║ 4. Gerar Relatórios               ║\n\
║ 5. Visualizar Configurações       ║\n\
║ 0. Sair                           ║\n\
╚════════════════════════════════════╝\n\
			");
		printf("Digite a opção: ");
		scanf("%d", &opcao);
		limparBufferEntrada();

		switch(opcao) {
			case 1: {
				int opcaoLivro;
				do {
					printf("\n\
--- Gerenciamento de Livros ---\n\
1. Adicionar Livro\n\
2. Atualizar Livro\n\
3. Excluir Livro\n\
4. Visualizar Todos os Livros\n\
5. Pesquisar Livros\n\
0. Voltar\n\
Digite a opção: \
						");
					scanf("%d", &opcaoLivro);
					limparBufferEntrada();

					switch(opcaoLivro) {
						case 1: adicionarLivro(livros, contadorLivros); break;
						case 2: atualizarLivro(livros, *contadorLivros); break;
						case 3: excluirLivro(livros, *contadorLivros); break;
						case 4: exibirTodosLivros(livros, *contadorLivros); pausarTela(); break;
						case 5: pesquisarLivros(livros, *contadorLivros); pausarTela(); break;
					}
				} while(opcaoLivro != 0);
				break;
			}

			case 2: {
				int opcaoUsuario;
				do {
					printf("\n\
--- Gerenciamento de Usuários ---\n\
1. Registrar Usuário\n\
2. Atualizar Usuário\n\
3. Excluir Usuário\n\
4. Visualizar Todos os Usuários\n\
0. Voltar\n\
Digite a opção: \
						");
					scanf("%d", &opcaoUsuario);
					limparBufferEntrada();

					switch(opcaoUsuario) {
						case 1: {
							printf("Digite o papel (admin/bibliotecario/leitor): ");
							char papel[10];
							fgets(papel, 10, stdin);
							papel[strcspn(papel, "\n")] = 0;
							registrarUsuario(usuarios, contadorUsuarios, papel);
							break;
						}
						case 2: /* atualizarUsuario(usuarios, *contadorUsuarios); */ break;
						case 3: /* excluirUsuario(usuarios, *contadorUsuarios); */ break;
						case 4: exibirTodosUsuarios(usuarios, *contadorUsuarios); pausarTela(); break;
					}
				} while(opcaoUsuario != 0);
				break;
			}

			case 3:
			exibirEmprestimosAtivos(emprestimos, *contadorEmprestimos, livros, *contadorLivros);
			pausarTela();
			break;

			case 4: {
				int opcaoRelatorio;
				do {
					printf("\n\
--- Relatórios ---\n\
1. Livros Mais Emprestados\n\
2. Livros Disponíveis\n\
3. Livros Atrasados\n\
4. Relatório de Multas\n\
5. Estatísticas de Uso\n\
0. Voltar\n\
Digite a opção: \
						");
					scanf("%d", &opcaoRelatorio);
					limparBufferEntrada();

					switch(opcaoRelatorio) {
						case 1: gerarRelatorioMaisEmprestados(emprestimos, *contadorEmprestimos, livros, *contadorLivros); pausarTela(); break;
						case 2: gerarRelatorioLivrosDisponiveis(livros, *contadorLivros); pausarTela(); break;
						case 3: gerarRelatorioLivrosAtrasados(emprestimos, *contadorEmprestimos, livros, *contadorLivros); pausarTela(); break;
						case 4: gerarRelatorioMultas(emprestimos, *contadorEmprestimos, usuarios, *contadorUsuarios); pausarTela(); break;
						case 5: gerarEstatisticasUso(emprestimos, *contadorEmprestimos); pausarTela(); break;
					}
				} while(opcaoRelatorio != 0);
				break;
			}

			case 5:
			printf("\n--- Configurações do Sistema ---\n");
			printf("Período de Empréstimo: %d dias\n", DIAS_DE_EMPRESTIMO);
			printf("Máximo de Renovações: %d\n", MAX_RENOVACOES);
			printf("Máximo de Empréstimos por Usuário: %d\n", MAX_EMPRESTIMOS_POR_USUARIO);
			printf("Multa por Dia: %dMZN\n", MULTA_POR_DIA);
			pausarTela();
			break;
		}
	} while(opcao != 0);
}

void menuBibliotecario(Usuario *usuarioAtual, Livro livros[], int *contadorLivros, Usuario usuarios[], int *contadorUsuarios,
	Emprestimo emprestimos[], int *contadorEmprestimos, Reserva reservas[], int *contadorReservas) {
	int opcao;

	do {
		printf("\n\
╔════════════════════════════════════╗\n\
║ MENU DO BIBLIOTECÁRIO         ║\n\
╠════════════════════════════════════╣\n\
║ 1. Emprestar Livro                ║\n\
║ 2. Devolver Livro                 ║\n\
║ 3. Renovar Livro                  ║\n\
║ 4. Visualizar Empréstimos Ativos  ║\n\
║ 5. Pesquisar Livros               ║\n\
║ 6. Visualizar Livros Atrasados    ║\n\
║ 0. Sair                           ║\n\
╚════════════════════════════════════╝\n\
			");
		printf("Digite a opção: ");
		scanf("%d", &opcao);
		limparBufferEntrada();

		switch(opcao) {
			case 1: emprestarLivro(emprestimos, contadorEmprestimos, livros, *contadorLivros, usuarios, *contadorUsuarios, reservas, contadorReservas); pausarTela(); break;
			case 2: devolverLivro(emprestimos, *contadorEmprestimos, livros, *contadorLivros, usuarios, *contadorUsuarios); pausarTela(); break;
			case 3: renovarLivro(emprestimos, *contadorEmprestimos, livros, *contadorLivros); pausarTela(); break;
			case 4: exibirEmprestimosAtivos(emprestimos, *contadorEmprestimos, livros, *contadorLivros); pausarTela(); break;
			case 5: pesquisarLivros(livros, *contadorLivros); pausarTela(); break;
			case 6: gerarRelatorioLivrosAtrasados(emprestimos, *contadorEmprestimos, livros, *contadorLivros); pausarTela(); break;
		}
	} while(opcao != 0);
}

void menuLeitor(Usuario *usuarioAtual, Livro livros[], int contadorLivros, Emprestimo emprestimos[], int contadorEmprestimos,
	Reserva reservas[], int *contadorReservas) {
	int opcao;

	do {
		printf("\n\
╔════════════════════════════════════╗\n\
║     MENU DO LEITOR                ║\n\
╠════════════════════════════════════╣\n\
║ Bem-vindo, %-20s ║\n\
╠════════════════════════════════════╣\n\
║ 1. Pesquisar Livros               ║\n\
║ 2. Visualizar Meus Empréstimos    ║\n\
║ 3. Reservar Livro                 ║\n\
║ 4. Visualizar Minhas Reservas     ║\n\
║ 5. Visualizar Minhas Multas       ║\n\
║ 0. Sair                           ║\n\
╚════════════════════════════════════╝\n\
			", usuarioAtual->nome);
		printf("Digite a opção: ");
		scanf("%d", &opcao);
		limparBufferEntrada();

		switch(opcao) {
			case 1: pesquisarLivros(livros, contadorLivros); pausarTela(); break;
			case 2: exibirEmprestimosUsuario(emprestimos, contadorEmprestimos, usuarioAtual->id, livros, contadorLivros); pausarTela(); break;
			case 3: fazerReserva(reservas, contadorReservas, usuarioAtual->id, livros, contadorLivros); pausarTela(); break;
			case 4: visualizarReservas(reservas, *contadorReservas, usuarioAtual->id, livros, contadorLivros); pausarTela(); break;
			case 5:
			printf("\n--- Suas Multas ---\n");
			printf("Total de Multas Pendentes: R$%.2f\n", usuarioAtual->multasTotais);
			pausarTela();
			break;
		}
	} while(opcao != 0);
}

void exibirTodosUsuarios(const Usuario usuarios[], int contador) {
	printf("\n--- Todos os Usuários ---\n");
	printf("%-10s %-20s %-15s %-10s\n", "ID", "Nome", "Papel", "Empréstimos");
	imprimirSeparador();

	for (int i = 0; i < contador; i++) {
		if (usuarios[i].estaAtivo) {
			printf("%-10s %-20s %-15s %d\n", usuarios[i].id, usuarios[i].nome,
				usuarios[i].papel, usuarios[i].contadorEmprestimos);
		}
	}
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
	// Inicializa todas as estruturas de dados
	Livro livros[MAX_LIVROS];
	int contadorLivros;
	inicializarLivros(livros, &contadorLivros);

	Usuario usuarios[MAX_USUARIOS];
	int contadorUsuarios;
	inicializarUsuarios(usuarios, &contadorUsuarios);

	Emprestimo emprestimos[MAX_EMPRESTIMOS];
	int contadorEmprestimos;
	inicializarEmprestimos(emprestimos, &contadorEmprestimos);

	Reserva reservas[MAX_RESERVAS];
	int contadorReservas;
	inicializarReservas(reservas, &contadorReservas);

	printf("\
╔════════════════════════════════════════════════╗\n\
║ SISTEMA DE GERENCIAMENTO DE BIBLIOTECA         ║\n\
║ Bem-vindo à Biblioteca!                        ║\n\
╚════════════════════════════════════════════════╝\n\
		");

	while (1) {
		Usuario *usuarioAtual = autenticarUsuario(usuarios, contadorUsuarios);

		if (usuarioAtual != NULL) {
			if (strcmp(usuarioAtual->papel, "admin") == 0) {
				menuAdmin(usuarioAtual, livros, &contadorLivros, usuarios, &contadorUsuarios,
					emprestimos, &contadorEmprestimos, reservas, &contadorReservas);
			} else if (strcmp(usuarioAtual->papel, "bibliotecario") == 0) {
				menuBibliotecario(usuarioAtual, livros, &contadorLivros, usuarios, &contadorUsuarios,
					emprestimos, &contadorEmprestimos, reservas, &contadorReservas);
			} else if (strcmp(usuarioAtual->papel, "leitor") == 0) {
				menuLeitor(usuarioAtual, livros, contadorLivros, emprestimos, contadorEmprestimos,
					reservas, &contadorReservas);
			} else printf("Papel de usuário inválido!\n");
		}

		printf("\nDeseja continuar? (1=Sim, 0=Sair): ");
		int opcaoContinuar;
		scanf("%d", &opcaoContinuar);
		limparBufferEntrada();

		if (opcaoContinuar == 0) break;
	}

	printf("\nObrigado por usar o Sistema de Gerenciamento de Biblioteca!\n");
	//fim
	return 0;
}
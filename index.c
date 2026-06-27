#ifndef SISTEMA_DE_GESTAO_DE_BIBLIOTECA
#define SISTEMA_DE_GESTAO_DE_BIBLIOTECA
// 1 para windows, 0 para outros
#define SISTEMA_OPERACIONAL 0
#include <stdio.h>	//Biblioteca para entrada e saída de dados
#include <stdlib.h> //biblioteca para chamadas no sistema e manipulação de memória
#include <string.h> //biblioteca para operações com strings
#include <time.h>	//biblioteca para operações com tempo
#include <ctype.h>	//biblioteca para classificar caracteres da string

// CONSTANTES (TAM = tamanho da string, MAX = número de elementos no vetor)

// Constantes para livros
#define TAM_ISBN 30
#define TAM_TITULO 100
#define TAM_AUTOR 100
#define TAM_EDITORA 50
#define TAM_CATEGORIA 30
#define TAM_LOCALIZACAO 20

// Constantes para usuários
#define TAM_ID 20
#define TAM_NOME 50
#define TAM_EMAIL 50
// Os números moçambicanos geralmente têm 9 caracteres
#define TAM_TELEFONE 9

// Outras constantes (não sabemos classoficar)
#define MAX_LIVROS 1000
#define MAX_USUARIOS 500
#define MAX_EMPRESTIMOS 1000
#define MAX_RESERVAS 200
#define MULTA_POR_DIA 50
#define DIAS_DE_EMPRESTIMO 14
#define MAX_RENOVACOES 2
#define MAX_EMPRESTIMOS_POR_USUARIO 5

// Cores para estilizar a interface
#define COR_AMARELO "\033[33m"
#define COR_AZUL "\033[34m"
#define COR_BOLD "\033[1m"
#define COR_BG_ESCURO "\033[48;5;235m"
#define COR_BRANCO "\033[37m"
#define COR_CIANO "\033[36m"
#define COR_CINZA "\033[90m"
#define COR_MAGENTA "\033[35m"
#define COR_RESET "\033[0m"
#define COR_VERDE "\033[32m"
#define COR_VERMELHO "\033[31m"

// Arquivos
#define USUARIOS_ARQUIVO "usuarios.bin"
#define LIVROS_ARQUIVO "livros.bin"
#define EMPRESTIMOS_ARQUIVO "emprestimos.bin"
#define RESERVAS_ARQUIVO "reservas.bin"
#define CONTADORES_ARQUIVO "contadores.bin"

// Estrutura de data
typedef struct
{
	int dia;
	int mes;
	int ano;
} Data;

// Estrutura de livro
typedef struct
{
	char isbn[TAM_ISBN];
	char titulo[TAM_TITULO];
	char autor[TAM_AUTOR];
	char editora[TAM_EDITORA];
	char categoria[TAM_CATEGORIA];
	int anoPublicacao;
	int totalCopias;
	int copiasDisponiveis;
	char localizacao[TAM_LOCALIZACAO];
	int estaAtivo; // 1 se ativo, 0 se excluído
} Livro;

// Enumerador para defenir o papel do usuário
typedef enum
{
	ADMINISTRADOR,
	BIBLIOTECARIO,
	LEITOR
} Papel;

// Estrutura de usuário
typedef struct
{
	char id[TAM_ID];
	char nome[TAM_NOME];
	char email[TAM_EMAIL];
	char telefone[TAM_TELEFONE];
	Papel papel; // administrador, leitor, bibliotecario
	int contadorEmprestimos;
	char historicoEmprestimos[50][TAM_ISBN]; // Armazena ISBNs dos livros emprestados
	int estaAtivo;
	float multasTotais;
} Usuario;

// Estrutura de empréstimo
typedef struct
{
	int idEmprestimo;
	char idUsuario[TAM_ID];
	char isbn[TAM_ISBN];
	Data dataEmprestimo;
	Data dataVencimento;
	Data dataDevolucao;
	int foiDevolvido;
	int renovacoesUtilizadas;
	float valorMulta;
	int estaAtivo;
} Emprestimo;

// estrutura de reserva
typedef struct
{
	int idReserva;
	char idUsuario[TAM_ID];
	char isbn[TAM_ISBN];
	Data dataReserva;
	int estaAtivo;
	int foiAtendida;
} Reserva;

typedef struct
{
	int contadorLivros;
	int contadorUsuarios;
	int contadorEmprestimos;
	int contadorReservas;
} Contadores;

// Funções para gerenciamento de livros
void inicializarLivros(Livro livros[], int *contador);
int adicionarLivro(Livro livros[], int *contador);
int atualizarLivro(Livro livros[], int contador);
int excluirLivro(Livro livros[], int contador);
void exibirLivro(const Livro *livro);
void exibirTodosLivros(const Livro livros[], int contador);
int encontrarLivroPorISBN(const Livro livros[], int contador, const char *isbn);
void pesquisarLivros(const Livro livros[], int contador);

//  funções para Gerenciamento de Usuários
void inicializarUsuarios(Usuario usuarios[], int *contador);
int registrarUsuario(Usuario usuarios[], int *contador, const Papel papel);
int atualizarUsuario(Usuario usuarios[], int contador);
int excluirUsuario(Usuario usuarios[], int contador);
void exibirUsuario(const Usuario *usuario);
void exibirTodosUsuarios(const Usuario usuarios[], int contador);
int encontrarUsuarioPorId(const Usuario usuarios[], int contador, const char *id);
Usuario *autenticarUsuario(Usuario usuarios[], int contador);

// funções para Operações de Empréstimo
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

// funções para reservas
void inicializarReservas(Reserva reservas[], int *contador);
int fazerReserva(Reserva reservas[], int *contador, const char *idUsuario,
				 const Livro livros[], int contadorLivros);
void visualizarReservas(const Reserva reservas[], int contador, const char *idUsuario,
						const Livro livros[], int contadorLivros);

// funções para Relatórios
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
void exibirLogo();
void limparTela();
void papelParaTexto(Papel papel);

// Funções de menu
void menuAdmin(Usuario *usuarioAtual, Livro livros[], int *contadorLivros, Usuario usuarios[], int *contadorUsuarios,
			   Emprestimo emprestimos[], int *contadorEmprestimos, Reserva reservas[], int *contadorReservas);
void menuBibliotecario(Usuario *usuarioAtual, Livro livros[], int *contadorLivros, Usuario usuarios[], int *contadorUsuarios,
					   Emprestimo emprestimos[], int *contadorEmprestimos, Reserva reservas[], int *contadorReservas);
void menuLeitor(Usuario *usuarioAtual, Livro livros[], int contadorLivros, Emprestimo emprestimos[], int contadorEmprestimos,
				Reserva reservas[], int *contadorReservas);

#endif

// FUNÇÕES UTILITÁRIAS

// funçào para obter a dats atual (data do dispositivo)
Data obterDataAtual()
{
	Data hoje;
	time_t t = time(NULL);
	struct tm *tm_info = localtime(&t);

	hoje.dia = tm_info->tm_mday;
	hoje.mes = tm_info->tm_mon + 1;
	hoje.ano = tm_info->tm_year + 1900;

	return hoje;
}

// quantos dias se passaram entre duas datas
int diasEntre(Data d1, Data d2)
{
	// Converte datas para dias desde a época para comparação
	struct tm data1 = {
				  0},
			  data2 = {0};

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

int ehDataValida(Data d)
{
	if (d.ano < 1900 || d.ano > 2100)
		return 0;
	if (d.mes < 1 || d.mes > 12)
		return 0;
	if (d.dia < 1)
		return 0;

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
		31};

	// Ajuste para ano bissexto
	if ((d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0))
		diasNoMes[1] = 29;

	if (d.dia > diasNoMes[d.mes - 1])
		return 0;

	return 1;
}

int compararDatas(Data d1, Data d2)
{
	if (d1.ano != d2.ano)
		return d1.ano - d2.ano;
	if (d1.mes != d2.mes)
		return d1.mes - d2.mes;
	return d1.dia - d2.dia;
}

void limparBufferEntrada()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

void paraMinusculas(char *str)
{
	for (int i = 0; str[i]; i++)
		str[i] = tolower(str[i]);
}

void imprimirSeparador()
{
	printf("\n========================================\n");
}

void pausarTela()
{
	printf("\nPressione Enter para continuar...");
	limparBufferEntrada();
	limparTela();
}

// funçào para exibir logo no cabeçalho
void exibirLogo()
{
	printf( // Desenho de livro magnífico usando símbolos
		COR_VERDE
		"\n"
		"            /;\n"
		"           / |'-,.\n"
		"          /  '    `\"---,.__\n"
		"         /  '    ,'     ,  '\"--,|\n"
		"        /  '    ,     ,'     ,\":|\n"
		"       /  '   ,'    ,      ,\":::|\n"
		"      /  '   ,    ,'     ,\":::::|\n"
		"     /  '  ,'   ,'     ,\":::::::|\n"
		"    /  '  ,    ,     ,\":::::::::|\n"
		"    k-,._    ,'   _.\":::::::::::|\n"
		"     \\.  `\"----'\"\".J::::::::::::|\n"
		"      \\.    .-,    .L:::::::::::|\n"
		"       \\.  (       .J:::::::::::!\n"
		"        \\.  `--     .L:::::::::/\n"
		"         \\.   .-.   .|::::::::/\n"
		"          \\. (   )  .J:::::::/\n"
		"           \\. `-'    .L:::::/\n"
		"            \\.  L    .|::::/\n"
		"             \\. !__  .J:::/\n"
		"              \\.  __  .L:/\n"
		"               \\. L_) .|/\n"
		"                `-,__,-'\n" COR_RESET);
}

void limparTela()
{
// Comando diferente para limpar a tela dependendo do sistema operacional (essa é a única utilidade da macro SISTEMA_OPERACIONAL)
#if SISTEMA_OPERACIONAL == 1
	system("cls");
#else
	system("clear");
#endif

	// Exibe a logo apôs limpar a tela
	exibirLogo();
}

char *papelParaTexto(Papel papel)
{
	switch (papel)
	{
	case ADMINISTRADOR:
		return "administrador";
	case BIBLIOTECARIO:
		return "bibliotecário";
	case LEITOR:
		return "leitor";
	default:
		return "desconhecido";
	}
}

// GERENCIAMENTO DE LIVROS

int adicionarLivro()
{
	Contadores contadores;
	FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb+");
	if (arquivoContadores == NULL)
		return 0;

	fread(&contadores, sizeof(Contadores), 1, arquivoContadores);

	if (contadores.contadorLivros >= MAX_LIVROS)
	{
		printf("Erro: Limite máximo de livros atingido!\n");
		return 0;
	}

	Livro novoLivro;
	printf("\n--- Adicionar Novo Livro ---\n");

	printf("Digite o ISBN (13 dígitos): ");
	fgets(novoLivro.isbn, TAM_ISBN, stdin);
	novoLivro.isbn[strcspn(novoLivro.isbn, "\n")] = 0;

	// Verifica ISBN duplicado
	if (!encontrarLivroPorISBN(novoLivro.isbn, &novoLivro))
	{
		printf("Erro: Já existe um livro com este ISBN!\n");
		return 0;
	}

	printf("Digite o Título: ");
	fgets(novoLivro.titulo, TAM_TITULO, stdin);
	novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = 0;

	printf("Digite o(s) Autor(es): ");
	fgets(novoLivro.autor, TAM_AUTOR, stdin);
	novoLivro.autor[strcspn(novoLivro.autor, "\n")] = 0;

	printf("Digite a Editora: ");
	fgets(novoLivro.editora, TAM_EDITORA, stdin);
	novoLivro.editora[strcspn(novoLivro.editora, "\n")] = 0;

	printf("Digite a Categoria/Gênero: ");
	fgets(novoLivro.categoria, TAM_CATEGORIA, stdin);
	novoLivro.categoria[strcspn(novoLivro.categoria, "\n")] = 0;

	printf("Digite o Ano de Publicação: ");
	scanf("%d", &novoLivro.anoPublicacao);
	limparBufferEntrada();

	printf("Digite o Total de Cópias: ");
	scanf("%d", &novoLivro.totalCopias);
	limparBufferEntrada();
	novoLivro.copiasDisponiveis = novoLivro.totalCopias;

	printf("Digite a Localização Física (ex: A1-Prateleira3): ");
	fgets(novoLivro.localizacao, TAM_LOCALIZACAO, stdin);
	novoLivro.localizacao[strcspn(novoLivro.localizacao, "\n")] = 0;

	novoLivro.estaAtivo = 1;

	FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "ab");
	if (arquivoLivros == NULL)
		fopen(LIVROS_ARQUIVO, "wb");

	fwrite(&novoLivro, sizeof(Livro), 1, arquivoLivros);
	fclose(arquivoLivros);

	contadores.contadorLivros++;

	// Atualiza o arquivo de contadores
	rewind(arquivoContadores);
	fwrite(&contadores, sizeof(Contadores), 1, arquivoContadores);
	fclose(arquivoContadores);

	printf("Livro adicionado com sucesso!\n");
	return 1;
}

int atualizarLivro(Livro livros[], int contador)
{
	char isbn[TAM_ISBN];
	printf("\n--- Atualizar Informações do Livro ---\n");
	printf("Digite o ISBN do livro a ser atualizado: ");
	fgets(isbn, TAM_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	Livro livro;
	int indice = encontrarLivroPorISBN(isbn, &livro);
	if (indice == -1)
	{
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	printf("\nDetalhes Atuais do Livro:\n");
	exibirLivro(&livro);

	printf("\nDigite as novas informações (pressione Enter para manter o valor atual):\n");

	char entrada[TAM_TITULO];

	// LER OS DETALHES DO LIVRO

	// Ler o título
	printf("Novo Título [%s]: ", livro.titulo);
	fgets(entrada, TAM_TITULO, stdin);
	if (strlen(entrada) > 1)
	{
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livro.titulo, entrada);
	}

	// Ler o autor
	printf("Novo Autor [%s]: ", livro.autor);
	fgets(entrada, TAM_AUTOR, stdin);
	if (strlen(entrada) > 1)
	{
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livro.autor, entrada);
	}

	// Ler a editora
	printf("Nova Editora [%s]: ", livro.editora);
	fgets(entrada, TAM_EDITORA, stdin);
	if (strlen(entrada) > 1)
	{
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livro.editora, entrada);
	}

	// Ler a categoria
	printf("Nova Categoria [%s]: ", livro.categoria);
	fgets(entrada, TAM_CATEGORIA, stdin);
	if (strlen(entrada) > 1)
	{
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livro.categoria, entrada);
	}

	// Ler a Localização
	printf("Nova Localização [%s]: ", livro.localizacao);
	fgets(entrada, TAM_LOCALIZACAO, stdin);
	if (strlen(entrada) > 1)
	{
		entrada[strcspn(entrada, "\n")] = 0;
		strcpy(livro.localizacao, entrada);
	}

	// Ler o total de cópias
	printf("Novo Total de Cópias [%d]: ", livro.totalCopias);
	fgets(entrada, 10, stdin);
	if (strlen(entrada) > 1)
	{
		int novoTotal = atoi(entrada);
		if (novoTotal >= livro.totalCopias - livro.copiasDisponiveis)
		{
			int emprestados = livro.totalCopias - livro.copiasDisponiveis;
			livro.totalCopias = novoTotal;
			livro.copiasDisponiveis = novoTotal - emprestados;
		}
		else
		{
			printf("Erro: Não é possível reduzir as cópias abaixo da quantidade atualmente emprestada!\n");
		}
	}

	FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb+");
	fseek(arquivoLivros, sizeof(Livro) * indice, SEEK_SET);
	fwrite(&livro, sizeof(Livro), 1, arquivoLivros);
	fclose(arquivoLivros);

	printf("Livro atualizado com sucesso!\n");
	return 1;
}

int excluirLivro()
{
	char isbn[TAM_ISBN];
	printf("\n--- Excluir Livro ---\n");
	printf("Digite o ISBN do livro a ser excluído: ");
	fgets(isbn, TAM_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	Livro livro;
	int indice encontrarLivroPorISBN(isbn, &livro);

	if (indice == -1)
	{
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	// Verifica se o livro está emprestado atualmente
	if (livro.copiasDisponiveis < livro.totalCopias)
	{
		printf("Erro: Não é possível excluir um livro que está emprestado!\n");
		return 0;
	}

	livro.estaAtivo = 0;

	FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb+");
	fseek(arquivoLivros, sizeof(Livro) * indice, SEEK_SET);
	fwrite(&livro, sizeof(Livro), 1, arquivoLivros);
	fclose(arquivoLivros);

	printf("Livro excluído com sucesso!\n");
	return 1;
}

void exibirLivro(const Livro *livro)
{
	printf("\nISBN: %s\n", livro->isbn);
	printf("Título: %s\n", livro->titulo);
	printf("Autor(es): %s\n", livro->autor);
	printf("Editora: %s\n", livro->editora);
	printf("Categoria: %s\n", livro->categoria);
	printf("Ano de Publicação: %d\n", livro->anoPublicacao);
	printf("Cópias Disponíveis: %d/%d\n", livro->copiasDisponiveis, livro->totalCopias);
	printf("Localização: %s\n", livro->localizacao);
}

void exibirTodosLivros()
{
	FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb");

	FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb");

	if (arquivoContadores == NULL || arquivoLivros == NULL)
	{
		printf("\nNão há livros na biblioteca.\n");
		return;
	}

	Contadores contadores;

	if (fread(arquivoContadores, sizeof(Contadores), 1, &contadores))
	{
		printf("\nNão há livros na biblioteca.\n");
		return;
	}

	printf("\n--- Catálogo da Biblioteca ---\n");
	printf("%-15s %-30s %-20s %-10s %s\n", "ISBN", "Título", "Autor", "Disponíveis", "Localização");
	imprimirSeparador();

	Livro livro;

	for (int i = 0; i < contadores.totalLivros; i++)
	{
		fread(arquivoLivros, sizeof(Livro), 1, &livro);

		if (livro.estaAtivo)
		{
			printf("%-15s %-30s %-20s %d/%-9d %s\n",
				   livro.isbn,
				   livro.titulo,
				   livro.autor,
				   livro.copiasDisponiveis,
				   livro.totalCopias,
				   livro.localizacao);
		}
	}
}

int encontrarLivroPorISBN(const char *isbn, Livro *livro)
{
	int indice = 0;
	FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb");
	if (arquivoLivros == NULL)
	{
		return -1;
	}

	while (fread(livro, sizeof(Livro), 1, arquivoLivros))
	{
		if (strcmp(livro->isbn, isbn) == 0)
		{
			fclose(arquivoLivros);
			return indice;
		}

		indice++;
	}

	fclose(arquivoLivros);
	return -1;
}

void pesquisarLivros()
{
	int opcao;
	printf(
		"\n"
		"╔════════════════════════════════════╗\n"
		"║ Pesquisar Livros                   ║\n"
		"╠════════════════════════════════════╣\n"
		"║ 1. Pesquisar por Título            ║\n"
		"║ 2. Pesquisar por Autor             ║\n"
		"║ 3. Pesquisar por ISBn              ║\n"
		"║ 4. Pesquisar por Categoria         ║\n"
		"╚════════════════════════════════════╝\n"
		"\n"
		"Digite a opção: ");
	scanf("%d", &opcao);
	limparBufferEntrada();

	char termoBusca[TAM_TITULO];
	int encontrados = 0;

	Livro livro;
	FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb");

	switch (opcao)
	{
	case 1:
		printf("\n\nDigite o título para pesquisar: ");
		fgets(termoBusca, TAM_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;
		paraMinusculas(termoBusca);

		limparTela();

		printf("Resultados da Pesquisa:\n");
		while (fread(&livro, sizeof(Livro), 1, arquivoLivros))
		{
			if (livro.estaAtivo)
			{
				char tituloCopia[TAM_TITULO];
				strcpy(tituloCopia, livro.titulo);
				paraMinusculas(tituloCopia);
				if (strstr(tituloCopia, termoBusca) != NULL)
				{
					exibirLivro(&livro);
					encontrados = 1;
				}
			}
		}
		break;

	case 2:
		printf("\n\nDigite o autor para pesquisar: ");
		fgets(termoBusca, TAM_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;
		paraMinusculas(termoBusca);

		limparTela();

		printf("Resultados da Pesquisa:\n");
		while (fread(&livro, sizeof(Livro), 1, arquivoLivros))
		{
			if (livro.estaAtivo)
			{
				char autorCopia[TAM_AUTOR];
				strcpy(autorCopia, livro.autor);
				paraMinusculas(autorCopia);
				if (strstr(autorCopia, termoBusca) != NULL)
				{
					exibirLivro(&livro);
					encontrados = 1;
				}
			}
		}
		break;

	case 3:
		printf("\n\nDigite o ISBN: ");
		fgets(termoBusca, TAM_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;

		limparTela();

		printf("Resultado da Pesquisa:\n");
		while (fread(&livro, sizeof(Livro), 1, arquivoLivros))
		{
			if (livro.estaAtivo && strcmp(livro.isbn, termoBusca) == 0)
			{
				exibirLivro(&livro);
				encontrados = 1;
				break;
			}
		}
		break;

	case 4:
		printf("\n\nDigite a categoria para filtrar: ");
		fgets(termoBusca, TAM_TITULO, stdin);
		termoBusca[strcspn(termoBusca, "\n")] = 0;
		paraMinusculas(termoBusca);

		limparTela();

		printf("Livros na categoria '%s':\n", termoBusca);
		while (fread(&livro, sizeof(Livro), 1, arquivoLivros))
		{
			if (livro.estaAtivo)
			{
				char catCopia[TAM_CATEGORIA];
				strcpy(catCopia, livro.categoria);
				paraMinusculas(catCopia);
				if (strstr(catCopia, termoBusca) != NULL)
				{
					exibirLivro(&livro);
					encontrados = 1;
				}
			}
		}
		break;

	default:
		printf("\n\nOpção inválida!\n");
		return;
	}

	if (!encontrados)
		printf("\n\nNenhum livro encontrado com os critérios de pesquisa.\n");
}

int registrarUsuario(const Papel papel)
{
	FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb");

	if (arquivoContadores == NULL)
	{
		printf("Erro: Não foi possível abrir o arquivo de contadores!\n");
		return 0;
	}

	Contador contadores;
	fread(&contadores, sizeof(Contadores), 1, arquivoContadores);

	if (contadores.contadorUsuarios >= MAX_USUARIOS)
	{
		printf("Erro: Limite máximo de usuários atingido!\n");
		return 0;
	}

	Usuario novoUsuario;
	printf("\n--- Registrar Novo Usuário ---\n");

	printf("Digite o ID: ");
	fgets(novoUsuario.id, TAM_ID, stdin);
	novoUsuario.id[strcspn(novoUsuario.id, "\n")] = 0;

	if (encontrarUsuarioPorId(novoUsuario.id) != -1)
	{
		printf("Erro: ID de usuário já existe!\n");
		return 0;
	}

	printf("Digite o Nome: ");
	fgets(novoUsuario.nome, TAM_NOME, stdin);
	novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0;

	printf("Digite o Email: ");
	fgets(novoUsuario.email, TAM_EMAIL, stdin);
	novoUsuario.email[strcspn(novoUsuario.email, "\n")] = 0;

	printf("Digite o Telefone: ");
	fgets(novoUsuario.telefone, TAM_TELEFONE, stdin);
	novoUsuario.telefone[strcspn(novoUsuario.telefone, "\n")] = 0;

	novoUsuario.papel = papel;
	novoUsuario.contadorEmprestimos = 0;
	novoUsuario.estaAtivo = 1;
	novoUsuario.multasTotais = 0.0;

	FILE *arquivoUsuarios = fopen(USUARIOS_ARQUIVO, "ab");
	fwrite(&novoUsuario, sizeof(Usuario), 1, arquivoUsuarios);

	printf("Usuário registrado com sucesso!\n");
	return 1;
}

void exibirUsuario(const Usuario *usuario)
{
	printf("\nID do Usuário: %s\n", usuario->id);
	printf("Nome: %s\n", usuario->nome);
	printf("Email: %s\n", usuario->email);
	printf("Telefone: %s\n", usuario->telefone);

	// Switc	case para exibir o papel do usuário dependendo do valor da enum
	switch (usuario->papel)
	{
	case ADMINISTRADOR:
		printf("Papel: administrador\n");
		break;
	case BIBLIOTECARIO:
		printf("Papel: bibliotecario\n");
		break;
	case LEITOR:
		printf("Papel: leitor\n");
		break;
	}

	printf("Empréstimos Ativos: %d\n", usuario->contadorEmprestimos);
	printf("Multas Totais: R$%.2f\n", usuario->multasTotais);
}

// Função para encontrar usuário pelo ID
int encontrarUsuarioPorId(char *id, Usuario *usuario)
{
	FILE *arquivo = fopen(USUARIOS_ARQUIVO, "rb");

	if (arquivo == NULL)
		return -1;

	int indice = 0;

	while (fread(usuario, sizeof(Usuario), 1, arquivo) == 1)
	{
		if (strcmp(usuario->id, id) == 0)
		{
			fclose(arquivo);
			return indice;
		}

		indice++;
	}

	fclose(arquivo);
	return -1;
}

int autenticarUsuario(Usuario *usuario)
{
	char idUsuario[TAM_ID];
	printf("\n--- Login no Sistema da Biblioteca ---\n");
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, TAM_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	if (encontrarUsuarioPorId(idUsuario, usuario) != -1)
	{
		printf("Bem-vindo, %s!\n", usuario->nome);
		return 1;
	}

	printf("Erro: Usuário não encontrado!\n");
	return 0;
}

int emprestarLivro()
{
	FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb+");

	if (arquivoContadores == NULL)
	{
		printf("Erro: Não foi possível abrir o arquivo de contadores!\n");
		return 0;
	}

	Contador contadores;
	fread(&contadores, sizeof(Contadores), 1, arquivoContadores);

	if (contadores.contadorEmprestimos >= MAX_EMPRESTIMOS)
	{
		printf("Erro: Limite máximo de empréstimos atingido!\n");
		return 0;
	}

	printf("\n--- Emprestar Livro ---\n");

	char idUsuario[TAM_ID];
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, TAM_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	Usuario usuario;

	int indiceUsuario = encontrarUsuarioPorId(idUsuario, &usuario);
	if (indiceUsuario == -1)
	{
		printf("Erro: Usuário não encontrado!\n");
		return 0;
	}

	if (usuarios[indiceUsuario].contadorEmprestimos >= MAX_EMPRESTIMOS_POR_USUARIO)
	{
		printf("Erro: Usuário atingiu o limite máximo de empréstimos (%d)!\n", MAX_EMPRESTIMOS_POR_USUARIO);
		return 0;
	}

	char isbn[TAM_ISBN];
	printf("Digite o ISBN do Livro: ");
	fgets(isbn, TAM_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	Livro livro;

	int indiceLivro = encontrarLivroPorISBN(isbn, &livro);
	if (indiceLivro == -1)
	{
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	if (livro.copiasDisponiveis <= 0)
	{
		printf("Livro está atualmente indisponível.\n");
		printf("Deseja fazer uma reserva? (1=Sim, 0=Não): ");
		int opcao;
		scanf("%d", &opcao);
		limparBufferEntrada();
		if (opcao == 1)
		{
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
		31};
	if (
		(novoEmprestimo.dataVencimento.ano % 4 == 0 && novoEmprestimo.dataVencimento.ano % 100 != 0) ||
		(novoEmprestimo.dataVencimento.ano % 400 == 0))
		diasNoMes[1] = 29;

	if (novoEmprestimo.dataVencimento.dia > diasNoMes[novoEmprestimo.dataVencimento.mes - 1])
	{
		novoEmprestimo.dataVencimento.dia -= diasNoMes[novoEmprestimo.dataVencimento.mes - 1];
		novoEmprestimo.dataVencimento.mes++;
		if (novoEmprestimo.dataVencimento.mes > 12)
		{
			novoEmprestimo.dataVencimento.mes = 1;
			novoEmprestimo.dataVencimento.ano++;
		}
	}

	novoEmprestimo.foiDevolvido = 0;
	novoEmprestimo.renovacoesUtilizadas = 0;
	novoEmprestimo.valorMulta = 0.0;
	novoEmprestimo.estaAtivo = 1;

	// Atualiza disponibilidade do livro
	livro.copiasDisponiveis--;

	// Atualiza contador de empréstimos e histórico do usuário
	usuario.contadorEmprestimos++;
	for (int i = 0; i < 50; i++)
		if (strlen(usuario.historicoEmprestimos[i]) == 0)
		{
			strcpy(usuario.historicoEmprestimos[i], isbn);
			break;
		}

	FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "ab");
	fwrite(&novoEmprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos);
	fclose(arquivoEmprestimos);

	contadores.contadorEmprestimos++;
	fseek(arquivoContadores, sizeof(Contadores) * -1, SEEK_SET);
	fwrite(&contadores, sizeof(Contadores), 1, arquivoContadores);
	fclose(arquivoContadores);

	printf("Livro emprestado com sucesso!\n");
	printf("Data de Vencimento: %02d/%02d/%d\n", novoEmprestimo.dataVencimento.dia, novoEmprestimo.dataVencimento.mes, novoEmprestimo.dataVencimento.ano);

	// Verifica se o usuário tinha uma reserva para este livro
	FILE *arquivoReservas = fopen(RESERVAS_ARQUIVO, "rb+");
	if (arquivoReservas == NULL)
	{
		printf("Erro: Não foi possível abrir o arquivo de reservas!\n");
		return 0;
	}

	Reserva reserva;
	for (int i = 0; i < contadores.contadorReservas; i++)
	{
		if (fread(&reserva, sizeof(Reserva), 1, arquivoReservas))
			if (reserva.estaAtivo && !reserva.foiAtendida &&
				strcmp(reserva.idUsuario, idUsuario) == 0 &&
				strcmp(reserva.isbn, isbn) == 0)
			{
				reserva.foiAtendida = 1;

				fseek(arquivoReservas, sizeof(Reserva) * -1, SEEK_CUR);
				fwrite(&reserva, sizeof(Reserva), 1, arquivoReservas);

				printf("Sua reserva para este livro foi atendida.\n");
				break;
			}
	}

	fclose(arquivoReservas);
	return 1;
}

// Função para devolver livro
int devolverLivro()
{
	FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb+");
	if (arquivoEmprestimos == NULL)
	{
		printf("Erro: Não foi possível abrir o arquivo de empréstimos!\n");
		return 0;
	}

	printf("\n--- Devolver Livro ---\n");

	char idUsuario[TAM_ID];
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, TAM_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	char isbn[TAM_ISBN];
	printf("Digite o ISBN do Livro: ");
	fgets(isbn, TAM_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	// Encontra empréstimo ativo
	int emprestimoExiste = 0;
	Emprestimo emprestimo;
	for (int i = 0; i < contadores.contadorEmprestimos; i++)
	{
		fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos);
		if (emprestimo.estaAtivo && !emprestimo.foiDevolvido &&
			strcmp(emprestimo.idUsuario, idUsuario) == 0 &&
			strcmp(emprestimo.isbn, isbn) == 0)
		{
			emprestimoExiste = 1;
			break;
		}
	}

	if (!emprestimoExiste)
	{
		printf("Erro: Nenhum empréstimo ativo encontrado para este usuário e livro.\n");
		return 0;
	}

	emprestimo.dataDevolucao = obterDataAtual();
	emprestimo.foiDevolvido = 1;

	// Calcula multa se estiver atrasado
	calcularMulta(&emprestimo);

	// Atualiza disponibilidade do livro
	Livro livro;
	int indiceLivro = encontrarLivroPorISBN(isbn, &livro);
	if (indiceLivro != -1)
	{
		livro.copiasDisponiveis++;
		FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb+");
		fseek(arquivoLivros, sizeof(Livro) * indiceLivro, SEEK_SET);
		fwrite(&livro, sizeof(Livro), 1, arquivoLivros);
		fclose(arquivoLivros);
	}

	// Atualiza contador de empréstimos do usuário
	Usuario usuario;
	int indiceUsuario = encontrarUsuarioPorId(idUsuario, &usuario);

	if (indiceUsuario != -1)
	{
		usuario.contadorEmprestimos--;
		if (emprestimo.valorMulta > 0)
			usuario.multasTotais += emprestimo.valorMulta;

		FILE *arquivoUsuarios = fopen(USUARIOS_ARQUIVO, "rb+");
		fseek(arquivoUsuarios, sizeof(Usuario) * indiceUsuario, SEEK_SET);
		fwrite(&usuario, sizeof(Usuario), 1, arquivoUsuarios);
		fclose(arquivoUsuarios);
	}

	printf("Livro devolvido com sucesso!\n");
	if (emprestimo.valorMulta > 0)
	{
		printf("Multa aplicada: R$%.2f\n", emprestimo.valorMulta);
	}

	return 1;
}

int renovarLivro()
{
	printf("\n--- Renovar Livro ---\n");

	FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb+");

	if (arquivoContadores == NULL)
	{
		printf("Erro: Não foi possível abrir o arquivo de contadores!\n");
		return 0;
	}

	Contador contadores;
	fread(&contadores, sizeof(Contadores), 1, arquivoContadores);
	fclose(arquivoContadores);

	char idUsuario[TAM_ID];
	printf("Digite o ID do Usuário: ");
	fgets(idUsuario, TAM_ID, stdin);
	idUsuario[strcspn(idUsuario, "\n")] = 0;

	char isbn[TAM_ISBN];
	printf("Digite o ISBN do Livro: ");
	fgets(isbn, TAM_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	// Encontra empréstimo
	Emprestimo emprestimo;
	int emprestimoExiste = 0;
	FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb+");

	for (int i = 0; i < contadores.contadorEmprestimos; i++)
	{
		if (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos))
			if (emprestimo.estaAtivo && !emprestimo.foiDevolvido &&
				strcmp(emprestimo.idUsuario, idUsuario) == 0 &&
				strcmp(emprestimo.isbn, isbn) == 0)
			{
				emprestimoExiste = 1;
				break;
			}
	}

	if (!emprestimoExiste)
	{
		printf("Erro: Nenhum empréstimo ativo encontrado para este usuário e livro.\n");
		fclose(arquivoEmprestimos);
		return 0;
	}

	if (emprestimo.renovacoesUtilizadas >= MAX_RENOVACOES)
	{
		printf("Erro: Número máximo de renovações atingido para este livro!\n");
		fclose(arquivoEmprestimos);
		return 0;
	}

	// Verifica se está atrasado
	Data hoje = obterDataAtual();
	if (compararDatas(hoje, emprestimo.dataVencimento) > 0)
	{
		printf("Erro: Não é possível renovar um livro atrasado. Devolva-o primeiro.\n");
		fclose(arquivoEmprestimos);
		return 0;
	}
	// Verifica se o livro tem reservas

	// Renova o empréstimo
	emprestimo.dataVencimento.dia += DIAS_DE_EMPRESTIMO;
	emprestimo.renovacoesUtilizadas++;

	// vetor contendo os dias de cads mês
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
		31};
	if ((emprestimo.dataVencimento.ano % 4 == 0 && emprestimo.dataVencimento.ano % 100 != 0) ||
		(emprestimo.dataVencimento.ano % 400 == 0))
		diasNoMes[1] = 29;

	if (emprestimo.dataVencimento.dia > diasNoMes[emprestimo.dataVencimento.mes - 1])
	{
		emprestimo.dataVencimento.dia -= diasNoMes[emprestimo.dataVencimento.mes - 1];
		emprestimo.dataVencimento.mes++;
		if (emprestimo.dataVencimento.mes > 12)
		{
			emprestimo.dataVencimento.mes = 1;
			emprestimo.dataVencimento.ano++;
		}
	}

	fseek(arquivoEmprestimos, sizeof(Emprestimo) * -1, SEEK_CUR);
	fwrite(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos);
	fclose(arquivoEmprestimos);

	printf(
		"Livro renovado com sucesso!\n"
		"Nova Data de Vencimento: %02d/%02d/%d\n"
		"Renovações utilizadas: %d/%d\n",
		emprestimo.dataVencimento.dia,
		emprestimo.dataVencimento.mes,
		emprestimo.dataVencimento.ano,
		emprestimo.renovacoesUtilizadas,
		MAX_RENOVACOES);

	return 1;
}

void calcularMulta(Emprestimo *emprestimo)
{
	Data hoje = emprestimo->dataDevolucao;
	int diasAtraso = diasEntre(emprestimo->dataVencimento, hoje);

	if (diasAtraso > 0)
	{
		emprestimo->valorMulta = diasAtraso * MULTA_POR_DIA;
	}
	else
		emprestimo->valorMulta = 0.0;
}

void exibirEmprestimosAtivos()
{
	printf("\n--- Empréstimos Ativos ---\n");
	int encontrados = 0;

	FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
	Emprestimo emprestimo;

	while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos))
	{
		if (emprestimo.estaAtivo && !emprestimo.foiDevolvido)
		{
			Livro livro;
			int indiceLivro = encontrarLivroPorISBN(emprestimo.isbn, &livro);
			if (indiceLivro != -1)
			{
				printf(
					"\nID do Empréstimo: %d\n"
					"Usuário: %s\n"
					"Livro: %s\n"
					"Emprestado em: %02d/%02d/%d\n"
					"Vencimento: %02d/%02d/%d\n"
					"Renovações: %d/%d\n",

					emprestimo.idEmprestimo,
					emprestimo.idUsuario,
					livro.titulo,
					emprestimo.dataEmprestimo.dia,
					emprestimo.dataEmprestimo.mes,
					emprestimo.dataEmprestimo.ano,
					emprestimo.dataVencimento.dia,
					emprestimo.dataVencimento.mes,
					emprestimo.dataVencimento.ano,
					emprestimo.renovacoesUtilizadas,
					MAX_RENOVACOES);

				Data hoje = obterDataAtual();
				int diasRestantes = diasEntre(hoje, emprestimo.dataVencimento);
				if (diasRestantes < 0)
				{
					printf("Status: ATRASADO por %d dias\n", -diasRestantes);
				}
				else
				{
					printf("Status: %d dias restantes\n", diasRestantes);
				}
				encontrados++;
			}
		}
	}

	if (!encontrados)
		printf("Nenhum empréstimo ativo.\n");
	else
		printf("\nTotal de Empréstimos Ativos: %d\n", encontrados);

	fclose(arquivoEmprestimos);
}

void exibirEmprestimosUsuario(const char *idUsuario)
{
	printf("\n--- Seus Empréstimos ---\n");
	int encontrados = 0;

	FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
	if (arquivoEmprestimos == NULL)
	{
		printf("Erro ao abrir o arquivo de empréstimos.\n");
		return;
	}

	Emprestimo emprestimo;
	while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos))
	{
		if (emprestimo.estaAtivo && !emprestimo.foiDevolvido && strcmp(emprestimo.idUsuario, idUsuario) == 0)
		{
			Livro livro;
			int indiceLivro = encontrarLivroPorISBN(emprestimo.isbn, &livro);
			if (indiceLivro != -1)
			{
				printf("\nLivro: %s\n", livro.titulo);
				printf("Emprestado em: %02d/%02d/%d\n", emprestimo.dataEmprestimo.dia,
					   emprestimo.dataEmprestimo.mes, emprestimo.dataEmprestimo.ano);
				printf("Vencimento: %02d/%02d/%d\n", emprestimo.dataVencimento.dia,
					   emprestimo.dataVencimento.mes, emprestimo.dataVencimento.ano);

				Data hoje = obterDataAtual();
				int diasRestantes = diasEntre(hoje, emprestimo.dataVencimento);
				if (diasRestantes < 0)
					printf("Status: ATRASADO por %d dias - Devolva imediatamente!\n", -diasRestantes);

				else
					printf("Status: %d dias restantes\n", diasRestantes);

				encontrados++;
			}
		}
	}

	if (!encontrados)
		printf("Nenhum empréstimo ativo.\n");
	else
		printf("\nTotal de Empréstimos Ativos: %d\n", encontrados);

	fclose(arquivoEmprestimos);
}

// SISTEMA DE RESERVAS

int fazerReserva()
{
	char isbn[TAM_ISBN];
	printf("Digite o ISBN do livro para reservar: ");
	fgets(isbn, TAM_ISBN, stdin);
	isbn[strcspn(isbn, "\n")] = 0;

	Livro livro;
	int indiceLivro = encontrarLivroPorISBN(isbn, &livro);
	if (indiceLivro == -1)
	{
		printf("Erro: Livro não encontrado!\n");
		return 0;
	}

	if (livro.copiasDisponiveis > 0)
	{
		printf("Este livro está atualmente disponível. Não é necessário reservar.\n");
		return 0;
	}

	// Verifica se o usuário já tem uma reserva para este livro
	FILE *arquivoReservas = fopen(RESERVAS_ARQUIVO, "rb+");
	if (arquivoReservas == NULL)
	{
		printf("Erro: Não foi possível abrir o arquivo de reservas!\n");
		return 0;
	}

	Reserva reserva;
	while(fread(&reserva, sizeof(Reserva), 1, arquivoReservas))
	{
		if (reserva.estaAtivo && !reserva.foiAtendida &&
			strcmp(reserva.idUsuario, idUsuario) == 0 &&
			strcmp(reserva.isbn, isbn) == 0)
		{
			printf("Você já tem uma reserva ativa para este livro.\n");
			fclose(arquivoReservas);
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

	fwrite(&novaReserva, sizeof(Reserva), 1, arquivoReservas);
	fclose(arquivoReservas);

	printf(
		"Reserva feita com sucesso!\n"
		"Você será notificado quando o livro estiver disponível.\n");

	return 1;
}

void visualizarReservas(const char *idUsuario)
{
	printf("\n--- Suas Reservas ---\n");
	int encontrados = 0;

	FILE *arquivoReservas = fopen(RESERVAS_ARQUIVO, "rb");
	if (arquivoReservas == NULL)
	{
		printf("Erro: Não foi possível abrir o arquivo de reservas!\n");
		return;
	}

	Reserva reserva;
	while(fread(&reserva, sizeof(Reserva), 1, arquivoReservas))
	{
		if (reserva.estaAtivo && strcmp(reserva.idUsuario, idUsuario) == 0)
		{
			Livro livro;
			int indiceLivro = encontrarLivroPorISBN(reserva.isbn, &livro);
			
			if (indiceLivro != -1)
			{
				printf("\nID da Reserva: %d\n", reserva.idReserva);
				printf("Livro: %s\n", livro.titulo);
				printf("Data: %02d/%02d/%d\n", reserva.dataReserva.dia,
					   reserva.dataReserva.mes, reserva.dataReserva.ano);
				printf("Status: %s\n", reserva.foiAtendida ? "Atendida" : "Pendente");
				encontrados ++;
			}
		}
	}

	if (!encontrados)
		printf("Nenhuma reserva encontrada.\n");
	else
		printf("\nTotal de reservas encontradas: %d\n", encontrados);

	fclose(arquivoReservas);
}

// GERAÇÃO DE RELATÓRIOS

void gerarRelatorioMaisEmprestados()
{
	printf("\n=== RELATÓRIO DE LIVROS MAIS EMPRESTADOS ===\n");

	// Cria array para contar empréstimos
	typedef struct
	{
		char isbn[TAM_ISBN];
		int contagem;
	} ContagemEmprestimo;

	ContagemEmprestimo contagens[MAX_LIVROS];
	int contagemUnica = 0;

	// contar empréstimos por livro
	FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
	Emprestimo emprestimo;

	while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos))
	{
		if (emprestimo.estaAtivo)
		{
			int encontrado = 0;
			for (int j = 0; j < contagemUnica; j++)
			{
				if (strcmp(contagens[j].isbn, emprestimo.isbn) == 0)
				{
					contagens[j].contagem++;
					encontrado = 1;
					break;
				}
			}
			if (!encontrado)
			{
				strcpy(contagens[contagemUnica].isbn, emprestimo.isbn);
				contagens[contagemUnica].contagem = 1;
				contagemUnica++;
			}
		}
	}

	// ordena por contagem decrescente
	for (int i = 0; i < contagemUnica - 1; i++)
	{
		for (int j = i + 1; j < contagemUnica; j++)
		{
			if (contagens[j].contagem > contagens[i].contagem)
			{
				ContagemEmprestimo temp = contagens[i];
				contagens[i] = contagens[j];
				contagens[j] = temp;
			}
		}
	}

	// exibe os 10 primeiros livros
	printf("%-5s %-30s %-20s %s\n", "Rank", "Título", "Autor", "Vezes Emprestado");
	imprimirSeparador();

	int limite = contagemUnica < 10 ? contagemUnica : 10;
	for (int i = 0; i < limite; i++)
	{
		Livro livro;
		int indiceLivro = encontrarLivroPorISBN(contagens[i].isbn, &livro);
		if (indiceLivro != -1)
		{
			printf("%-5d %-30s %-20s %d\n", i + 1, livro.titulo,
				   livro.autor, contagens[i].contagem);
		}
	}
}

void gerarRelatorioLivrosDisponiveis(const Livro livros[], int contador)
{
	printf("\n=== RELATÓRIO DE LIVROS DISPONÍVEIS ===\n");
	int encontrados = 0;

	printf("%-30s %-20s %-10s %s\n", "Título", "Autor", "Disponíveis", "Localização");
	imprimirSeparador();

	for (int i = 0; i < contador; i++)
	{
		if (livros[i].estaAtivo && livros[i].copiasDisponiveis > 0)
		{
			printf("%-30s %-20s %d/%-9d %s\n", livros[i].titulo, livros[i].autor,
				   livros[i].copiasDisponiveis, livros[i].totalCopias, livros[i].localizacao);
			encontrados = 1;
		}
	}

	if (!encontrados)
		printf("Nenhum livro disponível.\n");
}

void gerarRelatorioLivrosAtrasados(const Emprestimo emprestimos[], int contadorEmprestimos,
								   const Livro livros[], int contadorLivros)
{
	printf("\n=== RELATÓRIO DE LIVROS ATRASADOS ===\n");
	Data hoje = obterDataAtual();
	int encontrados = 0;

	printf("%-30s %-20s %-15s %s\n", "Título", "Usuário", "Vencimento", "Dias Atraso");
	imprimirSeparador();

	for (int i = 0; i < contadorEmprestimos; i++)
	{
		if (emprestimos[i].estaAtivo && !emprestimos[i].foiDevolvido)
		{
			int diasAtraso = diasEntre(emprestimos[i].dataVencimento, hoje);
			if (diasAtraso > 0)
			{
				int indiceLivro = encontrarLivroPorISBN(livros, contadorLivros, emprestimos[i].isbn);
				if (indiceLivro != -1)
				{
					printf("%-30s %-20s %02d/%02d/%d %13d\n",
						   livros[indiceLivro].titulo, emprestimos[i].idUsuario,
						   emprestimos[i].dataVencimento.dia, emprestimos[i].dataVencimento.mes,
						   emprestimos[i].dataVencimento.ano, diasAtraso);
					encontrados = 1;
				}
			}
		}
	}

	if (!encontrados)
		printf("Nenhum livro atrasado.\n");
}

void gerarRelatorioMultas(const Emprestimo emprestimos[], int contadorEmprestimos, const Usuario usuarios[], int contadorUsuarios)
{
	printf("\n=== RELATÓRIO DE MULTAS ===\n");
	float totalMultas = 0.0;
	int encontrados = 0;

	// Calcula multas de empréstimos ativos em atraso
	Data hoje = obterDataAtual();

	printf("%-20s %-30s %-15s %s\n", "ID do Usuário", "Nome", "Pendente", "Multas Totais");
	imprimirSeparador();

	for (int i = 0; i < contadorUsuarios; i++)
	{
		if (usuarios[i].estaAtivo)
		{
			float multaUsuario = usuarios[i].multasTotais;

			// Adiciona multas de empréstimos atuais em atraso
			for (int j = 0; j < contadorEmprestimos; j++)
			{
				if (emprestimos[j].estaAtivo && !emprestimos[j].foiDevolvido &&
					strcmp(emprestimos[j].idUsuario, usuarios[i].id) == 0)
				{
					int diasAtraso = diasEntre(emprestimos[j].dataVencimento, hoje);
					if (diasAtraso > 0)
					{
						multaUsuario += diasAtraso * MULTA_POR_DIA;
					}
				}
			}

			if (multaUsuario > 0)
			{
				printf("%-20s %-30s R$%-14.2f R$%.2f\n",
					   usuarios[i].id, usuarios[i].nome, multaUsuario, usuarios[i].multasTotais);
				totalMultas += multaUsuario;
				encontrados = 1;
			}
		}
	}

	if (!encontrados)
	{
		printf("Nenhuma multa a relatar.\n");
	}
	else
	{
		printf("\nTotal de Multas Pendentes: R$%.2f\n", totalMultas);
	}
}

void gerarEstatisticasUso(const Emprestimo emprestimos[], int contadorEmprestimos)
{
	printf("\n=== ESTATÍSTICAS DE USO ===\n");

	int emprestimosAtivos = 0;
	int emprestimosDevolvidos = 0;
	int emprestimosAtrasados = 0;
	Data hoje = obterDataAtual();

	for (int i = 0; i < contadorEmprestimos; i++)
	{
		if (emprestimos[i].estaAtivo)
		{
			if (emprestimos[i].foiDevolvido)
			{
				emprestimosDevolvidos++;
			}
			else
			{
				emprestimosAtivos++;
				if (diasEntre(emprestimos[i].dataVencimento, hoje) > 0)
				{
					emprestimosAtrasados++;
				}
			}
		}
	}

	printf("Total de Empréstimos: %d\n", contadorEmprestimos);
	printf("Empréstimos Ativos: %d\n", emprestimosAtivos);
	printf("Empréstimos Devolvidos: %d\n", emprestimosDevolvidos);
	printf("Empréstimos Atrasados: %d\n", emprestimosAtrasados);
	printf("Taxa de Devolução: %.2f%%\n", contadorEmprestimos > 0 ? ((float)emprestimosDevolvidos / contadorEmprestimos * 100) : 0);
}

// SISTEMA DE MENU

void menuAdmin(Usuario *usuarioAtual)
{
	int opcao;

	do
	{
		printf(
			"\n"
			"╔════════════════════════════════════╗\n"
			"║ MENU DO ADMINISTRADOR              ║\n"
			"╠════════════════════════════════════╣\n"
			"║ 1. Gerenciar Livros                ║\n"
			"║ 2. Gerenciar Usuários              ║\n"
			"║ 3. Visualizar Todos os Empréstimos ║\n"
			"║ 4. Gerar Relatórios                ║\n"
			"║ 5. Visualizar Configurações        ║\n"
			"║ 0. Sair                            ║\n"
			"╚════════════════════════════════════╝\n"
			"/n"
			"Digite a opção: ");
		scanf("%d", &opcao);

		limparBufferEntrada();
		limparTela();

		switch (opcao)
		{
		case 1:
		{
			int opcaoLivro;
			do
			{
				printf(
					"\n"
					"╔════════════════════════════════════╗\n"
					"║ Gerenciamento de Livros            ║\n"
					"╠════════════════════════════════════╣\n"
					"║ 1. Adicionar Livro                 ║\n"
					"║ 2. Atualizar Livro                 ║\n"
					"║ 3. Excluir Livro                   ║\n"
					"║ 4. Visualizar Todos os Livros      ║\n"
					"║ 5. Pesquisar Livros                ║\n"
					"║ 0. Voltar                          ║\n"
					"╚════════════════════════════════════╝\n"
					"\n"
					"Digite a opção: ");
				scanf("%d", &opcaoLivro);

				limparBufferEntrada();

				switch (opcaoLivro)
				{
				case 1:
					adicionarLivro();
					break;
				case 2:
					atualizarLivro();
					break;
				case 3:
					excluirLivro();
					break;
				case 4:
					exibirTodosLivros();
					pausarTela();
					break;
				case 5:
					pesquisarLivros();
					pausarTela();
					break;
				}
			} while (opcaoLivro != 0);
			break;
		}

		case 2:
		{
			int opcaoUsuario;
			do
			{
				printf(
					"\n"
					"╔════════════════════════════════════╗\n"
					"║ Gerenciamento de Usuários          ║\n"
					"╠════════════════════════════════════╣\n"
					"║ 1. Registrar Usuário               ║\n"
					"║ 2. Atualizar Usuário               ║\n"
					"║ 3. Excluir Usuário                 ║\n"
					"║ 4. Visualizar Todos os Usuários    ║\n"
					"║ 0. Voltar                          ║\n"
					"╚════════════════════════════════════╝\n"
					"\n"
					"Digite a opção: ");
				scanf("%d", &opcaoUsuario);
				limparBufferEntrada();

				switch (opcaoUsuario)
				{
				case 1:
				{
					printf(
						"Escolha o papel:\n"
						"\t1. Administrador"
						"\t2. Bibliotecário"
						"\t3. Leitor"
						"\n");

					short int papelEntrada;
					scanf("%hd", &papelEntrada);

					Papel papel;
					switch (papelEntrada)
					{
					case 1:
						papel = ADMINISTRADOR;
						break;
					case 2:
						papel = BIBLIOTECARIO;
						break;
					case 3:
						papel = LEITOR;
						break;
					}

					registrarUsuario(usuarios, contadorUsuarios, papel);
					break;
				}
				case 2: /* atualizarUsuario(usuarios, *contadorUsuarios); */
					break;
				case 3: /* excluirUsuario(usuarios, *contadorUsuarios); */
					break;
				case 4:
					exibirTodosUsuarios(usuarios, *contadorUsuarios);
					pausarTela();
					break;
				}
			} while (opcaoUsuario != 0);
			break;
		}

		case 3:
			exibirEmprestimosAtivos(emprestimos, *contadorEmprestimos, livros, *contadorLivros);
			pausarTela();
			break;

		case 4:
		{
			int opcaoRelatorio;
			do
			{
				printf(
					"\n"
					"--- Relatórios ---\n"
					"1. Livros Mais Emprestados\n"
					"2. Livros Disponíveis\n"
					"3. Livros Atrasados\n"
					"4. Relatório de Multas\n"
					"5. Estatísticas de Uso\n"
					"0. Voltar\n"
					"Digite a opção: ");
				scanf("%d", &opcaoRelatorio);
				limparBufferEntrada();

				switch (opcaoRelatorio)
				{
				case 1:
					gerarRelatorioMaisEmprestados(emprestimos, *contadorEmprestimos, livros, *contadorLivros);
					pausarTela();
					break;
				case 2:
					gerarRelatorioLivrosDisponiveis(livros, *contadorLivros);
					pausarTela();
					break;
				case 3:
					gerarRelatorioLivrosAtrasados(emprestimos, *contadorEmprestimos, livros, *contadorLivros);
					pausarTela();
					break;
				case 4:
					gerarRelatorioMultas(emprestimos, *contadorEmprestimos, usuarios, *contadorUsuarios);
					pausarTela();
					break;
				case 5:
					gerarEstatisticasUso(emprestimos, *contadorEmprestimos);
					pausarTela();
					break;
				}
			} while (opcaoRelatorio != 0);
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
	} while (opcao != 0);
}

void menuBibliotecario(Usuario *usuarioAtual, Livro livros[], int *contadorLivros, Usuario usuarios[], int *contadorUsuarios,
					   Emprestimo emprestimos[], int *contadorEmprestimos, Reserva reservas[], int *contadorReservas)
{
	int opcao;

	do
	{
		printf(
			"\n"
			"╔═════════════════════════════════════╗\n"
			"║ MENU DO BIBLIOTECÁRIO               ║\n"
			"╠═════════════════════════════════════╣\n"
			"║ 1. Emprestar Livro                  ║\n"
			"║ 2. Devolver Livro                   ║\n"
			"║ 3. Renovar Livro                    ║\n"
			"║ 4. Visualizar Empréstimos Ativos    ║\n"
			"║ 5. Pesquisar Livros                 ║\n"
			"║ 6. Visualizar Livros Atrasados      ║\n"
			"║ 0. Sair                             ║\n"
			"╚═════════════════════════════════════╝\n"
			"Digite a opção: ");
		scanf("%d", &opcao);

		limparBufferEntrada();
		limparTela();

		switch (opcao)
		{
		case 1:
			emprestarLivro(emprestimos, contadorEmprestimos, livros, *contadorLivros, usuarios, *contadorUsuarios, reservas, contadorReservas);
			pausarTela();
			break;
		case 2:
			devolverLivro(emprestimos, *contadorEmprestimos, livros, *contadorLivros, usuarios, *contadorUsuarios);
			pausarTela();
			break;
		case 3:
			renovarLivro(emprestimos, *contadorEmprestimos, livros, *contadorLivros);
			pausarTela();
			break;
		case 4:
			exibirEmprestimosAtivos(emprestimos, *contadorEmprestimos, livros, *contadorLivros);
			pausarTela();
			break;
		case 5:
			pesquisarLivros(livros, *contadorLivros);
			pausarTela();
			break;
		case 6:
			gerarRelatorioLivrosAtrasados(emprestimos, *contadorEmprestimos, livros, *contadorLivros);
			pausarTela();
			break;
		}
	} while (opcao != 0);
}

void menuLeitor(Usuario *usuarioAtual, Livro livros[], int contadorLivros, Emprestimo emprestimos[], int contadorEmprestimos,
				Reserva reservas[], int *contadorReservas)
{
	int opcao;

	do
	{
		printf(
			"\n"
			"╔════════════════════════════════════╗\n"
			"║     MENU DO LEITOR                 ║\n"
			"╠════════════════════════════════════╣\n"
			"║ Bem-vindo, %-20s ║\n"
			"╠════════════════════════════════════╣\n"
			"║ 1. Pesquisar Livros                ║\n"
			"║ 2. Visualizar Meus Empréstimos     ║\n"
			"║ 3. Reservar Livro                  ║\n"
			"║ 4. Visualizar Minhas Reservas      ║\n"
			"║ 5. Visualizar Minhas Multas        ║\n"
			"║ 0. Sair                            ║\n"
			"╚════════════════════════════════════╝"
			"\n",
			usuarioAtual->nome);

		printf("Digite a opção: ");
		scanf("%d", &opcao);

		limparBufferEntrada();
		limparTela();

		switch (opcao)
		{
		case 1:
			pesquisarLivros(livros, contadorLivros);
			pausarTela();
			break;
		case 2:
			exibirEmprestimosUsuario(emprestimos, contadorEmprestimos, usuarioAtual->id, livros, contadorLivros);
			pausarTela();
			break;
		case 3:
			fazerReserva(reservas, contadorReservas, usuarioAtual->id, livros, contadorLivros);
			pausarTela();
			break;
		case 4:
			visualizarReservas(reservas, *contadorReservas, usuarioAtual->id, livros, contadorLivros);
			pausarTela();
			break;
		case 5:
			// exibe as multas do leitor
			printf("\n--- Suas Multas ---\n");
			printf("Total de Multas Pendentes: R$%.2f\n", usuarioAtual->multasTotais);
			pausarTela();
			break;
		}
	} while (opcao != 0);
}

void exibirTodosUsuarios(const Usuario usuarios[], int numeroDeUsuarios)
{
	printf("\n--- Todos os Usuários ---\n");
	printf("%-10s %-20s %-15s %-10s\n", "ID", "Nome", "Papel", "Empréstimos");
	imprimirSeparador();

	for (int i = 0; i < numeroDeUsuarios; i++)
	{
		if (usuarios[i].estaAtivo)
		{
			printf("%-10s %-20s ", usuarios[i].id, usuarios[i].nome);

			printf("%s", papelParaTexto(usuarios[i].papel));

			printf(" %d\n", usuarios[i].contadorEmprestimos);
		}
	}
}

// função principal
int main()
{
	// exibir logo
	exibirLogo();

	// mensagem de boas vindas
	printf(
		COR_AMARELO
		"╔════════════════════════════════════════════════╗\n"
		"║ SISTEMA DE GESTÃO DE BIBLIOTECA                ║\n"
		"║ Bem-vindo à Biblioteca!                        ║\n"
		"╚════════════════════════════════════════════════╝\n" COR_RESET);

	while (1)
	{ // repete até o usuário não desejar continuar
		Usuario *usuarioAtual;

		FILE *usuariosArquivo = fopen(USUARIOS_ARQUIVO, "rb");

		if (usuariosArquivo == NULL || !fread(&usuarioAtual, sizeof(Usuario), 1, usuariosArquivo))
		{
			printf("Nenhum usuário encontrado!\n");
			Papel papel = ADMINISTRADOR;
			registrarUsuario(papel);
			continue;
		}

		fclose(usuariosArquivo);

		int autenticado = autenticarUsuario(usuarioAtual);

		if (autenticado)
		{
			limparTela();

			if (usuarioAtual->papel == ADMINISTRADOR)
			{
				menuAdmin(usuarioAtual);
			}
			else if (usuarioAtual->papel == BIBLIOTECARIO)
			{
				menuBibliotecario(usuarioAtual, livros, &contadorLivros, usuarios, &contadorUsuarios,
								  emprestimos, &contadorEmprestimos, reservas, &contadorReservas);
			}
			else if (usuarioAtual->papel == LEITOR)
			{
				menuLeitor(usuarioAtual, livros, contadorLivros, emprestimos, contadorEmprestimos,
						   reservas, &contadorReservas);
			}
			else
				printf("Papel de usuário inválido!\n");
		}

		// pergunta se o usuário deseja continuar
		printf("\nDeseja continuar? (1=Sim, 0=Sair): ");
		short int opcaoContinuar; // tipo short porque gasta menos memória

		scanf("%hd", &opcaoContinuar);
		limparBufferEntrada();

		// termina o siclo se o usuário escolheu não continuar
		if (opcaoContinuar == 0)
			break;
	}

	// mensagem de despedida
	printf("\nObrigado por usar o Sistema de Gerenciamento de Biblioteca!\n");
	// fim
	return 0;
}

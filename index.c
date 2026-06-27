#ifndef SISTEMA_DE_GESTAO_DE_BIBLIOTECA
#define SISTEMA_DE_GESTAO_DE_BIBLIOTECA
// 1 para windows, 0 para outros
#define SISTEMA_OPERACIONAL 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// CONSTANTES
#define TAM_ISBN 30
#define TAM_TITULO 100
#define TAM_AUTOR 100
#define TAM_EDITORA 50
#define TAM_CATEGORIA 30
#define TAM_LOCALIZACAO 20
#define TAM_ID 20
#define TAM_NOME 50
#define TAM_EMAIL 50
#define TAM_TELEFONE 9

#define MAX_LIVROS 1000
#define MAX_USUARIOS 500
#define MAX_EMPRESTIMOS 1000
#define MAX_RESERVAS 200
#define MULTA_POR_DIA 50
#define DIAS_DE_EMPRESTIMO 14
#define MAX_RENOVACOES 2
#define MAX_EMPRESTIMOS_POR_USUARIO 5

#define COR_AMARELO "\033[33m"
#define COR_VERDE "\033[32m"
#define COR_RESET "\033[0m"

#define USUARIOS_ARQUIVO "usuarios.bin"
#define LIVROS_ARQUIVO "livros.bin"
#define EMPRESTIMOS_ARQUIVO "emprestimos.bin"
#define RESERVAS_ARQUIVO "reservas.bin"
#define CONTADORES_ARQUIVO "contadores.bin"

typedef struct { int dia, mes, ano; } Data;

typedef struct {
    char isbn[TAM_ISBN];
    char titulo[TAM_TITULO];
    char autor[TAM_AUTOR];
    char editora[TAM_EDITORA];
    char categoria[TAM_CATEGORIA];
    int anoPublicacao;
    int totalCopias;
    int copiasDisponiveis;
    char localizacao[TAM_LOCALIZACAO];
    int estaAtivo;
} Livro;

typedef enum { ADMINISTRADOR, BIBLIOTECARIO, LEITOR } Papel;

typedef struct {
    char id[TAM_ID];
    char nome[TAM_NOME];
    char email[TAM_EMAIL];
    char telefone[TAM_TELEFONE];
    Papel papel;
    int contadorEmprestimos;
    char historicoEmprestimos[50][TAM_ISBN];
    int estaAtivo;
    float multasTotais;
} Usuario;

typedef struct {
    int idEmprestimo;
    char idUsuario[TAM_ID];
    char isbn[TAM_ISBN];
    Data dataEmprestimo, dataVencimento, dataDevolucao;
    int foiDevolvido;
    int renovacoesUtilizadas;
    float valorMulta;
    int estaAtivo;
} Emprestimo;

typedef struct {
    int idReserva;
    char idUsuario[TAM_ID];
    char isbn[TAM_ISBN];
    Data dataReserva;
    int estaAtivo;
    int foiAtendida;
} Reserva;

typedef struct {
    int contadorLivros, contadorUsuarios, contadorEmprestimos, contadorReservas;
} Contadores;

// Protótipos
int adicionarLivro();
int atualizarLivro();
int excluirLivro();
void exibirLivro(const Livro *livro);
void exibirTodosLivros();
int encontrarLivroPorISBN(const char *isbn, Livro *livro);
void pesquisarLivros();
int registrarUsuario(const Papel papel);
void exibirUsuario(const Usuario *usuario);
void exibirTodosUsuarios();
int encontrarUsuarioPorId(const char *id, Usuario *usuario);
int autenticarUsuario(Usuario *usuario);
int emprestarLivro();
int devolverLivro();
int renovarLivro();
void calcularMulta(Emprestimo *emprestimo);
void exibirEmprestimosAtivos();
void exibirEmprestimosUsuario(const char *idUsuario);
int fazerReserva(const char *idUsuario);
void visualizarReservas(const char *idUsuario);
void gerarRelatorioMaisEmprestados();
void gerarRelatorioLivrosDisponiveis();
void gerarRelatorioLivrosAtrasados();
void gerarRelatorioMultas();
void gerarEstatisticasUso();
Data obterDataAtual();
int diasEntre(Data d1, Data d2);
int compararDatas(Data d1, Data d2);
void limparBufferEntrada();
void paraMinusculas(char *str);
void imprimirSeparador();
void pausarTela();
void exibirLogo();
void limparTela();
char *papelParaTexto(Papel papel);
void menuAdmin(Usuario *usuarioAtual);
void menuBibliotecario(Usuario *usuarioAtual);
void menuLeitor(Usuario *usuarioAtual);
#endif

/* ============ FUNÇÕES UTILITÁRIAS ============ */
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
    struct tm data1 = {0}, data2 = {0};
    data1.tm_mday = d1.dia; data1.tm_mon = d1.mes - 1; data1.tm_year = d1.ano - 1900;
    data2.tm_mday = d2.dia; data2.tm_mon = d2.mes - 1; data2.tm_year = d2.ano - 1900;
    time_t tempo1 = mktime(&data1);
    time_t tempo2 = mktime(&data2);
    return (int)(difftime(tempo2, tempo1) / (60 * 60 * 24));
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
    for (int i = 0; str[i]; i++) str[i] = tolower((unsigned char)str[i]);
}

void imprimirSeparador() {
    printf("\n========================================\n");
}

void pausarTela() {
    printf("\nPressione Enter para continuar...");
    limparBufferEntrada();
    limparTela();
}

void exibirLogo() {
    printf(COR_VERDE
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

void limparTela() {
#if SISTEMA_OPERACIONAL == 1
    system("cls");
#else
    system("clear");
#endif
    exibirLogo();
}

char *papelParaTexto(Papel papel) {
    switch (papel) {
        case ADMINISTRADOR: return "administrador";
        case BIBLIOTECARIO: return "bibliotecário";
        case LEITOR:        return "leitor";
        default:            return "desconhecido";
    }
}

/* ============ GERENCIAMENTO DE LIVROS ============ */
int adicionarLivro() {
    FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb+");
    if (arquivoContadores == NULL) return 0;
    Contadores contadores;
    fread(&contadores, sizeof(Contadores), 1, arquivoContadores);

    if (contadores.contadorLivros >= MAX_LIVROS) {
        printf("Erro: Limite máximo de livros atingido!\n");
        fclose(arquivoContadores);
        return 0;
    }

    Livro novoLivro;
    printf("\n--- Adicionar Novo Livro ---\n");
    printf("Digite o ISBN (13 dígitos): ");
    fgets(novoLivro.isbn, TAM_ISBN, stdin);
    novoLivro.isbn[strcspn(novoLivro.isbn, "\n")] = 0;

    /* CORREÇÃO: encontrarLivroPorISBN retorna -1 se NÃO encontrou.
       Queremos bloquear quando ENCONTRAR (retorno != -1). */
    Livro tmp;
    if (encontrarLivroPorISBN(novoLivro.isbn, &tmp) != -1) {
        printf("Erro: Já existe um livro com este ISBN!\n");
        fclose(arquivoContadores);
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

    /* CORREÇÃO: "ab" já cria o arquivo se não existir; fallback desnecessário */
    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "ab");
    if (arquivoLivros == NULL) {
        printf("Erro ao abrir arquivo de livros!\n");
        fclose(arquivoContadores);
        return 0;
    }
    fwrite(&novoLivro, sizeof(Livro), 1, arquivoLivros);
    fclose(arquivoLivros);

    contadores.contadorLivros++;
    rewind(arquivoContadores);
    fwrite(&contadores, sizeof(Contadores), 1, arquivoContadores);
    fclose(arquivoContadores);

    printf("Livro adicionado com sucesso!\n");
    return 1;
}

int atualizarLivro() {
    char isbn[TAM_ISBN];
    printf("\n--- Atualizar Informações do Livro ---\n");
    printf("Digite o ISBN do livro a ser atualizado: ");
    fgets(isbn, TAM_ISBN, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    Livro livro;
    int indice = encontrarLivroPorISBN(isbn, &livro);
    if (indice == -1) {
        printf("Erro: Livro não encontrado!\n");
        return 0;
    }

    printf("\nDetalhes Atuais do Livro:\n");
    exibirLivro(&livro);
    printf("\nDigite as novas informações (pressione Enter para manter o valor atual):\n");

    char entrada[TAM_TITULO];

    printf("Novo Título [%s]: ", livro.titulo);
    fgets(entrada, TAM_TITULO, stdin);
    if (strlen(entrada) > 1) { entrada[strcspn(entrada, "\n")] = 0; strcpy(livro.titulo, entrada); }

    printf("Novo Autor [%s]: ", livro.autor);
    fgets(entrada, TAM_AUTOR, stdin);
    if (strlen(entrada) > 1) { entrada[strcspn(entrada, "\n")] = 0; strcpy(livro.autor, entrada); }

    printf("Nova Editora [%s]: ", livro.editora);
    fgets(entrada, TAM_EDITORA, stdin);
    if (strlen(entrada) > 1) { entrada[strcspn(entrada, "\n")] = 0; strcpy(livro.editora, entrada); }

    printf("Nova Categoria [%s]: ", livro.categoria);
    fgets(entrada, TAM_CATEGORIA, stdin);
    if (strlen(entrada) > 1) { entrada[strcspn(entrada, "\n")] = 0; strcpy(livro.categoria, entrada); }

    printf("Nova Localização [%s]: ", livro.localizacao);
    fgets(entrada, TAM_LOCALIZACAO, stdin);
    if (strlen(entrada) > 1) { entrada[strcspn(entrada, "\n")] = 0; strcpy(livro.localizacao, entrada); }

    printf("Novo Total de Cópias [%d]: ", livro.totalCopias);
    fgets(entrada, 10, stdin);
    if (strlen(entrada) > 1) {
        int novoTotal = atoi(entrada);
        if (novoTotal >= livro.totalCopias - livro.copiasDisponiveis) {
            int emprestados = livro.totalCopias - livro.copiasDisponiveis;
            livro.totalCopias = novoTotal;
            livro.copiasDisponiveis = novoTotal - emprestados;
        } else {
            printf("Erro: Não é possível reduzir as cópias abaixo da quantidade atualmente emprestada!\n");
        }
    }

    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb+");
    if (arquivoLivros == NULL) return 0;
    fseek(arquivoLivros, sizeof(Livro) * indice, SEEK_SET);
    fwrite(&livro, sizeof(Livro), 1, arquivoLivros);
    fclose(arquivoLivros);

    printf("Livro atualizado com sucesso!\n");
    return 1;
}

int excluirLivro() {
    char isbn[TAM_ISBN];
    printf("\n--- Excluir Livro ---\n");
    printf("Digite o ISBN do livro a ser excluído: ");
    fgets(isbn, TAM_ISBN, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    Livro livro;
    int indice = encontrarLivroPorISBN(isbn, &livro);
    if (indice == -1) {
        printf("Erro: Livro não encontrado!\n");
        return 0;
    }
    if (livro.copiasDisponiveis < livro.totalCopias) {
        printf("Erro: Não é possível excluir um livro que está emprestado!\n");
        return 0;
    }

    livro.estaAtivo = 0;
    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb+");
    if (arquivoLivros == NULL) return 0;
    fseek(arquivoLivros, sizeof(Livro) * indice, SEEK_SET);
    fwrite(&livro, sizeof(Livro), 1, arquivoLivros);
    fclose(arquivoLivros);

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

void exibirTodosLivros() {
    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb");
    FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb");

    if (arquivoContadores == NULL || arquivoLivros == NULL) {
        printf("\nNão há livros na biblioteca.\n");
        if (arquivoLivros) fclose(arquivoLivros);
        if (arquivoContadores) fclose(arquivoContadores);
        return;
    }

    Contadores contadores = {0};
    /* CORREÇÃO: a condição estava invertida. Agora verifica falha ou contador zero. */
    if (!fread(&contadores, sizeof(Contadores), 1, arquivoContadores) || contadores.contadorLivros == 0) {
        printf("\nNão há livros na biblioteca.\n");
        fclose(arquivoLivros);
        fclose(arquivoContadores);
        return;
    }

    printf("\n--- Catálogo da Biblioteca ---\n");
    printf("%-15s %-30s %-20s %-10s %s\n", "ISBN", "Título", "Autor", "Disponíveis", "Localização");
    imprimirSeparador();

    Livro livro;
    for (int i = 0; i < contadores.contadorLivros; i++) {
        if (!fread(&livro, sizeof(Livro), 1, arquivoLivros)) break;
        if (livro.estaAtivo) {
            printf("%-15s %-30s %-20s %d/%-9d %s\n",
                livro.isbn, livro.titulo, livro.autor,
                livro.copiasDisponiveis, livro.totalCopias, livro.localizacao);
        }
    }

    /* CORREÇÃO: fecha os arquivos */
    fclose(arquivoLivros);
    fclose(arquivoContadores);
}

int encontrarLivroPorISBN(const char *isbn, Livro *livro) {
    int indice = 0;
    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb");
    if (arquivoLivros == NULL) return -1;

    while (fread(livro, sizeof(Livro), 1, arquivoLivros)) {
        if (strcmp(livro->isbn, isbn) == 0) {
            fclose(arquivoLivros);
            return indice;
        }
        indice++;
    }
    fclose(arquivoLivros);
    return -1;
}

void pesquisarLivros() {
    int opcao;
    printf("\n"
        "╔════════════════════════════════════╗\n"
        "║ Pesquisar Livros                   ║\n"
        "╠════════════════════════════════════╣\n"
        "║ 1. Pesquisar por Título            ║\n"
        "║ 2. Pesquisar por Autor             ║\n"
        "║ 3. Pesquisar por ISBN              ║\n"
        "║ 4. Pesquisar por Categoria         ║\n"
        "╚════════════════════════════════════╝\n"
        "Digite a opção: ");
    scanf("%d", &opcao);
    limparBufferEntrada();

    char termoBusca[TAM_TITULO];
    int encontrados = 0;
    Livro livro;
    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb");
    if (arquivoLivros == NULL) {
        printf("Erro ao abrir catálogo.\n");
        return;
    }

    switch (opcao) {
        case 1:
            printf("\nDigite o título para pesquisar: ");
            fgets(termoBusca, TAM_TITULO, stdin);
            termoBusca[strcspn(termoBusca, "\n")] = 0;
            paraMinusculas(termoBusca);
            limparTela();
            printf("Resultados da Pesquisa:\n");
            while (fread(&livro, sizeof(Livro), 1, arquivoLivros)) {
                if (livro.estaAtivo) {
                    char copia[TAM_TITULO]; strcpy(copia, livro.titulo); paraMinusculas(copia);
                    if (strstr(copia, termoBusca) != NULL) { exibirLivro(&livro); encontrados = 1; }
                }
            }
            break;
        case 2:
            printf("\nDigite o autor para pesquisar: ");
            fgets(termoBusca, TAM_TITULO, stdin);
            termoBusca[strcspn(termoBusca, "\n")] = 0;
            paraMinusculas(termoBusca);
            limparTela();
            printf("Resultados da Pesquisa:\n");
            while (fread(&livro, sizeof(Livro), 1, arquivoLivros)) {
                if (livro.estaAtivo) {
                    char copia[TAM_AUTOR]; strcpy(copia, livro.autor); paraMinusculas(copia);
                    if (strstr(copia, termoBusca) != NULL) { exibirLivro(&livro); encontrados = 1; }
                }
            }
            break;
        case 3:
            printf("\nDigite o ISBN: ");
            fgets(termoBusca, TAM_TITULO, stdin);
            termoBusca[strcspn(termoBusca, "\n")] = 0;
            limparTela();
            printf("Resultado da Pesquisa:\n");
            while (fread(&livro, sizeof(Livro), 1, arquivoLivros)) {
                if (livro.estaAtivo && strcmp(livro.isbn, termoBusca) == 0) {
                    exibirLivro(&livro); encontrados = 1; break;
                }
            }
            break;
        case 4:
            printf("\nDigite a categoria para filtrar: ");
            fgets(termoBusca, TAM_TITULO, stdin);
            termoBusca[strcspn(termoBusca, "\n")] = 0;
            paraMinusculas(termoBusca);
            limparTela();
            printf("Livros na categoria '%s':\n", termoBusca);
            while (fread(&livro, sizeof(Livro), 1, arquivoLivros)) {
                if (livro.estaAtivo) {
                    char copia[TAM_CATEGORIA]; strcpy(copia, livro.categoria); paraMinusculas(copia);
                    if (strstr(copia, termoBusca) != NULL) { exibirLivro(&livro); encontrados = 1; }
                }
            }
            break;
        default:
            printf("\nOpção inválida!\n");
            fclose(arquivoLivros);
            return;
    }

    if (!encontrados) printf("\nNenhum livro encontrado com os critérios de pesquisa.\n");
    /* CORREÇÃO: fecha o arquivo */
    fclose(arquivoLivros);
}

/* ============ GERENCIAMENTO DE USUÁRIOS ============ */
int registrarUsuario(const Papel papel) {
    FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb");
    Contadores contadores = {0};
    if (arquivoContadores != NULL) {
        fread(&contadores, sizeof(Contadores), 1, arquivoContadores);
        fclose(arquivoContadores);
    }

    if (contadores.contadorUsuarios >= MAX_USUARIOS) {
        printf("Erro: Limite máximo de usuários atingido!\n");
        return 0;
    }

    Usuario novoUsuario;
    printf("\n--- Registrar Novo Usuário ---\n");
    printf("Digite o ID: ");
    fgets(novoUsuario.id, TAM_ID, stdin);
    novoUsuario.id[strcspn(novoUsuario.id, "\n")] = 0;

    Usuario tmp;
    if (encontrarUsuarioPorId(novoUsuario.id, &tmp) != -1) {
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
    memset(novoUsuario.historicoEmprestimos, 0, sizeof(novoUsuario.historicoEmprestimos));

    FILE *arquivoUsuarios = fopen(USUARIOS_ARQUIVO, "ab");
    if (arquivoUsuarios == NULL) return 0;
    fwrite(&novoUsuario, sizeof(Usuario), 1, arquivoUsuarios);
    fclose(arquivoUsuarios);

    /* Atualiza contador */
    arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb+");
    if (arquivoContadores == NULL) arquivoContadores = fopen(CONTADORES_ARQUIVO, "wb");
    if (arquivoContadores != NULL) {
        contadores.contadorUsuarios++;
        fwrite(&contadores, sizeof(Contadores), 1, arquivoContadores);
        fclose(arquivoContadores);
    }

    printf("Usuário registrado com sucesso!\n");
    return 1;
}

void exibirUsuario(const Usuario *usuario) {
    printf("\nID do Usuário: %s\n", usuario->id);
    printf("Nome: %s\n", usuario->nome);
    printf("Email: %s\n", usuario->email);
    printf("Telefone: %s\n", usuario->telefone);
    printf("Papel: %s\n", papelParaTexto(usuario->papel));
    printf("Empréstimos Ativos: %d\n", usuario->contadorEmprestimos);
    printf("Multas Totais: R$%.2f\n", usuario->multasTotais);
}

int encontrarUsuarioPorId(const char *id, Usuario *usuario) {
    FILE *arquivo = fopen(USUARIOS_ARQUIVO, "rb");
    if (arquivo == NULL) return -1;
    int indice = 0;
    while (fread(usuario, sizeof(Usuario), 1, arquivo) == 1) {
        if (strcmp(usuario->id, id) == 0) {
            fclose(arquivo);
            return indice;
        }
        indice++;
    }
    fclose(arquivo);
    return -1;
}

int autenticarUsuario(Usuario *usuario) {
    char idUsuario[TAM_ID];
    printf("\n--- Login no Sistema da Biblioteca ---\n");
    printf("Digite o ID do Usuário: ");
    fgets(idUsuario, TAM_ID, stdin);
    idUsuario[strcspn(idUsuario, "\n")] = 0;

    if (encontrarUsuarioPorId(idUsuario, usuario) != -1) {
        printf("Bem-vindo, %s!\n", usuario->nome);
        return 1;
    }
    printf("Erro: Usuário não encontrado!\n");
    return 0;
}

/* ============ EMPRÉSTIMOS ============ */
int emprestarLivro() {
    FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb+");
    if (arquivoContadores == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de contadores!\n");
        return 0;
    }
    Contadores contadores;
    fread(&contadores, sizeof(Contadores), 1, arquivoContadores);

    if (contadores.contadorEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Erro: Limite máximo de empréstimos atingido!\n");
        fclose(arquivoContadores);
        return 0;
    }

    printf("\n--- Emprestar Livro ---\n");
    char idUsuario[TAM_ID];
    printf("Digite o ID do Usuário: ");
    fgets(idUsuario, TAM_ID, stdin);
    idUsuario[strcspn(idUsuario, "\n")] = 0;

    Usuario usuario;
    int indiceUsuario = encontrarUsuarioPorId(idUsuario, &usuario);
    if (indiceUsuario == -1) {
        printf("Erro: Usuário não encontrado!\n");
        fclose(arquivoContadores);
        return 0;
    }
    if (usuario.contadorEmprestimos >= MAX_EMPRESTIMOS_POR_USUARIO) {
        printf("Erro: Usuário atingiu o limite máximo de empréstimos (%d)!\n", MAX_EMPRESTIMOS_POR_USUARIO);
        fclose(arquivoContadores);
        return 0;
    }

    char isbn[TAM_ISBN];
    printf("Digite o ISBN do Livro: ");
    fgets(isbn, TAM_ISBN, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    Livro livro;
    int indiceLivro = encontrarLivroPorISBN(isbn, &livro);
    if (indiceLivro == -1) {
        printf("Erro: Livro não encontrado!\n");
        fclose(arquivoContadores);
        return 0;
    }
    if (livro.copiasDisponiveis <= 0) {
        printf("Livro está atualmente indisponível.\n");
        printf("Deseja fazer uma reserva? (1=Sim, 0=Não): ");
        int opcao; scanf("%d", &opcao); limparBufferEntrada();
        if (opcao == 1) fazerReserva(idUsuario);
        fclose(arquivoContadores);
        return 0;
    }

    Emprestimo novoEmprestimo;
    novoEmprestimo.idEmprestimo = contadores.contadorEmprestimos + 1;
    strcpy(novoEmprestimo.idUsuario, idUsuario);
    strcpy(novoEmprestimo.isbn, isbn);
    novoEmprestimo.dataEmprestimo = obterDataAtual();
    novoEmprestimo.dataVencimento = novoEmprestimo.dataEmprestimo;
    novoEmprestimo.dataVencimento.dia += DIAS_DE_EMPRESTIMO;

    int diasNoMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((novoEmprestimo.dataVencimento.ano % 4 == 0 && novoEmprestimo.dataVencimento.ano % 100 != 0) ||
        (novoEmprestimo.dataVencimento.ano % 400 == 0)) diasNoMes[1] = 29;
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

    livro.copiasDisponiveis--;
    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb+");
    if (arquivoLivros) {
        fseek(arquivoLivros, sizeof(Livro) * indiceLivro, SEEK_SET);
        fwrite(&livro, sizeof(Livro), 1, arquivoLivros);
        fclose(arquivoLivros);
    }

    usuario.contadorEmprestimos++;
    for (int i = 0; i < 50; i++) {
        if (strlen(usuario.historicoEmprestimos[i]) == 0) {
            strcpy(usuario.historicoEmprestimos[i], isbn);
            break;
        }
    }
    FILE *arquivoUsuarios = fopen(USUARIOS_ARQUIVO, "rb+");
    if (arquivoUsuarios) {
        fseek(arquivoUsuarios, sizeof(Usuario) * indiceUsuario, SEEK_SET);
        fwrite(&usuario, sizeof(Usuario), 1, arquivoUsuarios);
        fclose(arquivoUsuarios);
    }

    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "ab");
    if (arquivoEmprestimos == NULL) { fclose(arquivoContadores); return 0; }
    fwrite(&novoEmprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos);
    fclose(arquivoEmprestimos);

    contadores.contadorEmprestimos++;
    /* CORREÇÃO: fseek com SEEK_SET e offset negativo é inválido.
       Usamos rewind() para voltar ao início. */
    rewind(arquivoContadores);
    fwrite(&contadores, sizeof(Contadores), 1, arquivoContadores);
    fclose(arquivoContadores);

    printf("Livro emprestado com sucesso!\n");
    printf("Data de Vencimento: %02d/%02d/%d\n",
        novoEmprestimo.dataVencimento.dia,
        novoEmprestimo.dataVencimento.mes,
        novoEmprestimo.dataVencimento.ano);

    FILE *arquivoReservas = fopen(RESERVAS_ARQUIVO, "rb+");
    if (arquivoReservas != NULL) {
        Contadores contRes;
        FILE *fc = fopen(CONTADORES_ARQUIVO, "rb");
        if (fc) { fread(&contRes, sizeof(Contadores), 1, fc); fclose(fc); }
        else contRes.contadorReservas = 0;

        Reserva reserva;
        for (int i = 0; i < contRes.contadorReservas; i++) {
            long pos = ftell(arquivoReservas);
            if (!fread(&reserva, sizeof(Reserva), 1, arquivoReservas)) break;
            if (reserva.estaAtivo && !reserva.foiAtendida &&
                strcmp(reserva.idUsuario, idUsuario) == 0 &&
                strcmp(reserva.isbn, isbn) == 0) {
                reserva.foiAtendida = 1;
                fseek(arquivoReservas, pos, SEEK_SET);
                fwrite(&reserva, sizeof(Reserva), 1, arquivoReservas);
                printf("Sua reserva para este livro foi atendida.\n");
                break;
            }
        }
        fclose(arquivoReservas);
    }
    return 1;
}

int devolverLivro() {
    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb+");
    if (arquivoEmprestimos == NULL) {
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

    int emprestimoExiste = 0;
    Emprestimo emprestimo;
    long posEmprestimo = 0;
    while (1) {
        posEmprestimo = ftell(arquivoEmprestimos);
        if (!fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos)) break;
        if (emprestimo.estaAtivo && !emprestimo.foiDevolvido &&
            strcmp(emprestimo.idUsuario, idUsuario) == 0 &&
            strcmp(emprestimo.isbn, isbn) == 0) {
            emprestimoExiste = 1;
            break;
        }
    }

    if (!emprestimoExiste) {
        printf("Erro: Nenhum empréstimo ativo encontrado para este usuário e livro.\n");
        fclose(arquivoEmprestimos);
        return 0;
    }

    emprestimo.dataDevolucao = obterDataAtual();
    emprestimo.foiDevolvido = 1;
    calcularMulta(&emprestimo);

    fseek(arquivoEmprestimos, posEmprestimo, SEEK_SET);
    fwrite(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos);
    fclose(arquivoEmprestimos);

    Livro livro;
    int indiceLivro = encontrarLivroPorISBN(isbn, &livro);
    if (indiceLivro != -1) {
        livro.copiasDisponiveis++;
        FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb+");
        if (arquivoLivros) {
            fseek(arquivoLivros, sizeof(Livro) * indiceLivro, SEEK_SET);
            fwrite(&livro, sizeof(Livro), 1, arquivoLivros);
            fclose(arquivoLivros);
        }
    }

    Usuario usuario;
    int indiceUsuario = encontrarUsuarioPorId(idUsuario, &usuario);
    if (indiceUsuario != -1) {
        usuario.contadorEmprestimos--;
        if (emprestimo.valorMulta > 0) usuario.multasTotais += emprestimo.valorMulta;
        FILE *arquivoUsuarios = fopen(USUARIOS_ARQUIVO, "rb+");
        if (arquivoUsuarios) {
            fseek(arquivoUsuarios, sizeof(Usuario) * indiceUsuario, SEEK_SET);
            fwrite(&usuario, sizeof(Usuario), 1, arquivoUsuarios);
            fclose(arquivoUsuarios);
        }
    }

    printf("Livro devolvido com sucesso!\n");
    if (emprestimo.valorMulta > 0) printf("Multa aplicada: R$%.2f\n", emprestimo.valorMulta);
    return 1;
}

int renovarLivro() {
    printf("\n--- Renovar Livro ---\n");
    char idUsuario[TAM_ID];
    printf("Digite o ID do Usuário: ");
    fgets(idUsuario, TAM_ID, stdin);
    idUsuario[strcspn(idUsuario, "\n")] = 0;

    char isbn[TAM_ISBN];
    printf("Digite o ISBN do Livro: ");
    fgets(isbn, TAM_ISBN, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb+");
    if (arquivoEmprestimos == NULL) return 0;

    Emprestimo emprestimo;
    int emprestimoExiste = 0;
    long posEmprestimo = 0;
    while (1) {
        posEmprestimo = ftell(arquivoEmprestimos);
        if (!fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos)) break;
        if (emprestimo.estaAtivo && !emprestimo.foiDevolvido &&
            strcmp(emprestimo.idUsuario, idUsuario) == 0 &&
            strcmp(emprestimo.isbn, isbn) == 0) {
            emprestimoExiste = 1;
            break;
        }
    }

    if (!emprestimoExiste) {
        printf("Erro: Nenhum empréstimo ativo encontrado para este usuário e livro.\n");
        fclose(arquivoEmprestimos);
        return 0;
    }
    if (emprestimo.renovacoesUtilizadas >= MAX_RENOVACOES) {
        printf("Erro: Número máximo de renovações atingido para este livro!\n");
        fclose(arquivoEmprestimos);
        return 0;
    }

    Data hoje = obterDataAtual();
    if (compararDatas(hoje, emprestimo.dataVencimento) > 0) {
        printf("Erro: Não é possível renovar um livro atrasado. Devolva-o primeiro.\n");
        fclose(arquivoEmprestimos);
        return 0;
    }

    emprestimo.dataVencimento.dia += DIAS_DE_EMPRESTIMO;
    emprestimo.renovacoesUtilizadas++;

    int diasNoMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((emprestimo.dataVencimento.ano % 4 == 0 && emprestimo.dataVencimento.ano % 100 != 0) ||
        (emprestimo.dataVencimento.ano % 400 == 0)) diasNoMes[1] = 29;
    if (emprestimo.dataVencimento.dia > diasNoMes[emprestimo.dataVencimento.mes - 1]) {
        emprestimo.dataVencimento.dia -= diasNoMes[emprestimo.dataVencimento.mes - 1];
        emprestimo.dataVencimento.mes++;
        if (emprestimo.dataVencimento.mes > 12) {
            emprestimo.dataVencimento.mes = 1;
            emprestimo.dataVencimento.ano++;
        }
    }

    fseek(arquivoEmprestimos, posEmprestimo, SEEK_SET);
    fwrite(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos);
    fclose(arquivoEmprestimos);

    printf("Livro renovado com sucesso!\nNova Data de Vencimento: %02d/%02d/%d\nRenovações utilizadas: %d/%d\n",
        emprestimo.dataVencimento.dia, emprestimo.dataVencimento.mes, emprestimo.dataVencimento.ano,
        emprestimo.renovacoesUtilizadas, MAX_RENOVACOES);
    return 1;
}

void calcularMulta(Emprestimo *emprestimo) {
    Data hoje = emprestimo->dataDevolucao;
    int diasAtraso = diasEntre(emprestimo->dataVencimento, hoje);
    emprestimo->valorMulta = (diasAtraso > 0) ? diasAtraso * MULTA_POR_DIA : 0.0;
}

void exibirEmprestimosAtivos() {
    printf("\n--- Empréstimos Ativos ---\n");
    int encontrados = 0;
    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
    if (!arquivoEmprestimos) return;

    Emprestimo emprestimo;
    while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos)) {
        if (emprestimo.estaAtivo && !emprestimo.foiDevolvido) {
            Livro livro;
            if (encontrarLivroPorISBN(emprestimo.isbn, &livro) != -1) {
                printf("\nID do Empréstimo: %d\nUsuário: %s\nLivro: %s\n"
                    "Emprestado em: %02d/%02d/%d\nVencimento: %02d/%02d/%d\nRenovações: %d/%d\n",
                    emprestimo.idEmprestimo, emprestimo.idUsuario, livro.titulo,
                    emprestimo.dataEmprestimo.dia, emprestimo.dataEmprestimo.mes, emprestimo.dataEmprestimo.ano,
                    emprestimo.dataVencimento.dia, emprestimo.dataVencimento.mes, emprestimo.dataVencimento.ano,
                    emprestimo.renovacoesUtilizadas, MAX_RENOVACOES);
                Data hoje = obterDataAtual();
                int diasRestantes = diasEntre(hoje, emprestimo.dataVencimento);
                if (diasRestantes < 0) printf("Status: ATRASADO por %d dias\n", -diasRestantes);
                else printf("Status: %d dias restantes\n", diasRestantes);
                encontrados++;
            }
        }
    }
    if (!encontrados) printf("Nenhum empréstimo ativo.\n");
    else printf("\nTotal de Empréstimos Ativos: %d\n", encontrados);
    fclose(arquivoEmprestimos);
}

void exibirEmprestimosUsuario(const char *idUsuario) {
    printf("\n--- Seus Empréstimos ---\n");
    int encontrados = 0;
    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
    if (!arquivoEmprestimos) { printf("Erro ao abrir o arquivo de empréstimos.\n"); return; }

    Emprestimo emprestimo;
    while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos)) {
        if (emprestimo.estaAtivo && !emprestimo.foiDevolvido && strcmp(emprestimo.idUsuario, idUsuario) == 0) {
            Livro livro;
            if (encontrarLivroPorISBN(emprestimo.isbn, &livro) != -1) {
                printf("\nLivro: %s\n", livro.titulo);
                printf("Emprestado em: %02d/%02d/%d\n", emprestimo.dataEmprestimo.dia, emprestimo.dataEmprestimo.mes, emprestimo.dataEmprestimo.ano);
                printf("Vencimento: %02d/%02d/%d\n", emprestimo.dataVencimento.dia, emprestimo.dataVencimento.mes, emprestimo.dataVencimento.ano);
                Data hoje = obterDataAtual();
                int diasRestantes = diasEntre(hoje, emprestimo.dataVencimento);
                if (diasRestantes < 0) printf("Status: ATRASADO por %d dias - Devolva imediatamente!\n", -diasRestantes);
                else printf("Status: %d dias restantes\n", diasRestantes);
                encontrados++;
            }
        }
    }
    if (!encontrados) printf("Nenhum empréstimo ativo.\n");
    else printf("\nTotal de Empréstimos Ativos: %d\n", encontrados);
    fclose(arquivoEmprestimos);
}

/* ============ RESERVAS ============ */
int fazerReserva(const char *idUsuario) {
    FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb");
    if (arquivoContadores == NULL) { printf("Erro: Não foi possível abrir o arquivo de contadores!\n"); return 0; }
    Contadores contadores = {0};
    fread(&contadores, sizeof(Contadores), 1, arquivoContadores);
    fclose(arquivoContadores);

    char isbn[TAM_ISBN];
    printf("Digite o ISBN do livro para reservar: ");
    fgets(isbn, TAM_ISBN, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    Livro livro;
    int indiceLivro = encontrarLivroPorISBN(isbn, &livro);
    if (indiceLivro == -1) { printf("Erro: Livro não encontrado!\n"); return 0; }
    if (livro.copiasDisponiveis > 0) {
        printf("Este livro está atualmente disponível. Não é necessário reservar.\n");
        return 0;
    }

    /* CORREÇÃO: usa "ab+" para criar o arquivo se não existir */
    FILE *arquivoReservas = fopen(RESERVAS_ARQUIVO, "ab+");
    if (arquivoReservas == NULL) { printf("Erro: Não foi possível abrir o arquivo de reservas!\n"); return 0; }
    rewind(arquivoReservas);

    Reserva reserva;
    while (fread(&reserva, sizeof(Reserva), 1, arquivoReservas)) {
        if (reserva.estaAtivo && !reserva.foiAtendida &&
            strcmp(reserva.idUsuario, idUsuario) == 0 &&
            strcmp(reserva.isbn, isbn) == 0) {
            printf("Você já tem uma reserva ativa para este livro.\n");
            fclose(arquivoReservas);
            return 0;
        }
    }

    Reserva novaReserva;
    novaReserva.idReserva = contadores.contadorReservas + 1;
    strcpy(novaReserva.idUsuario, idUsuario);
    strcpy(novaReserva.isbn, isbn);
    novaReserva.dataReserva = obterDataAtual();
    novaReserva.estaAtivo = 1;
    novaReserva.foiAtendida = 0;
    fwrite(&novaReserva, sizeof(Reserva), 1, arquivoReservas);
    fclose(arquivoReservas);

    /* Atualiza contador */
    arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb+");
    if (arquivoContadores == NULL) arquivoContadores = fopen(CONTADORES_ARQUIVO, "wb");
    if (arquivoContadores) {
        contadores.contadorReservas++;
        fwrite(&contadores, sizeof(Contadores), 1, arquivoContadores);
        fclose(arquivoContadores);
    }

    printf("Reserva feita com sucesso!\nVocê será notificado quando o livro estiver disponível.\n");
    return 1;
}

void visualizarReservas(const char *idUsuario) {
    printf("\n--- Suas Reservas ---\n");
    int encontrados = 0;
    FILE *arquivoReservas = fopen(RESERVAS_ARQUIVO, "rb");
    if (arquivoReservas == NULL) { printf("Nenhuma reserva encontrada.\n"); return; }

    Reserva reserva;
    while (fread(&reserva, sizeof(Reserva), 1, arquivoReservas)) {
        if (reserva.estaAtivo && strcmp(reserva.idUsuario, idUsuario) == 0) {
            Livro livro;
            if (encontrarLivroPorISBN(reserva.isbn, &livro) != -1) {
                printf("\nID da Reserva: %d\nLivro: %s\nData: %02d/%02d/%d\nStatus: %s\n",
                    reserva.idReserva, livro.titulo,
                    reserva.dataReserva.dia, reserva.dataReserva.mes, reserva.dataReserva.ano,
                    reserva.foiAtendida ? "Atendida" : "Pendente");
                encontrados++;
            }
        }
    }
    if (!encontrados) printf("Nenhuma reserva encontrada.\n");
    else printf("\nTotal de reservas encontradas: %d\n", encontrados);
    fclose(arquivoReservas);
}

/* ============ RELATÓRIOS ============ */
void gerarRelatorioMaisEmprestados() {
    printf("\n=== RELATÓRIO DE LIVROS MAIS EMPRESTADOS ===\n");
    typedef struct { char isbn[TAM_ISBN]; int contagem; } ContagemEmprestimo;
    ContagemEmprestimo contagens[MAX_LIVROS];
    int contagemUnica = 0;

    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
    if (!arquivoEmprestimos) return;

    Emprestimo emprestimo;
    while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos)) {
        if (emprestimo.estaAtivo) {
            int encontrado = 0;
            for (int j = 0; j < contagemUnica; j++) {
                if (strcmp(contagens[j].isbn, emprestimo.isbn) == 0) {
                    contagens[j].contagem++; encontrado = 1; break;
                }
            }
            if (!encontrado && contagemUnica < MAX_LIVROS) {
                strcpy(contagens[contagemUnica].isbn, emprestimo.isbn);
                contagens[contagemUnica].contagem = 1;
                contagemUnica++;
            }
        }
    }
    fclose(arquivoEmprestimos);

    for (int i = 0; i < contagemUnica - 1; i++)
        for (int j = i + 1; j < contagemUnica; j++)
            if (contagens[j].contagem > contagens[i].contagem) {
                ContagemEmprestimo temp = contagens[i];
                contagens[i] = contagens[j]; contagens[j] = temp;
            }

    printf("%-5s %-30s %-20s %s\n", "Rank", "Título", "Autor", "Vezes Emprestado");
    imprimirSeparador();
    int limite = contagemUnica < 10 ? contagemUnica : 10;
    for (int i = 0; i < limite; i++) {
        Livro livro;
        if (encontrarLivroPorISBN(contagens[i].isbn, &livro) != -1)
            printf("%-5d %-30s %-20s %d\n", i + 1, livro.titulo, livro.autor, contagens[i].contagem);
    }
}

void gerarRelatorioLivrosDisponiveis() {
    printf("\n=== RELATÓRIO DE LIVROS DISPONÍVEIS ===\n");
    FILE *arquivoLivros = fopen(LIVROS_ARQUIVO, "rb");
    if (!arquivoLivros) { printf("Erro ao abrir arquivo!\n"); return; }

    int encontrados = 0;
    printf("%-30s %-20s %-10s %s\n", "Título", "Autor", "Disponíveis", "Localização");
    imprimirSeparador();

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, arquivoLivros)) {
        if (livro.estaAtivo && livro.copiasDisponiveis > 0) {
            printf("%-30s %-20s %d/%-3d %s\n", livro.titulo, livro.autor, livro.copiasDisponiveis, livro.totalCopias, livro.localizacao);
            encontrados++;
        }
    }
    if (!encontrados) printf("Nenhum livro disponível.\n");
    else printf("\nTotal de Livros Disponíveis: %d\n", encontrados);
    fclose(arquivoLivros);
}

void gerarRelatorioLivrosAtrasados() {
    printf("\n=== RELATÓRIO DE LIVROS ATRASADOS ===\n");
    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
    if (!arquivoEmprestimos) { printf("Erro ao abrir arquivo!\n"); return; }

    Data hoje = obterDataAtual();
    int encontrados = 0;
    printf("%-30s %-20s %-15s %s\n", "Título", "Usuário", "Vencimento", "Dias Atraso");
    imprimirSeparador();

    Emprestimo emprestimo;
    while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos)) {
        if (emprestimo.estaAtivo && !emprestimo.foiDevolvido) {
            int diasAtraso = diasEntre(emprestimo.dataVencimento, hoje);
            if (diasAtraso > 0) {
                Livro livro;
                if (encontrarLivroPorISBN(emprestimo.isbn, &livro) != -1) {
                    printf("%-30s %-20s %02d/%02d/%d %13d\n",
                        livro.titulo, emprestimo.idUsuario,
                        emprestimo.dataVencimento.dia, emprestimo.dataVencimento.mes, emprestimo.dataVencimento.ano, diasAtraso);
                    encontrados++;
                }
            }
        }
    }
    if (!encontrados) printf("Nenhum livro atrasado.\n");
    else printf("\nTotal de Livros Atrasados: %d\n", encontrados);
    /*fecha o arquivo */
    fclose(arquivoEmprestimos);
}

void gerarRelatorioMultas() {
    printf("\n=== RELATÓRIO DE MULTAS ===\n");
    FILE *arquivoUsuarios = fopen(USUARIOS_ARQUIVO, "rb");
    if (!arquivoUsuarios) { printf("Erro ao abrir usuários!\n"); return; }
    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
    if (!arquivoEmprestimos) { printf("Erro ao abrir empréstimos!\n"); fclose(arquivoUsuarios); return; }

    float totalMultas = 0.0;
    int encontrados = 0;
    Data hoje = obterDataAtual();

    printf("%-20s %-30s %-15s %s\n", "ID do Usuário", "Nome", "Pendente", "Multas Totais");
    imprimirSeparador();

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivoUsuarios) == 1) {
        if (usuario.estaAtivo) {
            float multaUsuario = usuario.multasTotais;
            Emprestimo emprestimo;
            rewind(arquivoEmprestimos);
            while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos)) {
                if (emprestimo.estaAtivo && !emprestimo.foiDevolvido && strcmp(emprestimo.idUsuario, usuario.id) == 0) {
                    int diasAtraso = diasEntre(emprestimo.dataVencimento, hoje);
                    if (diasAtraso > 0) multaUsuario += diasAtraso * MULTA_POR_DIA;
                }
            }
            if (multaUsuario > 0) {
                printf("%-20s %-30s R$%-14.2f R$%.2f\n", usuario.id, usuario.nome, multaUsuario, usuario.multasTotais);
                totalMultas += multaUsuario;
                encontrados = 1;
            }
        }
    }
    if (!encontrados) printf("Nenhuma multa a relatar.\n");
    else printf("\nTotal de Multas Pendentes: %.2fMZN\n", totalMultas);

    /* fecha os arquivos */
    fclose(arquivoUsuarios);
    fclose(arquivoEmprestimos);
}

void gerarEstatisticasUso() {
    printf("\n=== ESTATÍSTICAS DE USO ===\n");
    FILE *arquivoEmprestimos = fopen(EMPRESTIMOS_ARQUIVO, "rb");
    if (!arquivoEmprestimos) { printf("Erro ao abrir empréstimos!\n"); return; }
    FILE *arquivoContadores = fopen(CONTADORES_ARQUIVO, "rb");
    if (!arquivoContadores) { fclose(arquivoEmprestimos); return; }

    Contadores contadores;
    fread(&contadores, sizeof(Contadores), 1, arquivoContadores);
    fclose(arquivoContadores);

    int emprestimosAtivos = 0, emprestimosDevolvidos = 0, emprestimosAtrasados = 0;
    Data hoje = obterDataAtual();
    Emprestimo emprestimo;
    while (fread(&emprestimo, sizeof(Emprestimo), 1, arquivoEmprestimos) == 1) {
        if (emprestimo.estaAtivo) {
            if (emprestimo.foiDevolvido) emprestimosDevolvidos++;
            else {
                emprestimosAtivos++;
                if (diasEntre(emprestimo.dataVencimento, hoje) > 0) emprestimosAtrasados++;
            }
        }
    }
    fclose(arquivoEmprestimos);

    printf("Total de Empréstimos: %d\nEmpréstimos Ativos: %d\nEmpréstimos Devolvidos: %d\n"
        "Empréstimos Atrasados: %d\nTaxa de Devolução: %.2f%%\n",
        contadores.contadorEmprestimos, emprestimosAtivos, emprestimosDevolvidos, emprestimosAtrasados,
        contadores.contadorEmprestimos > 0 ? ((float)emprestimosDevolvidos / contadores.contadorEmprestimos * 100) : 0);
}

/* ============ MENUS ============ */
void menuAdmin(Usuario *usuarioAtual) {
    int opcao;
    do {
        printf("\n"
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
            "Digite a opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        limparTela();

        switch (opcao) {
            case 1: {
                int opcaoLivro;
                do {
                    printf("\n"
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
                        "Digite a opção: ");
                    scanf("%d", &opcaoLivro);
                    limparBufferEntrada();
                    switch (opcaoLivro) {
                        case 1: adicionarLivro(); break;
                        case 2: atualizarLivro(); break;
                        case 3: excluirLivro(); break;
                        case 4: exibirTodosLivros(); pausarTela(); break;
                        case 5: pesquisarLivros(); pausarTela(); break;
                    }
                } while (opcaoLivro != 0);
                break;
            }
            case 2: {
                int opcaoUsuario;
                do {
                    printf("\n"
                        "╔════════════════════════════════════╗\n"
                        "║ Gerenciamento de Usuários          ║\n"
                        "╠════════════════════════════════════╣\n"
                        "║ 1. Registrar Usuário               ║\n"
                        "║ 2. Visualizar Todos os Usuários    ║\n"
                        "║ 0. Voltar                          ║\n"
                        "╚════════════════════════════════════╝\n"
                        "Digite a opção: ");
                    scanf("%d", &opcaoUsuario);
                    limparBufferEntrada();
                    switch (opcaoUsuario) {
                        case 1: {
                            printf("Escolha o papel:\n\t1. Administrador\n\t2. Bibliotecário\n\t3. Leitor\n");
                            short int papelEntrada;
                            scanf("%hd", &papelEntrada);
                 						Papel papel = LEITOR;
                            switch (papelEntrada) {
                                case 1: papel = ADMINISTRADOR; break;
                                case 2: papel = BIBLIOTECARIO; break;
                                case 3: papel = LEITOR; break;
                                default: printf("Papel inválido. Usando LEITOR.\n"); break;
                            }
                            registrarUsuario(papel);
                            break;
                        }
                      	case 0: exibirTodosUsuarios(); pausarTela(); break;
                    }
                } while (opcaoUsuario != 0);
                break;
            }
            case 3: exibirEmprestimosAtivos(); pausarTela(); break;
            case 4: {
                int opcaoRelatorio;
                do {
                    printf("\n--- Relatórios ---\n"
                        "1. Livros Mais Emprestados\n2. Livros Disponíveis\n"
                        "3. Livros Atrasados\n4. Relatório de Multas\n"
                        "5. Estatísticas de Uso\n0. Voltar\nDigite a opção: ");
                    scanf("%d", &opcaoRelatorio);
                    limparBufferEntrada();
                    switch (opcaoRelatorio) {
                        case 1: gerarRelatorioMaisEmprestados(); pausarTela(); break;
                        case 2: gerarRelatorioLivrosDisponiveis(); pausarTela(); break;
                        case 3: gerarRelatorioLivrosAtrasados(); pausarTela(); break;
                        case 4: gerarRelatorioMultas(); pausarTela(); break;
                        case 5: gerarEstatisticasUso(); pausarTela(); break;
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

void menuBibliotecario(Usuario *usuarioAtual) {
    int opcao;
    do {
        printf("\n"
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
        switch (opcao) {
            case 1: emprestarLivro(); pausarTela(); break;
            case 2: devolverLivro(); pausarTela(); break;
            case 3: renovarLivro(); pausarTela(); break;
            case 4: exibirEmprestimosAtivos(); pausarTela(); break;
            case 5: pesquisarLivros(); pausarTela(); break;
            case 6: gerarRelatorioLivrosAtrasados(); pausarTela(); break;
        }
    } while (opcao != 0);
}

void menuLeitor(Usuario *usuarioAtual) {
    int opcao;
    do {
        printf("\n"
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
            "╚════════════════════════════════════╝\n",
            usuarioAtual->nome);
        printf("Digite a opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        limparTela();
        switch (opcao) {
            case 1: pesquisarLivros(); pausarTela(); break;
            case 2: exibirEmprestimosUsuario(usuarioAtual->id); pausarTela(); break;
            case 3: fazerReserva(usuarioAtual->id); pausarTela(); break;
            case 4: visualizarReservas(usuarioAtual->id); pausarTela(); break;
            case 5:
                printf("\n--- Suas Multas ---\n");
                printf("Total de Multas Pendentes: %.2fMZN\n", usuarioAtual->multasTotais);
                pausarTela();
                break;
        }
    } while (opcao != 0);
}

void exibirTodosUsuarios() {
    printf("\n--- Todos os Usuários ---\n");
    FILE *arquivoUsuarios = fopen(USUARIOS_ARQUIVO, "rb");
    if (!arquivoUsuarios) { printf("Erro ao abrir arquivo!\n"); return; }

    printf("%-10s %-20s %-15s %-10s\n", "ID", "Nome", "Papel", "Empréstimos");
    imprimirSeparador();

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivoUsuarios)) {
        if (usuario.estaAtivo) {
            printf("%-10s %-20s %-15s %d\n", usuario.id, usuario.nome, papelParaTexto(usuario.papel), usuario.contadorEmprestimos);
        }
    }
    fclose(arquivoUsuarios);
}

/* ============ MAIN ============ */
int main() {
    exibirLogo();
    printf(COR_AMARELO
        "╔════════════════════════════════════════════════╗\n"
        "║ SISTEMA DE GESTÃO DE BIBLIOTECA                ║\n"
        "║ Bem-vindo à Biblioteca!                        ║\n"
        "╚════════════════════════════════════════════════╝\n" COR_RESET);

    while (1) {
      
        FILE *usuariosArquivo = fopen(USUARIOS_ARQUIVO, "rb");
        int temUsuarios = 0;
        if (usuariosArquivo != NULL) {
            Usuario tmp;
            if (fread(&tmp, sizeof(Usuario), 1, usuariosArquivo) == 1)
                temUsuarios = 1;
            fclose(usuariosArquivo);
        }

        if (!temUsuarios) {
            printf("Nenhum usuário encontrado! Criando administrador padrão...\n");
            registrarUsuario(ADMINISTRADOR);
            continue;
        }

        Usuario usuarioAtual;
        int autenticado = autenticarUsuario(&usuarioAtual);
        if (autenticado) {
            limparTela();
            if (usuarioAtual.papel == ADMINISTRADOR)       menuAdmin(&usuarioAtual);
            else if (usuarioAtual.papel == BIBLIOTECARIO)  menuBibliotecario(&usuarioAtual);
            else if (usuarioAtual.papel == LEITOR)         menuLeitor(&usuarioAtual);
            else printf("Papel de usuário inválido!\n");
        }

        printf("\nDeseja continuar? (1=Sim, 0=Sair): ");
        short int opcaoContinuar;
        scanf("%hd", &opcaoContinuar);
        limparBufferEntrada();
        if (opcaoContinuar == 0) break;
    }

    printf("\nObrigado por usar o Sistema de Gerenciamento de Biblioteca!\n");
    return 0;
}
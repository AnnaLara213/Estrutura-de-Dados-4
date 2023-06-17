#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
 
#define MAX_UFS 27
#define MAX_FABRICANTES 5
#define MAX_CLIENTES 30
#define MAX_PRODUTOS 50
 
void cadastrarFabricante();
void cadastrarCliente();
void cadastrarProduto();
void listarFabricantes();
void listarClientes();
void listarProdutos();
void listarProdutosPorFabricante();
void listarEstadosMaiorValor();
void listarFabricantesMenorValor();
void listarProdutosOrdemCrescenteValor();
void listarProdutosOrdemCrescenteLucro();
void verificarClientesIdadeSuperior60();
void exibirMenuSecundario();
 
typedef struct {
    char sigla[3];
    char nome[50];
} UF;
 
typedef struct {
    int codigo;
    char marca[50];
    char site[100];
    int telefone;
    UF uf;
} Fabricante;
 
typedef struct {
    char nome[50];
    int idade;
} Cliente;
struct Cliente {
    char nome[50];
    // outras informações do cliente
};
 
typedef struct {
    char descricao[100];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    Fabricante fabricante;
} Produto;
 
UF ufs[MAX_UFS] = {
    {"AC", "Acre"},
    {"AL", "Alagoas"},
    {"AP", "Amapá"},
    {"AM", "Amazonas"},
    {"BA", "Bahia"},
    {"CE", "Ceará"},
    {"DF", "Distrito Federal"},
    {"ES", "Espírito Santo"},
    {"GO", "Goiás"},
    {"MA", "Maranhão"},
    {"MT", "Mato Grosso"},
    {"MS", "Mato Grosso do Sul"},
    {"MG", "Minas Gerais"},
    {"PA", "Pará"},
    {"PB", "Paraíba"},
    {"PR", "Paraná"},
    {"PE", "Pernambuco"},
    {"PI", "Piauí"},
    {"RJ", "Rio de Janeiro"},
    {"RN", "Rio Grande do Norte"},
    {"RS", "Rio Grande do Sul"},
    {"RO", "Rondônia"},
    {"RR", "Roraima"},
    {"SC", "Santa Catarina"},
    {"SP", "São Paulo"},
    {"SE", "Sergipe"},
    {"TO", "Tocantins"}
};
 
Fabricante fabricantes[MAX_FABRICANTES];
Cliente clientes[MAX_CLIENTES];
Produto produtos[MAX_PRODUTOS];
 
int numFabricantes = 0;
int numClientes = 0;
int numProdutos = 0;
 
void cadastrarFabricante() {
	int i = 0;
 
    if (numFabricantes >= MAX_FABRICANTES) {
        printf("Limite de fabricantes atingido.\n");
        return;
    }
 
    Fabricante fabricante;
 
    printf("Código: ");
    scanf("%d", &fabricante.codigo);
    fflush(stdin);
 
    printf("Marca: ");
    scanf("%s", fabricante.marca);
    fflush(stdin);
 
    printf("Site: ");
    scanf("%s", fabricante.site);
    fflush(stdin);
 
    printf("Telefone: ");
    scanf("%d", &fabricante.telefone);
    fflush(stdin);
 
    printf("UF (sigla): ");
    scanf("%s", fabricante.uf.sigla);
    fflush(stdin);
    
    fabricante.uf.sigla[0] = toupper(fabricante.uf.sigla[0]); 
    fabricante.uf.sigla[1] = toupper(fabricante.uf.sigla[1]); 
 
    // Procurar o nome da UF correspondente à sigla informada
    for (i = 0; i < MAX_UFS; i++) {
        if (strcmp(ufs[i].sigla, fabricante.uf.sigla) == 0) {
            strcpy(fabricante.uf.nome, ufs[i].nome);
            break;
        }
    }
 
    // Verificar se a UF foi encontrada
    if (i == MAX_UFS) {
        printf("UF inválida.\n");
        return;
    }
 
 
    fabricantes[numFabricantes] = fabricante;
    numFabricantes++;
    printf("Fabricante cadastrado com sucesso.\n");
}
 
 
 
void cadastrarCliente() {
    if (numClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }
 
    Cliente cliente;
 
    printf("=== Cadastro de Cliente ===\n");
    printf("Nome: ");
    scanf("%s", cliente.nome);
    fflush(stdin);
    
    printf("Idade: ");
    scanf("%d", &cliente.idade);
    fflush(stdin);
     
    clientes[numClientes] = cliente;
    numClientes++;
    printf("Cliente cadastrado com sucesso.\n");
}
 
void cadastrarProduto() {
	int i;
	
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
 
    Produto produto;
 
    printf("=== Cadastro de Produto ===\n");
    printf("Descrição: ");
    scanf("%s", produto.descricao);
    fflush(stdin);
    
    printf("Peso: ");
    scanf("%f", &produto.peso);
    fflush(stdin);
    
    printf("Valor de Compra: ");
    scanf("%f", &produto.valorCompra);
    fflush(stdin);
    
    printf("Valor de Venda: ");
    scanf("%f", &produto.valorVenda);
    fflush(stdin);
    
	 
    // Cálculo do lucro e percentual do lucro
    produto.valorLucro = produto.valorVenda - produto.valorCompra;
    produto.percentualLucro = (produto.valorLucro / produto.valorCompra) * 100;
 
    
    printf("Fabricantes:\n");
    for (i = 0; i < numFabricantes; i++) {
        printf("%d - %s\n", fabricantes[i].codigo, fabricantes[i].marca);
    }
    
    printf("Fabricante (Código): ");
    scanf("%d", &produto.fabricante.codigo);
    fflush(stdin);
     
    // Busca o fabricante pelo código e copia os dados para o produto
    for (i = 0; i < numFabricantes; i++) {
        if (fabricantes[i].codigo == produto.fabricante.codigo) {
            strcpy(produto.fabricante.marca, fabricantes[i].marca);
            strcpy(produto.fabricante.site, fabricantes[i].site);
            produto.fabricante.telefone = fabricantes[i].telefone;
            strcpy(produto.fabricante.uf.sigla, fabricantes[i].uf.sigla);
            strcpy(produto.fabricante.uf.nome, fabricantes[i].uf.nome);
            break;
        }
    }
 
    produtos[numProdutos] = produto;
    numProdutos++;
    printf("Produto cadastrado com sucesso.\n");
}
 
void listarFabricantes() {
	int i;
 
    printf("=== Lista de Fabricantes ===\n");
    for (i = 0; i < numFabricantes; i++) {
        printf("Código: %d\n", fabricantes[i].codigo);
        printf("Marca: %s\n", fabricantes[i].marca);
        printf("Site: %s\n", fabricantes[i].site);
        printf("Telefone: %d\n", fabricantes[i].telefone);
        printf("UF: %s - %s\n", fabricantes[i].uf.sigla, fabricantes[i].uf.nome);
        printf("----------------------------\n");
    }
}
 
void listarClientes() {
	int i;
 
    printf("=== Lista de Clientes ===\n");
    for (i = 0; i < numClientes; i++) {
        printf("Nome: %s\n", clientes[i].nome);
        printf("Idade: %d\n", clientes[i].idade);
        printf("----------------------------\n");
    }
}
 
void listarProdutos() {
    int i;
 
    printf("=== Lista de Produtos ===\n");
    for (i = 0; i < numProdutos; i++) {
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
        printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
        printf("Valor do Lucro: R$ %.2f\n", produtos[i].valorLucro);
        printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("Fabricante: %d - %s\n", produtos[i].fabricante.codigo, produtos[i].fabricante.marca);
        printf("----------------------------\n");
    }
}
 
void listarProdutosPorFabricante() {
    int codigoFabricante;
    int i, j;
    int encontrou = 0;
    Produto temp;
 
    printf("Digite o código do fabricante: ");
    scanf("%d", &codigoFabricante);
    fflush(stdin);
     
    // Filtrar os produtos pelo código do fabricante
    for (i = 0; i < numProdutos; i++) {
        if (produtos[i].fabricante.codigo == codigoFabricante) {
            encontrou = 1;
            break;
        }
    }
 
    if (encontrou) {
        // Ordenar os produtos em ordem alfabética pelo nome
        for (i = 0; i < numProdutos - 1; i++) {
            for (j = 0; j < numProdutos - i - 1; j++) {
                if (produtos[j].descricao > produtos[j + 1].descricao) {
                    temp = produtos[j];
                    produtos[j] = produtos[j + 1];
                    produtos[j + 1] = temp;
                }
            }
        }
 
        printf("=== Produtos do Fabricante ===\n");
        for (i = 0; i < numProdutos; i++) {
            if (produtos[i].fabricante.codigo == codigoFabricante) {
                printf("Descrição: %s\n", produtos[i].descricao);
                printf("Peso: %.2f\n", produtos[i].peso);
                printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
                printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
                printf("Valor do Lucro: R$ %.2f\n", produtos[i].valorLucro);
                printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro);
                printf("----------------------------\n");
            }
        }
    } else {
        printf("Nenhum produto encontrado para o fabricante com o código informado.\n");
    }
}
 
void listarEstadosMaiorValor() {
    float maiorValor = 0;
    int i;
 
    for (i = 0; i < numProdutos; i++) {
        if (produtos[i].valorVenda > maiorValor) {
            maiorValor = produtos[i].valorVenda;
        }
    }
 
    printf("=== Estado(s) com Maior Valor ===\n");
    for (i = 0; i < numProdutos; i++) {
        if (produtos[i].valorVenda == maiorValor) {
            printf("%s\n", produtos[i].fabricante.uf.nome);
        }
    }
}
 
void listarFabricantesMenorValor() {
    float menorValor = produtos[0].valorVenda;
    int i;
 
    for (i = 1; i < numProdutos; i++) {
        if (produtos[i].valorVenda < menorValor) {
            menorValor = produtos[i].valorVenda;
        }
    }
 
    printf("=== Fabricante(s) com Menor Valor ===\n");
    for (i = 0; i < numProdutos; i++) {
        if (produtos[i].valorVenda == menorValor) {
            printf("%d - %s\n", produtos[i].fabricante.codigo, produtos[i].fabricante.marca);
        }
    }
}
 
void listarProdutosOrdemCrescenteValor() {
    int i, j;
    Produto temp;
 
    // Ordenar os produtos em ordem crescente de valor
    for (i = 0; i < numProdutos - 1; i++) {
        for (j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].valorVenda > produtos[j + 1].valorVenda) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
 
    printf("=== Produtos em Ordem Crescente de Valor ===\n");
    for (i = 0; i < numProdutos; i++) {
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
        printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
        printf("Valor do Lucro: R$ %.2f\n", produtos[i].valorLucro);
        printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("----------------------------\n");
    }
}
 
void listarProdutosOrdemCrescenteLucro() {
    int i, j;
    Produto temp;
 
    // Ordenar os produtos em ordem crescente de valor do lucro
    for (i = 0; i < numProdutos - 1; i++) {
        for (j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].valorLucro > produtos[j + 1].valorLucro) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
 
    printf("=== Produtos em Ordem Crescente de Valor do Lucro ===\n");
    for (i = 0; i < numProdutos; i++) {
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
        printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
        printf("Valor do Lucro: R$ %.2f\n", produtos[i].valorLucro);
        printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("----------------------------\n");
    }
}
 
void verificarClientesIdadeSuperior60() {
    int i, k, j = 0;
    Cliente clientes60[MAX_CLIENTES];
    int numClientes60 = 0;
 
    for (i = 0; i < numClientes; i++) {
        if (clientes[i].idade > 60) {
            clientes60[numClientes60] = clientes[i];
            numClientes60++;
        }
    }
 
    if (numClientes60 > 0) {
        printf("=== Clientes com Idade Superior a 60 ===\n");
        for (i = 0; i < numClientes60; i++) {
            printf("Nome: %s\n", clientes60[i].nome);
            printf("Idade: %d\n", clientes60[i].idade);
            printf("----------------------------\n");
        }
 
        // Remover os clientes da lista original
        for (i = 0; i < numClientes60; i++) {
            for (j = 0; j < numClientes; j++) {
                if (strcmp(clientes[j].nome, clientes60[i].nome) == 0 && clientes[j].idade == clientes60[i].idade) {
                    // Deslocar os clientes para remover o cliente atual
                    for (k = j; k < numClientes - 1; k++) {
                        clientes[k] = clientes[k + 1];
                    }
                    numClientes--;
                    break;
                }
            }
        }
    } else {
        printf("Não há clientes com idade superior a 60.\n");
    }
}
 
void buscarProdutoPorValor() {
    float valor;
    int inicio = 0;
    int fim = numProdutos - 1;
    int meio;
    int encontrou = 0;
 
    printf("Digite o valor do produto a ser buscado: ");
    scanf("%f", &valor);
    fflush(stdin);
    
 
    // Busca binária
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (produtos[meio].valorVenda == valor) {
            encontrou = 1;
            break;
        } else if (produtos[meio].valorVenda < valor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
 
    if (encontrou) {
        printf("Produto encontrado:\n");
        printf("Descrição: %s\n", produtos[meio].descricao);
        printf("Peso: %.2f\n", produtos[meio].peso);
        printf("Valor de Compra: R$ %.2f\n", produtos[meio].valorCompra);
        printf("Valor de Venda: R$ %.2f\n", produtos[meio].valorVenda);
        printf("Valor do Lucro: R$ %.2f\n", produtos[meio].valorLucro);
        printf("Percentual do Lucro: %.2f%%\n", produtos[meio].percentualLucro);
    } else {
        printf("Nenhum produto encontrado com o valor especificado.\n");
    }
}
 
void atenderClientesFila() {
	int i;
 
    if (numClientes == 0) {
        printf("Não há clientes para atender.\n");
        return;
    }
 
    printf("=== Atendendo Clientes na Ordem de Acesso (Fila) ===\n");
    printf("Atendendo o cliente: %s\n", clientes[0].nome);
 
    // Deslocar os clientes para remover o cliente atual
    for (i = 0; i < numClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    
    numClientes--;
}
 
void atenderClientesPilha() {
	int numClientes60;
	struct Cliente clientes60[100];
 
    if (numClientes60 == 0) {
        printf("Não há clientes com idade superior a 60 para atender.\n");
        return;
    }
 
    printf("=== Atendendo Clientes na Ordem de Acesso (Pilha) ===\n");
    printf("Atendendo o cliente: %s\n", clientes60[numClientes60 - 1].nome);
 
    // Remover o cliente atual da pilha
    numClientes60--;
}
 
void exibirMenuSecundario() {
    char opcao;
    setlocale(LC_ALL, "Portuguese");
 
    while (1) {
        printf("\n[Menu Secundário]\n");
        printf("[a] Listar os produtos de um determinado fabricante (filtrar por código do fabricante) em ordem alfabética\n");
        printf("[b] Apresentar o(s) estado(s) onde tenha(m) algum produto com o valor igual ao maior valor registrado no sistema\n");
        printf("[c] Apresentar o(s) fabricante(s) onde tenha(m) algum produto com o valor igual ao menor valor registrado no sistema\n");
        printf("[d] Listar todos os produtos em ordem crescente de valor\n");
        printf("[e] Listar todos os produtos em ordem crescente de maior 'valor do lucro'\n");
        printf("[f] Cadastrar novo cliente para atendimento na lista\n");
        printf("[g] Verificar se existe algum cliente para atendimento na lista com idade superior a 60 anos\n");
        printf("[h] Verificar se existe algum produto com o valor especificado pelo usuário\n");
        printf("[i] Usuário do sistema realizará o atendimento dos clientes que estão na lista original com 'ordem de acesso' baseado em fila\n");
        printf("[j] Usuário do sistema realizará o atendimento dos clientes que estão na lista_60 com 'ordem de acesso' baseado em pilha \n");
        printf("[s] Sair\n\n");
        printf("Digite sua opção: ");
        scanf(" %c", &opcao);
        opcao = tolower(opcao);
 
        switch (opcao) {
            case 'a':
                listarProdutosPorFabricante();
                system("pause");
                system("cls");
                break;
            case 'b':
                listarEstadosMaiorValor();
                system("pause");
                system("cls");
                break;
            case 'c':
                listarFabricantesMenorValor();
                system("pause");
                system("cls");
                break;
            case 'd':
                listarProdutosOrdemCrescenteValor();
                system("pause");
                system("cls");
                break;
            case 'e':
                listarProdutosOrdemCrescenteLucro();
                system("pause");
                system("cls");
                break;
            case 'f':
                cadastrarCliente();
                system("pause");
                system("cls");
                break;
            case 'g':
                verificarClientesIdadeSuperior60();
                system("pause");
                system("cls");
                break;
            case 'h':
                buscarProdutoPorValor();
                system("pause");
                system("cls");
                break;
            case 'i':
                atenderClientesFila();
                system("pause");
                system("cls");
                break;
            case 'j':
                atenderClientesPilha();
                system("pause");
                system("cls");
                break;
            case 's':
                return;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    }
}
 
 
int main() {
    int opcao;
    setlocale(LC_ALL, "Portuguese");
 
    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar Fabricante\n");
        printf("2. Cadastrar Cliente\n");
        printf("3. Cadastrar Produto\n");
        printf("4. Ir para o Menu Secundário\n");
        printf("0. Sair\n\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        opcao = tolower(opcao);
 
        switch (opcao) {
            case 1:
                cadastrarFabricante();
                system("pause");
                system("cls");
                break;
            case 2:
                cadastrarCliente();
                system("pause");
                system("cls");
                break;
            case 3:
                cadastrarProduto();
                system("pause");
                system("cls");
                break;
            case 4:
                exibirMenuSecundario();
                system("pause");
                system("cls");
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                system("pause");
                system("cls");
        }
    } while (opcao != 0);
    
    return 0;
}

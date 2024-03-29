#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Informações do paciente
typedef struct {
    char nome[30];
    char email[60];
    char telefone[15];
} Paciente;

// Realização de login
int realizarLogin() {
    char nomeUsuario[30];
    char senha[20];


    char nomeUsuarioCorreto[] = "thaismabelli";
    char senhaCorreta[] = "thais123";

    printf("Realizar Login: \n");
    printf("Nome de usuário: ");
    scanf("%s", nomeUsuario);
    printf("Senha: ");
    scanf("%s", senha);

    // Verificando se o usuário e senha estão corretos
    if (strcmp(nomeUsuario, nomeUsuarioCorreto) == 0 && strcmp(senha, senhaCorreta) == 0) {
        printf("Login realizado com sucesso!\n");
        return 1;
    } else {
        printf("Nome de usuário ou senha incorretos. Por favor, tente novamente.\n");
        return 0;
    }
}

// Mensagem de boas-vindas
void exibirMensagemBoasVindas() {
    printf("\nSeja bem-vindo(a) a nossa plataforma, a sua saude em primeiro lugar!\n");
}

// Menu de opções
int exibirMenu() {
    int escolha;

    printf("\n MENU DE OPÇÕES\n");
    printf("1. Cadastrar paciente\n");
    printf("2. Listar pacientes\n");
    printf("3. Editar paciente\n");
    printf("4. Excluir paciente\n");
    printf("5. Buscar paciente\n");
    printf("6. Consultar agendamento\n");
    printf("7. Consultar histórico do paciente\n");
    printf("8. Consultar resultados de exames\n");
    printf("9. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    return escolha;
}

// Cadastro de novo paciente:
void cadastrarPaciente() {
    Paciente paciente;
    FILE *arquivo;

    printf("\n Cadastro de Paciente\n");

    printf("Nome: ");
    scanf("%s", paciente.nome);

    printf("Email: ");
    scanf("%s", paciente.email);

    printf("Telefone: ");
    scanf("%s", paciente.telefone);

    arquivo = fopen("pacientes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "%s;%s;%s\n", paciente.nome, paciente.email, paciente.telefone);
    fclose(arquivo);

    printf("Paciente cadastrado com sucesso!\n");
}

// Listar pacientes
void listarPacientes() {
    Paciente paciente;
    FILE *arquivo;

    printf("\n Lista de Pacientes\n");

    arquivo = fopen("pacientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, "%s;%s;%s\n", paciente.nome, paciente.email, paciente.telefone) != EOF) {
        printf("Nome: %s\n", paciente.nome);
        printf("Email: %s\n", paciente.email);
        printf("Telefone: %s\n\n", paciente.telefone);
    }

    fclose(arquivo);
}

// Editar paciente
void editarPaciente() {
    char nomeBusca[50];
    Paciente paciente;
    FILE *arquivoTemp, *arquivo;
    int encontrado = 0;

    printf("\nEdição de Paciente\n");

    printf("Informe o nome do paciente que você deseja editar: ");
    scanf("%s", nomeBusca);

    arquivo = fopen("pacientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    while (fscanf(arquivo, "%s;%s;%s\n", paciente.nome, paciente.email, paciente.telefone) != EOF) {
        if (strcmp(nomeBusca, paciente.nome) == 0) {
            printf("Paciente encontrado!\n Digite as novas informações:\n");
            printf("Nome: ");
            scanf("%s", paciente.nome);
            printf("Email: ");
            scanf("%s", paciente.email);
            printf("Telefone: ");
            scanf("%s", paciente.telefone);
            encontrado = 1;
        }
        fprintf(arquivoTemp, "%s;%s;%s\n", paciente.nome, paciente.email, paciente.telefone);
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("pacientes.txt");
    rename("temp.txt", "pacientes.txt");

    if (!encontrado) {
        printf("Paciente não encontrado.\n");
    } else {
        printf("Paciente editado com sucesso.\n");
    }
}

//Excluir paciente
void excluirPaciente() {
    char nomeBusca[50];
    Paciente paciente;
    FILE *arquivoTemp, *arquivo;
    int encontrado = 0;

    printf("\nExclusão de Paciente\n");

    printf("Informe o nome do paciente que você deseja excluir: ");
    scanf("%s", nomeBusca);

    arquivo = fopen("pacientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    while (fscanf(arquivo, "%s;%s;%s\n", paciente.nome, paciente.email, paciente.telefone) != EOF) {
        if (strcmp(nomeBusca, paciente.nome) == 0) {
            printf("Paciente encontrado e excluído do registro.\n");
            encontrado = 1;
        } else {
            fprintf(arquivoTemp, "%s;%s;%s\n", paciente.nome, paciente.email, paciente.telefone);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("pacientes.txt");
    rename("temp.txt", "pacientes.txt");

    if (!encontrado) {
        printf("Paciente não encontrado.\n");
    }
}

// Busca de paciente pelo nome
void buscarPaciente(char nome[]) {
    Paciente paciente;
    FILE *arquivo;
    int encontrado = 0;

    printf("\nBusca de Paciente\n");

    arquivo = fopen("pacientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, "%s;%s;%s\n", paciente.nome, paciente.email, paciente.telefone) != EOF) {
        if (strcmp(nome, paciente.nome) == 0) {
            printf("Paciente encontrado:\n");
            printf("Nome: %s\n", paciente.nome);
            printf("Email: %s\n", paciente.email);
            printf("Telefone: %s\n", paciente.telefone);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Paciente não encontrado.\n");
    }

    fclose(arquivo);
}

// Consultar agendamento do paciente
void consultarAgendamento() {
    char nomeBusca[50];
    printf("\nConsulta de Agendamento\n");
    printf("Informe o nome do paciente para consultar agendamento: ");
    scanf("%s", nomeBusca);
}

// Consultar histórico do paciente
void consultarHistorico() {
    char nomeBusca[50];
    printf("\nConsulta de Histórico\n");
    printf("Informe o nome do paciente para consultar histórico: ");
    scanf("%s", nomeBusca);
}

// Consultar resultados de exames do paciente
void consultarResultadosExames() {
    char nomeBusca[50];
    printf("\nConsulta de Resultados de Exames\n");
    printf("Informe o nome do paciente para consultar resultados de exames: ");
    scanf("%s", nomeBusca);
}

int main() {
    int opcao;
    char nomeBusca[50];

    while (!realizarLogin()) {}

    exibirMensagemBoasVindas();

    do {
        opcao = exibirMenu();

        switch (opcao) {
            case 1:
                cadastrarPaciente();
                break;
            case 2:
                listarPacientes();
                break;
            case 3:
                editarPaciente();
                break;
            case 4:
                excluirPaciente();
                break;
            case 5:
                printf("\nInforme o nome do paciente que você deseja buscar: ");
                scanf("%s", nomeBusca);
                buscarPaciente(nomeBusca);
                break;
            case 6:
                consultarAgendamento();
                break;
            case 7:
                consultarHistorico();
                break;
            case 8:
                consultarResultadosExames();
                break;
            case 9:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 9);

    return 0;
}

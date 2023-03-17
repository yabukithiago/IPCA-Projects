/*****************************************************************//**
 * \file   Funcs.c
 * \brief  O arquivo Funcs.c contém a implementação de todas as funções do programa.
 * Essas funções foram projetadas para executar tarefas específicas e são independentes, modularizadas e reutilizáveis.
 * 
 * 
 * \author Thiago Yabuki
 * \date   March 2023
 *********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "Library.h"

#pragma region Binary

 /**
 * @brief Função que lê um arquivo binário e cria uma lista ligada com os dados lidos.
 *
 * \return
 */
Client* lerClientBinario() {
    FILE* fp_bin = fopen("Client.bin", "rb");

    if (fp_bin == NULL) {
        printf("Error opening input file\n");
        return NULL;
    }

    Client* inicio = NULL;
    Client* cleint_atual = NULL;
    Client client_buffer;

    while (fread(&client_buffer, sizeof(Client), 1, fp_bin) == 1) {
        Client* novo_client = (Client*)malloc(sizeof(Client));
        *novo_client = client_buffer;
        novo_client->c_next = NULL;

        if (inicio == NULL) {
            inicio = novo_client;
            cleint_atual = novo_client;
        }
        else {
            cleint_atual->c_next = novo_client;
            cleint_atual = novo_client;
        }
    }

    fclose(fp_bin);
    return inicio;
}

 /**
 * @brief Função que salva os clientes em um arquivo binário chamado Client.bin.
 *
 *
 * \param inicio
 */
void salvarClientBin(Client* inicio) {
    FILE* fp_bin = fopen("Client.bin", "ab");

    if (fp_bin == NULL) {
        printf("Error opening output file\n");
        return;
    }

    Client* client_atual = inicio;

    while (client_atual != NULL) {
        fwrite(client_atual, sizeof(Client), 1, fp_bin);
        client_atual = client_atual->c_next;
    }
    fclose(fp_bin);
}

 /**
  * @brief Função que lê um ficheiro binário e guarda os dados num array de structs do tipo Meio de Transporte.
  *
  * \return
  */
Meio* lerBinario() {
    FILE* fp_bin = fopen("MeansTransport.bin", "rb");

    if (fp_bin == NULL) {
        printf("Error opening input file\n");
        return NULL;
    }

    Meio* inicio = NULL;
    Meio* meio_atual = NULL;
    Meio meio_buffer;

    while (fread(&meio_buffer, sizeof(Meio), 1, fp_bin) == 1) {
        Meio* novo_meio = (Meio*)malloc(sizeof(Meio));

        *novo_meio = meio_buffer;
        novo_meio->ME_next = NULL;

        if (inicio == NULL) {
            inicio = novo_meio;
            meio_atual = novo_meio;
        }
        else {
            meio_atual->ME_next = novo_meio;
            meio_atual = novo_meio;
        }
    }

    fclose(fp_bin);
    return inicio;
}

/**
 * @brief Função que imprime o conteúdo do ficheiro binário para um ficheiro de texto.
 *
 */
void imprimirBinEmTxt() {
    FILE* fp_Clienttxt;
    fp_Clienttxt = fopen("Client_READBinary.txt", "w");

    FILE* fp_Clientbin;
    fp_Clientbin = fopen("Client.bin", "rb");

    FILE* fp_txt;
    fp_txt = fopen("MeansTransport_READBinary.txt", "w");

    FILE* fp_bin;
    fp_bin = fopen("MeansTransport.bin", "rb");

    if (fp_bin == NULL) {
        printf("Error opening binary file.\n");
        return;
    }

    if (fp_txt == NULL) {
        printf("Error opening txt file.\n");
        fclose(fp_bin);
        return;
    }

    if (fp_bin == NULL) {
        printf("Error opening binary file.\n");
        return;
    }

    if (fp_txt == NULL) {
        printf("Error opening txt file.\n");
        fclose(fp_bin);
        return;
    }

    Client client_lido;
    while (fread(&client_lido, sizeof(Client), 1, fp_Clientbin) == 1) {
        fprintf(fp_Clienttxt, "ID: %d \t| NIF: %d \t| Name: %s \t| Adress: %s \t| Bank Balance: %.2f \t|\n", client_lido.id, client_lido.nif, client_lido.name, client_lido.adress, client_lido.bankbalance);
    }

    Meio meio_lido;
    while (fread(&meio_lido, sizeof(Meio), 1, fp_bin) == 1) {
        fprintf(fp_txt, "Code: %d \t| Type: %15s \t| Battery: %7.2f \t| Cost: %2.2f \t| Autonomy: %2.2f \t| Status: %s \t|\n", meio_lido.code, meio_lido.type, meio_lido.battery, meio_lido.cost, meio_lido.autonomy, meio_lido.status);
    }

    fclose(fp_Clienttxt);
    fclose(fp_Clientbin);
    fclose(fp_bin);
    fclose(fp_txt);
}

/**
 * @brief Função que salva os meios de transporte em um arquivo binário.
 *
 * \param inicio
 */
void salvarMeioBin(Meio* inicio) {
    FILE* fp_bin = fopen("MeansTransport.bin", "ab");

    if (fp_bin == NULL) {
        printf("Error opening output file\n");
        return;
    }

    Meio* meio_atual = inicio;
    while (meio_atual != NULL) {
        fwrite(meio_atual, sizeof(Meio), 1, fp_bin);
        meio_atual = meio_atual->ME_next;
    }
    fclose(fp_bin);
}

#pragma endregion

#pragma region Manager

 /**
  * @brief Função que insere um novo gerente na lista de gerentes.
  * Ela recebe o identificador do gerente e o nome dele como parâmetros, aloca memória para o gerente e insere o novo gerente no início da lista. A função retorna um ponteiro para o gerente recém-inserido.
  *
  * \param inicio
  * \param identidade
  * \param nome
  * \return
  */
Manager* insertManagerStart(Manager* inicio, int identidade, char nome[]) {
    Manager* manager_inicio = (Manager*)malloc(sizeof(Manager));

    if (manager_inicio == NULL) return NULL;

    manager_inicio->MA_next = inicio;
    inicio = manager_inicio;

    manager_inicio->id = identidade;
    strncpy(manager_inicio->name, nome, sizeof(manager_inicio->name));

    return manager_inicio;
}

/**
 * @brief Função que lista todos os gestores existentes na lista encadeada de gestores.
 *
 * \param inicio
 */
void ListarManager(Manager* inicio) {
    FILE* fp;
    fp = fopen("Managers.txt", "a");

    Manager* manager_auxiliar = inicio;

    if (fp == NULL) {
        fp = fopen("Managers.txt", "w");
        if (fp == NULL) {
            printf("Error creating file!\n");
            return;
        }
    }


    while (manager_auxiliar != NULL) {
        fprintf(fp, "ID: %d | Name: %s |\n", manager_auxiliar->id, manager_auxiliar->name);
        manager_auxiliar = manager_auxiliar->MA_next;
    }

    fclose(fp);
}
#pragma endregion

#pragma region Client

/**
 * .
 *
 * \return
 */
Client* readClient() {
    FILE* fp;
    int id, nif;
    float bank;
    char name[50], adress[50];

    Client* aux = NULL;

    fp = fopen("Clients.txt", "r");

    if (fp != NULL) {
        while (fscanf(fp, "ID: %d | NIF: %d | Name: %[^|] | Adress: %[^|] | Bank Balance: %f |\n", &id, &nif, name, adress, &bank)== 5) {
            aux = insertClientStart(aux, id, nif, name, adress, bank);
        }
        fclose(fp);
    }
    return(aux);
}

/**
 * @brief Função que insere um novo cliente na lista de clientes.
 * Ela recebe o id, o nif, o nome, o endereço e o saldo do cliente como parâmetros, aloca memória para o cliente e insere o novo cliente no início da lista. A função retorna um ponteiro para o cliente recém-inserido.
 *
 * \param inicio
 * \param identidade
 * \param nif
 * \param nome
 * \param endereco
 * \param saldo
 * \return
 */
Client* insertClientStart(Client* inicio, int identidade, int nif, char nome[], char endereco[], float saldo) {
    Client* client_inicio = (Client*)malloc(sizeof(Client));
    if (client_inicio == NULL) return NULL;

    client_inicio->id = identidade;
    client_inicio->nif = nif;
    strncpy(client_inicio->name, nome, sizeof(client_inicio->name));
    strncpy(client_inicio->adress, endereco, sizeof(client_inicio->adress));
    client_inicio->bankbalance = saldo;

    client_inicio->c_next = inicio;
    inicio = client_inicio;

    return client_inicio;
}

/**
 * @brief Função que altera os dados de um cliente.
 * Ela recebe o id, o novo nif, o novo nome, o novo endereço e o novo saldo por parâmetros, aloca memória para o cliente e insere o novo cliente no inicio da lista. 
 * A função retorna um ponteiro para o cliente recém-inserido.
 *
 * \param inicio
 * \param identificador
 * \param novoNif
 * \param novoNome
 * \param novoEndereco
 * \param novoSaldo
 * \return
 */
Client* changeClient(Client* inicio, int identificador, int novoNif, char novoNome[], char novoEndereco[], float novoSaldo) {
    Client* atual = findClient(inicio, identificador);

    while (atual != NULL) {
        if (atual->id == identificador) {
            atual->nif = novoNif;
            strncpy(atual->name, novoNome, sizeof(atual->name));
            strncpy(atual->adress, novoEndereco, sizeof(atual->adress));
            atual->bankbalance = novoSaldo;
            ListarClient(inicio);
            return inicio;
        }
        atual = atual->c_next;
    }
    ListarClient(inicio);
    return inicio;
}

/**
 * @brief Função que procura um cliente na lista de clientes e retorna o ponteiro para o cliente encontrado.
 *
 * \param inicio
 * \param identidade
 * \return
 */
Client* findClient(Client* inicio, int identidade) {
    Client* current = inicio;

    while (current != NULL) {
        if (current->id == identidade) {
            return current;
        }
        current = current->c_next;
    }
    return NULL;
}

/**
 * .
 * 
 * \param inicio
 * \param identificador
 * \param preco
 * \return 
 */
Client* subtrairtotal(Client* inicio, int identificador, float preco) {
    Client* aux = inicio;

    while (aux != NULL) {
        if (aux->id == identificador) {
            aux->bankbalance -= preco;
            return aux;
        }
        aux = aux->c_next;
    }
    return NULL;
}

/**
 * @brief Função que remove um cliente da lista de clientes ativos do servidor e liberta a memoria alocada para o mesmo.
 *
 * \param inicio
 * \param identidade
 * \return
 */
Client* removeClient(Client* inicio, int identidade) {
    Client* previous = inicio, * current = inicio;

    if (current == NULL) return (NULL);

    else if (current->id == identidade) {
        inicio = current->c_next;
        free(current);
        return (inicio);
    }

    else {
        while ((current != NULL) && (current->id != identidade)) {
            previous = current;
            current = current->c_next;
        }
        if (current == NULL) 
            return inicio;
        else {
            previous->c_next = current->c_next;
            free(current);
            return(inicio);
        }
    }
}

/**
 * @brief Função que lista todos os clientes existentes na lista ligada de clientes e guarda a informação num ficheiro de texto.
 *
 * \param inicio
 */
void ListarClient(Client* inicio) {
    FILE* fp;
    fp = fopen("Clients.txt", "a");

    Client* client_auxiliar = inicio;

    if (fp == NULL) {
      printf("Error creating file!\n");
      return;
    }
    

    while (client_auxiliar != NULL) {
        fprintf(fp, "ID: %d \t| NIF: %d \t| Name: %s \t| Adress: %s \t| Bank Balance: %.2f \t|\n", client_auxiliar->id, client_auxiliar->nif, client_auxiliar->name, client_auxiliar->adress, client_auxiliar->bankbalance);
        client_auxiliar = client_auxiliar->c_next;
    }

    fclose(fp);
    salvarClientBin(inicio);
}
#pragma endregion

#pragma region Means

/**
 * @brief
 * 
 * \return 
 */
Meio* readMean() {
    FILE* fp;
    int code;
    char type[50], local[50], status[50];
    float bateria, autonomy, custo;

    Meio* aux = NULL;

    fp = fopen("MeansTransport.txt", "r");

    if (fp != NULL) {
        while (fscanf(fp, "Code: %d \t| Type: %15s \t| Battery: %7.2f \t| Cost: %2.2f \t| Autonomy: %2.2f \t| Local: %11s\t | Status: %11s \t| \n", &code, type, &bateria, &custo, &autonomy, local, status) == 7) {
            aux = insertMeioStart(aux, code, type, bateria, custo, autonomy, local, status);
        }
        fclose(fp);
    }
    return(aux);
}

/**
 * @brief
 *
 * \return
 */
Meio* insertMeioStart(Meio* inicio, int codigo, char tipo[], float bateria, float custo, float autonomia, char local[], char status[]) {
    Meio* meio_inicio = (Meio*)malloc(sizeof(Meio));
    if (meio_inicio == NULL) return NULL;

    meio_inicio->ME_next = NULL;

    meio_inicio->code = codigo;
    strcpy(meio_inicio->type, tipo);
    meio_inicio->battery = bateria;
    meio_inicio->cost = custo;
    meio_inicio->autonomy = autonomia;
    strcpy(meio_inicio->geocodigo, local);
    strcpy(meio_inicio->status, status);

    if (inicio == NULL) {
        inicio = meio_inicio;
    }
    else {
        meio_inicio->ME_next = inicio;
        inicio = meio_inicio;
    }

    ListarMeio(inicio);
    return meio_inicio;
}

/**
 * @brief Funcao que altera os dados de um meio de transporte el�trico.
 *
 * \param inicio
 * \param codigo
 * \param novoTipo
 * \param novaBateria
 * \param novoCusto
 * \param novaAutonomia
 * \return inicio
 */
Meio* changeMeio(Meio* inicio, int codigo, char novoTipo[], float novaBateria, float novoCusto, float novaAutonomia) {
    Meio* atual = findMeio(inicio, codigo);

    while (atual != NULL) {
        if (atual->code == codigo) {
            strncpy(atual->type, novoTipo, sizeof(atual->type));
            atual->battery = novaBateria;
            atual->cost = novoCusto;
            atual->autonomy = novaAutonomia;
            ListarMeio(inicio);
            return inicio;
        }

        atual = atual->ME_next;
    }

    ListarMeio(inicio);
    return inicio;
}

/**
 * @brief Fun��o que procura um meio de transporte na lista de meios de transporte e retorna o seu endere�o de mem�ria.
 *
 * \param inicio
 * \param codigo
 * \return
 */
Meio* findMeio(Meio* inicio, int codigo) {
    Meio* current = inicio;

    while (current != NULL) {
        if (current->code == codigo) {
            return current;
        }
        current = current->ME_next;
    }
    return NULL;
}

/**
 * @brief Fun��o que remove um meio de transporte da lista de meios de transporte do sistema.
 *
 * \param inicio
 * \param codigo
 * \return
 */
Meio* removeMeio(Meio* inicio, int codigo) {
    Meio* current = inicio, * previous = NULL;

    while (current != NULL) {
        if (current->code == codigo) {
            if (previous != NULL) {
                previous->ME_next = current->ME_next;
            }
            else {
                inicio = current->ME_next;
            }
            free(current);
            ListarMeio(inicio);
            return inicio;
        }
        previous = current;
        current = current->ME_next;
    }

    ListarMeio(inicio);
    return inicio;
}

/**
 * @brief Fun��o que lista os meios de transporte dispon�veis e salva em um arquivo .txt e .bin.
 *
 * \param inicio
 */
void ListarMeio(Meio* inicio) {
    FILE* fp_txt;
    fp_txt = fopen("MeansTransport.txt", "w");

    Meio* meio_auxiliar = inicio;

    if (fp_txt == NULL) {
        printf("Error creating file!\n");
        return;
    }

    while (meio_auxiliar != NULL) {
        fprintf(fp_txt, "Code: %d \t| Type: %15s \t| Battery: %7.2f \t| Cost: %2.2f \t| Autonomy: %2.2f \t| Local: %11s\t | Status: %11s \t| \n", meio_auxiliar->code, meio_auxiliar->type, meio_auxiliar->battery, meio_auxiliar->cost, meio_auxiliar->autonomy, meio_auxiliar->geocodigo, meio_auxiliar->status);
        meio_auxiliar = meio_auxiliar->ME_next;
    }
    fclose(fp_txt);
    salvarMeioBin(inicio);
}

/**
 * @brief Funcao que lista os meios de transporte ordenados por autonomia de forma decrescente em um arquivo.
 *
 * \param inicio
 * \param nome_arquivo
 */
void listMeanAutonomy(Meio* inicio, char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    int num_meios = 0;
    Meio* meio_atual = inicio;
    while (meio_atual != NULL) {
        num_meios++;
        meio_atual = meio_atual->ME_next;
    }

    Meio** meio_vetor = malloc(num_meios * sizeof(Meio*));
    meio_atual = inicio;
    for (int i = 0; i < num_meios; i++) {
        meio_vetor[i] = meio_atual;
        meio_atual = meio_atual->ME_next;
    }

    for (int i = 0; i < num_meios - 1; i++) {
        for (int j = 0; j < num_meios - i - 1; j++) {
            if (meio_vetor[j]->autonomy < meio_vetor[j + 1]->autonomy) {
                Meio* temp = meio_vetor[j];
                meio_vetor[j] = meio_vetor[j + 1];
                meio_vetor[j + 1] = temp;
            }
        }
    }

    fprintf(arquivo, "Means ordered in descending order by autonomy:\n");
    for (int i = 0; i < num_meios; i++) {
        fprintf(arquivo, "Code: %d \t| Type: %15s \t| Battery: %7.2f \t| Cost: %2.2f \t| Autonomy: %2.2f \t|\n", meio_vetor[i]->code, meio_vetor[i]->type, meio_vetor[i]->battery, meio_vetor[i]->cost, meio_vetor[i]->autonomy);
    }

    fclose(arquivo);
    free(meio_vetor);
}
#pragma endregion

#pragma region Rent

/**
 * .
 * 
 * \param inicio
 * \return 
 */
int guardarAluguer(Rent* inicio){
    FILE* fp;
    fp = fopen("RegistrationOfRents.txt", "w");

    if (fp != NULL){

        Rent* aux = inicio;

        while (aux != NULL) {
            fprintf(fp, "Code: %d \t| ID: %d \t| Rent Code: %d \t| Name: %s \t| Cost: %.2f \t|\n", aux->codigo, aux->id, aux->rentcode, aux->nomeCliente, aux->cost);
            aux = aux->seguinte;
        }

        fclose(fp);
        return(1);
    }
    else return(0);

}

/**
 * .
 * 
 * \param inicio
 * \return 
 */
Rent* lerAluguer(Client* inicio){
    FILE* fp;
    int codigo, id, rentcode;
    char nome[50];
    float preco;

    Rent* aux = NULL;

    fp = fopen("RegistrationOfRents.txt", "r");

    if (fp != NULL){
        while (!feof(fp)){
            fscanf(fp, "Code: %d \t| ID: %d \t| Rent Code: %d \t| Name: %s \t| Cost: %.2f \t|\n", &codigo, &id, &rentcode, nome, &preco);
            aux = inserirAluguer(aux, inicio ,codigo, id, rentcode, nome, preco);
        }

        fclose(fp);
    }
    return(aux);
}

/**
 * .
 * 
 * \param inicio
 * \param cinicio
 * \param codigo
 * \param identidade
 * \param codealuguel
 * \param nomeCliente
 * \param preco
 * \return 
 */
Rent* inserirAluguer(Rent* inicio, Client* cinicio, int codigo, int identidade, int codealuguel, char nomeCliente[], float preco) {
    Rent* novoAluguer = (Rent*)malloc(sizeof(Rent));

    novoAluguer->codigo = codigo;
    novoAluguer->id = identidade;
    novoAluguer->rentcode = codealuguel;
    strcpy(novoAluguer->nomeCliente, nomeCliente);
    novoAluguer->cost = preco;
    novoAluguer->seguinte = inicio;

    Client* aux = subtrairtotal(cinicio, identidade, preco);

    if (aux != NULL) {
        changeClient(cinicio, aux->id, aux->nif, aux->name,
            aux->adress, aux->bankbalance);
    }

    return novoAluguer;
}

//
//int existeAluguer(Meio* inicio, int cod){
//    while (inicio != NULL){
//        if (inicio->code == cod) return(1);
//        inicio = inicio->ME_next;
//    }
//    return(0);
//}
#pragma endregion

//#pragma region Managers functions
// 
// TO DO
// 
//void printTransactionHistory(Client* client, char* filename) {
//    FILE* fp = fopen(filename, "w");
//    if (fp == NULL) {
//        printf("Erro ao criar o arquivo!\n");
//        return;
//    }
//    fprintf(fp, "Historico de transacoes para o cliente ID %d:\n", client->id);
//    Transaction* current = client->t_next;
//    while (current != NULL) {
//        fprintf(fp, "Data: %s | Valor: %.2f |\n", current->date, current->amount);
//        current = current->t_next;
//    }
//    fclose(fp);
//}
//#pragma endregion
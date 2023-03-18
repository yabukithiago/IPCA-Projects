/*****************************************************************//**
 * \file   Library.h
 * \brief  Definições globais para a lista de gestores, clientes e meio de transportes sustentáveis.
 * Structs, constantes e assinaturas de funções.
 * 
 * \author Thiago Yabuki
 * \date   March 2023
 *********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#pragma region Structs
 /**
  * @brief Estrutura para armazenar um gestor
  *
  * Um gestor contém:
  * um id (@@id)
  * um nome (@@name)
  * um apontador para a próxima máquina (@@MA_next)
  */

typedef struct Manager {
    int id;
    char name[50];
    struct Manager* MA_next;
}Manager;

/**
 * @brief Estrutura para armazenar um cliente
 *
 * Um cliente contém:
 * um id (@@id)
 * um nif (@@nif)
 * um nome (@@name)
 * uma morada (@@adress]
 * um saldo (@@bankbalance)
 * um apontador para a próxima máquina (@@c_next)
 */

typedef struct Client {
    int id;
    int nif;
    char name[50];
    char adress[50];
    float bankbalance;
    struct Client* c_next;
}Client;

/**
 * @brief Estrutura para armazenar um meio de transporte
 *
 * Um meio de transporte contém:
 * um código (@@code)
 * um status (@@status)
 * um tipo (@@type)
 * uma bateria (@@battery)
 * um custo (@@cost)
 * uma autonomia (@@autonomy)
 * uma localização (@@geocodigo)
 * um apontador para a próxima máquina (@@ME_next)
 */

typedef struct Meio {
    int code;
    char status[50];
    char type[50];
    float battery;
    float cost;
    float autonomy;
    char geocodigo[50];
    struct Meio* ME_next;
}Meio;

/**
 * @brief Estrutura para armazenar um aluguer
 *
 * Um aluguer contém:
 * um código (@@codigo)
 * um codigo de aluguer (@@rentcode)
 * um custo (@@cost]
 * um apontador para a próxima máquina (@@seguinte)
 */

typedef struct Rent {
    int codigo;
    int id;
    int rentcode;
    char nomeCliente[50];
    float cost;
    struct Rent* seguinte;
} Rent;
#pragma endregion

#pragma region Binary
//Função para ler os dados de um cliente armazenados em um ficheiro binário.
Client* lerClientBinario();

//Função para imprimir os dados de um cliente em um ficheiro binário.
void salvarClientBin(Client* inicio);

//Função para salvar os dados de um meio de transporte em um ficheiro binário.
void salvarMeioBin(Meio* inicio);

//Função para ler um ficheiro binário.
Meio* lerBinario();

//Função para imprimir os dados lidos de um ficheiro binário em um ficheiro de texto.
void imprimirBinEmTxt();

#pragma endregion

#pragma region Manager
//Função para inserir um gestor.
Manager* insertManagerStart(Manager* inicio, int identidade, char nome[]);

//Função para salvar os dados de um gestor em um ficheiro de texto.
void ListarManager(Manager* inicio);

#pragma endregion

#pragma region Client
//Função para ler um cliente existente.
Client* readClient();

//Função para inserir um cliente.
Client* insertClientStart(Client* inicio, int identidade, int nif, char nome[], char endereco[], float saldo);

//Função para alterar os dados de um cliente existente.
Client* changeClient(Client* inicio, int identificador, int novoNif, char novoNome[], char novoEndereco[], float novoSaldo);

//Função para procuar um cliente existente.
Client* findClient(Client* inicio, int identidade);

//Função para subtrair o custo do aluguer no saldo do cliente.
Client* subtrairtotal(Client* inicio, int identificador, float preco);

//Função para remover os dados de um cliente existente.
Client* removeClient(Client* inicio, int identidade);

//Função para salvar os dados de um cliente em um ficheiro de texto.
void ListarClient(Client* inicio);

#pragma endregion

#pragma region Mean
//Função para ler um meio de transporte.
Meio* readMean();

//Função para inserir um meio de transporte.
Meio* insertMeioStart(Meio* inicio, int codigo, char tipo[], float bateria, float custo, float autonomia, char local[], char status[]);

//Função para alterar os dados de um meio de transporte já criado.
Meio* changeMeio(Meio* inicio, int codigo, char novoTipo[], float novaBateria, float novoCusto, float novaAutonomia);

//Função para procurar um meio de transporte especifico.
Meio* findMeio(Meio* inicio, int codigo);

//Função para remover um meio de transporte.
Meio* removeMeio(Meio* inicio, int codigo);

//Função para salvar os meios de transporte em um ficheiro texto.
void ListarMeio(Meio* inicio);

//Função para listar os meios de transporte por ordem decrescente de autonomia.
void listMeanAutonomy(Meio* inicio, char* nome_arquivo);

//Função para listar os meios de transporte em uma certa localização.
void listarMeioGeocodigo(Meio* inicio, char* geocodigo);

#pragma endregion

#pragma region Rent
//Função para guardar um aluguer.
int listarRent(Rent* inicio);

//Função para ler um aluguer.
Rent* lerAluguer(Client* inicio);

//Função para inserir um aluguer.
Rent* inserirAluguer(Rent* inicio, Client* cinicio, int codigo, int identidade, int codealuguel, char nomeCliente[], float preco);

/*int existeAluguer(Meio* inicio, int cod);*/
#pragma endregion
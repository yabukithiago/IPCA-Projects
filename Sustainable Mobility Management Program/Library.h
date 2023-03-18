/*****************************************************************//**
 * \file   Library.h
 * \brief  Defini��es globais para a lista de gestores, clientes e meio de transportes sustent�veis.
 * Structs, constantes e assinaturas de fun��es.
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
  * Um gestor cont�m:
  * um id (@@id)
  * um nome (@@name)
  * um apontador para a pr�xima m�quina (@@MA_next)
  */

typedef struct Manager {
    int id;
    char name[50];
    struct Manager* MA_next;
}Manager;

/**
 * @brief Estrutura para armazenar um cliente
 *
 * Um cliente cont�m:
 * um id (@@id)
 * um nif (@@nif)
 * um nome (@@name)
 * uma morada (@@adress]
 * um saldo (@@bankbalance)
 * um apontador para a pr�xima m�quina (@@c_next)
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
 * Um meio de transporte cont�m:
 * um c�digo (@@code)
 * um status (@@status)
 * um tipo (@@type)
 * uma bateria (@@battery)
 * um custo (@@cost)
 * uma autonomia (@@autonomy)
 * uma localiza��o (@@geocodigo)
 * um apontador para a pr�xima m�quina (@@ME_next)
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
 * Um aluguer cont�m:
 * um c�digo (@@codigo)
 * um codigo de aluguer (@@rentcode)
 * um custo (@@cost]
 * um apontador para a pr�xima m�quina (@@seguinte)
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
//Fun��o para ler os dados de um cliente armazenados em um ficheiro bin�rio.
Client* lerClientBinario();

//Fun��o para imprimir os dados de um cliente em um ficheiro bin�rio.
void salvarClientBin(Client* inicio);

//Fun��o para salvar os dados de um meio de transporte em um ficheiro bin�rio.
void salvarMeioBin(Meio* inicio);

//Fun��o para ler um ficheiro bin�rio.
Meio* lerBinario();

//Fun��o para imprimir os dados lidos de um ficheiro bin�rio em um ficheiro de texto.
void imprimirBinEmTxt();

#pragma endregion

#pragma region Manager
//Fun��o para inserir um gestor.
Manager* insertManagerStart(Manager* inicio, int identidade, char nome[]);

//Fun��o para salvar os dados de um gestor em um ficheiro de texto.
void ListarManager(Manager* inicio);

#pragma endregion

#pragma region Client
//Fun��o para ler um cliente existente.
Client* readClient();

//Fun��o para inserir um cliente.
Client* insertClientStart(Client* inicio, int identidade, int nif, char nome[], char endereco[], float saldo);

//Fun��o para alterar os dados de um cliente existente.
Client* changeClient(Client* inicio, int identificador, int novoNif, char novoNome[], char novoEndereco[], float novoSaldo);

//Fun��o para procuar um cliente existente.
Client* findClient(Client* inicio, int identidade);

//Fun��o para subtrair o custo do aluguer no saldo do cliente.
Client* subtrairtotal(Client* inicio, int identificador, float preco);

//Fun��o para remover os dados de um cliente existente.
Client* removeClient(Client* inicio, int identidade);

//Fun��o para salvar os dados de um cliente em um ficheiro de texto.
void ListarClient(Client* inicio);

#pragma endregion

#pragma region Mean
//Fun��o para ler um meio de transporte.
Meio* readMean();

//Fun��o para inserir um meio de transporte.
Meio* insertMeioStart(Meio* inicio, int codigo, char tipo[], float bateria, float custo, float autonomia, char local[], char status[]);

//Fun��o para alterar os dados de um meio de transporte j� criado.
Meio* changeMeio(Meio* inicio, int codigo, char novoTipo[], float novaBateria, float novoCusto, float novaAutonomia);

//Fun��o para procurar um meio de transporte especifico.
Meio* findMeio(Meio* inicio, int codigo);

//Fun��o para remover um meio de transporte.
Meio* removeMeio(Meio* inicio, int codigo);

//Fun��o para salvar os meios de transporte em um ficheiro texto.
void ListarMeio(Meio* inicio);

//Fun��o para listar os meios de transporte por ordem decrescente de autonomia.
void listMeanAutonomy(Meio* inicio, char* nome_arquivo);

//Fun��o para listar os meios de transporte em uma certa localiza��o.
void listarMeioGeocodigo(Meio* inicio, char* geocodigo);

#pragma endregion

#pragma region Rent
//Fun��o para guardar um aluguer.
int listarRent(Rent* inicio);

//Fun��o para ler um aluguer.
Rent* lerAluguer(Client* inicio);

//Fun��o para inserir um aluguer.
Rent* inserirAluguer(Rent* inicio, Client* cinicio, int codigo, int identidade, int codealuguel, char nomeCliente[], float preco);

/*int existeAluguer(Meio* inicio, int cod);*/
#pragma endregion
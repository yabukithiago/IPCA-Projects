/*********************************************************************
 * \file   Main.c
 * \brief  O arquivo Main.c contém a função principal do programa.
 * Esta é a função principal do programa que inicializa variáveis ​​e estruturas, chama funções de uma biblioteca e executa várias operações, como inserir, alterar e remover dados de listas encadeadas.
 * O código também grava e lê dados de arquivos binários e envia informações para um arquivo de texto.
 * 
 * 
 * 
 * \author Thiago Yabuki
 * \date   March 2023
 *********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "Library.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    Manager* manager_inicio = NULL;
    Client* client_inicio = NULL;
    Meio* meio_inicio = NULL;
    Rent* rent_inicio = NULL;

    char* files[] = { "Client.bin", "MeansTransport.bin" };
    

    manager_inicio = insertManagerStart(manager_inicio, 10, "Gaba");
    manager_inicio = insertManagerStart(manager_inicio, 100, "Raze");
    ListarManager(manager_inicio);

    client_inicio = insertClientStart(client_inicio, 1, 313780200, "Thiago", "Rua do Queimado", 1000.00);
    client_inicio = insertClientStart(client_inicio, 2, 987654321, "Isabela", "Rua do Queimado", 5000.00);
    client_inicio = insertClientStart(client_inicio, 3, 123456789, "Raphael", "Rua do Queimado", 500.00);
    client_inicio = insertClientStart(client_inicio, 4, 225780562, "Jessica", "Rua Vasco da Gama", 1000.00);

    meio_inicio = insertMeioStart(meio_inicio, 5, "Carro Eletrico", 100.00, 25.00, 800, "Barcelos", "Available");
    meio_inicio = insertMeioStart(meio_inicio, 10, "Trotinete", 10.00, 1.50, 250, "Braga", "Available");
    meio_inicio = insertMeioStart(meio_inicio, 15, "Skate Eletrico", 80.00, 3.00, 50, "Porto", "Available");
    meio_inicio = insertMeioStart(meio_inicio, 20, "Bike Eletrica", 60.00, 10, 400, "Lisboa", "Available");
    meio_inicio = insertMeioStart(meio_inicio, 25, "Moto Eletrica", 100.00, 15.00, 600, "Barcelos", "Available");
    

    client_inicio = changeClient(client_inicio, 1, 777777777, "Tiago", "Rua da Industria", 3000.00);
    meio_inicio = changeMeio(meio_inicio, 5, "Trotinete", 80.00, 3.00, 300);

    client_inicio = removeClient(client_inicio, 1);
    meio_inicio = removeMeio(meio_inicio, 20);

    rent_inicio = inserirAluguer(rent_inicio, client_inicio, 20, 4, 1, "Jessica", 10.00);
    rent_inicio = inserirAluguer(rent_inicio, client_inicio, 10, 2, 2, "Isabela", 1.50);
    listarRent(rent_inicio);

    listMeanAutonomy(meio_inicio, "MeansAutonomy.txt");
    listarMeioGeocodigo(meio_inicio, "Barcelos");

    meio_inicio = lerBinario();
    imprimirBinEmTxt();
}
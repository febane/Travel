/**
 * trablib.h
 * Main Library
 * 
 * @package     Travel
 *
 * @author      Fernando Barbosa Neto   
 * @author      Jeferson de Oliveira Batista   
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 30 // número de cidades
#define TAM 40 // tamanho máximo das strings

struct cidade
{	
	char nome[TAM+1];
	int x;
	int y;
	int diaria;
	float custo[N];
};


typedef struct cidade Cidade;

/*
 * Lê arquivo de dados
 * nome-coord.txt
 */
void ler_coord(Cidade cidades[], char arquivo[]);

/*
 * Lê arquivo de dados
 * diaria-custo.txt
 */
void ler_custo(Cidade cidades[], char arquivo[]);

/*
 * Calcula distâncias entre 
 * todas as cidades e armazena
 * em um arquivo distancia.txt 
 */
void armazenar_distancias(Cidade cidades[], char arquivo[], float D[][N]);

/*
 * Calcula os custos de viagem entre 
 * todas as cidades e armazena
 * em um arquivo custo.txt 
 */
void armazenar_custo(Cidade cidades[], char arquivo[], float D[][N], float C[][N]);

/*
 * Imprime na tela os nomes
 * das cidades mais ao norte,
 * mais ao sul, mais a oeste,
 * mais a leste e a mais central.
 */
void imprimir_cidades(Cidade cidades[]);

// Imprime os dados do caminho de 1 a 30
void imprimir_caminhos(float D[][N], float C[][N]);

/* 
 * Imprime os dados do caminho de 1 a 30,
 * seguindo uma lei de formação
 */
void imprimir_leiFormacao(int criterio, float D[][N], float C[][N], int origem, int destino);

// Função usada no desempate dos caminhos
int verCaminho(int criterio, float D[][N], float C[][N], int origem, int destino);

/*
 * Imprime os dados do caminho de origem a destino,
 * seguindo ambas as leis de formação
 */
void imprimir_OrigemDestino(float D[][N], float C[][N]);



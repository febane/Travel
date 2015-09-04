/**
 * trablib.c
 * Library's Implementation
 * 
 * @package     Travel
 *
 * @author      Fernando Barbosa Neto   
 * @author      Jeferson de Oliveira Batista   
 * 
 */

#include "trablib.h"

void ler_coord(Cidade cidades[], char arquivo[])
{
	FILE *f;
	int i=0;
	
	f = fopen(arquivo, "r");
	
	if(f==NULL)
	{
		printf("Erro ao acessar %s\n", arquivo);
		exit (1);
	}
	
	while(!feof(f))
	{		
		fgets(cidades[i].nome, TAM, f);
		fscanf(f, "%d %d\n", &cidades[i].x, &cidades[i].y);
		i++;
	}
}

void ler_custo(Cidade cidades[], char arquivo[])
{
	FILE *f;
	int i,j;
	
	f = fopen(arquivo, "r");
	
	if(f==NULL)
	{
		printf("Erro ao acessar %s\n", arquivo);
		exit (2);
	}
	
	for(i=0; i<N; i++)
		fscanf(f, "%d", &cidades[i].diaria);
	
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			fscanf(f, "%f", &cidades[i].custo[j]);
}

void armazenar_distancias(Cidade cidades[], char arquivo[], float D[][N])
{	
	int i,j;
	int x,y;
	FILE *f;
	
	f = fopen(arquivo, "w");
	
	if(f==NULL)
	{
		printf("Erro ao acessar %s\n", arquivo);
		exit (3);
	}
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			x = cidades[i].x - cidades[j].x;
			y = cidades[i].y - cidades[j].y;
			D[i][j] = sqrt(pow(x, 2) + pow(y, 2));
			fprintf(f, " %.2f", D[i][j]);
		}
		fprintf(f,"\n");
	}
}

void armazenar_custo(Cidade cidades[], char arquivo[], float D[][N], float C[][N])
{
	int i,j;
	FILE *f;
	
	f = fopen(arquivo, "w");
	
	if(f==NULL)
	{
		printf("Erro ao acessar %s", arquivo);
		exit (4);
	}
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			if(i==j)
				C[i][j] = 0;
			else
				C[i][j] = cidades[i].custo[j]*D[i][j] + cidades[j].diaria;
			fprintf(f, " %.2f", C[i][j]);
		}
		fprintf(f,"\n");
	}
}

void imprimir_cidades(Cidade cidades[])
{
	int norte=0, sul=0, leste=0, oeste=0, central=0;
	int i;
	int x,y;
	float mais_centro, dist_centro;
	
	x = cidades[0].x;
	y = cidades[0].y;
	mais_centro = sqrt(pow(x-12, 2) + pow(y-14, 2));
	
	for(i=1; i<N; i++)
	{
		x = cidades[i].x;
		y = cidades[i].y;
		if(y > cidades[norte].y)
			norte = i;
		
		if(y < cidades[sul].y)
			sul = i;
		
		if(x > cidades[leste].x)
			leste = i;
		
		if(x < cidades[oeste].x)
			oeste = i;
			
		dist_centro = sqrt(pow(x-12, 2) + pow(y-14, 2));
		
		if(dist_centro < mais_centro)
		{			
			central = i;
			mais_centro = dist_centro;
		}
	}
	
	printf("Cidades(s) mais ao norte:\n");
	for(i=0; i<N; i++)
		if(cidades[i].y == cidades[norte].y)
			printf("%s", cidades[i].nome);
	
	printf("\nCidades(s) mais ao sul:\n");
	for(i=0; i<N; i++)
		if(cidades[i].y == cidades[sul].y)
			printf("%s", cidades[i].nome);
			
	printf("\nCidades(s) mais ao leste:\n");
	for(i=0; i<N; i++)
		if(cidades[i].x == cidades[leste].x)
			printf("%s", cidades[i].nome);
	
	printf("\nCidades(s) mais a oeste:\n");
	for(i=0; i<N; i++)
		if(cidades[i].x == cidades[oeste].x)
			printf("%s", cidades[i].nome);
	
	printf("\nCidades(s) a mais central:\n");
	for(i=0; i<N; i++)
	{
		x = cidades[i].x;
		y = cidades[i].y;
		dist_centro = sqrt(pow(x-12, 2) + pow(y-14, 2));
		if(dist_centro == mais_centro)
			printf("%s", cidades[i].nome);
	}
}

void imprimir_caminhos(float D[][N], float C[][N])
{
	int i;
	float dist_total=0, custo_total=0;
	
	printf("\nCidade Origem: %d\nCidade Destino: %d\nCaminho: 1", 1, N);
	for(i=2; i<=N; i++)
	{
		printf(" -> %d", i);
		dist_total += D[i-2][i-1];
		custo_total += C[i-2][i-1];
	}
	printf("\nDistancia total: %f\nCusto total: %.2f\n", dist_total, custo_total);
}

void imprimir_leiFormacao(int criterio, float D[][N], float C[][N], int origem, int destino)
{
	if(criterio != 1 && criterio != 2)
	{
		printf("\nCriterio inexistente!\n");
		exit (5);
	}
	if(origem < 1 || destino > N || origem >= destino)
	{
		printf("\nProblemas com origem e destino!\n");
		exit (6);
	}
	int i=origem;
	int j;
	float dist_total=0, custo_total=0;
	int prox;
	float menor;
	
	float (*M)[N];
	if(criterio == 1)
		M = D;
	else
		M = C;
	
	printf("\nCidade Origem: %d\nCidade Destino: %d\n", origem, destino);
	printf("Caminho: %d", origem);
	while(i!=destino)
	{
		prox = i+1;
		menor = M[i-1][i];
		for(j=i+2; j<=destino; j++)
			if(M[i-1][j-1] < menor)
			{
				prox = j;
				menor = M[i-1][j-1];
			}
			else if(M[i-1][j-1] == menor)
			{
				if(verCaminho(criterio, D, C, j, destino) < verCaminho(criterio, D, C, prox, destino))
				{
					prox = j;
					menor = M[i-1][j-1];
				}
			}
		dist_total += D[i-1][prox-1];
		custo_total += C[i-1][prox-1];
		i = prox;
		printf(" -> %d", i);
	}
	printf("\nDistancia total: %f\nCusto total: %.2f\n", dist_total, custo_total);
}

int verCaminho(int criterio, float D[][N], float C[][N], int origem, int destino)
{
	int i=origem;
	int j;
	int tamCaminho = 0;
	int prox;
	float menor;
	
	float (*M)[N];
	if(criterio == 1)
		M = D;
	else
		M = C;
	
	while(i!=destino)
	{
		prox = i+1;
		menor = M[i-1][i];
		for(j=i+2; j<=destino; j++)
			if(M[i-1][j-1] < menor)
			{
				prox = j;
				menor = M[i-1][j-1];
			}
			else if(M[i-1][j-1] == menor)
			{
				if(verCaminho(criterio, D, C, j, destino) < verCaminho(criterio, D, C, prox, destino))
				{
					prox = j;
					menor = M[i-1][j-1];
				}
			}
		tamCaminho++;
		i = prox;
	}
	return tamCaminho;
}

void imprimir_OrigemDestino(float D[][N], float C[][N])
{
	int origem, destino;
	printf("\nCidade Origem: ");
	scanf("%d", &origem);
	printf("Cidade Destino: ");
	scanf("%d", &destino);
	imprimir_leiFormacao(1, D, C, origem, destino);
	imprimir_leiFormacao(2, D, C, origem, destino);
}



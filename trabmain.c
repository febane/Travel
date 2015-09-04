/**
 * trabmain.c
 * Main File
 * 
 * @package     Travel
 *
 * @author      Fernando Barbosa Neto   
 * @author      Jeferson de Oliveira Batista   
 * 
 */

#include "trablib.h" //todas as funções deste programa podem ser encontradas nesta biblioteca

int main()
{
	Cidade cidades[N];
	float D[N][N], C[N][N];
	
	ler_coord(cidades, "nome-coord.txt");
	ler_custo(cidades, "diaria-custo.txt");
	armazenar_distancias(cidades, "distancia.txt", D);
	armazenar_custo(cidades, "custo.txt", D, C);
	imprimir_cidades(cidades);
	imprimir_caminhos(D, C);
	imprimir_leiFormacao(1, D, C, 1, N);
	imprimir_leiFormacao(2, D, C, 1, N);
	imprimir_OrigemDestino(D, C);
	
	return 0;
}

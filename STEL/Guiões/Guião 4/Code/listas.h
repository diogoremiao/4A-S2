// Definição da estrutura da lista
typedef struct{
	int tipo;
	double tempo;
	double tempo_inicial_as;
	struct lista * proximo;
} lista;

lista * remover (lista * apontador);

lista * adicionar (lista * apontador, int n_tipo, double n_tempo, double n_tempo_as);

void imprimir (lista * apontador);
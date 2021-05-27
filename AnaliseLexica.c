#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define enderecosHash 42

typedef struct dados_sat {
    int chave;
    struct dados_sat *prox;
} dados;

typedef struct cel {
    char chave[21];
    dados *loc;
    dados *fim;
    struct cel *prox;
} celula;

typedef struct cel_hash {
    celula *lista;
    celula *fim;
} tab_hash;

/*
	função que recebe uma palavra-chave e
	calcula a soma do valor de cada letra
*/
int valor(char palavra[21]) {
	int i = 0, v = 0;

	while(palavra[i] != '\0') {
		v += palavra[i];
		i++;
	}

	return v;
}

/*
	função que recebe uma palavra-chave e
	calcula o endereço da tabela hash
*/
int h(char palavra[21]) {
	return valor(palavra) % 41;
}

/*
	função que recebe as palavras-chave pré-determinadas, 
	o endereço da tabela hash e do ponteiro do fim da lista e 
	executa a inserção dessas palavras na tabela
*/
void inserir_palavra(char palavra[21], celula **L, celula **fim)
{
	celula *novo;

	novo = (celula*) malloc(sizeof(celula));
	strcpy(novo->chave, palavra);
	novo->prox = NULL;
	novo->loc = NULL;
	novo->fim = novo->loc;

	if(*L == NULL) {
		*L = novo;
		*fim = novo;
	}

	else {
		(*fim)->prox = novo;	
		*fim = novo;
	}
}

/*
	função que recebe uma palavra-chave e o endereço
	da sua respectiva posição na tabela e consulta
	se a palavra recebida se encontra na tabela
*/
int consultar_palavra(char palavra[21], celula *L) {
	celula *aux;
	int i = 0;

	aux = L;

	while(i == 0 && aux != NULL) {
		if(strcmp(aux->chave, palavra) == 0)
			i = 1;
		else
			aux = aux->prox;
	}

	if(i == 1)
		return 1;
	else
		return 0;
}

/*
	função que recebe uma palavra no arquivo de entrada,
	a linha na qual foi encontrada e o endereço da tabela
	e insere tal linha na lista encadeada
*/
void inserir_linha(char palavra[21], int linha, celula **L) {
	dados *novo;
	celula *aux;

	novo = (dados*) malloc(sizeof(dados));
	novo->chave = linha;
	novo->prox = NULL;

	aux = *L;

	while(strcmp(aux->chave, palavra) != 0)
		aux = aux->prox;
	
	if(aux->loc == NULL) {
		aux->loc = novo;
		aux->fim = novo;
	}

	else {
		aux->fim->prox = novo;
		aux->fim = novo;
	}
}

/*
	função que recebe o endereço de cada célula
	da lista de linhas e a desaloca	
*/
void apagar_dados(dados **D)
{
	dados *aux;

	while(*D != NULL) {
		aux = *D;
		*D = (*D)->prox;
		free(aux);
	}
}

/*
	função que recebe o endereço de cada célula
	da lista de palavras-chave e as desaloca
*/
void apagar_tokens(celula **L) {
    celula *aux;
 
    while(*L != NULL) {
    	apagar_dados(&(*L)->loc);
        aux = *L;
        *L = (*L)->prox;
        free(aux);
    }
}

/*
	função que recebe o endereço
	da tabela hash e a desaloca
*/
void apagar_hash(tab_hash **T) {
	int i;

	for(i = 0; i < 41; i++)
		apagar_tokens(&(*T)[i].lista);

	free(*T);	
}

int main(int argc, char *argv[]) {
	FILE *entrada;
	tab_hash *T;
	celula *aux;
	dados *aux2;
	int i, endereco, linha = 1;
	int numeroDeTokens;
	char palavra[21], caractere;
	char *tokens[] = {	"auto", "break", "case", "char", 
						"const", "continue", "default", "do",
						"double", "else", "enum", "extern",
						"float", "for", "goto", "if",
						"int", "long", "register", "return",
						"short", "signed", "sizeof", "static",
						"struct", "switch", "typedef", "union",
						"unsigned", "void", "volatile", "while"	};

	for(i = 0; tokens[i] != NULL; i++)
		numeroDeTokens++;
	
	if(argc != 2) {
		printf("Erro de argumento\n");
		return 0;
	}

	entrada = fopen(argv[1], "r");

	if(!entrada)
		printf("Nao foi possivel abrir o arquivo %s\n", argv[1]);
	else {
		T = (tab_hash*) calloc(41, sizeof(tab_hash));

		for(i = 0; i < 32; i++) {
			endereco = h(tokens[i]);
			inserir_palavra(tokens[i], &T[endereco].lista, &T[endereco].fim);
		}

		while(!feof(entrada)) {
			i = 0;

			fscanf(entrada, "%c", &caractere);

			if(caractere == '\n')
				linha++;
		
			while((caractere >= 65 && caractere <= 90) || (caractere >= 97 && caractere <= 122)) {
				palavra[i] = caractere;
				i++;
				
				fscanf(entrada, "%c", &caractere);

				if(caractere == '\n')
					linha++;
			}
			
			palavra[i] = '\0';
			
			if(i > 1) {
				printf("%d: %s\n", linha, palavra);
				endereco = h(palavra);
				
				if(consultar_palavra(palavra, T[endereco].lista) == 1)
					inserir_linha(palavra, linha, &T[endereco].lista);
			}
		}
	}
	fclose(entrada);

	printf("\n");

	for(i = 0; i < enderecosHash; i++) {
		printf("%d: ", i);
			aux = T[i].lista;

		while(aux != NULL) {
			aux2 = aux->loc;
				
			printf("%s(", aux->chave);
			while(aux2 != NULL) {
				if(aux2->prox == NULL)
					printf("%d", aux2->chave);
				else
					printf("%d,", aux2->chave);

				aux2 = aux2->prox;
			}
			printf(") ");
				
			aux = aux->prox;
		}
		printf("\n");
	}
	printf("Fator de carga: %g\n", numeroDeTokens/enderecosHash);

	apagar_hash(&T);	

	return 0;
}
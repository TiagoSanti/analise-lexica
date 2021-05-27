# AnaliseLexica-C
Algorítmo que lê um código em C e organiza *tokens* pré-definidos encontrados nesse código em uma *tabela hash*.

# Descrição
A ideia do algorítmo é armazenar os tokens em uma tabela hash, percorrer um arquivo de texto e identificar a existência dos tokens neste arquivo, se os tokens forem identificados, o algorítmo armazena a linha junto aos tokens que estão presentes no texto na tabela. Foi utilizada alocação dinâmica nas listas quando possível.

## Execução
O nome do arquivo a ser lido deve ser inserido no argumento na linha de comando, no caso de executar o código "AnaliseLexica.c" para ler o arquivo "teste.c", deve-se executar da seguinte maneira:\
Terminal Linux: ```./AnaliseLexica teste.c```\
Prompt Windows: ```AnaliseLexica teste.c```

# Análise Léxica
É a primeira fase de um processo de compilação, consiste em agrupar caracteres e produzir tokens. A análise neste código não está totalmente condizente com a definição de análise léxica, já que comentários no código não deveriam ser considerados.

# Tabela Hash
## Descrição básica
Uma tabela hash, ou tebela de dispersão é uma estrutura de dados, seu objetivo é permitir, a partir de uma chave, uma busca e obtenção do valor desejado. Essa chave é calculada a partir de uma função hash. No código da Análise Léxica, o método utilizado para a função hash é o da divisão: ```h(k) = k mod m```, sendo *m* o tamanho da tabela. A função está localizada nas linhas 43-45:
```
int h(char palavra[21]) {
	return valor(palavra) % 41;
}
```
A função *valor( )* recebe uma palavra e soma os valores referentes a tabela ASCII de cada letra e retorna essa soma:
```
int valor(char palavra[21]) {
	int i = 0, v = 0;

	while(palavra[i] != '\0') {
		v += palavra[i];
		i++;
	}

	return v;
}
```

## Tokens, endereços da tabela e Fator de Carga
Os tokens selecionados são definidos nas linhas 177-184:
```
char *tokens[] = {  "auto", "break", "case", "char",
                    "const", "continue", "default", "do",
                    "double", "else", "enum", "extern",
                    "float", "for", "goto", "if",
                    "int", "long", "register", "return",
                    "short", "signed", "sizeof", "static",
                    "struct", "switch", "typedef", "union",
                    "unsigned", "void", "volatile", "while"   };
```
A quantidade de endereços da tabela é definida como constante na linha 5:
```
# define enderecosHash 41
```
**Fator de carga** é uma estatística relacionada a tabelas Hash, indica a proporção de distribuição das chaves dentro da tabela dada por ```carga = n/k```, em que *n* é o número de chaves ou tokens inseridos e *k* é o número total de endereços da tabela. O valor do fator de carga varia entre 0.0 e 1.0. Quanto maior o fator de carga, menor a chance de o tempo de execução ser constante O(1). Ou seja, quanto menos espaços disponíveis dentro da tabela, maior a chance de colisão para novas chaves. No código, o fator de carga é calculado na linha e impresso na linha 265:
```
printf("Fator de carga: %g\n", numeroDeTokens/enderecosHash);
```
# Exemplo de execução
Ao executar o código tendo como o arquivo "teste.c" presente no repositório a ser lido, a saída esperada é uma lista no seguinte formato: ```<linha>: <token>``` representando os tokens identificados e as respectivas linhas onde foram encontrados. Em seguida, é impressa a tabela hash contendo os tokens em seus respectivos endereços e linhas entre parênteses no formato:<br/> ```<endereço>: <token>(<linha1>, <linha2>,<...>) <token2>(<linha1>, <linha2>,<...>) <...>```<br/>O fator de carga é impresso ao final da saída.
```
1: include
1: stdio
3: define
3: MAX
5: int
5: main
5: void
7: int
7: aux
7: MAX
9: scanf
10: for
11: scanf
13: for
15: for
16: if
18: aux
20: aux
23: for
24: printf
25: printf
27: return

0: sizeof() unsigned()
1: float()
2: case() if(16) switch()
3: default() int(5,7) volatile()
4: char() while()
5:
6: do() extern()
7:
8: continue() register()
9:
10:
11:
12:
13:
14:
15: else() typedef()
16: return(27)
17:
18: const()
19: signed()
20: double() union()
21: struct()
22: long()
23:
24: void(5)
25: break()
26:
27: enum() short()
28:
29:
30:
31: auto() goto()
32:
33: static()
34:
35:
36:
37:
38:
39:
40: for(10,13,15,23)
Fator de carga: 0.780488
```

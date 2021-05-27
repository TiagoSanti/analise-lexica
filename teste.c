#include <stdio.h>

#define MAX 100

int main(void)
{
	int i, j, k, aux, n, A[MAX];
	
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	
	for (i = 0; i < n - 1; i++) {
		k = i;
		for (j = i + 1; j < n; j++)
			if (A[j] < A[k])
				k = j;
		aux = A[i];
		A[i] = A[k];
		A[k] = aux;
	}

	for (i = 0; i < n; i++)
		printf("%d ", A[i]);
	printf("\n");
	
	return 0;
}
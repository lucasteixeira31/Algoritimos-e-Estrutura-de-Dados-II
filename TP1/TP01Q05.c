#include <stdio.h>

int soma(int numero){

	if (numero == 0){
	return 0;
	}else{
	return numero % 10 + soma(numero/10);
	}
}


int main(){

	int numero;
	
	while (scanf("%d", &numero)!= EOF ){
		printf("%d\n", soma(numero));
	}

return 0;
}

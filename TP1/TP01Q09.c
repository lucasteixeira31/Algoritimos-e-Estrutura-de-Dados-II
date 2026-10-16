#include <stdio.h>
#include <stdlib.h>

//deloca cada caractere 3 posições na tabela ASCII recursivamente
void crip(char *texto, int i){
	if (texto[i] == '\0'){
		return;
	}

	//avança recursivamente para proxima posição
	texto[i] = texto[i]+3;
	crip(texto, i+1);
}

int main(){
	char texto[1000];
	
	//le linhas completas usando scanf até o fim do arquivo
	while (scanf( " %[^\n]", texto) != EOF){
	//verifica a condição de parada se flag acionada
		if (texto[0] == 'F' && texto[1] == 'I' && texto[2]=='M' && texto[3]== '\0' ){
			break;
	
		}
		crip(texto, 0);
		printf("%s\n", texto);
	}
return 0;
}

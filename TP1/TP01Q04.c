#include <stdio.h>
#include <stdlib.h>


char *lerTexto(){
	char *texto =NULL;
	int tamanho=0;
	int c;
	
	while ((c = getchar()) != '\n' && (c != EOF)){
		
		texto = realloc(texto, (tamanho + 2)* sizeof(char));
		texto[tamanho]=(char)c;
		tamanho++;		
		
		texto[tamanho]='\0';
	}	
	return texto;
}

char *inverter (char *texto){
	int tamanho=0;
	int j=0;
	while(texto[tamanho] != '\0'){
		tamanho++;
	}	
	char *textoInvertido = malloc ((tamanho+1)* sizeof(char));
	for (int i = tamanho -1; i>=0; i--){
	textoInvertido[j] = texto[i];
	j++;
	}
	textoInvertido[j] = '\0';
	
	return textoInvertido;
	}

int sair (char *texto, char *FIM){
	int i=0;
	while(texto[i] != '\0'){
		if(texto[i] != FIM[i]){
		 return 0;
		}
	i++;	
	}
	if(texto[i] == '\0' && FIM[i]== '\0'){
		return 1;
	}
 return 0;	
}


int main (){

	while(1){

	char *texto = lerTexto();

	if (sair (texto, "FIM") == 1){
		free(texto);
		return 0;
	}

	char *textoInvertido = inverter(texto);
	
	printf ("%s\n", textoInvertido);

	free(textoInvertido);
	free(texto);

	}
return 0;	
}

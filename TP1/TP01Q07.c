#include <stdio.h>
#include <stdlib.h>
//encontra compriment da maior substring sem caracteres repetidos
int maiors(char *entrada){
	
	int ascii[256];
	int start =0;	
	int maior = 0;
	int i=0;
	//inicialisa a tabela ASCII com valor negativo
	for(int j=0;j<256; j++){
		ascii[j]=-1;
	}
		//percorre a string expandindo a janela deslizante
		while (entrada[i] != '\0'){
	
		unsigned char indice = (unsigned char)entrada[i];
		//se o caractere ja foi visto na janela atual, desloca o inicio para a posição seguinte
		if(ascii[indice]>=start){
		start=ascii[indice]+1;
		}
		//atualiza a ultima posição em que o caractre foi encontrado
		ascii[indice]=i;
		//calcula o tamanho da janela atual e atualiza o tamanho maximo
		int tamanho = i-start+1;
		if(tamanho>maior){
			maior=tamanho;
		}

		i++;
	}
	return maior;
}

//Função responsavel pelo encerramento do programa caso flag FIM
int parar (char  *entrada){
	//chacagem da posição dos caracteres
	if(entrada[0]== 'F' && entrada[1] == 'I' && entrada[2]== 'M'&& entrada[3] == '\0'){
		return 1;
	}
return 0;
}
int main (){

	char entrada[1000];
	
		
	while(1){
	
	       	scanf(" %s", entrada);
		//encerra laço quando a flag de encerramento for acionada
		if(parar(entrada)==1){
		break;
		}
		//chama a função maiors e exibe o comprimento da maior string sem repetição
		printf("%d\n", maiors(entrada));
	
	}

return 0;
}

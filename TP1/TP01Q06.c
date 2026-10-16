#include <stdio.h>
#include <stdlib.h>
//converte maiusculo pra minusculo
char minuscula(char letra){
	//verifica se o caractere esta no intervalo maiusculo
	if (letra >= 'A' && letra <= 'Z'){
		letra =letra + ('a' - 'A');
	
	}
	return letra;
}

//verifica se duas palavras são anagramas
int anagrama(int *contador,char *palavra, char *palavra2){
	int i=0;	
	//converte a primeira palavra pra minusculo e incrementa frequencia de cada letra
	while(palavra[i]!='\0'){ 
		palavra[i] = minuscula(palavra[i]);
	       	contador[palavra[i]- 'a']++;
		i++;
	}
	i=0;
	//converte segunda palavra para minuscula e decrementa frequencia de cada letra
	while (palavra2[i] != '\0'){
	 	palavra2[i]= minuscula(palavra2[i]);
		contador[palavra2[i]-'a']--;
	i++;
	}
	//se qualquer contagem for diferente de 0, a frequencia de letras não bate
	for(int i=0; i<26;i++){
		if(contador[i]!=0){
		 return 1;
		}
		
	}
	return 0;

}

int main (){
	
	
	char palavra[1000];
	char palavra2[1000];
	int i;
	
	while(1){
		int contador[26]= {0} ;
		
		//le as duas palavras separadas por esspaço na mesma linha
		scanf("%s %s", palavra, palavra2);
		//verifica se a primeira palavra e a condição de parada FIM
		if (palavra[0] == 'F' && palavra[1]== 'I' && palavra[2]=='M' && palavra[3]== '\0'){
		break;
		}
	
		//executa a verificacao de anagrama 
		int resultado = anagrama(contador, palavra, palavra2);
		
		if(resultado == 0){
			printf("SIM\n");
		}else{
			printf("NAO\n");
		}
	}

return 0;
}

#include <stdio.h>
#include <stdlib.h>


//verifica recursivamente se a sring é só vogal
int vogal(char *palavra, int i){
	//fim da palavra alcançado
	if (palavra[i] == '\0'){
		return 1;
	}
	//se encontrar qualquer caracterer não vogal invalida
	char c = palavra[i];
	if(c != 'a' && c!='e' && c!='i' && c != 'o' && c != 'u' && c!='A' && c!='E' && c != 'I' && c != 'O' && c !='U'){
		return 0;
	}
return vogal(palavra, i+1);
}

	//verifica recursivamente se é composta de consoante
int consoante(char *palavra, int i){
	if(palavra[i]=='\0'){
		return 1;
	}		
	char c = palavra[i];
	//se não for letra do alfabeto ou uma vogal não é consoante
	if(!((c>='a' && c<='z') || (c >= 'A' && c<='Z')) ||(c=='a' || c=='e' || c=='i' || c=='o'||c=='u'||c=='A'|| c=='E' || c=='I' || c=='O' || c=='U')){
		return 0;
	}
	return consoante(palavra, i+1);
}	

//verifica recursivamente se e mm numero inteiro
int inteiro( char *palavra, int i){
	if (palavra[i] == '\0'){
		return 1;
	}
	//se o carater estiver fora do intervalo de 0a9 invalida	
	char c =palavra[i];
	if(c<'0' ||c>'9'){ 
		return 0;
	}

	return inteiro(palavra, i+1);
}

//verifica recursivamente se é um numero real
int real(char *palavra, int i, int separador, int digito){
	//invalida se tiver mais de um separador
	if(separador>1){
	return 0;
	}
	//ao chegar no fim exige no minimo um digito e no maximo um separador, se não, invalida
	if (palavra[i] == '\0'){
		if (separador <=1 && digito > 0){
			return 1;
		}
	return 0;
	}
	char c = palavra[i];
	//contagem de digitos
	if (c>='0' && c<='9'){
		return real(palavra, i+1, separador, digito +1);
	}
	//contagem de separador
	else if (c=='.' || c==','){
		return real(palavra, i+1, separador+1, digito);
	}
	//invalida se tiver qualquer outro caracter (letas, simbolos, etc)	
	return 0;
}

int main(){
	char palavra[1000];
	while(scanf (" %[^\n\r]",palavra) !=EOF){
		//condição de parada
		if(palavra[0] == 'F' && palavra[1]== 'I' && palavra[2]=='M' && palavra[3]=='\0'){
			break;
		
		}
		//chama a função que veifica vogal		
		if(vogal(palavra, 0) == 1){
			printf("SIM ");
		}else{
			printf("NAO ");
		}
		//chama função que verifica consoante
		if(consoante(palavra, 0)==1){
			printf("SIM ");

		}else{
			printf("NAO ");
		}
		//chama função que verifica inteiro
		if(inteiro(palavra, 0)==1){
			printf("SIM ");
		}else{
			printf("NAO ");
		
		}
		//Chama função que verifica real
		if(real(palavra, 0, 0, 0)==1){
			printf("SIM\n");

		}else{
			printf("NAO\n");
		}
	}
return 0;
}







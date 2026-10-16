import java.util.Scanner;

public class TP01Q08{

	//valida se a senha informada tem o tamanh correto
	public static boolean tamanho(String senha){
		//verifica se o comprimento é no mnimo 8 caracteres		
		if(senha.length()>=8){
			return true;
		}
	return false;
	}
	//valida se a senha informada tem maiusculas
	public static boolean maiuscula(String senha){
		for(int i=0; i<senha.length(); i++){
			char c = senha.charAt(i);			
			if(c>='A' && c <='Z' ){
				return true;
			}
		}	
	return false;
	}
	//valida se a senha informada tem miusculas
	public static boolean minusculas(String senha){
		for(int i =0; i<senha.length(); i++){
			char c = senha.charAt(i);
			if(c >= 'a' && c <='z'){
				return true;
			}
		}
	return false;
	}
	//valida se a senha informada tem numeros
	public static boolean numeros(String senha){
		for (int i=0; i < senha.length(); i++){
			char c =senha.charAt(i);
			if(c >='0' && c<='9'){
				return true;
			
			}
		}
	return false;	
	}
	
	//valida caractere especial
	public static boolean especial(String senha){
		for(int i= 0; i<senha.length(); i++){
			char c = senha.charAt(i);
			if(!(c>='0' && c <='9')&&!(c>='a'&& c <='z')&&!(c>='A' &&c<='Z')){
			return true;
			}
		}
	return false;
	}
	 //verifica flag de saida 
	public static boolean exit(String senha, String FIM){
		if(senha.length() != FIM.length()){
			return false;
		}
		for(int i=0; i<senha.length();i++){
			if(senha.charAt(i) != FIM.charAt(i)){
				return false;
			}
		}
	return true;	
	}
	
	public static void main (String[] args){
		Scanner entrada = new Scanner(System.in);

		while(true){
			String palavra = entrada.nextLine();
			
			if (exit(palavra, "FIM")== true){
			return;
			}
			//valida simultaneamente todas as regras exigidas
			if(tamanho(palavra) && maiuscula(palavra)&& minusculas(palavra)&&especial(palavra) && numeros(palavra)){
				System.out.println("SIM");
			}else{
				System.out.println("NAO");
			}
		}
	}	
}


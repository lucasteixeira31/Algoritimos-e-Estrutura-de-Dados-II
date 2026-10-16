import java.util.Scanner;


public class TP01Q03{
	
	public static boolean DefineVogal(String palavra){
		boolean resp = true;

		for(int i=0;i<palavra.length(); i++){
			char c= palavra.charAt(i);
			if (c!='a' && c!='e' && c!='i' && c!='o' && c!='u' && c!='A' && c!='E' && c!='I' &&c!='O' &&c!='U'){
				resp = false;
			}
		}
	return resp;
	}

	public static boolean DefineConsoante(String palavra){
		boolean resp = true;
		char vogais [] = {'a', 'e', 'i', 'o', 'u' , 'A', 'E', 'I', 'O', 'U'};
		for (int i =0; i < palavra.length(); i++){
			char c = palavra.charAt(i);
			if ((c >='a' && c <='z') || (c >='A' &&c<='Z')){
				for(int j=0; j< vogais.length; j++){
					if (vogais[j]==c){
						resp=false;
					}
				}
				
			}else{
				resp = false;
			}

		}
	return resp;
	}
	public static boolean DefineInteiro(String palavra){
		boolean resp = true;
		
		for (int i=0; i<palavra.length(); i++){
			char c = palavra.charAt(i);
			if (c < '0' || c > '9'){
				resp= false;
			}	
		
		}
	return resp;
	}
	
	public static boolean DefineReal(String palavra){
		boolean resp = true;
		int separador=0;

		for (int i =0; i< palavra.length(); i++){
			char c = palavra.charAt(i);

			if (c>='0' && c<='9'){
			
			}else if (c== '.' || c==','){
				separador++;
			
			}else {
				resp=false;
			}
		}
		if (separador > 1){
		resp = false;
		}
	return resp;	
	}

	public static boolean exit (String palavra){
		String FIM = "FIM";
		if (palavra.length() != FIM.length()){
			return false;
		}
		for (int i =0; i < palavra.length(); i++){
			if (palavra.charAt(i) != FIM.charAt(i)){
			return false;
			}
		}
	return true;
	}

	public static void main (String[] args){
		Scanner entrada = new Scanner(System.in);
		
		while(true){
		String palavra = entrada.nextLine();

		if (exit(palavra)== true){
			return;
		}
		if (DefineVogal(palavra) == true ){
			System.out.print("SIM ");
		}else{
			System.out.print("NAO ");
		}
		
		if(DefineConsoante(palavra) == true){
			System.out.print("SIM ");
		}else{
			System.out.print("NAO ");
		}
		
		if (DefineInteiro(palavra) == true){
			System.out.print("SIM ");
		}else{
			System.out.print("NAO ");
		}

		if (DefineReal(palavra)==true){
			System.out.println("SIM");
		}else{
			System.out.println("NAO");
		}

		
		
		}
	}

}

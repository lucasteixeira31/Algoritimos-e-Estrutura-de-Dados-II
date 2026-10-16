import java.util.Scanner;
import java.util.Random;


public class TP01Q02{
	public static String TrocaFrase (String palavra, Random gerador){
		String palavraNova = "";
		char letra1 = (char)('a'+(Math.abs(gerador.nextInt()%26)));
		char letra2 = (char)('a'+(Math.abs(gerador.nextInt()%26)));		
		
		for (int i =0; i < palavra.length(); i++){
			if (palavra.charAt(i) == letra1 ){
				palavraNova += letra2;
			}else{
				palavraNova += palavra.charAt(i);
			}
		}
	return palavraNova;
	}

	public static boolean exit(String palavra, String FIM){
		if (palavra.length() != FIM.length()){
		return false;
		}
		for (int i =0; i< palavra.length(); i++){
			if (palavra.charAt(i)!= FIM.charAt(i))
		return false; 
		}
	return true;
	}
	
	public static void main(String[] args){
	
		Scanner entrada = new Scanner(System.in);

		Random gerador = new Random();
		gerador.setSeed(4);

		while (true){
		
			String palavra = entrada.nextLine();
			if (exit(palavra, "FIM")){
				return;
			}	
		
		
		System.out.println(TrocaFrase(palavra,gerador));
		}
	}
}

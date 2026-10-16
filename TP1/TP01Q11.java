import java.util.Scanner;


public class TP01Q11{
	//metodo recursivo auxiliar  que constroi a string invertida
	public static String  auxinverter (String palavra, int i){
		//condição de parada da recurção
		if (i<0){
			return "";
		}
		return palavra.charAt(i) + auxinverter(palavra, i-1);
		
	}
	//metodo de sobracarga que  inverte a partirr do ultimo caractere
	public static String inverter(String palavra){
		return auxinverter(palavra, palavra.length()-1);
	}
	//compara a palavra lida com a flag de encerramento
	public static boolean exit(String palavra, String FIM){
		if(palavra.length()!= FIM.length()){
			return false;
		}

		for(int i =0; i<palavra.length(); i++){
			if (palavra.charAt(i) != FIM.charAt(i)) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args){
		Scanner entrada =new Scanner(System.in);
		
		while(true){
			String palavra = entrada.nextLine();
	
			if(exit(palavra, "FIM")){
				break;
			}
	
		System.out.println(inverter(palavra));
		}
	}
}

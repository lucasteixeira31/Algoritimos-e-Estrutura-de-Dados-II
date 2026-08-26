import java.util.Scanner;

public class TP01Q01{
	public static String Crip(String palavra){
		String palavraCrip= "";
		for (int i=0; i<palavra.length(); i++){
			
			palavraCrip = palavraCrip+ (char)(palavra.charAt(i)+3);
		}
	
		return palavraCrip;
	}
	
	public static boolean exit(String palavra, String FIM){
		if(palavra.length() != FIM.length()){
			return false;
		}
		for (int i=0; i<palavra.length(); i++){
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
		
       			if(exit(palavra, "FIM")==true){
				return;
			}else{
				System.out.println(Crip(palavra)); 
			}
		}
	}

}


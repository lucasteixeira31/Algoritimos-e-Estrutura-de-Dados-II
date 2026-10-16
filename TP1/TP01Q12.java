import java.util.Scanner;

public class TP01Q12{
	//calcula recursivamente a soma dos digitos
	public static int soma(int numero){
		//retorna o numero com apenas 1 digitto
		if (numero<10){
			return numero;
		}
		//pega o ultimo digito e soma com a chamada reciursiva restante
		return (numero % 10)+ soma(numero/10);
	}
	//compara a string com a flag de encerramento
	public static boolean exit(String palavra, String FIM){
		if (palavra.length() != FIM.length()){
			return false;
		}
		for (int i=0; i<palavra.length(); i++){
			if(palavra.charAt(i) != FIM.charAt(i)){
				return false;
		}
			}
	return true;
	}
	public static void main(String[] args){
		Scanner entrada=new Scanner(System.in);
		
		while(entrada.hasNextLine()){
			String palavra= entrada.nextLine();
		//chama metodo que verifica fla de parada
		if(exit(palavra, "FIM")){
			break;
		}
		
		int numero = Integer.parseInt(palavra);
		System.out.println(soma(numero));
		}

	}
}

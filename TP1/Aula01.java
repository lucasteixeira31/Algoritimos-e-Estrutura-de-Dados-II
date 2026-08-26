import java.util.Scanner;

public class Aula01{
	public static void main(String[] args){
		Scanner entrada = new Scanner(System.in);
		int count1 =0;
		int count = 0;
		System.out.println("digite o nome");		
		String nome = entrada.nextLine(); 

		for(int i=0; i < nome.length(); i++){

		System.out.println(nome.charAt(i));
		
			if (nome.charAt(i)== 'a' || nome.charAt(i)=='e'|| nome.charAt(i)== 'i' || nome.charAt(i)=='o'|| nome.charAt(i)== 'u') {
			count++; 
			}else{
			count1++;
			
			}
		}
	System.out.println(nome.length());
	System.out.println("a quantidade de vogais é: " + count);
	System.out.println("a quantidade de consoantes é: " + count1);
	}

}

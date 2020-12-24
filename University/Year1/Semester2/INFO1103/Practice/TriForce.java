import java.util.Scanner;

public class Triforce {
	/*public static boolean validInput(int a){
		boolean check = true;
		if(a < 2 || a > 20){
			check = false;
			return check;
		}

		try{
			int a1 = Integer.parseInt(a);
		}
		catch(NumberFormatException e){
			check = false;
		}
		return check;
	}*/

	public static void main(String[] args) {
		Scanner keyboard = new Scanner(System.in);
		System.out.print("Enter height: ");
		int n1 = keyboard.nextInt();

		/*if(keyboard.hasNextInt()){
			System.out.println();
			System.out.println("Invalid height.");
			return;
		}*/

		for(int i = 1; i <= 4*n1; i++){
			if(i!=2*n1 && i!=2*n1+1 && i!=4*n1){
				System.out.print(" ");
			}
			else if(i==2*n1){
				System.out.print("/");
			}
			else if(i==2*n1+1){
				System.out.print("\\");
			}
			else{
				System.out.println(" ");
			}
		}

		for(int i = 1; i <= 4*n1; i++){
			if(i<2*n1-1 || i>2*n1+2 && i!=4*n1){
				System.out.print(" ");
			}
			else if(i>2*n1-1 && i<2*n1+2){
				System.out.print("_");
			}
			else if(i==2*n1-1){
				System.out.print("/");
			}
			else if(i==2*n1+2){
				System.out.print("\\");
			}
			else if(i == 4*n1){
				System.out.println(" ");
			}
		}

		for(int i = 1; i <= 4*n1; i++){
			if(i<2*n1-2 || i>2*n1+3 && i!=4*n1){
				System.out.print(" ");
			}
			else if(i>2*n1-2 && i<2*n1+3){
				System.out.print("_");
			}
			else if(i==2*n1-2){
				System.out.print("/");
			}
			else if(i==2*n1+3){
				System.out.print("\\");
			}
			else if(i == 4*n1){
				System.out.println(" ");
			}
		}
	}
}

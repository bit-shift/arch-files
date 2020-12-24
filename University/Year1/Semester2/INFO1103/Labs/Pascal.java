public class Pascal {

	public static int factorial(int n){
		int fact = 1;
		while(n>0){
			fact = fact*n;
			n = n-1;
		}

		return fact;
	}

	public static void main(String[] args) {
		if(args.length == 0){
			System.out.println("Not enough arguments.");
			return;
		}
		else if(args.length > 1){
			System.out.println("Too many arguments.");
			return;
		}
		int n1;
		try{
			n1 = Integer.parseInt(args[0]);
		}
		catch(NumberFormatException e){
			System.out.println("Invalid argument.");
			return;
		}

		for(int i = 0; i<=n1; i++){
			for(int j = 0; j<=i; j++){
				if(j==i){
					System.out.print((factorial(i))/((factorial(i-j))*factorial(j)));
				}
				else{
					System.out.print((factorial(i))/((factorial(i-j))*factorial(j))+" ");
				}
			}
			System.out.println();
		}

	}
}

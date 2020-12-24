public class AddFour {

	public static int addFour(int n1, int n2, int n3, int n4) {


		int sum;

		sum = n1+n2+n3+n4;

		return sum;
	}

	public static void main(String[] args) {

		if (args.length < 4) {
			return;
		}


		int x = Integer.parseInt(args[0]);
		int y = Integer.parseInt(args[1]);
		int z = Integer.parseInt(args[2]);
		int w = Integer.parseInt(args[3]);



		System.out.println("RESULT: " + addFour(x,y,w,z));
	}
}

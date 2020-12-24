import java.util.HashMap;
import java.util.Scanner;

public class Occurence {

	public static void main(String[] args) {
		
		String input;
		HashMap<Character, Integer> occurence = new HashMap<Character, Integer>();
		Scanner scan = new Scanner(System.in);
		System.out.print("Please input a string: ");
		while (scan.hasNext()) {
			input = scan.next();
			for (int i = 0; i < input.length(); i++) {
				if (occurence.containsKey(input.charAt(i))) {
					occurence.put(input.charAt(i), occurence.get(input.charAt(i)) + 1);
				} else {
					occurence.put(input.charAt(i), 1);
				}
			}
			System.out.println(occurence);
			System.out.print("Please input a string: ");
		}
	}
}

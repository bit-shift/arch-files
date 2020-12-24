import java.util.Scanner;

public class KeyboardInput {
  public static void main(String[] args) {
    int n1, n2;
    double d1, d2;
    String s1, s2, s3;
    Scanner keyboard = new Scanner(System.in);
    System.out.println("Please enter two integers on the next line");
    n1 = keyboard.nextInt();
    n2 = keyboard.nextInt();
    System.out.println("The two integers that you entered were " + n1 + " and " + n2);
    System.out.println("Please enter two numbers, decimals are okay");
    d1 = keyboard.nextDouble();
    d2 = keyboard.nextDouble();
    System.out.println("The decimals that you have entered have the following product " + d1*d2);
    System.out.println("Please enter two words");
    s1 = keyboard.next();
    s2 = keyboard.next();
    System.out.println("You entered " + s1 + " and " + s2);
    s3 = keyboard.nextLine();
    System.out.println("Please enter a sentence");
    s3 = keyboard.nextLine();
    System.out.println("Just checking that what you entered was this:");
    System.out.println(s3);
  }
}

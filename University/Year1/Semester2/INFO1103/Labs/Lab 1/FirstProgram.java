import java.util.Scanner;

public class FirstProgram {

  public static void main(String[] args) {

    System.out.println("Hello");
    System.out.println("I will add three numbers for you");
    System.out.println("Please enter three whole numbers on the one line");

    int n1, n2, n3;

    Scanner keyboard = new Scanner(System.in);

    n1 = keyboard.nextInt();
    n2 = keyboard.nextInt();
    n3 = keyboard.nextInt();

    System.out.println("The sum of the three numbers is:");
    System.out.println(n1+n2+n3);

    keyboard.close();

  }
}

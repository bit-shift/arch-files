import java.util.Scanner;
public class SubCipher {
  public static void main(String[] args) {
    Scanner keyboard = new Scanner(System.in);
    int n1;
    String s1;
    System.out.print("Please enter the key: ");
    n1 = keyboard.nextInt();
    s1 = keyboard.nextLine();
    System.out.println("Please enter your message:");
    s1 = keyboard.nextLine();
    System.out.println("The encrypted message is as folows:");
    System.out.println(s1);

  }
}

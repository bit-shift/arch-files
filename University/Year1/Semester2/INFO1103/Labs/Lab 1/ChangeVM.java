import java.util.Scanner;

public class ChangeVM {
  public static void main(String[] args) {
    System.out.println("Please enter a number from 1 to 99");
    int amount, originalAmount;
    Scanner keyboard = new Scanner(System.in);
    amount = keyboard.nextInt();

    int q = 25, d = 10, n = 5, p = 1;
    int quarters, dimes, nickels, pennies;

    originalAmount = amount;
    quarters = amount/q;
    amount = amount%q;

    dimes = amount/d;
    amount = amount%d;

    nickels = amount/n;
    amount = amount%n;

    pennies = amount/p;
    amount = amount%p;

    System.out.println("The change given will be as follows:");
    System.out.println(quarters + " Quarter(s)");
    System.out.println(dimes + " Dime(s)");
    System.out.println(nickels + " Nickel(s)");
    System.out.println(pennies + " Pennies/Penny");

    




  }
}

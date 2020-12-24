import java.util.Scanner;

public class EggBasket {
  public static void  main(String[] args) {
    int numberOfBaskets, eggsPerBasket, totalEggs;

    Scanner keyboard = new Scanner(System.in);

    System.out.println("Please enter the number of Baskets");

    numberOfBaskets = keyboard.nextInt();

    System.out.println("Please enter the number of eggs per basket");

    eggsPerBasket = keyboard.nextInt();

    totalEggs = numberOfBaskets * eggsPerBasket;

    System.out.println("The number of baskets is: " + numberOfBaskets);
    System.out.println("The number of eggs per basket is: " + eggsPerBasket);
    System.out.println("The total number of eggs is: " + totalEggs);

  }
}

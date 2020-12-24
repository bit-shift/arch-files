import java.util.Scanner;

public class CoffeeBot{
  public static void main(String[] args){

    if(args.length == 0){
      System.out.println("No arguments. System terminating.");
      return;
    }

    if(args.length == 1){
      System.out.println("Not enough arguments. System terminating.");
      return;
    }

    if(args.length > 2){
      System.out.println("Too many arguments. System terminating.");
      return;
    }

    int cupSupply = Integer.parseInt(args[0]);
    int shotSupply = Integer.parseInt(args[1]);

    if(cupSupply < 0 && shotSupply < 0){
      System.out.println("Negative supply chain. System terminating.");
      return;
    }

    if(cupSupply < 0){
      System.out.println("Negative supply of coffee cups. System terminating.");
      return;
    }

    if(shotSupply < 0){
      System.out.println("Negative supply of coffee shots. System terminating.");
      return;
    }

    Scanner keyboard = new Scanner(System.in);

    String name;

    System.out.print("Hello, what's your name? ");

    name = keyboard.next();

    System.out.print("Would you like to order some coffee, "+name+"? (y/n) ");

    String answer;

    answer = keyboard.next();

    // WHILE LOOP NEEDED FOR NON Y OR N RESPONSES

    if(answer == "n"){
      System.out.println("Come back next time, " + name + ".");
      return;
    }

    if(answer == "y"){
      System.out.println("Great! Let's get started.");
    }

    System.out.println();
    System.out.println("Order selection");
    System.out.println("---------------");
    System.out.println();

    System.out.println("There is " + cupSupply + " coffee cup in stock and each costs $2.00.");
    System.out.println("There is " + shotSupply + " coffee shot in stock and each costs $1.00.");
    System.out.println();
    System.out.print("How many cups of coffee would you like? ");

    int cupUser;

    cupUser = keyboard.nextInt();

    if(cupUser == 0){
      System.out.println("No cups. No coffee. Goodbye.");
      return;
    }

    if(cupUser < 0){
      System.out.println("Does not compute. System terminating.");
      return;
    }

    if(cupUser > cupSupply){
      System.out.println("Not enough stock. Come back later.");
      return;
    }



    for(int i=1; i <= cupUser; i++){
      System.out.print("How many coffee shots in cup "+i+"? ");
      int cupiShots = keyboard.nextInt();

      // WHILE LOOP TO TRY AGAIN IF THE INTEGER ENTERED IS ILLEGAL
      // IE THE NUMBER IS EITHER NEGATIVE OR EXCEEDS THE SUPPLY CHAIN
    }

    System.out.println();
    System.out.println("Order summary");
    System.out.println("-------------");
    System.out.println();

    int totalCost = 0;

    for(int i=1; i <= cupUser; i++){
      int costCupi = (cupiShots*2.00+1.00);
      System.out.print("Cup "+ i + " has " +cupiShots+ " shots and will cost $"+costCupi);
      totalCost = totalCost + costCupi;
    }

    System.out.println();
    System.out.println(cupUser+" coffees to purchase.");
    System.out.println("Purchase price is $"+totalCost);
    System.out.print("Proceed to payment? (y/n)");

    String pay;

    pay = keyboard.next();

    if(pay != "y"){
      return;
    }
  }
}

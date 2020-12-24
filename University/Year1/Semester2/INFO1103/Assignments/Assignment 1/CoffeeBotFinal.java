import java.util.Scanner;

public class CoffeeBotFinal{
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

    String orderAnswer;

    orderAnswer = keyboard.next();

    while(!orderAnswer.equals("y") && !orderAnswer.equals("n")){
      System.out.println("Invalid response. Try again.");
      System.out.print("Would you like to order some coffee, "+name+"? (y/n) ");
      orderAnswer = keyboard.next();
    }

    if(orderAnswer.equals("n")){
      System.out.println("Come back next time, "+name+".");
      return;
    }

    if(orderAnswer.equals("y")){
      System.out.println("Great! Let's get started.");
    }

    System.out.println();
    System.out.println("Order selection");
    System.out.println("---------------");
    System.out.println();

    if(cupSupply == 1){
      System.out.println("There is "+cupSupply+" coffee cup in stock and each costs $2.00.");
    }
    else{
      System.out.println("There are "+cupSupply+" coffee cups in stock and each costs $2.00.");
    }

    if(shotSupply == 1){
      System.out.println("There is "+shotSupply+" coffee shot in stock and each costs $1.00.");
    }
    else{
      System.out.println("There are "+shotSupply+" coffee shots in stock and each costs $1.00.");
    }

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

    System.out.println();

    double cupShots = 0;
    double totalShots = 0;
    double[] cupShotsArray = new double[cupUser];

    double totalCost = 0;

    for(int i=0; i < cupUser; i++){

      System.out.print("How many coffee shots in cup "+(i+1)+"? ");
      cupShots = keyboard.nextInt();

      while(cupShots < 0){
        System.out.println("Does not compute. Try again.");
        System.out.print("How many coffee shots in cup "+(i+1)+"? ");
        cupShots = keyboard.nextInt();
      }

      totalShots = totalShots + cupShots;

      while(totalShots > shotSupply){
        totalShots = totalShots - cupShots;

        if(shotSupply - totalShots == 1){
          System.out.printf("There is only %.0f coffee shot left. Try again.\n",(shotSupply - totalShots));
        }
        else{
          System.out.printf("There are only %.0f coffee shots left. Try again.\n",(shotSupply - totalShots));
        }

        System.out.print("How many coffee shots in cup "+(i+1)+"? ");
        cupShots = keyboard.nextInt();
        totalShots = totalShots + cupShots;
      }

      cupShotsArray[i] = cupShots;
      totalCost = totalCost + cupShots + 2;
    }

    System.out.println();
    System.out.println("Order summary");
    System.out.println("-------------");
    System.out.println();

    for(int i=0; i < cupUser; i++){
      if(cupShotsArray[i] == 1){
        System.out.printf("Cup " + (i+1) + " has %.0f shot and will cost $%.2f\n",cupShotsArray[i],cupShotsArray[i]+2);
      }
      else{
        System.out.printf("Cup " + (i+1) + " has %.0f shots and will cost $%.2f\n",cupShotsArray[i],cupShotsArray[i]+2);
      }
    }

    System.out.println();

    if(cupUser == 1){
      System.out.println(cupUser+" coffee to purchase.");
    }
    else{
      System.out.println(cupUser+" coffees to purchase.");
    }

    System.out.printf("Purchase price is $%.2f\n",totalCost);
    System.out.print("Proceed to payment? (y/n) ");

    String payAnswer;

    payAnswer = keyboard.next();

    while(!payAnswer.equals("y") && !payAnswer.equals("n")){
      System.out.println("Invalid response. Try again.");
      System.out.print("Proceed to payment? (y/n) ");
      payAnswer = keyboard.next();
    }

    if(payAnswer.equals("n")){
      System.out.println("Come back next time, "+name+".");
      return;
    }

    System.out.println();
    System.out.println("Order payment");
    System.out.println("-------------");
    System.out.println();

    String payment;
    double paymentD;
    double remainingPayment = totalCost;
    double totalPaid = 0;

    do{

      System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
      payment = keyboard.next();

      while(!payment.equals("$100.00") && !payment.equals("$50.00") && !payment.equals("$20.00") && !payment.equals("$10.00") && !payment.equals("$5.00") && !payment.equals("$2.00") && !payment.equals("$1.00") && !payment.equals("$0.50") && !payment.equals("$0.20") && !payment.equals("$0.10") && !payment.equals("$0.05")){
        System.out.println("Invalid coin or note. Try again.");
        System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
        payment = keyboard.next();
      }

      paymentD = Double.parseDouble(payment.replace("$",""));
      totalPaid = totalPaid + paymentD;

      remainingPayment = remainingPayment - paymentD;
    }while(remainingPayment > 0);

  if(remainingPayment == 0){
      System.out.println();
      System.out.printf("You gave $%.2f\n",totalPaid);
      System.out.println("Perfect! No change given.");
      System.out.println();
      System.out.println("Thank you, "+name+".");
      System.out.println("See you next time.");
      return;
    }

    double change = (-1)*remainingPayment;
    double[] money = {100,50,20,10,5,2,1,0.5,0.2,0.1,0.05};

    System.out.println();
    System.out.printf("You gave $%.2f\n",totalPaid);
    System.out.println("Your change:");

    int count;

    for(int i = 0; i < 11; i++){

      count = 0;

      while((change - money[i]) > -0.001){
        count = count + 1;
        change = change - money[i];
      }

      if(count > 0){
        System.out.printf(count+" x $%.2f\n",money[i]);
      }
    }

    System.out.println();
    System.out.println("Thank you, "+name+".");
    System.out.println("See you next time.");

    keyboard.close();
  }
}

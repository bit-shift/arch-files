import java.util.Scanner;

public class PaymentTest{
  public static void main(String[] args){


    Scanner keyboard = new Scanner(System.in);
    String payment;
    int decimalPlaces;
    double paymentD;
    double remainingPayment = totalCost;

    do{

      System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
      payment = keyboard.next();
      decimalPlaces = payment.length()-(payment.indexOf(".")+1);
      paymentD = Double.parseDouble(payment.replace("$",""));


      while(decimalPlaces != 2 || payment.charAt(0) != '$' || paymentD != 100 && paymentD != 50 && paymentD != 20 && paymentD != 10 && paymentD != 5 && paymentD != 2 && paymentD != 1 && paymentD != 0.5 && paymentD != 0.2 && paymentD != 0.1 && paymentD != 0.05){
        System.out.println("Invalid coin or note. Try again.");
        System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
        payment = keyboard.next();
        decimalPlaces = payment.length()-(payment.indexOf(".")+1);
        paymentD = Double.parseDouble(payment.replace("$",""));
      }

      remainingPayment = remainingPayment - paymentD;
    }while(remainingPayment > 0);
  }
}

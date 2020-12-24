import java.util.ArrayList;
import java.util.Scanner;

public class PrimeFactors{
  public static int[] arrayReturn(int number){
    ArrayList<Integer> primes = new ArrayList<Integer>();
    for(int i = 2; i <= number; i++){
      boolean check = true;
      for(int j = 2; j <= (int)Math.sqrt(i); j++){
        if(i%j == 0){
          check = false;
        }
      }
      if(check){
        primes.add(i);
      }
    }
    int[] returnArray = new int[primes.size()];
    for(int z = 0; z < returnArray.length; z++){
      returnArray[z] = primes.get(z);
    }
    return returnArray;
  }

  public static int[] factorisation(int number){
    ArrayList<Integer> primeFactors = new ArrayList<Integer>();
    int[] primeUpTo = arrayReturn(number);
    for(int i = 0; i < primeUpTo.length; i++){
      while(number%primeUpTo[i]==0){
        number = number/primeUpTo[i];
        primeFactors.add(primeUpTo[i]);
      }
    }
    int[] factorised = new int[primeFactors.size()];
    for(int z = 0; z < factorised.length; z++){
      factorised[z] = primeFactors.get(z);
    }
    return factorised;
  }

  public static void main(String[] args){
    Scanner keyboard = new Scanner(System.in);
    System.out.print("Please enter an integer: ");
    int n1 = keyboard.nextInt();
    if(n1 == 1){
      System.out.println("Prime factors of "+n1+" are: " + 1);
      return;
    }
    if(n1 < 1){
      System.out.println("Invalid entry. Try again later.");
      return;
    }
    int[] finalFactors = factorisation(n1);
    System.out.print("Prime factors of "+n1+" are: ");
    for(int z = 0; z < finalFactors.length; z++){
      if(z != finalFactors.length -1){
        System.out.print(finalFactors[z] + " ");
      }
      else{
        System.out.println(finalFactors[z]);
      }
    }

  }
}

import java.util.Scanner;

public class NumberCrunch{
  public static void main(String[] args){

    int[] array = new int[3];
    Scanner keyboard = new Scanner(System.in);

    System.out.println("Please enter up to three positive numbers:");

    for(int i = 0; i < 3; i++){
      array[i] = keyboard.nextInt();

      if(array[i] < 0){
        array[i] = 0;
        break;
      }
    }

    int count = 0;

    for(int j = 0; j < array.length; j++){
      if(array[j] > 0){
        count = count + 1;
      }
    }

    while(count == 0){
      System.out.println("You have not entered any positive number. Please enter at least one positive.");

      for(int i = 0; i < 3; i++){
        array[i] = keyboard.nextInt();

        if(array[i] < 0){
          array[i] = 0;
          break;
        }
      }

      count = 0;

      for(int j = 0; j < array.length; j++){
        if(array[j] > 0){
          count = count + 1;
        }
      }
    }
    int[] factors = new int[array[0]];

    if(count == 1){
      System.out.println("You have entered 1 positive number.");

      for(int w = 1; w <= array[0]; w++){
        if(array[0]%w == 0){
          factors[w-1] = w;
        }
      }

      System.out.print("The factors of " + array[0] + " are: ");
      for(int w = 0; w < factors.length; w++){
        if(factors[w] != 0){
          System.out.print(factors[w]+", ");
        }
      }

      System.out.println();
      return;
    }

    if(count == 2){
      System.out.println("You have entered 2 positive numbers.");
      System.out.print("Their product is "+ array[0]*array[1]+",");

      if(array[0]-array[1] < 0){
        System.out.println(" and "+array[0] + " is less than "+array[1]+".");
      }
      else if(array[0] - array[1] > 0){
        System.out.println(" and "+array[0] + " is greater than "+array[1]+".");
      }
      else{
        System.out.println(" and they are equal.");
      }
      return;
    }

    if(count == 3){
      System.out.println("You have entered 3 positive numbers.");

      int max = array[0];

      for(int j = 0; j < array.length; j++){
        if(array[j] > max){
          max = array[j];
        }
      }

      System.out.println("The largest is "+max);
      return;
    }

  }
}

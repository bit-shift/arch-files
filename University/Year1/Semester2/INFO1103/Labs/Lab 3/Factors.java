public class Factors{
  public static void main(String[] args){

    int[] factors = new int[args[0]];

    if(count == 1){
      System.out.println("You have entered 1 positive number.");

      for(int w = 1; w <= args[0]; w++){
        if(args[0]%w == 0){
          factors[w-1] = w;
        }
      }

      System.out.print("The factors of " + args[0] + " are: ");
      for(int w = 0; w < factors.length; w++){
        if(factors[w] != 0){
          System.out.print(factors[w]+", ");
        }
      }
    }
  }
}

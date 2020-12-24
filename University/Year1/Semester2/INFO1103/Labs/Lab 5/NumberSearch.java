import java.util.Scanner;
public class NumberSearch{
  public static void main(String[] args){
    int[] integers = new int[args.length];
    for(int i=0; i<args.length;i++){
      integers[i] = Integer.parseInt(args[i]);
    }
    Scanner keyboard = new Scanner(System.in);
    System.out.println("Enter a number: ");
    String s = "";
    int n1,count;
    while(!s.equals("exit")){
      s = keyboard.next();
      try{
        n1 = Integer.parseInt(s);
      }
      catch(NumberFormatException e){
        if(!s.equals("exit")){
          System.out.println("Try again.");
        }
        continue;
      }
      count = 0;
      for(int j=0; j<args.length;j++){
        if(n1==integers[j]){
          count = count + 1;
        }
      }
      if(count>0){
        System.out.println("That number is in the array.");
      }
      else{
        System.out.println("That number is not in the array.");
      }
    }
    System.out.println("Exiting the program.");
  }
}

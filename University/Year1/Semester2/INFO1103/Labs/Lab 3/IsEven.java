import java.util.Scanner;

public class IsEven{
  public static void main(String[] args){

  int n1;
  Scanner keyboard = new Scanner(System.in);
  System.out.print("Please enter a number: ");
  n1 = keyboard.nextInt();

  if(n1 < 0){
    n1 = -1*n1;
  }

  int remain = n1;

  while(remain > 0){
    remain = remain - 2;
  }

  if(remain == 0){
    System.out.println("The number "+n1+" is even.");
  }
  else{
    System.out.println("The number "+n1+" is odd.");
  }
  }
}

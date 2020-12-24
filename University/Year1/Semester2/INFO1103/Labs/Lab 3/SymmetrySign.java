import java.util.Scanner;

public class SymmetrySign{
  public static void main(String[] args){

    Scanner keyboard = new Scanner(System.in);

    int n1;

    System.out.print("Please enter an integer: ");
    n1 = keyboard.nextInt();

    if(n1 >= 20 && n1 <= 200 && n1%2 == 0){
      System.out.println("PASS");
    }
    else if(n1 < 0 && n1%2 != 0){
      System.out.println("PASS");
    }
    else{
      System.out.println("FAIL");
    }
  }
}

import java.util.Scanner;

public class Palindrome{
  public static void main(String[] args){
    Scanner keyboard = new Scanner(System.in);
    System.out.print("Please enter a word: ");
    String input = keyboard.next();
    int half = input.length()/2;
    boolean check = true;
    for(int i = 0; i < half; i++){
      if(input.charAt(i) != input.charAt(input.length()-1-i)){
        check = false;
        break;
      }
    }
    if(check){
      System.out.println(input + " is a palindrome.");
    }
    else {
      System.out.println(input + " is not a palindrome.");
    }
  }
}

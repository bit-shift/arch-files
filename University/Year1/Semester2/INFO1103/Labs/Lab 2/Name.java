import java.util.Scanner;

public class Name{
  public static void main(String[] args){
    Scanner scan = new Scanner(System.in);
    System.out.println("Please enter your first name:");
    String firstName = scan.next();
    System.out.println("Please enter your last name:");
    String lastName = scan.next();

    System.out.println("Your full name is:");
    System.out.println(firstName + " " + lastName);

    int indexHalfFirst = (int) firstName.length()/2;
    String firstNickname = "";
    for(int i = 0; i < indexHalfFirst; i++){
      firstNickname = firstNickname + firstName.charAt(i);
    }

    int indexHalfLast = (int) lastName.length()/2;
    String lastNickname = "";
    for(int i = indexHalfLast; i < lastName.length(); i++){
      lastNickname = lastNickname + lastName.charAt(i);
    }

    System.out.println(firstNickname + lastNickname);

  }
}

import java.util.Scanner;

  public class Birthday {

    public static void main(String[] args) {

      System.out.println("Hello");
      System.out.println("I will determine how old you are");
      System.out.println("Please enter the year that you were born");

      int birthYear, currentYear, age;

      currentYear = 2017;

      Scanner keyboard = new Scanner(System.in);

      birthYear = keyboard.nextInt();

      age = currentYear - birthYear;

      System.out.println("Your current age is:");
      System.out.println(age);

    }

}

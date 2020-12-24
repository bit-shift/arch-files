import java.util.Scanner;

public class SaveHandler{
  public static void main(String[] args){
    Scanner keyboard = new Scanner(System.in);
    String input = keyboard.nextLine();
    String[] inputParts = input.split(" ");
    String row;
    String[] check;

    if(inputParts.length == 2 && inputParts[0].equals("save")){
      System.out.println("yaya");
      row = inputParts[1];
      check = row.split("\\.");
      if(check.length == 2 && check[1].equals("txt")){
        System.out.println("yaya");
      }
    }
    else{
      System.out.println("no");
    }



    /*String[] fileValid = (inputParts[1]).split(".");
    for(int i = 0; i < inputParts.length; i++){
      System.out.println(inputParts[i]);
    }

    if(fileValid.length == 2 && fileValid[1].equals("txt")){
      System.out.println("yaya");
    }
    else{
      System.out.println("no");
    }
    */



    /*if(inputParts.length > 1){
      fileValid = (inputParts[1]).split(".");
    }
    else{
      System.out.println("no");
      return;
    }

    if(fileValid.length != 2){
      System.out.println("no");
      return;
    }
    else if(fileValid[1].equals("txt")){
      System.out.println("yaya");
    }
    */


  }
}

import java.util.Scanner;

public class PetTester{
  public static void main(String[] args){
    String name = "Hobbes";
    String[] nicknames = {"Hops", "Hobbes"};
    int age = 4;
    String species = "Tiger";
    boolean trained = true;



    Pet teddyBear = new Pet(name,nicknames,age,species,trained);
    System.out.println(teddyBear.hasNickname("Hobbes"));


  }
}

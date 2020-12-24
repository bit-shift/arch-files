public class OldestPet{
  public static void main(String[] args){
    String name1 = "Spot";
    String[] nicknames1 = {"Purple"};
    int age1 = 4;
    String species1 = "Bear";
    boolean trained1 = true;

    Pet teddy1 = new Pet(name1,nicknames1,age1,species1,trained1);

    String name2 = "Freddy";
    String[] nicknames2 = {"Chicken"};
    int age2 = 10;
    String species2 = "Chicken";
    boolean trained2 = true;

    Pet teddy2 = new Pet(name2,nicknames2,age2,species2,trained2);

    String name3 = "Yoshi";
    String[] nicknames3 = {};
    int age3 = 1;
    String species3 = "Dinosaur";
    boolean trained3 = false;

    Pet teddy3 = new Pet(name3,nicknames3,age3,species3,trained3);


  }
}

public class Pokemon {
  static int currentSize = 4;
  static String[] currentBox = {"Charmander", "Bulbasaur", "Pikachu", "Squirtle" };
  public static void main(String[] args){
    release("Bulbasaur");
    for(int i = 0; i < currentSize; i++){
        System.out.println(currentBox[i]);
    }
  }

  public static void release(String name){
    currentSize = currentSize - 1;
    for(int i = 0; i < currentBox.length; i++){
      if(name.equals(currentBox[i])){
        currentBox[i] = "remove";
      }
    }
    int count = 0;
    String[] newBox = new String[currentSize];
    for(int i = 0; i < currentBox.length; i++){
      if(!(currentBox[i].equals("remove"))){
        newBox[count] = currentBox[i];
        count++;
      }
    }
    currentBox = newBox;
  }
}

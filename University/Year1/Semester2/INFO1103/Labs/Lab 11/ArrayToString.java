public class ArrayToString{
  public static void main(String[] args){
    int[] values = {1,2,3,4};
    String readable = arrayToString(values);
    System.out.println(readable);
  }

  public static String arrayToString(int[] integers){
    String aString = "";
    for(int i = 0; i < integers.length; i++){
      if(i < integers.length - 1){
        aString = aString + integers[i] + ", ";
      }
      else{
        aString = aString + integers[i];
      }
    }
    return aString;
  }
}

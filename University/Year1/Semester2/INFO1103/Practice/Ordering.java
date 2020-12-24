public class Ordering{
  public static void main(String[] args){
    int[] arr = {1,5,3,4,5,6,6,7};
    System.out.println(inOrder(arr));
  }

  public static boolean inOrder(int[] array){
    boolean check = true;
    for(int i = 0; i < array.length - 1; i++){
      if(array[i+1] < array[i]){
        check = false;
        return check;
      }
    }
    return check;
  }
}

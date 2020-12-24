public class ArraySort{
  public static int marker;
  public static int[] array = {0,1,3,4,5,1,9,6,3};

  public static void main(String[] args){
    marker = 0;
    int min = array[0];
    for(int i = 0; i < array.length; i++){
      if(array[i] < min){
        min = array[i];
      }
    }
    marker = min - 1;
    int[] sortedArray = new int[array.length];
    for(int i = 0; i < array.length; i++){
      sortedArray[i] = getMin();
    }

    for(int i = 0; i < array.length; i++){
      System.out.print(sortedArray[i]+ " ");
    }
  }

  public static int getMin(){
    int minm = 0, index = 0;
    for(int i = 0; i < array.length; i++){
      if(array[i] != marker){
        minm = array[i];
        index = i;
        break;
      }
    }
    for(int i = 0; i < array.length; i++){
      if(array[i] != marker && array[i] < minm){
        minm = array[i];
        index = i;
      }
    }
    array[index] = marker;
    return minm;
  }
}

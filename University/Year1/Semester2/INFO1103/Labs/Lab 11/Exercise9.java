public class Exercise9{
  public static void main(String[] args){
    int[] values = {1,2,3,4,5,5,6,6,7,7,8,6,4,64,6,6,6,6,646,65743,737458,9436534,3546,4,6,78,89};
    halfEvens(values);
  }

  public static void halfEvens(int[] values){
    for(int i = 0; i < values.length; i++){
      if(values[i] % 2 == 0){
        values[i] = values[i]/2;
      }
    }
  }
}

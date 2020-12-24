import java.util.ArrayList;

public class Exercises{
  public static void main(String[] args){
    double[] values = {1.3,2.4,3,4,5.9,5,6,6.7,7,7,8,6,4,64.4,6.2,6};
    System.out.println(largestDouble(values));
    int[] valuesT = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int x = 7;
    int[] multiples = findMultiplesOf(x, valuesT);
    for(int i = 0; i < multiples.length; i++){
      System.out.println(multiples[i]);
    }
  }

  public static void halfEvens(int[] values){
    for(int i = 0; i < values.length; i++){
      if(values[i] % 2 == 0){
        values[i] = values[i]/2;
      }
    }
  }

  public static double largestDouble(double[] values){
    double max = values[0];
    for(int i = 0; i < values.length; i++){
      if(values[i] > max){
        max = values[i];
      }
    }
    return max;
  }

  public static int[] findMultiplesOf(int x, int[] values){
    ArrayList<Integer> multiplesList = new ArrayList<Integer>();
    for(int i = 0; i < values.length; i++){
      if(values[i] % x == 0){
        multiplesList.add(values[i]);
      }
    }
    int[] multiplesArray = new int[multiplesList.size()];
    int j = 0;
    for(int number : multiplesList){
      multiplesArray[j] = number;
      j++;
    }
    return multiplesArray;
  }
}

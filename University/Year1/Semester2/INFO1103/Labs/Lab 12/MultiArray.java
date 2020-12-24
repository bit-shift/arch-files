import java.util.Random;

public class MultiArray{
  public static void main(String[] args){
    Random r = new Random();
    int[][] array = new int[4][3];
    for(int s = 0; s < 4; s++){
      for(int c = 0; c < 3; c++){
        array[s][c] = r.nextInt(100);
      }
    }

    for(int w = 0; w < 4; w++){
      for(int l = 0; l < 3; l++){
        System.out.print(array[w][l] + " ");
      }
      System.out.println();
    }

    System.out.println(sumOfRow(0,array));
    System.out.println(sumOfColumn(0,array));
    System.out.println(sumOfRows(array));
    System.out.println(maxValue(array));
  }

  public static int sumOfRow(int row, int[][] array){
    int sum = 0;
    for(int c = 0; c < array[row].length; c++){
      sum = sum + array[row][c];
    }
    return sum;
  }

  public static int sumOfColumn(int column, int[][] array){
    int sum = 0;
    for(int r = 0; r < array.length; r++){
      sum = sum + array[r][column];
    }
    return sum;
  }

  public static int sumOfRows(int[][] array){
    int total = 0;
    for(int j = 0; j < array.length; j++){
      total = total + sumOfRow(j,array);
    }
    return total;
  }

  public static int maxValue(int[][] array){
    int max = array[0][0];
    for(int r = 0; r < 4; r++){
      for(int c = 0; c < 3; c++){
        if(array[r][c] > max){
          max = array[r][c];
        }
      }
    }
    return max;
  }
}

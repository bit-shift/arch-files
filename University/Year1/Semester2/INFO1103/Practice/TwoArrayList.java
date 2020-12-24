import java.util.ArrayList;
import java.util.Scanner;

public class TwoArrayList{
  public static void main(String[] args){
    ArrayList<Integer> arrList = new ArrayList<Integer>();
    Scanner scan = new Scanner(System.in);
    while(scan.hasNextInt()){
      arrList.add(scan.nextInt());
    }
    ArrayList<Integer> arrListOdd = new ArrayList<Integer>();
    for(int x : arrList){
      if(x % 2 == 1){
        arrListOdd.add(scan.nextInt());
      }
    }
    for(int x : arrListOdd){
      if(x % 2 == 1){
        System.out.print(x + " ");
      }
    }
  }
}

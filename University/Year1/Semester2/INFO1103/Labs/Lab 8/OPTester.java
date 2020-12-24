import java.util.Scanner;

public class OPTester{
  public static void main(String[] args){
    OrderedPair pair = new OrderedPair(4,5);
    pair.setOrderedPair(72,56);
    OrderedPair pair2 = new OrderedPair(56,72);
    System.out.println(pair.equals(pair2));
  }
}

import java.util.Arrays;
public class SortArray{
  public static void main(String[] args){
    int[] integers = new int[args.length];
    for(int i=0; i<args.length;i++){
      integers[i] = Integer.parseInt(args[i]);
    }
    Arrays.sort(integers);

    System.out.println(Arrays.toString(integers));
  }
}

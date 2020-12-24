public class IntegerArray{
  public static void main(String[] args){
    int[] integers = new int[args.length];
    System.out.print("My values:");
    for(int i=0; i<args.length;i++){
      integers[i] = Integer.parseInt(args[i]);
      System.out.print(" "+integers[i]);
    }
    System.out.println();
  }
}

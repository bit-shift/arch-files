public class BinomialCoefficient{
  public static void main(String[] args){
    System.out.println(choose(Integer.parseInt(args[0]),Integer.parseInt(args[1])));
  }

  public static int choose(int n, int k){
    if(k == 0 || k == n){
      return 1;
    }
    else{
      return choose(n-1,k) + choose(n-1,k-1);
    }
  }
}

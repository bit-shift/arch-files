public class Factorial{
  public static void main(String[] args){
    System.out.println(fac(Integer.parseInt(args[0])));
  }

  public static int fac(int n){
    if(n == 0){
      return 1;
    }
    else{
      return n*fac(n-1);
    }
  }
}

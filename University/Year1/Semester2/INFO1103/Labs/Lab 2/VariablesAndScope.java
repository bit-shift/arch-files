public class VariablesAndScope{
  public static void main(String[] args){
    int x = 7;
    float y = x;
    int m;
    x = x + 3;
    System.out.println(y);
    System.out.println(x);
    {
      x = 17;
      m = 0;
      m = x + (int) y;
      x = x + 4;
    }
    System.out.println(m);
    System.out.println(x);
  }
}

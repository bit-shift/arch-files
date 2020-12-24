public class Handshake{
  public static void main(String[] args){
    int i = 156;
    System.out.println("With " + i + " people, there are " + computeHandshakes(i) + " handshakes in the room.");
  }

  public static int computeHandshakes(int n){
    if(n == 1){
      return 0;
    }
    else {
      return n-1 + computeHandshakes(n-1);
    }
  }
}

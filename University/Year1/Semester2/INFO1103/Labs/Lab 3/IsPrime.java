public class IsPrime{
  public static void main(String[] args){

    int count = 0;
    for(int j = 10000; j < 11000; j++){
      count = 0;
      for(int i = 2; i <= Math.sqrt(j); i++){
        if(j%i == 0){
          count = count + 1;
        }
      }
      if(count == 0){
        System.out.println(j);
      }
    }

  }
}

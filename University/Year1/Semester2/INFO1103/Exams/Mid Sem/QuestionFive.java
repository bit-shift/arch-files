public class QuestionFive{

  public static int searchFor7(int[] array){
    for(int i = 0; i < array.length; i++){
      if(array[i]==7){
        return i;
      }
    }
    return -1;
  }

  public static void main(String[] args){
    int[] array = {2,4,5,6,3,78,79,1,2,3};
    System.out.println(searchFor7(array));
  }
}

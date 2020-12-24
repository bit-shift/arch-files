import java.util.Scanner;
import java.util.Arrays;

public class Vowels{
  public static void main(String[] args){
    Scanner scan = new Scanner(System.in);
    System.out.print("Enter a word with no spaces: ");
    String word = scan.next();
    char[] wordArray = word.toCharArray();
    for(int i = 0; i < wordArray.length; i++){
      if(wordArray[i] == 'a'){
        wordArray[i] = '_';
      }
      else if(wordArray[i] == 'e'){
        wordArray[i] = '_';
      }
      else if(wordArray[i] == 'i'){
        wordArray[i] = '_';
      }
      else if(wordArray[i] == 'o'){
        wordArray[i] = '_';
      }
      else if(wordArray[i] == 'u'){
        wordArray[i] = '_';
      }
    }
    String wordFinal = new String(wordArray);
    System.out.println(wordFinal);
  }
}

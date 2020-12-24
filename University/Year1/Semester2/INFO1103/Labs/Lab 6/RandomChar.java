import java.util.Random;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class RandomChar{
  public static void main(String[] args){
    File output = new File("randomChars.txt");
    PrintWriter outStream = null;

    try{
      outStream = new PrintWriter(output);
    }
    catch(FileNotFoundException fnfe){
      System.err.println("Cannot write to " + output);
    }

    for(int i = 0; i < 15; i++){
      outStream.println(randomChar());
    }
    outStream.close();
  }

  public static char randomChar(){
    Random r = new Random();
    char c = (char) (r.nextInt(26) + 'a');
    return c;
  }
}

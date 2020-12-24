import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Arrays;

public class SortFile{
  public static void main(String[] args){
    File inputName = new File(args[0]+".txt");
    File outputName = new File(args[0]+"-sorted.txt");
    Scanner inputStream = null;
    PrintWriter outputStream = null;
    try{
      inputStream = new Scanner(inputName);
    }
    catch(FileNotFoundException fnfe){
      System.err.println("Cannot find "+ args[0]+".txt");
      System.exit(1);
    }
    try{
      outputStream = new PrintWriter(outputName);
    }
    catch(FileNotFoundException fnfe){
      System.err.println("Cannot find "+ args[0]+"-sorted.txt");
      System.exit(1);
    }

    ArrayList<String> inputs = new ArrayList<String>();

    while(inputStream.hasNextLine()){
      inputs.add(inputStream.nextLine());
    }

    String[] inputsArrayNew = convertListToString(inputs);
    Arrays.sort(inputsArrayNew);

    for(int i = 0; i < inputsArrayNew.length; i++){
      outputStream.println(inputsArrayNew[i]);
    }
    outputStream.close();
    inputStream.close();
  }

  public static String[] convertListToString(ArrayList<String> list){
    String[] inputsArray = new String[list.size()];
    int i = 0;
    for(String element : list){
      inputsArray[i] = element;
      i++;
    }
    return inputsArray;
  }
}

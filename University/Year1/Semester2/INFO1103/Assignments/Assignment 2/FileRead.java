import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;

public class FileRead{
  static ArrayList<String> boardList = new ArrayList<String>();
  static String[] boardString = new String[boardList.size()];
  static int strLength = boardString.length;
  static char[][] boardArray;


  public static void main(String[] args){
    String fileName = "easy_board.txt";
    Scanner inputStream = null;
    try{
        inputStream = new Scanner(new File(fileName));
    }
    catch(FileNotFoundException e){
        System.out.println("Error opening the file " + fileName);
        System.exit(0);
    }

    int[] fileParameters = new int[4];
    int i = 0;
    while(inputStream.hasNextInt()){
        fileParameters[i] = inputStream.nextInt();
      i = i + 1;
    }
    while(inputStream.hasNextLine()){
        boardList.add(inputStream.nextLine());
    }
    boardList.remove(0);
    boardString = boardList.toArray(boardString);
    /*for(int j = 0; j < boardString.length; j++){
      boardString[i] = boardString[i].toCharArray();
    }*/

    /*for (int j = 0; j < boardString.length; j++) // What is `array`?
    {
        boardArray[j] = boardString[j].toCharArray();
    }

    for (int row = 0; row < boardArray.length; row++) // Use actual size of 2darray row
    {
        for (int col = 0; col < boardArray[0].length; col++) // use actual size of 2darray column
        {
             System.out.print(boardArray[row][col]);
        }
        System.out.println();
    }*/

    // THIS WORKS EXCEPT FOR THE INITIALISATION
    String row = boardString[0];
    boardArray = new char[boardString.length][row.length()];

    for(int r = 0; r < boardString.length; r++) {
        row = boardString[r];
        for(int c = 0; c < row.length(); c++){
              boardArray[r][c] = row.charAt(c);
              System.out.print(boardArray[r][c]);
        }
        System.out.println();
    }

    /*for(int r = 0; r < boardString.length; r++){
      for(int c = 0; c < (boardString[0]).length(); c++){
            boardArray[r][c] = (boardString[r])[c];
      }
    }*/
  }

}

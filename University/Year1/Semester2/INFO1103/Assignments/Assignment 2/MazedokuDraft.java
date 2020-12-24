import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;


/**
 * Maze Game
 *
 * INFO1103 Assignment 2
 * 2017 Semester 1
 *
 * The Maze Game.
 * In this assignment you will be designing a maze game.
 * You will have a maze board and a player moving around the board.
 * The player can step left, right, up or down.
 * However, you need to complete the maze within a given number of steps.
 *
 * As in any maze, there are walls that you cannot move through. If you try to
 * move through a wall, you lose a life. You have a limited number of lives.
 * There is also gold on the board that you can collect if you move ontop of it.
 *
 * Please implement the methods provided, as some of the marks are allocated to
 * testing these methods directly.
 *
 * Keegan Gyoery
 * SID 470413467
 * 15 September 2017
 *
 */
public class MazedokuDraft {
    /* You can put variables that you need throughout the class up here.
     * You MUST INITIALISE ALL of these class variables in your initialiseGame
     * method.
     */

    // A sample variable to show you can put variables here.
    // You would initialise it in initialiseGame method.
  	static int LIVES_REMAINING = 0;
    static int STEPS_REMAINING = 0;
  	static int GOLD_PERSON = 0;
  	static int R = 0;
  	static char WALL = '#';
  	static char BEEN = '.';
  	static char GOAL = '@';
  	static char PERSON = '&';
    static int destinationX = 0;
    static int destinationY = 0;
    static int[] fileParameters;
  	static ArrayList<String> boardList = new ArrayList<String>();
    static String[] boardString;
    static char[][] boardArray;
    /**
     * Initialises the game from the given configuration file.
     * This includes the number of lives, the number of steps, the starting gold
     * and the board.
     *
     * If the configuration file name is "DEFAULT", load the default
     * game configuration.
     *
     * Please also initialise all of your class variables.
     *
     * @args configFileName The name of the game configuration file to read from.
     * If there was an error reading in the game.
     *         For example, if the input file could not be found.
     */
    public static void initialiseGame(String configFileName) throws IOException {

        // Initialises the Scanner object inputStream through which text file is read
    		Scanner inputStream = null;

        // Tries to read the file with the given name and will throw an error
        inputStream = new Scanner(new File(configFileName));

        // Reads the inputs from file and stores them in the array file parameters
        // Contains the parameters that define the game
        fileParameters = new int[4];
    		int i = 0;
    		while(inputStream.hasNextInt()){
            fileParameters[i] = inputStream.nextInt();
    			  i = i + 1;
        }

        LIVES_REMAINING = fileParameters[0];
        STEPS_REMAINING = fileParameters[1];
        R = fileParameters[3];


        // Reads the next lines from the file and stores them in the List
        // for the configuration of the board
    		while(inputStream.hasNextLine()){
            boardList.add(inputStream.nextLine());
        }

        // Removes the first element of the board config list as it is empty
        // due to the parameters being already read into their own separate array
        boardList.remove(0);

        boardString = new String[boardList.size()];

        // Converts the board configuration list into a string array
        boardString = boardList.toArray(boardString);

        // Sets the first row of the board config string array to a variable for
        // the ease of getting the length of the string elements of the array
        String row = boardString[0];

        // Determine the size of the 2d character array in which the board config
        // will be stored
        boardArray = new char[boardString.length][row.length()];

        // Loops through the board string array and places each element at the
        // correct position in the character array, and prints them to the screen.
        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){
                  boardArray[r][c] = row.charAt(c);
            }
        }

        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){
                  if(boardArray[r][c] == '@'){
                      destinationY = r;
                      destinationX = c;
                  }
            }
        }
    }

    /**
     * Save the current board to the given file name.
     * Note: save it in the same format as you read it in.
     * That is:
     *
     * <number of lives> <number of steps> <amount of gold> <number of rows on the board>
     * <BOARD>
     *
     * @args toFileName The name of the file to save the game configuration to.
     * If there was an error writing the game to the file.
     */
    public static void saveGame(String toFileName) throws IOException {
        PrintWriter p = new PrintWriter(toFileName);
        for(int j = 0; j < 4; j++){
          p.print(fileParameters[j]+ " ");
        }
        p.println();

        String row = boardString[0];

        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){

                      p.print(boardArray[r][c]);
                  }
            p.println();
        }
        p.close();
    }

    /**
     * Gets the current x position of the player.
     *
     * The players current x position.
     */
    public static int getCurrentXPosition() {
        int currentX = 0;
        String row = boardString[0];

        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){
                  if(boardArray[r][c] == '&'){
                      currentX = c;
                  }
            }
        }
        return currentX;
    }

    /**
     * Gets the current y position of the player.
     *
     * The players current y position.
     */
    public static int getCurrentYPosition() {
        int currentY = 0;
        String row = boardString[0];

        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){
                  if(boardArray[r][c] == '&'){
                      currentY = r;
                  }
            }
        }
        return currentY;
    }

    /**
     * Gets the number of lives the player currently has.
     *
     * The number of lives the player currently has.
     */
    public static int numberOfLives() {

        return LIVES_REMAINING;
    }

    /**
     * Gets the number of remaining steps that the player can use.
     *
     * The number of steps remaining in the game.
     */
    public static int numberOfStepsRemaining() {
        //Implement this method.
        return STEPS_REMAINING;
    }

    /**
     * Gets the amount of gold that the player has collected so far.
     *
     * The amount of gold the player has collected so far.
     */
    public static int amountOfGold() {
        //Implement this method.
        return GOLD_PERSON;
    }


    /**
     * Checks to see if the player has completed the maze.
     * The player has completed the maze if they have reached the destination.
     *
     * True if the player has completed the maze.
     */
    public static boolean isMazeCompleted() {
        if(getCurrentYPosition() == destinationY && getCurrentXPosition() == destinationX){
            return true;
        }

        return false;
    }

    /**
     * Checks to see if it is the end of the game.
     * It is the end of the game if one of the following conditions is true:
     *  - There are no remaining steps.
     *  - The player has no lives.
     *  - The player has completed the maze.
     *
     * True if any one of the conditions that end the game is true.
     */
    public static boolean isGameEnd() {
        if (numberOfLives() == 0 && numberOfStepsRemaining() == 0){
          System.out.println("Oh no! You have no lives and no steps left.");
          System.out.println("Better luck next time!");
          return true;
        }
        else if(isMazeCompleted()){
          System.out.println("Congratulations! You completed the maze!");
          System.out.println("Your final status is:");
          printStatus();
          return true;
        }
        else if(numberOfLives() == 0){
          System.out.println("Oh no! You have no lives left.");
          System.out.println("Better luck next time!");
          return true;
        }
        else if(numberOfStepsRemaining() == 0){
          System.out.println("Oh no! You have no steps left.");
          System.out.println("Better luck next time!");
          return true;
        }

        return false;
    }

    /**
     * Checks if the coordinates (x, y) are valid.
     * That is, if they are on the board.
     *
     * @args x The x coordinate.
     * @args y The y coordinate.
     * True if the given coordinates are valid (on the board),
     *         otherwise, false (the coordinates are out or range).
     */
    public static boolean isValidCoordinates(int x, int y) {
        if((x >= 0 && x < (boardString[0]).length())&&(y >= 0 && y < boardString.length)){
          return true;
        }
        else{
          return false;
        }
    }

    /**
     * Checks if a move to the given coordinates is valid.
     * A move is invalid if:
     *  - It is move to a coordinate off the board.
     *  - There is a wall at that coordinate.
     *  - The game is ended.
     *
     * @args x The x coordinate to move to.
     * @args y The y coordinate to move to.
     * True if the move is valid, otherwise false.
     */
    public static boolean canMoveTo(int x, int y) {
        if(isValidCoordinates(x,y) && boardArray[y][x] != '#' && !isGameEnd()){
          return true;
        }
        return false;
    }

    /**
     * Move the player to the given coordinates on the board.
     * After a successful move, it prints "Moved to (x, y)."
     * where (x, y) were the coordinates given.
     *
     * If there was gold at the position the player moved to,
     * the gold should be collected and the message "Plus n gold."
     * should also be printed, where n is the amount of gold collected.
     *
     * If it is an invalid move, a life is lost.
     * The method prints: "Invalid move. One life lost."
     *
     * @args x The x coordinate to move to.
     * @args y The y coordinate to move to.
     */
    public static void moveTo(int x, int y) {
        if(!canMoveTo(x,y)){
            System.out.println("Invalid move. One life lost.");
            LIVES_REMAINING = LIVES_REMAINING - 1;
            STEPS_REMAINING = STEPS_REMAINING - 1;
            return;
        }

        String goldChar = "" + boardArray[y][x];

        if(goldChar.matches("[0-9]+")){
            int goldAtLocation = Integer.parseInt(goldChar);
            GOLD_PERSON = GOLD_PERSON + goldAtLocation;
            boardArray[getCurrentYPosition()][getCurrentXPosition()] = '.';
            boardArray[y][x] = '&';
            System.out.println("Moved to (" + x +", "+ y +").");
            System.out.println("Plus " + goldAtLocation + " gold.");
            STEPS_REMAINING = STEPS_REMAINING - 1;
            return;
        }


        if(canMoveTo(x,y)){
            boardArray[getCurrentYPosition()][getCurrentXPosition()] = '.';
            boardArray[y][x] = '&';
            System.out.println("Moved to (" + x +", "+ y +").");
            STEPS_REMAINING = STEPS_REMAINING - 1;
            return;
        }
    }

    /**
     * Prints out the help message.
     */
    public static void printHelp() {
        System.out.println("Usage: You can type one of the following commands.");
        System.out.printf("%-12s %s\n","help","Print this help message.");
        System.out.printf("%-12s %s\n","board","Print the current board.");
        System.out.printf("%-12s %s\n","status","Print the current status.");
        System.out.printf("%-12s %s\n","left","Move the player 1 square to the left.");
        System.out.printf("%-12s %s\n","right","Move the player 1 square to the right.");
        System.out.printf("%-12s %s\n","up","Move the player 1 square up.");
        System.out.printf("%-12s %s\n","down","Move the player 1 square down.");
        System.out.printf("%-12s %s\n","save <file>","Save the current game configuration to the given file.");
    }

    /**
     * Prints out the status message.
     */
    public static void printStatus() {
        System.out.println("Number of live(s): " + numberOfLives());
        System.out.println("Number of step(s) remaining: " + numberOfStepsRemaining());
        System.out.println("Amount of gold: " + amountOfGold());
    }

    /**
     * Prints out the board.
     */
    public static void printBoard() {

        // Creates a variable to take the position of the length of the first row in
        // the string array that contains the board configuration
        String row = boardString[0];

        // Nested for loop to loop through every element in the 2D character array that
        // stores the current board configuration
        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){

                      // Prints the current element to the screen
                      System.out.print(boardArray[r][c]);
                  }

            // Prints a new line in the putput of the board
            System.out.println();
        }
    }

    /**
     * Performs the given action by calling the appropriate helper methods.
     * [For example, calling the printHelp() method if the action is "help".]
     *
     * The valid actions are "help", "board", "status", "left", "right",
     * "up", "down", and "save".
     * [Note: The actions are case insensitive.]
     * If it is not a valid action, an IllegalArgumentException should be thrown.
     *
     * @args action The action we are performing.
     * If the action given isn't one of the
     *         allowed actions.
     */
    public static void performAction(String input) throws IllegalArgumentException {
        // Need to do some stuff with the splitting and consider the save file case
        //toLower(input);
        input = input.toLowerCase();
        Scanner keyboardAction = new Scanner(System.in);

        while(!input.equals("help") && !input.equals("board") && !input.equals("status") && !input.equals("left") && !input.equals("right") && !input.equals("up") && !input.equals("down")){
            // ASK THE USER TO RE ENTER AND SAY THAT IT IS NOT A VALID COMMAND
            String[] inputParts = input.split(" ");
            String row;
            String[] check;

            if(inputParts.length == 2 && inputParts[0].equals("save")){
                row = inputParts[1];
                check = row.split("\\.");
                if(check.length == 2 && check[1].equals("txt")){
                  try{
                      saveGame(row);
                  }
                  catch(IOException e){
                    System.out.println("Error: Could not find command '" + input + "'.");
                    System.out.println("To find the list of valid commands, please type 'help'.");
                  }
                  finally{
                  return;
                  }
                }
                else{
                System.out.println("Error: Could not find command '" + input + "'.");
                System.out.println("To find the list of valid commands, please type 'help'.");
                }
            }
            else{
                System.out.println("Error: Could not find command '" + input + "'.");
                System.out.println("To find the list of valid commands, please type 'help'.");
            }
            input = keyboardAction.nextLine();
            input = input.toLowerCase();

        }

        if(input.equals("right")){
            moveTo(getCurrentXPosition() + 1,getCurrentYPosition());
            return;
        }
        if(input.equals("left")){
            moveTo(getCurrentXPosition() - 1,getCurrentYPosition());
            return;
        }
        if(input.equals("up")){
            moveTo(getCurrentXPosition(),getCurrentYPosition()-1);
            return;
        }
        if(input.equals("down")){
            moveTo(getCurrentXPosition(),getCurrentYPosition()+1);
            return;
        }
        if(input.equals("help")){
            printHelp();
            return;
        }
        if(input.equals("status")){
            printStatus();
            return;
        }
        if(input.equals("board")){
            printBoard();
            return;
        }

    }

    /**
     * The main method of your program.
     *
     * @args args[0] The game configuration file from which to initialise the
     *       maze game. If it is DEFAULT, load the default configuration.
     */
    public static void main(String[] args) {

        if(args.length < 1){
            System.out.println("Error: Too few arguments given. Expected 1 argument, found " + args.length);
            System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
            return;
        }
        if(args.length > 1){
          System.out.println("Error: Too many arguments given. Expected 1 argument, found " + args.length);
          System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
          return;
        }

        String FileName = args[0];
        if(args[0].equals("DEFAULT")){
            fileParameters = new int[]{3,20,0,4};
            LIVES_REMAINING = fileParameters[0];
            STEPS_REMAINING = fileParameters[1];
            boardString = new String[4];
            boardString[0] = "#@ ##  &4#";
            boardString[1] = "##  # ## #";
            boardString[2] = "###  3#   ";
            boardString[3] = "#######  #";

            boardArray = new char[4][10];
            for(int r = 0; r < 4; r++){
              String row = boardString[r];
              for(int c = 0; c < 10; c++){
                boardArray[r][c] = row.charAt(c);
              }
            }

            for(int r = 0; r < 4; r++){
              String row = boardString[r];
              for(int c = 0; c < 10; c++){
                if(boardArray[r][c] == '@'){
                    destinationY = r;
                    destinationX = c;
                }
              }
            }
            //boardArray = new char[4][10]{{'#','@','\u0009','#','#','\u0009','\u0009','&','4','#'},{'#','#','\u0009','\u0009','#','\u0009','#','#','\u0009','#'},{'#','#','#','\u0009','\u0009','3','#','\u0009','\u0009','\u0009'},{'#','#','#','#','#','#','#','\u0009','\u0009','#'}};
        }
        else{
            try{
                initialiseGame(FileName);
            }
            catch(IOException e){
                System.out.println("Error: Could not load the game configuration from '"+ args[0] +"'.");
                return;
            }
        }

        Scanner keyboard = new Scanner(System.in);
        String input1 = keyboard.nextLine();
        performAction(input1);
        while(!isGameEnd()){
            input1 = keyboard.nextLine();
            try{
                performAction(input1);
            }
            catch(IllegalArgumentException e){
                System.out.println("Error: Could not find command '" + input1 + "'.");
                System.out.println("To find the list of valid commands, please type 'help'.");
            }

        }



        /*
        String row = boardString[0];

        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){

                      System.out.print(boardArray[r][c]);
                  }
            System.out.println();
        }

        moveTo(4,1);

        System.out.println();

        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){

                      System.out.print(boardArray[r][c]);
                  }
            System.out.println();
        }
        */

        /*

        System.out.println(getCurrentXPosition());
        System.out.println(getCurrentYPosition());
        System.out.println(destinationX);
        System.out.println(destinationY);
        boardArray[getCurrentYPosition()][getCurrentXPosition()] = ' ';
        boardArray[destinationY][destinationX] = '&';
        String row = boardString[0];

        for(int r = 0; r < boardString.length; r++) {
            row = boardString[r];
            for(int c = 0; c < row.length(); c++){

                      System.out.print(boardArray[r][c]);
                  }
            System.out.println();
        }

        System.out.println(isMazeCompleted());

        */


    }
}

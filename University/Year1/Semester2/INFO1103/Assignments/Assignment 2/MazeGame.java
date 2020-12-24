import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.NoSuchElementException;
import java.util.Arrays;

/*
* Keegan Gyoery
* SID 470413467
* 15 September 2017
*/
public class MazeGame {
  static int LIVES_REMAINING = 0;
  static int STEPS_REMAINING = 0;
  static int GOLD_PERSON = 0;
  static int rows = 0;
  static int columns = 0;
  static int positionX = 0;
  static int positionY = 0;
  static int destinationX = 0;
  static int destinationY = 0;
  static int[] rowLengths;
  static char[][] boardArray;

  /**
  *
  * Initialises the game from the given file, ie configFileName
  * @args configFileName The name of the game configuration file to read from.
  * If there is an error, it will be thrown and caught by the main method
  * IO Exception will be thrown
  **/
  public static void initialiseGame(String configFileName) throws IOException {
    File readFile = new File(configFileName); // Creates a new file to read from
    Scanner inputStream = new Scanner(readFile); // Creates a new scanning object

    int[] fileParameters = new int[4]; // Initialise an array to store the game parameters
    for(int i = 0; i < 4; i++){
      fileParameters[i] = inputStream.nextInt(); // Read each integer into the parameters array from the file
    }

    // Set each variable that defines the game to their relevant position in the parameters array
    LIVES_REMAINING = fileParameters[0];
    STEPS_REMAINING = fileParameters[1];
    GOLD_PERSON = fileParameters[2];
    rows = fileParameters[3];
    inputStream.nextLine(); // Read out the now blank line where the file parameters where read from

    rowLengths = new int[rows]; // Initialise an array to store the length of each row in the input file

    for(int z = 0; z < rows; z++){
      rowLengths[z] = inputStream.nextLine().length(); // Add the length of the file row to the array
    }

    int max = rowLengths[0]; // Set the max row length to the first element of the row lengths array
    for(int k = 0; k < rows; k++){
      if(rowLengths[k] > max){
        max = rowLengths[k]; // Change the variable max if the row length is greater
      }
    }

    columns = max; // Set the amount of columns equal to the max row length from the file
    boardArray = new char[rows][columns]; // Initialise the 2D character array
    Scanner boardInput = new Scanner(readFile); // Create a new Scanner object to read through the file again
    boardInput.nextLine(); // Scan away the first line as it isn't important to the board array
    for (int r = 0; r < rows; r++) {
      String currentLine = boardInput.nextLine(); // Set the variable currentLine to the line read in from the file
      for (int c = 0; c < currentLine.length(); c++) {
        boardArray[r][c] = currentLine.charAt(c); // Place the character at the relevant position in the file row into the board array
      }
    }
    positionX = getCurrentXPosition(); // Set the current x position
    positionY = getCurrentYPosition(); // Set the current y position
    for(int r = 0; r < rows; r++) {
      for(int c = 0; c < columns; c++){
        if(boardArray[r][c] == '@'){
          destinationY = r; // Set the destination y position
          destinationX = c; // Set the destination x position
          break;
        }
      }
    }
  }

  /**
  * Saves the current board to the given file name.
  * @param toFileName The name of the file to save the game configuration to.
  * If there is an error, it will be thrown and caught by the main method
  * IO Exception will be thrown
  **/
  public static void saveGame(String toFileName) throws IOException {
    PrintWriter outputStream = new PrintWriter(new File(toFileName)); // Create a new writer object to write to the file with the given file name
    outputStream.printf("%d %d %d %d\n",numberOfLives(),numberOfStepsRemaining(),amountOfGold(),rows); // Write the first line to file as the parameters
    for(int r = 0; r < rows; r++) {
      for(int c = 0; c < columns; c++){
        outputStream.print(boardArray[r][c]); // Print the character of the board to the file
      }
      outputStream.println(); // Print a new line after the row
    }
    outputStream.close(); // Close the file in order for it to be saved properly
    System.out.printf("Successfully saved the current game configuration to '%s'.\n", toFileName); // Outputs this message if the save was successful
  }

  /**
  * Gets the current x position of the player.
  * @return positionX, The players current x position.
  **/
  public static int getCurrentXPosition() {
    for(int r = 0; r < rows; r++) {
      for(int c = 0; c < columns; c++){
        if(boardArray[r][c] == '&'){
          positionX = c; // Sets the column of the ampersand character to the current x position
        }
      }
    }
    return positionX;
  }

  /**
  * Gets the current y position of the player.
  * @return positionY, The players current y position.
  **/
  public static int getCurrentYPosition() {
    for(int r = 0; r < rows; r++) {
      for(int c = 0; c < columns; c++){
        if(boardArray[r][c] == '&'){
          positionY = r; // Sets the row of the ampersand character to the current y position
        }
      }
    }
    return positionY;
  }

  /**
  * Gets the number of lives the player currently has.
  * @return LIVES_REMAINING, The number of lives the player currently has.
  **/
  public static int numberOfLives() {
    return LIVES_REMAINING;
  }

  /**
  * Gets the number of steps the player currently has.
  * @return STEPS_REMAINING, The number of steps the player currently has.
  **/
  public static int numberOfStepsRemaining() {
    return STEPS_REMAINING;
  }

  /**
  * Gets the amount of gold the player currently has.
  * @return GOLD_PERSON, The amount of gold the player currently has.
  **/
  public static int amountOfGold() {
    return GOLD_PERSON;
  }

  /**
  * Checks to see if the player has completed the maze.
  * The player has completed the maze if they have reached the destination.
  * @return true, if the player has completed the maze.
  **/
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
  * @return true, if any one of the conditions that end the game is true.
  **/
  public static boolean isGameEnd() {
    if(numberOfLives() <=0 || numberOfStepsRemaining() <=0 || isMazeCompleted()){
      return true;
    }
    return false;
  }

  /**
  * Checks if the coordinates (x, y) are valid.
  * That is, if they are on the board.
  * @param x The x coordinate.
  * @param y The y coordinate.
  * @return true, if the given coordinates are valid.
  * @return false, if the given coordinates are invalid.
  **/
  public static boolean isValidCoordinates(int x, int y) {
    if(x >= 0 && x < columns && y >= 0 && y < rows){
      return true;
    }
    return false;
  }

  /**
  * Checks if a move to the given coordinates is valid.
  * A move is invalid if:
  *  - It is move to a coordinate off the board.
  *  - There is a wall at that coordinate.
  *  - The game is ended.
  *
  * @param x The x coordinate to move to.
  * @param y The y coordinate to move to.
  * @return true, if the move is valid.
  * @return false, if the move is invalid.
  **/
  public static boolean canMoveTo(int x, int y) {
    if(isGameEnd()){
      return false;
    }
    if(isValidCoordinates(x,y) && boardArray[y][x] != '#'){ // Check if it is valid or a wall character
      return true;
    }
    return false;
  }

  /**
  * Move the player to the given coordinates on the board.
  * After a successful move, it prints "Moved to (x, y)." where (x, y) were the coordinates given.
  *
  * If there was gold at the position the player moved to, the gold should be collected
  * and the message "Plus n gold."should also be printed, where n is the amount of gold collected.
  *
  * If it is an invalid move, a life is lost.
  * The method prints: "Invalid move. One life lost."
  *
  * @param x The x coordinate to move to.
  * @param y The y coordinate to move to.
  **/
  public static void moveTo(int x, int y) {
    if(canMoveTo(x,y)){
      boardArray[getCurrentYPosition()][getCurrentXPosition()] = '.'; // Set the current position to a . character
      positionX = x; // Change the x position to the new coordinates
      positionY = y; // Change the y position to the new coordinates
      System.out.println("Moved to (" + getCurrentXPosition() +", "+ getCurrentYPosition() +")."); // Print the move to message
      String goldChar = "" + boardArray[y][x]; // Set the variable equal to the character at the position that the move is to

      if(goldChar.matches("[0-9]+")){ // Check if the character at the new position matches a number
        int goldAtLocation = Integer.parseInt(goldChar); // Parse the character as an integer
        GOLD_PERSON = GOLD_PERSON + goldAtLocation; // Increase the gold of the person by the amount at the location
        System.out.println("Plus " + goldAtLocation + " gold."); // Print the gold message
      }
      boardArray[getCurrentYPosition()][getCurrentXPosition()] = '&'; // Change the new position to the person character, ampersand
      STEPS_REMAINING -= 1; // Decrease the steps remaining by one step
    }
    else if(!canMoveTo(x,y)){
      System.out.println("Invalid move. One life lost."); // Print the invalid message if it isn't possible to move there
      STEPS_REMAINING -= 1; // Decrease the steps remaining by one step
      LIVES_REMAINING -= 1; // Decrease the lives remaining by one step
    }
    else{
      return;
    }
  }

  /**
  * Prints out the help message.
  **/
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
  **/
  public static void printStatus() {
    System.out.println("Number of live(s): " + numberOfLives());
    System.out.println("Number of step(s) remaining: " + numberOfStepsRemaining());
    System.out.println("Amount of gold: " + amountOfGold());
  }

  /**
  * Prints out the board.
  **/
  public static void printBoard() {
    for(int r = 0; r < rows; r++) {
      for(int c = 0; c < columns; c++){
        System.out.print(boardArray[r][c]); // Print out the character at the position
      }
      System.out.println(); // Print a new line at the end of the row
    }
  }

  /**
  * Performs the given action by calling the appropriate helper methods.
  *
  * The valid actions are "help", "board", "status", "left", "right", "up", "down", and "save".
  * The actions are case insensitive.
  * If it is not a valid action, an IllegalArgumentException should be thrown.
  * The error is caught by the main method and prints the appropriate message.
  *
  * @param input The action we are performing.
  */
  public static void performAction(String input) throws IllegalArgumentException {
    String[] inputParts = input.split(" "); // Splits the input
    if (inputParts.length == 2) { // If the input after splitting has exactly two parts, attempt to save the game
      try {
        if (inputParts[0].toLowerCase().equals("save")) { // Check if the first element equals the word save
          saveGame(inputParts[1]); // Save the game to the second word as the file name
        } else {
          throw new IllegalArgumentException(); // Throw the exception
        }
      } catch (IOException e) {
        System.out.printf("Error: Could not save the current game configuration to '%s'.\n", inputParts[1]); // Print message if cannot save to file
      }
    }
    else if(input.toLowerCase().equals("right")){
      moveTo(getCurrentXPosition() + 1,getCurrentYPosition()); // Attempts to move the character right
    }
    else if(input.toLowerCase().equals("left")){
      moveTo(getCurrentXPosition() - 1,getCurrentYPosition()); // Attempts to move the character left
    }
    else if(input.toLowerCase().equals("up")){
      moveTo(getCurrentXPosition(),getCurrentYPosition()-1); // Attempts to move the character up
    }
    else if(input.toLowerCase().equals("down")){
      moveTo(getCurrentXPosition(),getCurrentYPosition()+1); // Attempts to move the character down
    }
    else if(input.toLowerCase().equals("help")){ // Prints the help message
      printHelp();
    }
    else if(input.toLowerCase().equals("status")){ // Prints the status
      printStatus();
    }
    else if(input.toLowerCase().equals("board")){ // Prints the board
      printBoard();
    }
    else if(input.toLowerCase().trim().isEmpty()) { // Ignores the empty line or enter from the user
      return;
    }
    else{
      throw new IllegalArgumentException(); // If this all fails, throw an exception to be caught later
    }
  }

  /**
  * Main method of the program
  * @param args[0] The game configuration file from which to initialise the maze game.
  **/
  public static void main(String[] args) {
    if(args.length < 1){ // If the program is loaded without a file, print the following messages
      System.out.println("Error: Too few arguments given. Expected 1 argument, found " + args.length + ".");
      System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
      return;
    }
    if(args.length > 1){ // If the program is loaded with too many files, print the following messages
      System.out.println("Error: Too many arguments given. Expected 1 argument, found " + args.length + ".");
      System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
      return;
    }

    String FileName = args[0]; // Set the variable fileName to the first element in the array args
    try{
      initialiseGame(FileName); // Attempt to initialise the game
    }
    catch(IOException e){ // Catch the error if the file couldn't be loaded and print the following messages
      System.out.println("Error: Could not load the game configuration from '"+ args[0] +"'.");
      return;
    }
    Scanner keyboard = new Scanner(System.in); // Create a new Scanner object to read users input
    try{ // Attempt to get an input from the user
      while(!isGameEnd()){
        String inputUser = keyboard.nextLine(); // Read in the users input to pass tp the method performAction()
        try{
          performAction(inputUser); // Try the perform action method and catch any illegal argument exceptions
        }
        catch(IllegalArgumentException e){ // Print the appropriate message
          System.out.println("Error: Could not find command '" + inputUser + "'.");
          System.out.println("To find the list of valid commands, please type 'help'.");
        }
      }
    }
    catch(NoSuchElementException e){ // If the user terminates their input without completing the game, print the following message
      System.out.println("You did not complete the game.");
      return;
    }

    if(isMazeCompleted()){ // Check if the maze is completed and print the following message
      System.out.println("Congratulations! You completed the maze!");
      System.out.println("Your final status is:");
      printStatus();
      return;
    }
    else if (numberOfLives() == 0 && numberOfStepsRemaining() == 0){ // Check if lives and steps are zero
      System.out.println("Oh no! You have no lives and no steps left.");
      System.out.println("Better luck next time!");
      return;
    }
    else if(numberOfLives() == 0){ // Check if lives are zero
      System.out.println("Oh no! You have no lives left.");
      System.out.println("Better luck next time!");
      return;
    }
    else if(numberOfStepsRemaining() == 0){ // Check if steps are zero
      System.out.println("Oh no! You have no steps left.");
      System.out.println("Better luck next time!");
      return;
    }
  }
}

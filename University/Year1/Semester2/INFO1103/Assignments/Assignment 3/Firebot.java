/**
 * INFO1103 Assignment 3 - FireBot
 * Keegan Gyoery
 * 470413467
 **/

import java.util.Scanner;
import java.util.NoSuchElementException;

public class Firebot {

  // Global variables used throughout the program
  public static boolean isOver = false; // Used to terminate the program
  public static int day = 1; // Tracks the day of teh simulation
  public static String wind = "none"; // Stores the direction of the wind
  public static int heightR = 0; // Height of the region of fire
  public static int widthR = 0; // Width of the region of fire
  public static int heightE = 0; // Height of the region to be extinguished
  public static int widthE = 0; // Width of the region to be extinguished
  public static String[] parts; // String array to hold the user's input

  /**
  * Calls the appropriate wind function from the simulation class in order
  * to move the fire.
  * Takes the input parameter days, which is an integer. Days will determine
  * how long to run the wind simulation for.
  * Returns nothing.
  **/
  public static void windMover(int days){
    if(wind.equals("north")){
      sim.windNorth(days);
    }
    else if(wind.equals("east")){
      sim.windEast(days);
    }
    else if(wind.equals("south")){
      sim.windSouth(days);
    }
    else if(wind.equals("west")){
      sim.windWest(days);
    }
    else if(wind.equals("none")){
      sim.windNone(days);
    }
    else if(wind.equals("all")){
      nextAll(days);
    }
  }

  /**
  * Sets the fire at a particular region or tree by calling the setFireTree
  * function from the simulation class.
  * Takes the input integer parameters r and c. They determine where the
  * single fire is set, or where the region begins.
  * Returns nothing.
  **/
  public static void fireSetting(int r, int c){
    if(!sim.isValidRegion(r,c,heightR,widthR)){ // Checks if the parameters are valid
      System.out.println("Invalid command");
      System.out.println();
      return;
    }
    sim.setFireTree(r,c,heightR,widthR);
    System.out.println();
  }

  /**
  * Extinguishes the fire at a particular region or tree by calling the
  * extinguishFire function from the simulation class.
  * Takes the input integer parameters r and c. They determine where the
  * single fire is to be extinguished, or where the region begins.
  * Returns nothing.
  **/
  public static void extinguisher(int r, int c){
    if(!sim.isValidRegion(r,c,heightE,widthE)){ // Checks if the parameters are valid
      System.out.println("Invalid command");
      System.out.println();
      return;
    }
    sim.extinguishFire(r,c,heightE,widthE);
    System.out.println();
  }

  /**
  * Sets every tree in the forest on fire by calling the setEveryFire
  * function in the simulation class.
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void fireAll(){
    sim.setEveryFire();
    System.out.println();
  }

  /**
  * Extinguishes every fire in the forest by calling the
  * extinguishEveryFire function in the simulation class.
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void extinguishAll(){
    sim.extinguishEveryFire();
    System.out.println();
  }

  /**
  * Prints the heights of the trees in the forest by calling the
  * showHeights function in the simulation class.
  * Takes no parameters.
  * Returns nothing.
  **/
	public static void printHeightBoard(){
    sim.showHeights();
    System.out.println();
  }

  /**
  * Prints the fires in the forest by calling the
  * showFire function in the simulation class.
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void printFireBoard(){
    sim.showFire();
    System.out.println();
  }

  /**
  * Prints the help list of valid commands.
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void printHelp(){
    System.out.println("BYE");
    System.out.println("HELP");
    System.out.println();
    System.out.println("DATA");
    System.out.println("STATUS");
    System.out.println();
    System.out.println("NEXT <days>");
    System.out.println("SHOW <attribute>");
    System.out.println();
    System.out.println("FIRE <region>");
    System.out.println("WIND <direction>");
    System.out.println("EXTINGUISH <region>");
    System.out.println();
  }

  /**
  * Prints the status of the simulation.
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void printStatus(){
    System.out.println("Day: " + day); // Prints the day of the simulation
    System.out.println("Wind: " + wind); // Prints the wind direction
    System.out.println();
  }

  /**
  * Prints the data of the simulation, that is the damage and pollution
  * in the simulation.
  * Calls the burntDamage and pollution functions from the simulation class.
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void printData(){
    double damage = sim.burntDamage();
    int pollution = sim.pollution;
    if(pollution < 0){
			pollution = 0; // Sets pollution to zero if its negative
      sim.pollution = 0; // Sets the pollution variable in the Simulation class to zero as well
		}
    System.out.printf("Damage: %.2f",damage); // Prints to two decimal places
    System.out.println("%"); // Prints the percentage symbol after the damage
    System.out.printf("Pollution: %d\n",pollution);
    System.out.println();
  }

  /**
  * Deals with the user input of the word next, and handles the case where
  * the following command is all. Calls the increaseAll function to
  * increase all of the current fires by 1. Calls the windAll function to
  * move the fire in all directions.
  * Takes an integer parameter, days which determines the number of times
  * to run the simulation.
  * Returns nothing.
  **/
  public static void nextAll(int days){
    for(int i = 1; i <= days; i++){
      sim.increaseAll();
      sim.windAll();
    }
  }

  /**
  * Deals with the user input of the word next, and handles all of the
  * error cases, printing the appropriate messages for errors.
  * The command next is in the following formats:
  * next
  * next <days>
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void nextProcessor(){
    int daysInc = 1; // Variable that stores the increment of days
    if(parts.length == 2){ // Checks if next is followed by a number
      try{
        daysInc = Integer.parseInt(parts[1]);
      }
      catch(NumberFormatException nfe){
        System.out.println("Invalid command");
        System.out.println();
        return;
      }
      day = day + daysInc; // Updates the variable day that stores the day of the simulation
      printStatus();
      windMover(daysInc);
    }
    else if(parts.length == 1){ // Handles the case when only next is entered
      day = day + daysInc; // Updates the variable day that stores the day of the simulation
      printStatus();
      windMover(daysInc);
    }
    else{
      System.out.println("Invalid command");
      System.out.println();
      return;
    }
  }

  /**
  * Deals with the user input of the word fire, and handles all of the
  * error cases, printing the appropriate messages for errors.
  * The command fire is in the following formats:
  * fire <x> <y>
  * fire <x> <y> <width> <height>
  * fire all
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void fireProcessor(){
    if(parts.length == 2){ // Checks if fire is followed by all
      if(parts[1].equals("all")){
        fireAll();
      }
      else{
        System.out.println("Invalid command");
        System.out.println();
        return;
      }
    }
    else if(parts.length == 3 || parts.length == 5){ // Checks if fire is followed by a point or a region
      int fireR, fireC;
      try{
        fireC = Integer.parseInt(parts[1]);
        fireR = Integer.parseInt(parts[2]);

        if(parts.length == 5){
          if(Integer.parseInt(parts[3]) == 0 && Integer.parseInt(parts[4]) == 0){
            throw new NumberFormatException(); // Can't enter 0 for height and width of region
          }
          else{ // Only parse values if they exist/are entered by the user
            widthR = Integer.parseInt(parts[3]);
            heightR = Integer.parseInt(parts[4]);
          }
        }
      }
      catch(NumberFormatException nfe){
        System.out.println("Invalid command");
        System.out.println();
        return;
      }
      fireSetting(fireR,fireC);
    }
    else {
      System.out.println("Invalid command");
      System.out.println();
      return;
    }
  }

  /**
  * Deals with the user input of the word extinguish, and handles all of the
  * error cases, printing the appropriate messages for errors.
  * The command fire is in the following formats:
  * extinguish <x> <y>
  * extinguish <x> <y> <width> <height>
  * extinguish all
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void extinguishProcessor(){
    if(parts.length == 2){ // Checks if extinguish is followed by all
      if(parts[1].equals("all")){
        extinguishAll();
      }
      else{
        System.out.println("Invalid command");
        System.out.println();
        return;
      }
    }
    else if(parts.length == 3 || parts.length == 5){ // Checks if extinguish is followed by a point or a region
      int extR, extC;
      try{
        extC = Integer.parseInt(parts[1]);
        extR = Integer.parseInt(parts[2]);

        if(parts.length == 5){
          if(Integer.parseInt(parts[3]) == 0 && Integer.parseInt(parts[4]) == 0){
            throw new NumberFormatException(); // Can't enter 0 for height and width of region
          }
          else{ // Only parse values if they exist/are entered by the user
            widthE = Integer.parseInt(parts[3]);
            heightE = Integer.parseInt(parts[4]);
          }
        }
      }
      catch(NumberFormatException nfe){
        System.out.println("Invalid command");
        System.out.println();
        return;
      }
      extinguisher(extR,extC);
    }
    else {
      System.out.println("Invalid command");
      System.out.println();
      return;
    }
  }

  /**
  * Deals with the user input of the word wind, and handles all of the
  * error cases, printing the appropriate messages for errors.
  * The command wind is in the following formats:
  * wind <direction>
  * wind all
  * wind none
  * Direction can be north, east, south or west.
  * Takes no parameters.
  * Returns nothing.
  **/
  public static void windProcessor(){
    if(parts.length == 2){
      if(parts[1].equals("none")){
        wind = parts[1];
        System.out.println("Set wind to "+ wind);
        System.out.println();
      }
      else if(parts[1].equals("north")){
        wind = parts[1];
        System.out.println("Set wind to "+ wind);
        System.out.println();
      }
      else if(parts[1].equals("east")){
        wind = parts[1];
        System.out.println("Set wind to "+ wind);
        System.out.println();
      }
      else if(parts[1].equals("south")){
        wind = parts[1];
        System.out.println("Set wind to "+ wind);
        System.out.println();
      }
      else if(parts[1].equals("west")){
        wind = parts[1];
        System.out.println("Set wind to "+ wind);
        System.out.println();
      }
      else if(parts[1].equals("all")){
        wind = parts[1];
        System.out.println("Set wind to "+ wind);
        System.out.println();
      }
      else{
        System.out.println("Invalid command");
        System.out.println();
        return;
      }
    }
    else{
      System.out.println("Invalid command");
      System.out.println();
      return;
    }
  }

  /**
  * Deals with the user input, and handles all of the
  * error cases, printing the appropriate messages for errors.
  * The valid commands are listed in the printHelp function.
  * Takes a string parameter, whish is the input read from the user.
  * Returns nothing.
  **/
  public static void inputProcessor(String input){
    parts = input.split(" "); // Splits the users input into parts
    if(input.equals("bye")){
      isOver = true; // Determines if the program continues to run or not
    }
    else if(input.equals("help")){
      printHelp();
    }
    else if(input.equals("status")){
      printStatus();
    }
    else if(input.equals("data")){
      printData();
    }
    else if(input.equals("show height")){
      printHeightBoard();
    }
    else if(input.equals("show fire")){
      printFireBoard();
    }
    else if(parts[0].equals("next")){
      nextProcessor();
    }
    else if(parts[0].equals("fire")){
      fireProcessor();
    }
    else if(parts[0].equals("extinguish")){
      extinguishProcessor();
    }
    else if(parts[0].equals("wind")){
      windProcessor();
    }
    else{
      System.out.println("Invalid command");
      System.out.println();
    }
  }


  private static Scanner scan; // Creates a Scanner object called scan
  private static Simulation sim; // Creates a Simulation object called sim

	public static void main(String[] args) {
    int seed, width, height; // Initialise the variables seed, width and height
    try{ // Try to parse the variables as integers
      seed = Integer.parseInt(args[0]);
      width = Integer.parseInt(args[1]);
      height = Integer.parseInt(args[2]);
    }
    catch(NumberFormatException nfe){ // Catch if they are not integers
      System.out.println("Usage: java Firebot <seed> <width> <height>");
      return;
    }
    catch(ArrayIndexOutOfBoundsException aioobe){ // Catch if there are not enough parameters
      System.out.println("Usage: java Firebot <seed> <width> <height>");
      return;
    }

    if(args.length > 3){ // Catches if there are too many parameters
      System.out.println("Usage: java Firebot <seed> <width> <height>");
      return;
    }

    sim = new Simulation(seed, width, height); // Initialise the object sim with the command line parameters
    scan = new Scanner(System.in); // Initialise the scan object
    printStatus(); // Print the status whenever the program is first loaded
    while(!isOver){ // Continue taking input from the user until isOver is true
      String input;
      System.out.print("> "); // Print the symbol to the screen
      try{
        input = scan.nextLine(); // Try to read the next line from the user
      }
      catch(NoSuchElementException nsee){ // Catch if EOF
        System.out.println();
        System.out.println("bye");
        return;
      }
      input = input.toLowerCase(); // Convert the users input to lower case
      inputProcessor(input);
    }
    System.out.println("bye");
	}
}

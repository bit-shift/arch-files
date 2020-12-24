/**
 * INFO1103 Assignment 3 - FireBot
 * Keegan Gyoery
 * 470413467
 **/

public class Simulation {

	// Declares the instance variables to be used for the simulation class
	private int width;
	private int height;
	private Tree[][] trees;
	public int pollution = 0;

	/**
	* Constructor for the Simulation object.
	* Takes the integer parameters of seed, width and height to define a
	* Simulation object.
	* Returns nothing.
	**/
  public Simulation(int seed, int width, int height){
    this.height = height; // Sets the instance variable height to the parameter given when running the program
    this.width = width; // Sets the instance variable width to the parameter given when running the program
    Tree treestance = new Tree(height, width); // Initialises a new instance of the Tree object
    trees = treestance.getTree(); // Uses the instance to get the 2D array of Tree objects
    generateTerrain(seed); // Passes the seed parameter to the generateTerrain function
  }

	/**
	* Checks to determine if the given parameters are valid, that is,
	* the single point lies inside the array of Tree objects, and that
	* the region also lies in the array of Tree objects
	* Takes the integer parameters of r, c, heightR, widthR to check if
	* the point position given by (r,c) is valid, and the region given by
	* (r,c) -> (r + heightR, c + widthC) is valid.
	* Returns a boolean based on whether the conditions are valid or not.
	* Returns true if the conditions are valid.
	**/
	public boolean isValidRegion(int r, int c, int heightR, int widthR){
		boolean isValid = false;
		if(heightR == 0 && widthR == 0){
			if(r > -1 && r < height && c > -1 && c < width){
				isValid = true;
			}
			return isValid;
		}
		if(r + heightR - 1 < height && r + heightR - 1 > -1 && heightR -1 > -1 && heightR - 1 < height && r > -1 && r < height){
			if(c + widthR - 1 < width && c + widthR - 1 > -1 && widthR - 1 > -1 && widthR -1 < width && c > -1 && c < width){
				isValid = true;
			}
		}
		return isValid;
	}

	/**
	* Prints out the surrounding board and array of heights of each Tree object.
	* Takes no parameters.
	* Returns nothing.
	**/
  public void showHeights(){
    for(int r = 0; r < height + 2; r++){
      for(int c = 0; c < width + 2; c++){
        if((r == 0 && c == 0) || (r == height + 1 && c == 0) || (r == 0 && c == width + 1) || (r == height + 1 && c == width + 1)){
          System.out.print("+"); // Prints the corner symbol
        }
        else if(r == 0 || r == height + 1){
          if(c == 1){ // There needs to be one less dash than all double dashes
            System.out.print("-");
          }
          else{
            System.out.print("--");
          }
        }
        else if(c == 0 || c == width + 1){
          System.out.print("|"); // Prints the wall of the border
        }
				else if(trees[r-1][c-1].isBurntDown){
					System.out.print("x"); // Prints an x if the Tree object has the attribute isBurntDown set to true
				}
        else if(trees[r-1][c-1].height == 0){
          System.out.print(" "); // Prints a space if the Tree object has height attribute 0
        }
				else{
					System.out.print(trees[r-1][c-1].height); // If the height of the Tree object is greater than zero it is printed to the screen
				}
        if((c > 0 && c < width) && r != 0 && r != height + 1){
          System.out.print(" "); // Prints an extra space to space the array out
        }
      }
      System.out.println(); // New line
    }
  }

	/**
	* Prints out the surrounding board and array of fire intensities
	* of each Tree object.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void showFire(){
    for(int r = 0; r < height + 2; r++){
      for(int c = 0; c < width + 2; c++){
        if((r == 0 && c == 0) || (r == height + 1 && c == 0) || (r == 0 && c == width + 1) || (r == height + 1 && c == width + 1)){
          System.out.print("+"); // Prints the corner symbol
        }
        else if(r == 0 || r == height + 1){
          if(c == 1){
            System.out.print("-"); // There needs to be one less dash than all double dashes
          }
          else{
            System.out.print("--");
          }
        }
        else if(c == 0 || c == width + 1){
          System.out.print("|"); // Prints the wall of the border
        }
				else if(trees[r-1][c-1].height != 0 && trees[r-1][c-1].fire == 0){
					System.out.print("."); // Prints a period if the tree has height and no fire
				}
				else if(trees[r-1][c-1].isBurntDown){
					System.out.print("x"); // Prints an x if the Tree object has the attribute isBurntDown set to true
				}
        else if(trees[r-1][c-1].height == 0){
          System.out.print(" "); // Prints a space if the Tree object has height attribute 0
        }
				else{
					System.out.print(trees[r-1][c-1].fire);  // If the fire of the Tree object is greater than zero it is printed to the screen
				}
        if((c > 0 && c < width) && r != 0 && r != height + 1){
          System.out.print(" ");
        }
      }
      System.out.println(); // New line
    }
  }

	/**
	* Sets a Tree object with height greater than 0 on fire, if it is
	* not already on fire. Can set either a single Tree object on fire,
	* or a region of Tree objects.
	* Takes the integer parameters of r, c, heightR, widthR to set a fire at
	* the point position given by (r,c), or the region given by
	* (r,c) -> (r + heightR, c + widthC).
	* Returns nothing.
	**/
	public void setFireTree(int r, int c, int heightR, int widthR){
		int count = 0; // Tracker to count the number of fires set
		if(heightR == 0){
			heightR = 1; // Sets the height of the region to 1 if a point is given
		}
		if(widthR == 0){
			widthR = 1; // Sets the width of the region to 1 if a point is given
		}
		for(int y = r; y < r + heightR; y++){
			for(int x = c; x < c + widthR; x++){
				if(trees[y][x].height > 0 && trees[y][x].fire == 0){ // Checks if there is a Tree object with height greater than 0 and no fire
					trees[y][x].setFire(); // If these conditions are met, calls the setFire method of the Tree class
					count = count + 1; // Increases the tracker's count
				}
			}
		}
		if(count > 0){
			System.out.println("Started a fire"); // If there have been any fires set, print the message
		}
		else{
			System.out.println("No fires were started"); // Otherwise print this
		}
	}

	/**
	* Sets every Tree object in the array with height greater than 0 on fire, if it is
	* not already on fire.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void setEveryFire(){
		int count = 0; // Tracker to count the number of fires set
		for(int r = 0; r < height; r++){
			for(int c = 0; c < width; c++){
				if(trees[r][c].height > 0 && trees[r][c].fire == 0){ // Checks if there is a Tree object with height greater than 0 and no fire
					trees[r][c].setFire(); // If these conditions are met, calls the setFire method of the Tree class
					count = count + 1; // Increases the tracker's count
				}
			}
		}
		if(count > 0){
			System.out.println("Started a fire"); // If there have been any fires set, print the message
		}
		else{
			System.out.println("No fires were started"); // Otherwise print this
		}
	}

	/**
	* Extinguishes a Tree object's fire if it is on fire.
	* Can extinguish a single fire or a region of fires.
	* Takes the integer parameters of r, c, heightR, widthR to extinguish
	* a fire at the point position given by (r,c), or the region given by
	* (r,c) -> (r + heightR, c + widthC).
	* Returns nothing.
	**/
	public void extinguishFire(int r, int c, int heightR, int widthR){
		int count = 0; // Tracker to count the number of fires extinguished
		if(heightR == 0){
			heightR = 1;
		}
		if(widthR == 0){
			widthR = 1;
		}
		for(int y = r; y < r + heightR; y++){
			for(int x = c; x < c + widthR; x++){
				if(trees[y][x].fire > 0){ // Checks if there is a fire to extinguish
					trees[y][x].extFire(); // Calls the extFire method from the Tree class
					count = count + 1; // Increases the tracker's count
				}
			}
		}
		if(count > 0){
			System.out.println("Extinguished fires"); // If there have been any fires extinguished, print the message
		}
		else{
			System.out.println("No fires to extinguish"); // Otherwise print this
		}
	}

	/**
	* Extinguishes every Tree object's fire in the array, if it is on fire.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void extinguishEveryFire(){
		int count = 0; // Tracker to count the number of fires extinguished
		for(int r = 0; r < height; r++){
			for(int c = 0; c < width; c++){
				if(trees[r][c].fire > 0){ // Checks if there is a fire to extinguish
					trees[r][c].fire = 0; // Calls the extFire method from the Tree class
					count = count + 1; // Increases the tracker's count
				}
			}
		}
		if(count > 0){
			System.out.println("Extinguished fires"); // If there have been any fires extinguished, print the message
		}
		else{
			System.out.println("No fires to extinguish"); // Otherwise print this
		}
	}

	/**
	* Calculates the pollution in the current simulation. The calculation is
	* given by pollution = fire intensity of all trees - height of all trees.
	* Takes no parameters.
	* Returns an integer for the pollution level. Returns 0 if the pollution
	* level is negative.
	**/
	public int pollution(){
		int heightCount = 0; // Tracker to count the total height
		int fireCount = 0; // Tracker to count the total fire intensity
		for(int r = 0; r < height; r++){
			for(int c = 0; c < width; c++){
				if(trees[r][c].height > 0){ // If the Tree obejct has a height greater than zero, add its height ot the total
					heightCount = heightCount + trees[r][c].height;
				}
				if(trees[r][c].fire > 0){ // If the Tree object has a fire intensity greater than zero, add its fire intensity to the total
					fireCount = fireCount + trees[r][c].fire;
				}
			}
		}
		pollution = fireCount - heightCount; // Determines the pollution level
		return pollution; // Returns the value of pollution
	}

	/**
	* Calculates the burn damage in the current simulation. The calculation is
	* given by damage = (no. burnt down)/(no. trees with positive height).
	* Takes no parameters.
	* Returns a double for the damage.
	**/
	public double burntDamage(){
		int treeCount = 0; // Tracker to count the total number of trees
		int burnCount = 0; // Tracker to count the total number of burnt trees
		double damage = 0;
		for(int r = 0; r < height; r++){
			for(int c = 0; c < width; c++){
				if(trees[r][c].isBurntDown){ // If the Tree object is burnt down, increases the burnt down count and the tree count
					burnCount = burnCount + 1;
					treeCount = treeCount + 1;
				}
				if(trees[r][c].height > 0){ // If the Tree object has height greater than 0, increase the tree count
					treeCount = treeCount + 1;
				}
			}
		}
		damage = 100*(((double) burnCount)/((double) treeCount)); // Cast the trackers as doubles to calculate damage
		return damage; // Return the damage value
	}

	/**
	* Moves the fire in the simulation according to the wind direction north
	* and the number of days the simulation is currently running for.
	* The fire moves to a tree adjacent to a tree on fire in the direction
	* of the wind, and increases the current fire by a value of 1 on each tree.
	* Takes an integer parameter days, which determines how many loops to run
	* the current simulation for.
	* Returns nothing.
	**/
	public void windNorth(int days){
		for(int i = 1; i <= days; i++){ // Loops through the wind movements for the specified number of days
			for(int r = 0; r < height; r++){
				for(int c = 0; c < width; c++){
					if(trees[r][c].fire > 0){
						if(r-1 > -1 && trees[r-1][c].height > 0 && trees[r-1][c].fire > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if the adjacent tree is already on fire
						}
						else if(r-1 > -1 && trees[r-1][c].height > 0 && trees[r-1][c].fire == 0){
							trees[r][c].increaseFire(); // Increases a tree's fire
							trees[r-1][c].setFire(); // Sets a fire at the adjacent tree if there was no fire
						}
						else if(trees[r][c].height > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if there is a fire at the tree
						}
					}
				}
			}
			pollution = pollution + pollution(); // Calculates the cumulative pollution
		}
	}

	/**
	* Moves the fire in the simulation according to the wind direction east
	* and the number of days the simulation is currently running for.
	* The fire moves to a tree adjacent to a tree on fire in the direction
	* of the wind, and increases the current fire by a value of 1 on each tree.
	* Takes an integer parameter days, which determines how many loops to run
	* the current simulation for.
	* Returns nothing.
	**/
	public void windEast(int days){
		for(int i = 1; i <= days; i++){ // Loops through the wind movements for the specified number of days
			for(int r = height - 1; r > -1; r--){
				for(int c = width - 1; c > -1; c--){
					if(trees[r][c].fire > 0){
						if(c < width-1 && trees[r][c+1].height > 0 && trees[r][c+1].fire > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if the adjacent tree is already on fire
						}
						else if(c < width-1 && trees[r][c+1].height > 0 && trees[r][c+1].fire == 0){
							trees[r][c].increaseFire(); // Increases a tree's fire
							trees[r][c+1].setFire(); // Sets a fire at the adjacent tree if there was no fire
						}
						else if(trees[r][c].height > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if there is a fire at the tree
						}
					}
				}
			}
			pollution = pollution + pollution(); // Calculates the cumulative pollution
		}
	}

	/**
	* Moves the fire in the simulation according to the wind direction south
	* and the number of days the simulation is currently running for.
	* The fire moves to a tree adjacent to a tree on fire in the direction
	* of the wind, and increases the current fire by a value of 1 on each tree.
	* Takes an integer parameter days, which determines how many loops to run
	* the current simulation for.
	* Returns nothing.
	**/
	public void windSouth(int days){
		for(int i = 1; i <= days; i++){ // Loops through the wind movements for the specified number of days
			for(int r = height - 1; r > -1; r--){
				for(int c = width - 1; c > -1; c--){
					if(trees[r][c].fire > 0){
						if(r < height - 1 && trees[r+1][c].height > 0 && trees[r+1][c].fire > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if the adjacent tree is already on fire
						}
						else if(r < height -1  && trees[r+1][c].height > 0 && trees[r+1][c].fire == 0){
							trees[r][c].increaseFire(); // Increases a tree's fire
							trees[r+1][c].setFire(); // Sets a fire at the adjacent tree if there was no fire
						}
						else if(trees[r][c].height > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if there is a fire at the tree
						}
					}
				}
			}
			pollution = pollution + pollution(); // Calculates the cumulative pollution
		}
	}

	/**
	* Moves the fire in the simulation according to the wind direction west
	* and the number of days the simulation is currently running for.
	* The fire moves to a tree adjacent to a tree on fire in the direction
	* of the wind, and increases the current fire by a value of 1 on each tree.
	* Takes an integer parameter days, which determines how many loops to run
	* the current simulation for.
	* Returns nothing.
	**/
	public void windWest(int days){
		for(int i = 1; i <= days; i++){ // Loops through the wind movements for the specified number of days
			for(int r = 0; r < height; r++){
				for(int c = 0; c < width; c++){
					if(trees[r][c].fire > 0){
						if(c-1 > -1 && trees[r][c-1].height > 0 && trees[r][c-1].fire > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if the adjacent tree is already on fire
						}
						else if(c-1 > -1 && trees[r][c-1].height > 0 && trees[r][c-1].fire == 0){
							trees[r][c].increaseFire(); // Increases a tree's fire
							trees[r][c-1].setFire(); // Sets a fire at the adjacent tree if there was no fire
						}
						else if(trees[r][c].height > 0){
							trees[r][c].increaseFire(); // Increases a tree's fire if there is a fire at the tree
						}
					}
				}
			}
			pollution = pollution + pollution(); // Calculates the cumulative pollution
		}
	}

	/**
	* Does not move the fire, as there is no wind direction, rather only
	* increases the current fire by a value of 1 on each tree.
	* Takes an integer parameter days, which determines how many loops to run
	* the current simulation for.
	* Returns nothing.
	**/
	public void windNone(int days){
		for(int i = 1; i <= days; i++){ // Loops through the wind movements for the specified number of days
			for(int r = 0; r < height; r++){
				for(int c = 0; c < width; c++){
					if(trees[r][c].fire > 0){
						trees[r][c].increaseFire(); // Increases a tree's fire if there is a fire at the tree
					}
				}
			}
			pollution = pollution + pollution(); // Calculates the cumulative pollution
		}
	}

	/**
	* Moves the fire in the simulation according to the wind direction,
	* which is  every direction, and the number of days the simulation
	* is currently running for.
	* The fire moves to a tree adjacent to a tree on fire in the direction
	* of the wind, and increases the current fire by a value of 1 on each tree.
	* Takes an integer parameter days, which determines how many loops to run
	* the current simulation for.
	* Returns nothing.
	**/
	public void windAll(){
		boolean[][] fireSetBoolean = new boolean[height][width]; // Boolean 2D array
		for(int r = 0; r < height; r++){
			for(int c = 0; c < width; c++){
				if(trees[r][c].fire == 0 && trees[r][c].height > 0){
					if((r > 0 && trees[r-1][c].fire > 0) || (r < height -1 && trees[r+1][c].fire > 0) || (c > 0 && trees[r][c-1].fire > 0) || (c < width - 1) && trees[r][c+1].fire > 0){
						fireSetBoolean[r][c] = true; // Stores a 1 in the current position of there is a tree on fire in one of the four squares around it
					}
				}
			}
		}
		for(int r = 0; r < height; r++){ // Loops through the fire boolean array
			for(int c = 0; c < width; c++){
				if(fireSetBoolean[r][c]){
					trees[r][c].setFire(); // Sets a fire at the position if it is true in the boolean array
				}
			}
		}
		pollution = pollution + pollution(); // Updates the pollution of the fire
	}

	/**
	* Increases the fire at the current position of there already is a fire
	* at that position. This function is only called for the all wind
	* direction.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void increaseAll(){
		for(int r = 0; r < height; r++){
			for(int c = 0; c < width; c++){
				if(trees[r][c].fire > 0){
					trees[r][c].increaseFire(); // Calls the increaseFire method
				}
			}
		}
	}

	private void generateTerrain(int seed) {

		// ###################################
		// ### DO NOT MODIFY THIS FUNCTION ###
		// ###################################

		Perlin perlin = new Perlin(seed);
		double scale = 10.0 / Math.min(width, height);

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				double height = perlin.noise(x * scale, y * scale, 0.5);
				height = Math.max(0, height * 1.7 - 0.7) * 10;
				trees[y][x] = new Tree((int) height);
			}
		}
	}
}

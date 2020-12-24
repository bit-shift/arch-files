/**
 * INFO1103 Assignment 3 - FireBot
 * Keegan Gyoery
 * 470413467
 **/

public class Tree {

	// Declare the instance variables, or properties of the Tree class
	int fire = 0; // Fire attribute
	int height; // Height of the array of Tree objects. Also the height attribute for the individual tree
	int width; // Width of the array of Tree objects
	boolean isBurntDown = false; // Attribute of burnt down
	Tree[][] trees;

	/**
	* Constructor for a Tree object.
	* Takes the integer parameter of height to give the Tree object a height.
	**/
	public Tree(int height) {
		setHeight(height);
	}

	/**
	* Constructor for a Tree object.
	* Takes the integer parameters of height and width, to create a 2D
	* array that stores Tree objects.
	**/
	public Tree(int height, int width){
		trees = new Tree[height][width];
		this.height = height;
		this.width = width;
	}

	/**
	* Get method that returns the 2D array of Tree objects.
	* Takes no parameters.
	**/
	public Tree[][] getTree(){
		return trees;
	}

	/**
	* Set method that sets the height of Tree objects.
	* Takes the integer parameter of height to give the Tree object a height.
	* Returns nothing.
	**/
	public void setHeight(int height){
		this.height = height;
	}

	/**
	* Set method that sets the fire of Tree objects. Sets the fire attribute
	* of the Tree object equal to 1.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void setFire(){
		fire = 1;
	}

	/**
	* A method that increases the fire of Tree objects. Increases the fire of
	* the Tree object until it reaches 9, and holds it at 9 after that.
	* Once the fire is at 9 for that Tree object, the method calls the
	* decreaseHeight method, which decreases the height of the Tree object.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void increaseFire(){
		if(fire + 1 > 9){
			decreaseHeight();
		}
		else{
			fire = fire + 1;
		}
	}

	/**
	* A method that extinguishes the fire of Tree objects. Sets the fire attribute
	* of the Tree object equal to 0.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void extFire(){
		this.fire = 0;
	}

	/**
	* A method that decreases the height of Tree objects. Decreases the height by 1
	* each time it is called. Once the height of the Tree object is 0, the method
	* sets the fire attribute of that Tree object equal to 0, and changes the
	* variable isBurntDown to true.
	* Takes no parameters.
	* Returns nothing.
	**/
	public void decreaseHeight(){
		height = height - 1;
		if (height == 0){
			isBurntDown = true;
			fire = 0;
		}
	}
}

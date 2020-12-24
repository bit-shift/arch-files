public class SimulationTwo{

  private int width;
	private int height;
	private Tree[][] trees;

  public SimulationTwo(int height, int width, int seed){
    this.height = height;
    this.width = width;
    Tree treestance = new Tree(height, width);
    trees = treestance.getTree();
    generateTerrain(seed);
  }

  public void showHeights(){
    for(int r = 0; r < height + 2; r++){
      for(int c = 0; c < width + 2; c++){
        if((r == 0 && c == 0) || (r == height + 1 && c == 0) || (r == 0 && c == width + 1) || (r == width + 1 && c == width + 1)){
          System.out.print("+");
        }
        else if(r == 0 || r == height + 1){
          if(c == 1){
            System.out.print("-");
          }
          else{
            System.out.print("--");
          }
        }
        else if(c == 0 || c == width + 1){
          System.out.print("|");
        }
        else if(trees[r-1][c-1].height == 0){
          System.out.print(" ");
        }
        else{
          System.out.print(trees[r-1][c-1].height);
        }

        if((c > 0 && c < width) && r != 0 && r != height + 1){
          System.out.print(" ");
        }
      }
      System.out.println();
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

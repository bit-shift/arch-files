public class OrderedPair {
  int x = 0;
  int y = 0;
  public OrderedPair(int x, int y){
    setOrderedPair(x,y);
  }

  public int[] getOrderedPair(){
    int[] returnValues = new int[2];
    returnValues[0] = this.x;
    returnValues[1] = this.y;
    return returnValues;
  }

  public int getSmall(){
    return this.x;
  }

  public int getLarge(){
    return this.y;
  }

  public void setOrderedPair(int x, int y){
    if(x <= y){
      this.x = x;
      this.y = y;
    }
    else{
      this.y = x;
      this.x = y;
    }
  }

  public String toString(){
    String toString = "("+this.x+", "+this.y+")";
    return toString;
  }

  public boolean equals(OrderedPair pair1){
    boolean check = false;
    if(pair1.getSmall() == this.x && pair1.getLarge() == this.y){
      check = true;
    }
    return check;
  }
}

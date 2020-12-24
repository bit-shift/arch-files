public void windMovement(int wind, int days){
  for(int i = 1; i <= days; i++){
    if(wind == 0){
      for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
          if(trees[r][c].fire > 0){
            trees[r][c].increaseFire();
          }
        }
      }
    }
    else if(wind == 1 || wind == 4){
      for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
          if(trees[r][c].fire > 0){
            if(wind == 1){
              if(r-1 > -1 && trees[r-1][c].height > 0 && trees[r-1][c].fire > 0){
                trees[r][c].increaseFire();
              }
              else if(r-1 > -1 && trees[r-1][c].height > 0 && trees[r-1][c].fire == 0){
                trees[r][c].increaseFire();
                trees[r-1][c].setFire();
              }
              else if(trees[r][c].height > 0){
                trees[r][c].increaseFire();
              }
            }
            else if(wind == 4){
              if(c-1 > -1 && trees[r][c-1].height > 0 && trees[r][c-1].fire > 0){
                trees[r][c].increaseFire();
              }
              else if(c-1 > -1 && trees[r][c-1].height > 0 && trees[r][c-1].fire == 0){
                trees[r][c].increaseFire();
                trees[r][c-1].setFire();
              }
              else if(trees[r][c].height > 0){
                trees[r][c].increaseFire();
              }
            }
          }
        }
      }
    }
    else if(wind == 2 || wind == 3){
      for(int r = height - 1; r > -1; r--){
        for(int c = width - 1; c > -1; c--){
          if(trees[r][c].fire > 0){
            if(wind == 2){
              if(c < width-1 && trees[r][c+1].height > 0 && trees[r][c+1].fire > 0){
                trees[r][c].increaseFire();
              }
              else if(c < width-1 && trees[r][c+1].height > 0 && trees[r][c+1].fire == 0){
                trees[r][c].increaseFire();
                trees[r][c+1].setFire();
              }
              else if(trees[r][c].height > 0){
                trees[r][c].increaseFire();
              }
            }
            else if(wind == 3){
              if(r < height - 1 && trees[r+1][c].height > 0 && trees[r+1][c].fire > 0){
                trees[r][c].increaseFire();
              }
              else if(r < height -1  && trees[r+1][c].height > 0 && trees[r+1][c].fire == 0){
                trees[r][c].increaseFire();
                trees[r+1][c].setFire();
              }
              else if(trees[r][c].height > 0){
                trees[r][c].increaseFire();
              }
            }
          }
        }
      }
    }
  }
}

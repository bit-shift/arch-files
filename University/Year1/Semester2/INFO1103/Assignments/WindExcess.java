else if(wind == 2){
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

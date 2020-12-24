String FileName = args[0];

if(FileName.equals("DEFAULT")){
    fileParameters = new int[]{3,20,0,4};
    LIVES_REMAINING = fileParameters[0];
    STEPS_REMAINING = fileParameters[1];
    GOLD_PERSON = fileParameters[2];
    R = fileParameters[3];
    boardString = new String[4];
    boardString[0] = "#@ ##  &4#";
    boardString[1] = "##  # ## #";
    boardString[2] = "###  3#   ";
    boardString[3] = "#######  #";

    String row = boardString[0];

    boardArray = new char[R][row.length()];
    for(int r = 0; r < R; r++){
      row = boardString[r];
      for(int c = 0; c < 10; c++){
        boardArray[r][c] = row.charAt(c);
      }
    }

    positionX = getCurrentXPosition();

    positionY = getCurrentYPosition();




    for(int r = 0; r < 4; r++){
      row = boardString[r];
      for(int c = 0; c < 10; c++){
        if(boardArray[r][c] == '@'){
            destinationY = r;
            destinationX = c;
            break;
        }
      }
    }
}

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

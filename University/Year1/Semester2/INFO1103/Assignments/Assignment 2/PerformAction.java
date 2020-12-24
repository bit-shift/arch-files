input = input.toLowerCase();
Scanner keyboardAction = new Scanner(System.in);

while(!input.equals("help") && !input.equals("board") && !input.equals("status") && !input.equals("left") && !input.equals("right") && !input.equals("up") && !input.equals("down")){
    // ASK THE USER TO RE ENTER AND SAY THAT IT IS NOT A VALID COMMAND
    String[] inputParts = input.split(" ");
    String row;
    String[] check;

    if(inputParts.length == 2 && inputParts[0].equals("save")){
        row = inputParts[1];
        check = row.split("\\.");
        if(check.length == 2 && check[1].equals("txt")){
            try{
                saveGame(row);
            }
            catch(IOException e){
                throw new IllegalArgumentException();
            }
            finally{
                return;
            }
        }
        else{
            throw new IllegalArgumentException();
        }
    }
    else{
        throw new IllegalArgumentException();

    input = keyboardAction.nextLine();
    input = input.toLowerCase();
  }

}

if(input.equals("right")){
    moveTo(getCurrentXPosition() + 1,getCurrentYPosition());
    return;
}
if(input.equals("left")){
    moveTo(getCurrentXPosition() - 1,getCurrentYPosition());
    return;
}
if(input.equals("up")){
    moveTo(getCurrentXPosition(),getCurrentYPosition()-1);
    return;
}
if(input.equals("down")){
    moveTo(getCurrentXPosition(),getCurrentYPosition()+1);
    return;
}
if(input.equals("help")){
    printHelp();
    return;
}
if(input.equals("status")){
    printStatus();
    return;
}
if(input.equals("board")){
    printBoard();
    return;
}




if(inputParts.length == 2){
    if(inputParts[0].equals("save")){
        row = inputParts[1];
        check = row.split("\\.");
        if(check.length == 2 && check[1].equals("txt")){
            try{
                saveGame(row);
            }
            catch(IOException e){
                System.out.printf("Error: Could not save the current game configuration to '%s'.\n", inputParts[1]);
            }
        }
        else{
            System.out.printf("Error: Could not save the current game configuration to '%s'.\n", inputParts[1]);
        }
    }
    else{
        throw new IllegalArgumentException();
    }
}

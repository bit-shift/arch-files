import java.util.Scanner;

public class InputHandler{
    public static void performAction(String input) /*throws IllegalArgumentException*/ {
        // Need to do some stuff with the splitting and consider the save file case
        //toLower(input);
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
                
                return;
              }
              else{
              System.out.println("Error: Could not find command '" + input + "'.");
              System.out.println("To find the list of valid commands, please type 'help'.");
              }
            }
            else{
            System.out.println("Error: Could not find command '" + input + "'.");
            System.out.println("To find the list of valid commands, please type 'help'.");
            }
            input = keyboardAction.nextLine();
            input = input.toLowerCase();

        }
    }

    public static void main(String[] args){
        Scanner keyboard = new Scanner(System.in);
        String answer = keyboard.nextLine();
        performAction(answer);
    }
}

/*

&& !input.equals("board") && !input.equals("status") && !input.equals("left") && !input.equals("right") && !input.equals("up") && !input.equals("down") && input.equals("save")

*/

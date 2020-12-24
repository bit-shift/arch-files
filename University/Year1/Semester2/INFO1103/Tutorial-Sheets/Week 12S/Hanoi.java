public class Hanoi {

    public static void main(String[] args) {
        moveDish(Integer.parseInt(args[0]), 'A', 'B', 'C');
    }
    
    public static void moveDish(int level, char from, char inter, char to) {
        if (level == 1) {
            System.out.println("Disk 1 from rod " + from + " to rod " + to);
        } else {
            moveDish(level - 1, from, to, inter);
            System.out.println("Disk " + level + " from rod " + from + " to rod " + to);
            moveDish(level - 1, inter, from, to);
        }
    }

}
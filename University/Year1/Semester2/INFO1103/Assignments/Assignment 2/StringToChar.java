public class StringToChar {
    public static void main(String[] args) {
        String[] strArr = { "HELLO", "WORLD" };
        String strC = "";
        char[] charArr = new char[strArr.length];
        //char[][] char2D = new char[strArr.length][];

        for (int i = 0; i < strArr.length; i++) {
            strC = strC + strArr[i];
        }
        charArr = strC.toCharArray();
        System.out.println(charArr);

        /*for (char[] char1D : char2D) {
            for (char c : char1D)
                System.out.print(c);

            System.out.println();
        }*/
    }
}

public class QuestionFourC {
 public static void main(String[] args){
   double x=( double )(( int )( 15.0f / ( double )2 ) ) ;
   if ( x < 2 || x > 5){
     int fx = (int )(x) % 3;
     System.out.println("x: " + fx);
     x *= fx;
   }
   System.out.println("x: " + x);
   System.out.println("x: " + 5.5789456795);
 }
}

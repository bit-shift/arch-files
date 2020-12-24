import java.util.Scanner;
import java.lang.Math;

public class Sand {
  public static void main(String[] args) {
    double width, length, height;
    Scanner keyboard = new Scanner(System.in);

    System.out.println("Please enter the width of the room");
    width = keyboard.nextDouble();
    System.out.println("Please enter the length of the room");
    length = keyboard.nextDouble();
    System.out.println("Please enter the height of the room");
    height = keyboard.nextDouble();

    System.out.println("The measurements for the room that you have entered are as follows");
    System.out.println(width+"m x "+length+"m x " +height+ "m");

    double volume;
    volume = width*height*length;
    System.out.println("The volume of the room is " + volume);

    double radius;
    System.out.println("Please enter the radius of the balls to fill the room");
    radius = keyboard.nextDouble();

    double volumeOfBallSpace, volumeOfBall, volumeLeftOver;
    volumeOfBall = (4/3)*3.14151926*java.lang.Math.pow(radius,3);
    volumeOfBallSpace = java.lang.Math.pow(2*radius,3);
    volumeLeftOver = volumeOfBallSpace - volumeOfBall;

    double amountOfBalls, volumeLeftOverRoom, volumeOfSand;
    amountOfBalls = Math.floor(volume/volumeOfBallSpace);
    volumeLeftOverRoom = amountOfBalls*volumeLeftOver;
    volumeOfSand = volumeLeftOverRoom;

    System.out.println("The amount of balls of radius " + radius + " that will fit inside the room is "+ amountOfBalls);
    System.out.println("The amount of sand needed to fill the rest of the room is "+ volumeOfSand+ "m^3"); 
  }
}

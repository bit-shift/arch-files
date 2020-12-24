
import java.util.Arrays;

public class TwoDimensionalArray {

	public static void main(String[] args) {
		int[][] arr = new int[4][3];
		for (int i = 0; i < arr.length; i++) {
			for (int j = 0; j < arr[i].length; j++) {
				arr[i][j] = (int) (Math.random() * 101);
			}
		}

		System.out.println("This 2d-array is:");
		for (int i = 0; i < arr.length; i++) {
			System.out.println(Arrays.toString(arr[i]));
		}

		int row = 1;
		int column = 2;

		System.out.println("The sum of row " + row + " is " + rowSum(arr, row));
		System.out.println("The sum of column " + column + " is " + columnSum(arr, column));
		System.out.println("The sums of each row are " + Arrays.toString(allRowSum(arr)));
		System.out.println("The maximum value in this array is " + max(arr));

	}

	public static int rowSum(int[][] arr, int row) {
		int sum = 0;
		for (int i = 0; i < arr[0].length; i++) {
			sum = sum + arr[row][i];
		}
		return sum;
	}

	public static int columnSum(int[][] arr, int column) {
		int sum = 0;
		for (int i = 0; i < arr.length; i++) {
			sum = sum + arr[i][column];
		}
		return sum;
	}

	public static int[] allRowSum(int[][] arr) {
		int[] rowSums = new int[arr[0].length];
		for (int i = 0; i < rowSums.length; i++) {
			rowSums[i] = 0;
		}
		for (int i = 0; i < arr[0].length; i++) {
			for (int j = 0; j < arr[i].length; j++) {
				rowSums[i] = rowSums[i] + arr[i][j];
			}
		}
		return rowSums;
	}

	public static int max(int[][] arr) {
		int max = arr[0][0];
		for (int i = 0; i < arr.length; i++) {
			for (int j = 0; j < arr[i].length; j++) {
				if (arr[i][j] > max) {
					max = arr[i][j];
				}
			}
		}
		return max;
	}

}

import java.util.Arrays;

public class findMultiplesOf {

	public static void main(String[] args) {
		int num =3;
		int[] arr={12,2,4,5,22};
		int[] result=findMultiplesOf(num,arr);
		System.out.println(Arrays.toString(result));

	}

	public static int[] findMultiplesOf(int num, int[] arr) {
		int[] result=new int[arr.length];
		for(int i=0;i<arr.length;i++){
			result[i]=num*arr[i];
		}
		return result;
	}

}

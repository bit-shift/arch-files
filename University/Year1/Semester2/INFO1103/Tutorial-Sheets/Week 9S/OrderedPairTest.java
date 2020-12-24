
public class OrderedPairTest {

	public static void main(String[] args) {
		testConstructor1();
		testConstructor2();
		testToString();
		testEquals1();
		testEquals2();
		testEquals3();
	}
	
	private static void testConstructor1() {
		OrderedPair op = new OrderedPair(1, 2);
		if(op.getFirst() == 1 && op.getSecond() == 2) {
			System.out.println("testConstructor1 passed");
		} else {
			System.out.println("testConstructor1 failed");
		}
	}
	
	private static void testConstructor2() {
		OrderedPair op = new OrderedPair(2, 1);
		if(op.getFirst() == 1 && op.getSecond() == 2) {
			System.out.println("testConstructor2 passed");
		} else {
			System.out.println("testConstructor2 failed");
		}
	}
	
	private static void testToString() {
		OrderedPair op = new OrderedPair(1, 2);
		if(op.toString().equals("(1.0, 2.0)")) {
			System.out.println("testToString passed");
		} else {
			System.out.println("testToString failed");
		}
	}
	
	private static void testEquals1() {
		OrderedPair op1 = new OrderedPair(1, 2);
		OrderedPair op2 = new OrderedPair(1, 2);
		if(op1.equals(op2)) {
			System.out.println("testEquals1 passed");
		} else {
			System.out.println("testEquals1 failed");
		}
	}
	
	private static void testEquals2() {
		OrderedPair op1 = new OrderedPair(1, 2);
		OrderedPair op2 = new OrderedPair(2, 1);
		if(op1.equals(op2)) {
			System.out.println("testEquals2 passed");
		} else {
			System.out.println("testEquals2 failed");
		}
	}
	
	private static void testEquals3() {
		OrderedPair op1 = new OrderedPair(1, 2);
		OrderedPair op2 = new OrderedPair(3, 4);
		if(!op1.equals(op2)) {
			System.out.println("testEquals3 passed");
		} else {
			System.out.println("testEquals3 failed");
		}
	}

}

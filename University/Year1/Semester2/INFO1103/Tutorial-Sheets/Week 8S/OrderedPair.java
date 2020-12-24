
public class OrderedPair {
	private double first;
	private double second;
	
	public OrderedPair(double first, double second) {
		if(second < first) {
			this.second = first;
			this.first = second;
		} else {
			this.first = first;
			this.second = second;
		}
	}

	public double getFirst() {
		return first;
	}

	public double getSecond() {
		return second;
	}
	
	/**
	 * Gets a String of the form (first, second)
	 */
	public String toString() {
		return "(" + first + ", " + second + ")";
	}
	
	/**
	 * Two OrderedPair objects are equal if they have the same first and second values.
	 */
	public boolean equals(OrderedPair other) {
		return equal(this.first, other.first) &&
				equal(this.second, other.second);
	}
	
	/**
	 * Checks if two double values are equal.
	 * 
	 * To check if they are equal, see if the difference between the two numbers
	 * is small enough. This can be done by checking if the difference is less
	 * than an arbitrary number (such as < 0.0001), however to make sure this
	 * works for comparing really small numbers, use Math.ulp(), which will
	 * compare against a number small enough to be relevant to this calculation.
	 */
	private boolean equal(double a, double b) {
		double diff = Math.abs(a - b);
		return (diff < (10 * Math.ulp(a)));
	}
	
	/*
	 * An alternate and simpler method, that works in most cases:
	 * 
	 * public boolean equals(double a, double b) {
	 * 		return Math.abs(a - b) < 0.0001;
	 * }
	 */
}

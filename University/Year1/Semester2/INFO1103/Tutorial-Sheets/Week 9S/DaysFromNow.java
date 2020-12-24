public class DaysFromNow {

	public static void main(String[] args) {
		int currentDayIndex = Integer.parseInt(args[0]);
		int numDaysAhead = Integer.parseInt(args[1]);
		
		Weekday[] allDays = Weekday.values();
		
		int dayIndex = currentDayIndex + numDaysAhead;
		dayIndex = wrap(dayIndex, allDays.length);
		Weekday dayOfWeek = allDays[dayIndex];
		
		System.out.printf("In %d day(s) it will be a %s.\n", numDaysAhead, dayOfWeek);
	}
	
	/**
	 * Wraps a number x into the range 0 to (n-1).
	 * 
	 * e.g. for n = 3:
	 * -4 -> 2
	 * -3 -> 0
	 * -2 -> 1
	 * -1 -> 2
	 *  0 -> 0
	 *  1 -> 1
	 *  2 -> 2
	 *  3 -> 0
	 *  4 -> 1
	 * etc...
	 * 
	 */
	public static int wrap(int x, int n) {
		return (((x % n) + n) % n);
	}

}

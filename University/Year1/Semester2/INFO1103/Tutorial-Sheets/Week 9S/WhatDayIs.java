public class WhatDayIs {
	
	public static void main(String[] args) {
		int dayOfWeekIndex = Integer.parseInt(args[0]);
		Weekday[] allWeekdays = Weekday.values();
		
		if(dayOfWeekIndex < 0 || dayOfWeekIndex >= allWeekdays.length) {
			System.out.println("Invalid day of the week.");
			return;
		}
		
		Weekday dayOfWeek = allWeekdays[dayOfWeekIndex];
		System.out.printf("Day %d of the week is %s. ", dayOfWeekIndex, dayOfWeek);
		
		boolean isWeekend = (dayOfWeek == Weekday.SATURDAY || dayOfWeek == Weekday.SUNDAY);
		if(isWeekend) {
			System.out.println("It is a weekend.");
		} else {
			System.out.println("It is not a weekend.");
		}
	}
	
}

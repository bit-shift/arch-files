public class WhatDayIs{
  public static void main(String[] args){
    int indexOfDay = Integer.parseInt(args[0]);
    Weekday[] days = Weekday.values();
    if(indexOfDay < 0 || indexOfDay >= days.length) {
			System.out.println("Invalid day of the week.");
			return;
		}

    Weekday dayOfWeek = days[indexOfDay];
		System.out.printf("Day %d of the week is %s. ", indexOfDay, dayOfWeek);

		boolean isWeekend = (dayOfWeek == Weekday.SATURDAY || dayOfWeek == Weekday.SUNDAY);
		if(isWeekend) {
			System.out.println("It is a weekend.");
		} else {
			System.out.println("It is not a weekend.");
		}
  }

}

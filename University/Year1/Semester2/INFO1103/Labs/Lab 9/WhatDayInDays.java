public class WhatDayInDays{
  public static void main(String[] args){
    int indexOfCurrentDay = Integer.parseInt(args[0]);
    int increaseByDays = Integer.parseInt(args[1]);
    int daysInc = increaseByDays % 7;

    Weekday[] days = Weekday.values();

    if(indexOfCurrentDay < 0 || indexOfCurrentDay >= days.length) {
			System.out.println("Invalid day of the week.");
			return;
		}

    if(increaseByDays < 0){
      System.out.println("Invalid increase of days.");
      return;
    }

    Weekday currentDayOfWeek = days[indexOfCurrentDay];
    Weekday newDayOfWeek = days[indexOfCurrentDay+daysInc];
		System.out.printf("Day %d of the week is %s, and in %d days time it will be %s\n.", indexOfCurrentDay, currentDayOfWeek, increaseByDays, newDayOfWeek);
  }

}

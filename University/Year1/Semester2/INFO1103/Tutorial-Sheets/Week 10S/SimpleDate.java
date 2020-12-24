import java.text.DecimalFormat;

/**
 * A simple implementation of a date. There is no implemented validation of
 * day/month ranges, so use at your own risk.
 */
public class SimpleDate {
	private int day, month, year;

	public SimpleDate(int day, int month, int year) {
		this.day = day;
		this.month = month;
		this.year = year;
	}
	
	public boolean isLessThan(SimpleDate other) {
		return this.year <= other.year && this.month <= other.month && this.day < other.day;
	}
	public boolean isLessThanOrEqualTo(SimpleDate other) {
		return this.year <= other.year && this.month <= other.month && this.day <= other.day;
	}
	public boolean isEqualTo(SimpleDate other) {
		return this.year == other.year && this.month == other.month && this.day == other.day;
	}
	public boolean isGreaterThanOrEqualTo(SimpleDate other) {
		return this.year >= other.year && this.month >= other.month && this.day >= other.day;
	}
	public boolean isGreaterThan(SimpleDate other) {
		return this.year >= other.year && this.month >= other.month && this.day > other.day;
	}
	
	public String toString() {
		DecimalFormat dayFormat = new DecimalFormat("00");
		return dayFormat.format(day) + "/" + dayFormat.format(month) + "/" + year;
	}
	
	public int getDay() {
		return day;
	}
	public void setDay(int day) {
		this.day = day;
	}

	public int getMonth() {
		return month;
	}
	public void setMonth(int month) {
		this.month = month;
	}

	public int getYear() {
		return year;
	}
	public void setYear(int year) {
		this.year = year;
	}
}


public class PhoneNumber {
	private String number;
	private UsageType usageType;
	
	public PhoneNumber(String number, UsageType usageType) {
		this.number = number;
		this.usageType = usageType;
	}

	public String getNumber() {
		return number;
	}
	public void setNumber(String number) {
		this.number = number;
	}

	public UsageType getUsageType() {
		return usageType;
	}
	public void setUsageType(UsageType usageType) {
		this.usageType = usageType;
	}
	
	public String toString() {
		return number + " (" + usageType + ")";
	}
}

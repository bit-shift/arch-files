
public class Email {
	private String address;
	private UsageType usageType;
	
	public Email(String address, UsageType usageType) {
		this.address = address;
		this.usageType = usageType;
	}

	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}

	public UsageType getUsageType() {
		return usageType;
	}
	public void setUsageType(UsageType usageType) {
		this.usageType = usageType;
	}
	
	public String toString() {
		return address + " (" + usageType + ")";
	}
}

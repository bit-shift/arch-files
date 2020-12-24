
public class Address {
	private String[] lines;
	private int postcode;
	private String state;
	private String country;
	
	public Address(String line1, String line2, int postcode, String state, String country) {
		this.lines = new String[] {line1, line2};
		this.postcode = postcode;
		this.state = state;
		this.country = country;
	}

	public String getFirstLine() {
		return lines[0];
	}
	public void setFirstLine(String line) {
		this.lines[0] = line;
	}
	
	public String getSecondLine() {
		return lines[1];
	}
	public void setSecondLine(String line) {
		this.lines[1] = line;
	}
	
	public int getPostcode() {
		return postcode;
	}
	public void setPostcode(int postcode) {
		this.postcode = postcode;
	}

	public String getState() {
		return state;
	}
	public void setState(String state) {
		this.state = state;
	}

	public String getCountry() {
		return country;
	}
	public void setCountry(String country) {
		this.country = country;
	}
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(lines[0]);
		if(lines[1] != null && !lines[1].isEmpty()) {
			sb.append(", ").append(lines[1]);
		}
		sb.append(", ").append(postcode);
		sb.append(", ").append(state);
		sb.append(", ").append(country);
		return sb.toString();
	}
}

import java.util.Arrays;


public class Contact {
	private String name;
	private Address address;
	private Email[] emailAddresses;
	private PhoneNumber[] phoneNumbers;
	
	public Contact(String name) {
		this(name, null);
	}
	
	public Contact(String name, Address address) {
		this.name = name;
		this.address = address;
		this.emailAddresses = new Email[0];
		this.phoneNumbers = new PhoneNumber[0];
	}
	
	public void addEmailAddress(Email newEmail) {
		int currentNumEmails = emailAddresses.length;
		emailAddresses = Arrays.copyOf(emailAddresses, currentNumEmails + 1);
		emailAddresses[currentNumEmails] = newEmail;
	}
	
	public void addPhoneNumber(PhoneNumber newNumber) {
		int currentNumPhoneNumbers = phoneNumbers.length;
		phoneNumbers = Arrays.copyOf(phoneNumbers, currentNumPhoneNumbers + 1);
		phoneNumbers[currentNumPhoneNumbers] = newNumber;
	}

	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}

	public Address getAddress() {
		return address;
	}
	public void setAddress(Address address) {
		this.address = address;
	}

	public Email[] getEmailAddresses() {
		return emailAddresses;
	}

	public PhoneNumber[] getPhoneNumbers() {
		return phoneNumbers;
	}
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(name).append(":\n");
		sb.append("\t").append("Address: ").append(address.toString()).append("\n");
		sb.append("\t").append("Email addresses:").append("\n");
		for(int i = 0; i < emailAddresses.length; i++) {
			sb.append("\t\t").append(emailAddresses[i].toString()).append("\n");
		}
		sb.append("\t").append("Phone numbers:").append("\n");
		for(int i = 0; i < phoneNumbers.length; i++) {
			sb.append("\t\t").append(phoneNumbers[i].toString()).append("\n");
		}
		return sb.toString();
	}
}

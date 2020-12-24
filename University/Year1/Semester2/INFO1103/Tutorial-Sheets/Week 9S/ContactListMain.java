
public class ContactListMain {

	public static void main(String[] args) {
		ContactList list = new ContactList();
		
		Contact pat = new Contact("Patrick");
		Address patsAddress = new Address("42 Wallaby Way", "Sydney", 2000, "NSW", "Australia");
		pat.setAddress(patsAddress);
		
		pat.addEmailAddress(new Email("p.sherman@email.com", UsageType.PERSONAL));
		pat.addEmailAddress(new Email("p.sherman@work.com", UsageType.WORK));
		
		pat.addPhoneNumber(new PhoneNumber("0412345678", UsageType.OTHER));
		
		list.addContact(pat);
		
		Contact homer = new Contact("Homer Simpson");
		Address homerAddress = new Address("742 Evergreen Terrace", "Springfield", 12345, "Oregon", "USA");
		homer.setAddress(homerAddress);
		
		homer.addEmailAddress(new Email("ChunkyLover53@aol.com", UsageType.PERSONAL));
		
		homer.addPhoneNumber(new PhoneNumber("555-8707", UsageType.PERSONAL));
		homer.addPhoneNumber(new PhoneNumber("555-7334", UsageType.WORK));
		
		list.addContact(homer);
		
		list.printContacts();
	}

}

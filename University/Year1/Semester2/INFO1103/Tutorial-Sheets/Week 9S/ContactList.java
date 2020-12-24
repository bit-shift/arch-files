import java.util.Arrays;


public class ContactList {
	private Contact[] contacts;
	
	public ContactList() {
		contacts = new Contact[0];
	}
	
	public void addContact(Contact contact) {
		//Get the current size of the contacts list
		int curNumContacts = contacts.length;
		
		//Copy contacts into a new array that is 1 bigger than current array
		contacts = Arrays.copyOf(contacts, curNumContacts + 1);
		
		//Set the last element to the new contact
		contacts[curNumContacts] = contact;
	}
	
	public void printContacts() {
		int i = 0;
		while(i < contacts.length) {
			System.out.println(contacts[i].toString());
			i++;
		}
	}
}

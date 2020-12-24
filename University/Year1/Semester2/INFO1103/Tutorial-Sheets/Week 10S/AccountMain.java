public class AccountMain {

	public static void main(String[] args) {
		
		System.out.println("Testing Account\n");
		
		Account account = new Account(123456789, 123456, 1.5f, 0.35);
		
		account.makeTransaction(new Transaction(new SimpleDate(3, 5, 2012), "Salary Crazy clown airlines", 451));
		account.makeTransaction(new Transaction(new SimpleDate(6, 5, 2012), "HD Max virtual cinema", -30));
		account.makeTransaction(new Transaction(new SimpleDate(6, 5, 2012), "HD Max virtual cinema candy", -8));
		account.makeTransaction(new Transaction(new SimpleDate(6, 5, 2012), "Hip froyo", -16.1));
		account.makeTransaction(new Transaction(new SimpleDate(6, 5, 2012), "Dodgem car city", -18.75));
		account.makeTransaction(new Transaction(new SimpleDate(6, 5, 2012), "Taximeter co services", -47));
		account.makeTransaction(new Transaction(new SimpleDate(17, 5, 2012), "Salary Crazy clown airlines", 529));
		account.makeTransaction(new Transaction(new SimpleDate(18, 5, 2012), "Towering property rental", -200));
		account.makeTransaction(new Transaction(new SimpleDate(19, 5, 2012), "Foodsworth shopping", -129.98));
		account.gainInterest(new SimpleDate(31, 5, 2012));
		SimpleDate start = new SimpleDate(1, 5, 2012);
		SimpleDate end = new SimpleDate(31, 5, 2012);
		Invoice invoice = account.generateInvoice(start, end);
		invoice.printStatement();
		
		System.out.println("\nTesting Saver Account\n");
		
		SaverAccount saver = new SaverAccount(987654321, 654321, 1.5f, 2.3f, 0.35);
		
		saver.makeTransaction(new Transaction(new SimpleDate(3, 5, 2012), "Salary Crazy clown airlines", 451));
		saver.makeTransaction(new Transaction(new SimpleDate(6, 5, 2012), "HD Max virtual cinema", -30));
		saver.makeTransaction(new Transaction(new SimpleDate(17, 5, 2012), "Salary Crazy clown airlines", 529));
		saver.gainInterest(new SimpleDate(31, 5, 2012));
		SimpleDate start2 = new SimpleDate(1, 5, 2012);
		SimpleDate end2 = new SimpleDate(31, 5, 2012);
		Invoice invoice2 = saver.generateInvoice(start, end);
		invoice2.printStatement();
		
	}

}

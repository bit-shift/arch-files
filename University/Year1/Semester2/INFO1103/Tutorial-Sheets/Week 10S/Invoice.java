import java.util.ArrayList;

public class Invoice {
	private double startBalance;
	private SimpleDate startDate;
	private SimpleDate endDate;
	private Account bankAccount;
	
	public Invoice(double startBalance, SimpleDate startDate, SimpleDate endDate, Account bankAccount) {
		this.startBalance = startBalance;
		this.startDate = startDate;
		this.endDate = endDate;
		this.bankAccount = bankAccount;
	}
	
	public void printStatement() {
		System.out.println(bankAccount.toString());
		System.out.println();
		System.out.println("Statement for " + startDate + " to " + endDate);
		System.out.println();
		System.out.printf("%-12s%-30s%-10s%-10s%-10s\n", "Date:", "Details:", "Debit:", "Credit:", "Balance:");
		printTransaction(startDate, "Opening balance", null, null, startBalance);
		
		double balance = startBalance;
		ArrayList<Transaction> transactions = bankAccount.getTransactionsInRange(startDate, endDate);
		for(int i = 0; i < transactions.size(); i++) {
			Transaction tr = transactions.get(i);
			Double debit = null;
			Double credit = null;
			if(tr.getAmount() > 0) {
				credit = tr.getAmount();
			} else {
				debit = Math.abs(tr.getAmount());
			}
			balance = balance + tr.getAmount();
			printTransaction(tr.getDate(), tr.getDescription(), debit, credit, balance);
		}
	}
	
	private void printTransaction(SimpleDate date, String details, Double debit, Double credit, double balance) {
		String debitString = "";
		if(debit != null) {
			debitString = String.format("$%.2f", debit);
		}
		String creditString = "";
		if(credit != null) {
			creditString = String.format("$%.2f", credit);
		}
		String balanceString = String.format("$%.2f", balance);
		System.out.printf("%-12s%-30s%-10s%-10s%-10s\n", date, details, debitString, creditString, balanceString);
	}
}

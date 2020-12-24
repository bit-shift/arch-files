public class Transaction {
	private SimpleDate date;
	private String description;
	private double amount;
	
	public Transaction(SimpleDate date, String description, double amount) {
		this.date = date;
		this.description = description;
		this.amount = amount;
	}
	
	public SimpleDate getDate() {
		return date;
	}
	
	public String getDescription() {
		return description;
	}
	
	public double getAmount() {
		return amount;
	}
}

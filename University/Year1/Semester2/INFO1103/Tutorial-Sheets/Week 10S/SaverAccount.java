import java.util.ArrayList;

public class SaverAccount extends Account {

	private float bonusInterestRate;

	public SaverAccount(long accountNumber, int bsb, float interestRate, float bonusInterestRate, double initialBalance) {
		super(accountNumber, bsb, interestRate, initialBalance);
		this.bonusInterestRate = bonusInterestRate;
	}
	
	/**
	 * override the gainInterest() method in Account class
	 */
	public void gainInterest(SimpleDate date) {
		double balanceAtDate = getBalanceAt(date);
		double balanceAtFirstDayOfMonth = getBalanceAt(new SimpleDate(1, date.getMonth(), date.getYear()));
		super.gainInterest(date);
		if (balanceAtDate - balanceAtFirstDayOfMonth >= 500) {
			double interest = balanceAtDate * (this.bonusInterestRate / 100 / 12);
			makeTransaction(new Transaction(date, "Bonus interest", interest));
		}
		
	}
}

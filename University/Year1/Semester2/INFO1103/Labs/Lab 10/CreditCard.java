public class CreditCard extends Card{

  String bankName;
  String expiryDate;
  long cardNum;
  int securityChip;

  public CreditCard(String name, String bankName, long cardNum, String expiryDate, int securityChip){
    setName(name);
    setBankName(bankName);
    setCardNum(cardNum);
    setExpiryDate(expiryDate);
    setSecurityChip(securityChip);
  }

  public void setName(String name){
    super(name);
  }

  public void setBankName(String bankName){
    this.bankName = bankName;
  }

  public void setCardNum(long cardNum){
    this.cardNum = cardNum;
  }

  public void setExpiryDate(String expiryDate){
    this.expiryDate = expiryDate;
  }

  public void setSecurityChip(int securityChip){
    this.securityChip = securityChip;
  }
}

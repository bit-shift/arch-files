public class License extends Card{

  String address;
  long cardNum;
  String issueState;
  long licenseNum;

  public License(String name, String address, long cardNum, String issueState, long licenseNum){
    setName(name);
    setAddress(address);
    setCardNum(cardNum);
    setIssueState(issueState);
    setLicenseNum(licenseNum);
  }

  public void setName(String name){
    super(name);
  }

  public void setAddress(String address){
    this.address = address;
  }

  public void setCardNum(long cardNum){
    this.cardNum = cardnum;
  }

  public void setIssueState(String issueState){
    this.issueState = issueState;
  }

  public void setLicenseNum(long licenseNum){
    this.licenseNum = licenseNum;
  }
}

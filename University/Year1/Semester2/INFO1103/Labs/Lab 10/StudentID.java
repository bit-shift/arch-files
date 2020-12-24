public class StudentID extends Card{

  long studentID;
  String issueDate;
  long magneticStrip;

  public StudentID(String name, long studentID, String issueDate, long magneticStrip){
    setName(name);
    setStudentID(studentID);
    setIssueDate(issueDate);
    setMagneticStrip(magneticStrip);
  }

  public void setName(String name){
    super(name);
  }

  public void setStudentID(long studentID){
    this.studentID = studentID;
  }

  public void setIssueDate(String issueDate){
    this.issueDate = issueDate;
  }

  public void setMagneticStrip(long magneticStrip){
    this.magneticStrip = magneticStrip;
  }
}

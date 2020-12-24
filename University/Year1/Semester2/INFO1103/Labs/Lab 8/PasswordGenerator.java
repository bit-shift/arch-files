public class PasswordGenerator{

  public PasswordGenerator(boolean useLetters, boolean useNumbers, boolean useSymbols){
    if(useLetters && useNumbers && useSymbols){
      PasswordGenerator();
    }
    else //if(!useLetters && !useNumbers && !useSymbols)
    {
      throw new ExceptionGenerator();
    }
  }

  public PasswordGenerator(){
    
  }
}

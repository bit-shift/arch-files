public class Pet{

  String name;
  String[] nicknames;
  int age;
  String species;
  boolean trained;
  public Pet(String name, String[] nicknames, int age, String species, boolean trained){
    setPet(name, nicknames, age, species, trained);
  }

  public void setPet(String name, String[] nicknames, int age, String species, boolean trained){
    this.name = name;
    this.age = age;
    this.species = species;
    this.trained = trained;
    this.nicknames = nicknames;
  }

  public void setName(String name){
    this.name = name;
  }

  public void setAge(int age){
    this.age = age;
  }

  public void setSpecies(String species){
    this.species = species;
  }

  public void setTrained(boolean trained){
    this.trained = trained;
  }

  public String getName(){
    return name;
  }

  public String[] getNicknames(){
    return nicknames;
  }

  public int getAge(){
    return age;
  }

  public String getSpecies(){
    return species;
  }

  public boolean getTrained(){
    return trained;
  }

  public boolean equal(Pet pet){
    if(this.name.equals(pet.getName()) && this.age == pet.getAge() && this.species.equals(pet.getSpecies())){
      return true;
    }
    return false;
  }

  public void addNickname(String nickname){
    if(nicknames.length == 0){
      String[] nicknamesNew = new String[1];
      nicknamesNew[0] = nickname;
      this.nicknames = nicknamesNew;
    }
  }

  public boolean hasNickname(String nickname){
    boolean check = false;
    for(int i = 0; i < nicknames.length; i++){
      if(nicknames[i].equals(nickname)){
        check = true;
        return check;
      }
    }
    return check;
  }


}

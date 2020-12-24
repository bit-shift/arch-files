class Person{
  public String name;
  public int age;

  public Person(String name, int age){
    setName(name);
    setAge(age);
  }

  public void setName(String name){
    this.name = name;
  }

  public void setAge(int age){
    this.age = age;
  }
}

public class PersonSearch{
  public static void main(String[] args){
    Person[] people = new Person[] {
      new Person("Alice", 32),
      new Person("Bob", 51),
      new Person("Carol", 15),
      new Person("Dylan", 5),
      new Person("Erin", 25),
      new Person("Frank", 48),
    };

    Person youngest = findYoungest(people);
    System.out.println("Youngest: " + youngest.name);
  }

  public static Person findYoungest(Person[] people){
    Person youngestPerson = people[0];
    for(int i = 0; i < people.length; i++){
      if(people[i].age < youngestPerson.age){
        youngestPerson = people[i];
      }
    }
    return youngestPerson;
  }
}

public class PersonSearchA {

	public static void main(String[] args) {
		Person[] people = new Person[] { new Person("Alice", 32), new Person("Bob", 51), new Person("Carol", 15), new Person("Dylan", 5), new Person("Erin", 25), new Person("Frank", 48) };

		Person youngest = findYoungest(people);
		System.out.println("Youngest: " + youngest.getName());
		String name = "Erin";
		int age = findAgeOf(name, people);
		System.out.println("The age of " + name + " is " + age);
	}

	public static int findAgeOf(String name, Person[] people) {
		int age = -1;
		for (int i = 0; i < people.length; i++) {
			if (people[i].getName().equals(name)) {
				age = people[i].getAge();
				break;
			}
		}
		return age;
	}

	public static Person findYoungest(Person[] people) {
		Person YoungestPerson = null;
		for (int i = 0; i < people.length; i++) {
			if (i == 0) {
				YoungestPerson = people[i];
			} else {
				if (people[i].getAge() < YoungestPerson.getAge()) {
					YoungestPerson = people[i];
				}
			}
		}
		return YoungestPerson;
	}

}

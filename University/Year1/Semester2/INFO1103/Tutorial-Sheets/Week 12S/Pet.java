import java.util.ArrayList;

public class Pet {
	private String name;
	private int age;
	private String species;
	private boolean houseTrained;
	
	private ArrayList<String> nicknames;
	
	public Pet(String name, int age, String species, boolean houseTrained) {
		this.name = name;
		this.age = age;
		this.species = species;
		this.houseTrained = houseTrained;
		
		this.nicknames = new ArrayList<String>();
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}

	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}

	public boolean isHouseTrained() {
		return houseTrained;
	}
	public void setHouseTrained(boolean houseTrained) {
		this.houseTrained = houseTrained;
	}

	public String getSpecies() {
		return species;
	}

	public ArrayList<String> getNicknames() {
		return nicknames;
	}

	public void addNickname(String nickname) {
		if(hasNickname(nickname)) {
			return;
		}
		nicknames.add(nickname);
	}
	
	public boolean hasNickname(String nickname) {
		if(nicknames.contains(nickname)) {
			return true;
		} else {
			return false;
		}
	}

	public boolean equals(Pet other) {
		if(other == null) {
			return false;
		}
		return (this.name.equals(other.name) &&
				this.species.equals(other.species) &&
				this.age == other.age);
	}
	
	public static void main(String[] args) {
			
			Pet p = new Pet("Milo", 3, "Cat", true);
			p.addNickname("MyMy");
			p.addNickname("MoMo");
			System.out.println(p.hasNickname("MoMo"));
			System.out.println(p.getNicknames());
	}
}


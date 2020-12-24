import java.util.Arrays;


public class Pet {
	private String name;
	private int age;
	private String species;
	private boolean houseTrained;
	
	private int numNicknames;
	private String[] nicknames;
	
	public Pet(String name, int age, String species, boolean houseTrained) {
		this.name = name;
		this.age = age;
		this.species = species;
		this.houseTrained = houseTrained;
		
		this.numNicknames = 0;
		this.nicknames = new String[numNicknames];
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

	public String[] getNicknames() {
		return nicknames;
	}

	public void addNickname(String nickname) {
		if(hasNickname(nickname)) {
			return;
		}
		// Adding a new array position requires creating an entirely new array!
		// copy the old nicknames into a new array that is 1 bigger
		nicknames = Arrays.copyOf(nicknames, numNicknames + 1);
		// set the last position of the array to the new nickname
		nicknames[numNicknames] = nickname;
		numNicknames = numNicknames + 1;
	}
	
	public boolean hasNickname(String nickname) {
		int index = 0;
		while(index < nicknames.length) {
			if(nicknames[index].equalsIgnoreCase(nickname)) {
				return true;
			}
			index++;
		}
		return false;
	}

	public boolean equals(Pet other) {
		if(other == null) {
			return false;
		}
		return (this.name.equals(other.name) &&
				this.species.equals(other.species) &&
				this.age == other.age);
	}
}

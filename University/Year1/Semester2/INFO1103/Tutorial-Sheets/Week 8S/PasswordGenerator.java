import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Random;

public class PasswordGenerator {
	public static final int passwordLength = 12;
	
	private final String symbols = "!@#$%^&*_-+=,./?;:";
	
	private boolean useLetters;
	private boolean useNumbers;
	private boolean useSymbols;
	
	private String[] passwords;
	private Random random;
	
	public PasswordGenerator() {
		this(true, true, true);
	}
	
	public PasswordGenerator(boolean useLetters, boolean useNumbers, boolean useSymbols) {
		if(!useLetters && !useNumbers && !useSymbols) {
			throw new IllegalArgumentException("Must use at least one of letters, numbers or symbols");
		}
		
		this.useLetters = useLetters;
		this.useNumbers = useNumbers;
		this.useSymbols = useSymbols;
		
		this.random = new Random();
		generatePasswords();
	}

	/**
	 * Called from the constructor only.
	 * Calling again would do nothing.
	 */
	private void generatePasswords() {
		if(passwords != null) {
			return;
		}
		passwords = new String[10];
		int index = 0;
		while(index < passwords.length) {
			passwords[index] = generatePassword();
			index++;
		}
	}
	
	private String generatePassword() {
		String password = "";
		while(password.length() < passwordLength) {
			password = password + getCharacter();
		}
		return password;
	}
	
	private char getCharacter() {
		boolean[] usage = new boolean[] {useLetters, useNumbers, useSymbols};
		int type = -1;
		// Keep randomly choosing character type until 
		// one is chosen that is allowed to be used
		while(type < 0 || usage[type] == false) {
			type = random.nextInt(3);
		}
		
		// Generate a...
		if(type == 0) { // ...letter
			int letterIndex = random.nextInt('z' - 'a' + 1);
			char letter = (char) ('a' + letterIndex);
			boolean makeUppercase = random.nextBoolean();
			if(makeUppercase) {
				letter = Character.toUpperCase(letter);
			}
			return letter;
		} else if(type == 1) { // ...number
			int numberIndex = random.nextInt(10);
			return (char)('0' + numberIndex);
		} else { // ...symbol
			int symbolIndex = random.nextInt(symbols.length());
			return symbols.charAt(symbolIndex);
		}
	}
	
	public void generateExtraPasswords(int n) {
		String[] extraPasswords = new String[n];
		int index = 0;
		while(index < extraPasswords.length) {
			extraPasswords[index] = generatePassword();
			index++;
		}
		
		File passwordFile = new File("extraPasswords.txt");
		try {
			PrintWriter writer = new PrintWriter(passwordFile);
			for(int i = 0; i < extraPasswords.length; i++) {
				writer.println(extraPasswords[i]);
			}
			writer.close();
		} catch (FileNotFoundException e) {
			System.out.println("Cannot write to " + passwordFile);
		}
	}
	
	public String[] getPasswords() {
		return passwords;
	}
}

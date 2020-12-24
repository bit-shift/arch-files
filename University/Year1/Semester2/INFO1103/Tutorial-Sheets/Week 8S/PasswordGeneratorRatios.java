import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Random;

/**
 * This is a more complex version of the PasswordGenerator class that uses
 * ratios for the amount of letters, numbers and symbols. The original
 * PasswordGenerator class chooses from picking a letter, number or symbol with
 * equal probability. (So should create passwords with equal amounts of letters,
 * numbers and symbols.)
 */
/**
 * @author root
 *
 */
public class PasswordGeneratorRatios {
	public static final int passwordLength = 12;
	
	private final String symbols = "!@#$%^&*_-+=,./?;:";
	
	// 60% letters, 30% numbers and 10% symbols
	private final double letterRatio = 0.6;
	private final double numberRatio = 0.3;
	private final double symbolRatio = 0.1;
	
	private double letterPercentage;
	private double numberPercentage;
	private double symbolPercentage;
	
	private boolean useLetters;
	private boolean useNumbers;
	private boolean useSymbols;
	
	private String[] passwords;
	private Random random;
	
	public PasswordGeneratorRatios() {
		this(true, true, true);
	}
	
	public PasswordGeneratorRatios(boolean useLetters, boolean useNumbers, boolean useSymbols) {
		if(!useLetters && !useNumbers && !useSymbols) {
			throw new IllegalArgumentException("Must use at least one of letters, numbers or symbols");
		}
		
		this.useLetters = useLetters;
		this.useNumbers = useNumbers;
		this.useSymbols = useSymbols;
		determinePercentages();
		
		this.random = new Random();
		generatePasswords();
	}

	
	/**
	 * Ensure the selected ratios result in percentages adding up to 1.0.
	 */
	private void determinePercentages() {
		double sum = 0;
		if(useLetters)
			sum = sum + letterRatio;
		if(useNumbers)
			sum = sum + numberRatio;
		if(useSymbols)
			sum = sum + symbolRatio;
		
		if(useLetters)
			letterPercentage = letterRatio / sum;
		if(useNumbers)
			numberPercentage = numberRatio / sum;
		if(useSymbols)
			symbolPercentage = symbolRatio / sum;
		
		double percentSum = letterPercentage + numberPercentage + symbolPercentage;
		if(Math.abs(1.0 - percentSum) > 0.0001) {
			throw new IllegalStateException("Ratios must add up to 1.0");
		}
	}

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
		double randomRoll = random.nextDouble();
		
		double chanceTotal = letterPercentage;
		if(useLetters && randomRoll < chanceTotal) {
			int letterIndex = random.nextInt('z' - 'a' + 1);
			char letter = (char) ('a' + letterIndex);
			boolean makeUppercase = random.nextBoolean();
			if(makeUppercase) {
				letter = Character.toUpperCase(letter);
			}
			return letter;
		}
		
		chanceTotal = chanceTotal + numberPercentage;
		if(useNumbers && randomRoll < chanceTotal) {
			int numberIndex = random.nextInt(10);
			return (char)('0' + numberIndex);
		}
		
		chanceTotal = chanceTotal + symbolPercentage;
		if(useSymbols && randomRoll < chanceTotal) {
			int symbolIndex = random.nextInt(symbols.length());
			return symbols.charAt(symbolIndex);
		}
		
		throw new IllegalStateException("Code should never reach here if percentages add up to 1.0");
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

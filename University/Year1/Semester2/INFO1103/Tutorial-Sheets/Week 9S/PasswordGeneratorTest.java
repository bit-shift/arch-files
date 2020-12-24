import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class PasswordGeneratorTest {

	public static void main(String[] args) {
		testNumPasswords();
		testPasswordLength();
		testLetters();
		testNumbers();
		testSymbols();
		testFileCreation();
		testFileLength();
	}
	
	private static void testNumPasswords() {
		PasswordGenerator pGen = new PasswordGenerator();
		if(pGen.getPasswords().length == 10) {
			System.out.println("testNumPasswords passed");
		} else {
			System.out.println("testNumPasswords failed");
		}
	}
	
	private static void testPasswordLength() {
		PasswordGenerator pGen = new PasswordGenerator();
		for(int i = 0; i < 10; i++) {
			if(pGen.getPasswords()[i].length() != PasswordGenerator.passwordLength) {
				System.out.println("testPasswordLength failed");
				return;
			}
		}
		System.out.println("testPasswordLength passed");
	}
	
	private static void testLetters() {
		PasswordGenerator pGen = new PasswordGenerator(true, false, false);
		for(int i = 0; i < 10; i++) {
			for(int c = 0; c < pGen.getPasswords()[i].length(); c++) {
				String validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
				char ch = pGen.getPasswords()[i].charAt(c);
				if(!validChars.contains(String.valueOf(ch))) {
					System.out.println("testLetters failed: " + pGen.getPasswords()[i]);
					return;
				}
			}
		}
		System.out.println("testLetters passed");
	}
	
	private static void testNumbers() {
		PasswordGenerator pGen = new PasswordGenerator(false, true, false);
		for(int i = 0; i < 10; i++) {
			for(int c = 0; c < pGen.getPasswords()[i].length(); c++) {
				String validChars = "0123456789";
				char ch = pGen.getPasswords()[i].charAt(c);
				if(!validChars.contains(String.valueOf(ch))) {
					System.out.println("testNumbers failed: " + pGen.getPasswords()[i]);
					return;
				}
			}
		}
		System.out.println("testNumbers passed");
	}
	
	private static void testSymbols() {
		PasswordGenerator pGen = new PasswordGenerator(false, false, true);
		for(int i = 0; i < 10; i++) {
			for(int c = 0; c < pGen.getPasswords()[i].length(); c++) {
				String validChars = "!@#$%^&*_-+=,./?;:";
				char ch = pGen.getPasswords()[i].charAt(c);
				if(!validChars.contains(String.valueOf(ch))) {
					System.out.println("testSymbols failed: " + pGen.getPasswords()[i]);
					return;
				}
			}
		}
		System.out.println("testSymbols passed");
	}
	
	private static void testFileCreation() {
		File file = new File("extraPasswords.txt");
		if(file.exists()) {
			file.delete();
		}
		PasswordGenerator pGen = new PasswordGenerator();
		pGen.generateExtraPasswords(5);
		if(file.exists()) {
			System.out.println("testFileCreation passed");
		} else {
			System.out.println("testFileCreation failed");
		}
	}
	
	private static void testFileLength() {
		PasswordGenerator pGen = new PasswordGenerator();
		pGen.generateExtraPasswords(5);
		File file = new File("extraPasswords.txt");
		Scanner scn = null;
		try {
			scn = new Scanner(file);
		} catch (FileNotFoundException e) {
			System.out.println("testFileLength failed");
			return;
		}
		int passwordCount = 0;
		while(scn.hasNextLine()) {
			String password = scn.nextLine();
			if(password.length() != PasswordGenerator.passwordLength) {
				System.out.println("testFileLength failed");
				break;
			}
			passwordCount++;
		}
		scn.close();
		if(passwordCount == 5) {
			System.out.println("testFileLength passed");
		} else {
			System.out.println("testFileLength failed");
		}
	}

}

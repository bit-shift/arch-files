// WHILE LOOP TO RUN THROUGH AND PRINT OUT THE REMAINING PAYMENT
// THERE NEEDS TO BE AN IF STATEMENT INSIDE CHECKING THE INPUT OF $
// BEFORE THE DENOMINATION ENTERED.
// THE WHILE LOOP HAS THE CONDITION THAT THE AMOUNT ENTERED IS LESS THAN
// THE AMOUNT LEFT. IF IT ISNT, THE LOOP SHOULD PROGRESS TO WORKING OUT
// CHANGE. THERE NEEDS TO BE AN INNER WHILE LOOP THAT CHECKS THE VALIDITY
// OF THE ENTERED VALUE - WHETHER IT IS IN THE CORRECT FORMAT AND A
// A VALID DENOMINATION. OUTER LOOP CHECKS CHANGE PROGRESSION.
// INITIALLY THERE MUST BE A CHECK OF THE VALIDITY BEFORE ENTERING THE
// OUTER WHILE LOOP.

while(payment != hundredNote && payment != fiftyNote && payment != twentyNote && payment != tenNote && payment != fiveNote && payment != twoCoin && payment != oneCoin && payment != fiftyCoin && payment != twentyCoin && payment != tenCoin && payment != fiveCoin){
  System.out.println("Invalid coin or note. Try again.");
  System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
  payment = keyboard.nextDouble();
}

while(payment <= remainingPayment){

  while(payment != hundredNote && payment != fiftyNote && payment != twentyNote && payment != tenNote && payment != fiveNote && payment != twoCoin && payment != oneCoin && payment != fiftyCoin && payment != twentyCoin && payment != tenCoin && payment != fiveCoin){
    System.out.println("Invalid coin or note. Try again.");
    System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
    payment = keyboard.nextDouble();
  }

  if(payment == remainingPayment){
    System.out.println();
    System.out.printf("You gave $%.2f\n",payment);
    System.out.println("Perfect! No change given.");
    System.out.println();
    System.out.println("Thank you, "+ name +".");
    System.out.println("See you next time.");
    return;
  }

  remainingPayment = remainingPayment-payment;
  System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
  payment = keyboard.nextDouble();
}

while(payment != hundredNote && payment != fiftyNote && payment != twentyNote && payment != tenNote && payment != fiveNote && payment != twoCoin && payment != oneCoin && payment != fiftyCoin && payment != twentyCoin && payment != tenCoin && payment != fiveCoin){
  System.out.println("Invalid coin or note. Try again.");
  System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
  payment = keyboard.nextDouble();
}


// REWORK LOGIC GATES HERE IN ORDER TO CATCH ALL POSSIBILITIES PROPERLY
// NEED TO ADJUST WHILE LOOP STRUCTURE IN TERMS OF OUTISDE AND INSIDE
// LOOPS AND WHOCH IS THE OVERRIDING LOGICAL CONDITION
// MIDNIGHT SCREENSHOT IS THE CONDITIONS UNDER WHICH THE WHILE LOOP
// CAN BE BROKEN BY INCORRECT NOTES



double hundredNoteLeft, fiftyNoteLeft, twentyNoteLeft, tenNoteLeft, fiveNoteLeft;
double twoCoinLeft, oneCoinLeft, fiftyCoinLeft, twentyCoinLeft, tenCoinLeft, fiveCoinLeft;

hundredNoteLeft = change/hundredNote;
change = change%hundredNote;

int hundredNoteLeftInt = (int) hundredNoteLeft;

fiftyNoteLeft = change/fiftyNote;
change = change%fiftyNote;

int fiftyNoteLeftInt = (int) fiftyNoteLeft;

twentyNoteLeft = change/twentyNote;
change = change%twentyNote;

int twentyNoteLeftInt = (int) twentyNoteLeft;

tenNoteLeft = change/tenNote;
change = change%tenNote;

int tenNoteLeftInt = (int) tenNoteLeft;

fiveNoteLeft = change/fiveNote;
change = change%fiveNote;

int fiveNoteLeftInt = (int) fiveNoteLeft;

twoCoinLeft = change/twoCoin;
change = change%twoCoin;

int twoCoinLeftInt = (int) twoCoinLeft;

oneCoinLeft = change/oneCoin;
change = change%oneCoin;

int oneCoinLeftInt = (int) oneCoinLeft;

fiftyCoinLeft = change/fiftyCoin;
change = change%fiftyCoin;

int fiftyCoinLeftInt = (int) fiftyCoinLeft;

twentyCoinLeft = change/twentyCoin;
change = change%twentyCoin;

int twentyCoinLeftInt = (int) twentyCoinLeft;

tenCoinLeft = change/tenCoin;
change = change%tenCoin;

int tenCoinLeftInt = (int) tenCoinLeft;

fiveCoinLeft = change/fiveCoin;
change = change%fiveCoin;

int fiveCoinLeftInt = (int) fiveCoinLeft;

System.out.println();
System.out.printf("You gave $%.2f\n",payment);
System.out.println("Your change:");

if(hundredNoteLeftInt > 0){
  System.out.print(hundredNoteLeftInt + " x $");
  System.out.printf("%.2f\n",hundredNote);
}

if(fiftyNoteLeftInt > 0){
  System.out.print(fiftyNoteLeftInt +" x $");
  System.out.printf("%.2f\n",fiftyNote);
}

if(twentyNoteLeftInt > 0){
  System.out.print(twentyNoteLeftInt + " x $");
  System.out.printf("%.2f\n",twentyNote);
}

if(tenNoteLeftInt > 0){
  System.out.print(tenNoteLeftInt + " x $");
  System.out.printf("%.2f\n",tenNote);
}

if(fiveNoteLeftInt > 0){
  System.out.print(fiveNoteLeftInt + " x $");
  System.out.printf("%.2f\n",fiveNote);
}

if(twoCoinLeftInt > 0){
  System.out.print(twoCoinLeftInt + " x $");
  System.out.printf("%.2f\n",twoCoin);
}

if(oneCoinLeftInt > 0){
  System.out.print(oneCoinLeftInt + " x $");
  System.out.printf("%.2f\n",oneCoin);
}

if(fiftyCoinLeftInt > 0){
  System.out.print(fiftyCoinLeftInt + " x $");
  System.out.printf("%.2f\n",fiftyCoin);
}

if(twentyCoinLeftInt > 0){
  System.out.print(twentyCoinLeftInt + " x $");
  System.out.printf("%.2f\n",twentyCoin);
}

if(tenCoinLeftInt > 0){
  System.out.print(tenCoinLeftInt + " x $");
  System.out.printf("%.2f\n",tenCoin);
}

if(fiveCoinLeftInt > 0){
  System.out.print(fiveCoinLeftInt + " x $");
  System.out.printf("%.2f\n",fiveCoin);
}

System.out.println();
System.out.println("Thank you, "+ name +".");
System.out.println("See you next time.");
return;

keyboard.close();






paymentD = Double.parseDouble(payment.replace("$",""));
paymentSplit = paymentD;
splitter = paymentSplit.toString().split("\\.");

}while(splitter[1] != 2);

while(paymentD != hundredNote && paymentD != fiftyNote && paymentD != twentyNote && paymentD != tenNote && paymentD != fiveNote && paymentD != twoCoin && paymentD != oneCoin && paymentD != fiftyCoin && paymentD != twentyCoin && paymentD != tenCoin && paymentD != fiveCoin){
  System.out.println("Invalid coin or note. Try again.");
  System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
  paymentD = keyboard.nextDouble();
}

double hundredNote = 100.00, fiftyNote = 50.00, twentyNote = 20.00, tenNote = 10.00, fiveNote = 5.00;
double twoCoin = 2.00, oneCoin = 1.00, fiftyCoin = 0.50, twentyCoin = 0.20, tenCoin = 0.10, fiveCoin = 0.05;
do{

  System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
  payment = keyboard.next();
  decimalPlaces = payment.length()-(payment.indexOf(".")+1);
  if(Character.isDigit(payment.charAt(1))){
    paymentD = Double.parseDouble(payment.replace("$",""));
  }
  else{
  paymentD = 0;
  }

  while(payment.length() <= 3 || decimalPlaces != 2 || payment.charAt(0) != '$' || paymentD != 100 && paymentD != 50 && paymentD != 20 && paymentD != 10 && paymentD != 5 && paymentD != 2 && paymentD != 1 && paymentD != 0.5 && paymentD != 0.2 && paymentD != 0.1 && paymentD != 0.05){
    System.out.println("Invalid coin or note. Try again.");
    System.out.printf("$%.2f remains to be paid. Enter coin or note: ",remainingPayment);
    payment = keyboard.next();
    decimalPlaces = payment.length()-(payment.indexOf(".")+1);
    if(Character.isDigit(payment.charAt(1))){
      paymentD = Double.parseDouble(payment.replace("$",""));
    }
    else{
    paymentD = 0;
    }
  }

remainingPayment = remainingPayment - paymentD;
}while(remainingPayment > 0);



decimalPlaces = payment.length()-(payment.indexOf(".")+1);
if(Character.isDigit(payment.charAt(1))){
  paymentD = Double.parseDouble(payment.replace("$",""));
}
else{
  paymentD = 0;
}


payment.length() <= 3 || decimalPlaces != 2 || payment.charAt(0) != '$' ||


decimalPlaces = payment.length()-(payment.indexOf(".")+1);
if(Character.isDigit(payment.charAt(1))){
  paymentD = Double.parseDouble(payment.replace("$",""));
}
else{
  paymentD = 0;
}

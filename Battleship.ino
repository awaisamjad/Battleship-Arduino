int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };  // Pins used for LED's
const int ship_size = 3;                     // size of Battleship
int locationCells[ship_size];                // makes array size of the ship_size variable
int numberOfHits = 0;                        // number of times the Battleship has been hit
int winPin = 10;                             // Pin number for the Green/Win LED
int numberOfGuesses = 5;                     // number of guesses the user has

void setup() {
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(winPin, OUTPUT);
  randomSeed(analogRead(A3));
  Serial.begin(9600);
  setLocationCells();
}

void loop() {
  String final_result = checkYourself();
  Serial.println(final_result);
  delay(500);
  if (final_result == "kill") {  // if the final result is a kill exit game, declare user as winner
    numberOfGuesses = 0;
    delay(500);
    exit(1);
  } else if (numberOfGuesses == 0) {  // if the user has ran out of guesses exit game, declare user as loser
    Serial.println("You lose");
    Serial.println("Press Reset button to restart");
    delay(500);
    exit(1);
  }
}

char getGuess() {
  char readinput = '^';
  while ((readinput < '1') || (readinput > '8')) {  // makes sure guess is within bounds
    Serial.println("Enter a guess (1-8):");         //prompts user for guess within bounds
    Serial.print("Number of guesses remaining:");   //shows remaining number of guesses
    Serial.println(numberOfGuesses);
    while (Serial.available() == 0) {}
    readinput = Serial.read();  // gets users guess
    Serial.print("You have entered: ");
    Serial.println(readinput);  // diplays what the user entered
    numberOfGuesses--;
    if ((readinput < '1') || (readinput > '8')) {
      Serial.println("Invalid input. Please enter number 1-8");  // if guess is not within bounds it
    }                                                            // tells user this
  }
  return readinput;  // returns guess
}

void setLocationCells() {                   //Create random places for ship
  int startLocation1 = random(1, 6);        //generate random number 1-5
  int startLocation2 = startLocation1 + 1;  // next number for battleship is 1 after first number
  int startLocation3 = startLocation1 + 2;  // next number for battleship is 2 after first number
  locationCells[0] = startLocation1;
  locationCells[1] = startLocation2;
  locationCells[2] = startLocation3;
  Serial.println("Best score will be 3 guesses");  // tells the user what the best score is
}


String checkYourself() {
  char userGuess = getGuess();
  String outcome = "MISS";
  int guess = (userGuess - '0');  //convert user guess to int
  for (int i = 0; i < ship_size; i++) {
    if (guess == locationCells[0] || guess == locationCells[1] || guess == locationCells[2]) {
      numberOfHits++;
      digitalWrite(ledPins[guess - 1], HIGH);
      if (numberOfHits == ship_size) {
        outcome = "KILL. You WON!!!!!!!";
        digitalWrite(winPin, HIGH);
      } else outcome = "HIT";
      break;
    }
    return outcome;
  }
}
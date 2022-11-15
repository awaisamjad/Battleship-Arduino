const int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };  // array of pins used for LEDs
const int ship_size = 3;                           // size of the ship
int locationCells[ship_size];                      // array with size of the ship
int numberOfHits = 0;
const int buttonPin1 = 12;
const int buttonPin2 = 13;
int guessButton = 0;
int number;
int winPin = 10;
int numberOfGuesses = 5;
int speakerPin = 11;
int length = 15;         // the number of notes
char hitNotes[] = "aa";  // note played when guess is correct
char missNotes[] = "c";
char winMusic[] = "ccdcfeccdcgf ";  // note played when guess is wrong
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(A0));
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(speakerPin, OUTPUT);
  Serial.begin(9600);
}
//declared after cuz of randomSeed(analogRead(A3));
int startLocation1 = random(1, 6);        // start location with random number between 1 and 5
int startLocation2 = startLocation1 + 1;  // next number for battleship is 1 after first number
int startLocation3 = startLocation1 + 2;  // next number for battleship is 2 after first number
int hit;
void loop() {
  // // GUESS BUTTON
  if (digitalRead(buttonPin1) == LOW) {  // if the button state is low/button has been pressed then execute code
    guessButton++;
    delay(200);                             // delay when LED changes
    number = constrain(guessButton, 0, 8);  // constrains number of guesses between 0 and 8
    number = number - 1;
    digitalWrite(ledPins[number], HIGH);  // turns on LED
    delay(50);
    digitalWrite(ledPins[number - 1], LOW);  //turns off previous LED
    if (startLocation1 == ledPins[number - 1] || startLocation2 == ledPins[number - 1] || startLocation3 == ledPins[number - 1]) {
      digitalWrite(ledPins[number], HIGH);  //if guess matches battleship location light LED
      hit++;
    }
    if (guessButton > 8) {  // if the button is at last LED and is pressed, it will return back to first LED
      digitalWrite(ledPins[number], LOW);
      guessButton = 0;
    }
  }
  // CONFIRM BUTTON
  if (digitalRead(buttonPin2) == LOW) {  // if the button state is low/button has been pressed then execute code
    if (startLocation1 == ledPins[number - 1] || startLocation2 == ledPins[number - 1] || startLocation3 == ledPins[number - 1]) {
      Serial.println("HIT");  // Prints hit when guess is right
      for (int i = 0; i < sizeof(hitNotes); i++) {
        if (hitNotes[i] == ' ') {
          delay(beats[i] * tempo);  // rest
        } else {
          playNote(hitNotes[i], beats[i] * tempo);  // play note when guess is right
          digitalWrite(ledPins[number - 1], HIGH);  // light up LED when guess is right
        }
      }
      if (hit == 3) {
        digitalWrite(winPin, HIGH);  // if 3 hits have landed light winPin
        Serial.println("You Won");
        for (int i = 0; i < sizeof(winMusic); i++) {
          playNote(winMusic[i], beats[i] * tempo);  // play music for winning
        }
      }
    }

    else {
      Serial.println("MISS");  // Prints miss when guess is right
      for (int i = 0; i < sizeof(missNotes); i++) {
        playNote(missNotes[i], beats[i] * tempo);  // play the note for wrong guess
      }
    }
  }
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 900, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
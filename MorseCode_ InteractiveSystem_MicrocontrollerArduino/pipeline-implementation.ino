#include <Servo.h>
#include<String.h>
Servo S;                        // the servo that we used
int Button = D1;                // the button that we used
int LED = D3 ;                  // the Led that we used for an alternative decoding method
int shorttime = 500 ;           // Indicates the long of time that LED will light when we have a dot
int longtime = 1000 ;           // Indicates the long of time that LED will light when we have a dash

int B_Active_notActive = 0;     // Indicates if the Button is aktiv or not
int PressTime = 0;              // This variable stores the time where the button was pressed.
int TIME = 0;                   // A variable to hold the time that we spend

int starttime = 0;              // The time after that the button is pressed

bool term0 = true;              // this Variable to say that the button is pressed  
bool term1 = false;             // this Variable to say that a part from the code is using the button is pressed
bool term3 = false;             // this Varuíable to say if the code for a letter or a character fully pressed

String oldOUTPUT = "";
String letter = "";             // Help-Variable to print the Letter or the character that we got from input after decoding
const String ShortPress = "S";  // TO denote the short time pressing 
const String LongPress = "L";   // TO denote the long time pressing 
int timeButtonNOTactive = 0;    // This variable stores the time where the button was not pressed.
int NotPressing = 0;            // This variable indicates if the Button is not pressed
bool morsecode = false;         // identifying that the input time is over and we will start give the output
int count = 0 ;                 // Help-variable to count the number of letter in the input-word.

void setup() {
  // put your setup code here, to run once:
  pinMode(Button, INPUT);       // We denote here that the Button as Input
  pinMode(LED, OUTPUT);         // We denote here that our LED for alternative decoding as output*/
  S.attach(D2, 500, 2500);      // We define here the rounding rang of the servo*/
  S.write(0);                   // At first, the servo is going to point on the 0*/
  Serial.begin(9600);
}

void LED_ON_OFF(int time) {    //This function helps us in alternative decoding by awtiching the LED ON and OFF for a mount of time  */
  digitalWrite(LED, HIGH);
  delay(time);
  digitalWrite(LED, LOW);
  delay(shorttime);
}

void loop() {
  B_Active_notActive = digitalRead(Button);   // Reading the Input from the button
  starttime = millis();
  String newOUTPUT = "";                      // we store the Input what we read in this variable "newOUTPUT"

  while (B_Active_notActive == HIGH) {        // If the button still pressed do the following
    NotPressing = 0;
    timeButtonNOTactive = 0;                  // the button is aktive"high" and we get the input right now from it 
    term0 = true;                             // the button st ill pressed 
    newOUTPUT = oldOUTPUT;                    // we copy the Input in the variable "newOUTPUT"

    B_Active_notActive = digitalRead(Button); // while the button is pressed we read the input-signal
    PressTime = millis();                     // Calculate the time right now when the button is pressed
    TIME = PressTime - starttime;             // Calculate the time from start-pressing until now
    term1 = true;                             // A part from the code for a letter or a character is using the button is pressed
    term3 = false;                            // The code for a letter or a character is not fully pressed
  }

  if (term0 == false ) {                      // if the button not pressed now we Calculate the time from the last time-pressing until now
    timeButtonNOTactive = millis();
    NotPressing = timeButtonNOTactive - PressTime;
  }

  if (TIME >= 402  && term1 == true) {  // Pressing Time was long which mean the code is a dash!
    newOUTPUT = "L";
    count++;
    oldOUTPUT +=  newOUTPUT;            // we add the L-mark to the variable that we used to save the input signal
    term1 = false;
    term0 = false;
  }
  if (TIME < 402 && term1 == true) {    // Pressing Time was short which mean the code is a dot!
    newOUTPUT = "S";   
    count++;
    oldOUTPUT +=  newOUTPUT;            // we add the L-mark to the variable that we used to save the input signal
    term1 = false;
    term0 = false;                      // we say here that the pressing is recognized and we let the button at un-pressing model
  }
  if ( NotPressing > 5000) {            // if the button is not pressed for longer than 5 sec than the input-word is over and we start with output
    morsecode = true;
  }
  if ( NotPressing > 2000 && term3 == false) {
    //if the button is not pressed for longer than 2 sec than the code for an input-letter(or character) is fully pressed and we add a semicolon to separate the letters.
    Serial.println(NotPressing);
    letter = oldOUTPUT;       // save the new letter 
    Serial.println(letter);   // print the letter 
    count++;                 
    oldOUTPUT += ";";
    term3 = true;
  }

  if (morsecode) {                 // if the input time is over and code for a word is pressed using the button 
    letter = "";
    for (int i = 0 ;  i < count; i++) {
      if (oldOUTPUT[i] != ';') {   // seperate the word to the letter or character by read the word until the first semicolon
        letter += oldOUTPUT[i] ;    
      }
      else {                       // when we read a semicolon than a part of the word saved in the variable letter 
        /*The letter A*/           // Now we compaire the signal in letter with the morse codes and point the servo to the right angle. 
        if ( letter == "SL") {     // If the Letter has the code form SL it is the morse code for the letter A and the HEX code is 41 
          S.write(0);
          delay(1500);
          S.write(114);            // To let the servo pointing to the number 4 on the paper 
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(80);             // To let the servo pointing to the number 1 on the paper 
          delay(1500);
          S.write(0);
          delay(2500);             
          LED_ON_OFF(shorttime);  // "alternative Decoding" appear as fashes of the LED that represent the Morse Code "here we have a short time lighting a first"  
          LED_ON_OFF(longtime);   // After that we will have a long time lighting then we are done and the LED presented the morse code for A "SL"
          letter = "";
          Serial.println("A");
        }
        /*The letter B*/
        if ( letter == "LSSS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(90);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("B");
        }
        /*The letter C*/
        if ( letter == "LSLS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("C");
        }
        /*The letter D*/
        if ( letter == "LSS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("D");
        }
        /*The letter E*/
        if ( letter == "S" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("E");
        }
        /*The letter F*/
        if ( letter == "SSLS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(137);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("F");
        }
        /*The letter G*/
        if ( letter == "LLS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(149);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("G");
        }
        /*The letter H*/
        if ( letter == "SSSS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(164);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("H");
        }
        /*The letter I*/
        if ( letter == "SS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(175);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("I");
        }
        /*The letter J*/
        if ( letter == "SLLL" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(7);
          delay(1500);
          S.write(0);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          delay(2500);
          letter = "";
          Serial.println("J");
        }
        /*The letter K*/
        if ( letter == "LSL" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(18);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("K");
        }
        /*The letter L*/
        if ( letter == "SLSS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(30);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("L");
        }
        /*The letter M*/
        if ( letter == "LL" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(40);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("M");
        }
        /*The letter N*/
        if ( letter == "LS" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(52);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("N");
        }
        /*The letter O*/
        if ( letter == "LLL" ) {
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(62);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("O");
        }

        /*The letter P*/
        if ( letter == "SLLS" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(72);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("P");
        }


        /*The letter Q*/
        if ( letter == "LLSL" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(80);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("Q");
        }
        /*The letter R*/
        if ( letter == "SLS" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(90);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("R");
        }
        /*The letter S*/
        if ( letter == "SSS" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("S");
        }
        /*The letter T*/
        if ( letter == "L" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("T");
        }
        /*The letter U*/
        if ( letter == "SSL" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("U");
        }
        /*The letter V*/
        if ( letter == "SSSL" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(137);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("V");
        }
        /*The letter W*/
        if ( letter == "SLL" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(149);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("W");
        }
        /*The letter X*/
        if ( letter == "LSSL" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(164);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("X");
        }
        /*The letter Y*/
        if ( letter == "LSLL" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(175);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("Y");
        }
        /*The letter Z*/
        if ( letter == "LLSS" ) {
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(7);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("Z");
        }
        /*The character 1*/
        if ( letter == "SLLLL" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(80);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("1");
        }
        /*The character 2*/
        if ( letter == "SSLLL" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(90);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("2");
        }

        /*The character 3*/
        if ( letter == "SSSLL" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("3");
        }

        /*The character 4*/
        if ( letter == "SSSSL" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(114);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("4");
        }
        /*The character 5*/
        if ( letter == "SSSSS" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(125);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("5");
        }
        /*The character 6*/
        if ( letter == "LSSSS" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(137);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("6");
        }
        /*The character 7*/
        if ( letter == "LLSSS" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(149);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("7");
        }
        /*The character 8*/
        if ( letter == "LLLSS" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(164);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("8");

        }
        /*The character 9*/
        if ( letter == "LLLLS" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(175);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(shorttime);
          letter = "";
          Serial.println("9");
        }
        /*The character 0*/
        if ( letter == "LLLLL" ) {
          S.write(0);
          delay(1500);
          S.write(104);
          delay(1500);
          S.write(0);
          delay(1500);
          S.write(72);
          delay(1500);
          S.write(0);
          delay(2500);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          LED_ON_OFF(longtime);
          letter = "";
          Serial.println("0");
        }



      }

    }
    morsecode = false;
    NotPressing = 0;
    count = 0;




  }



}

1. Project concept
My project represents a simple interactive system, that allow the user to send
messages using Morse code and receive it again as a hex code.

2. Implementation:

I used the c programming language with Arduino IDE.

a) I used these libraries : servo.h and string.h
i. The benefit of servo library is to have the method that let the servo moving to the right position.
ii. The benefit of string library is to save the input as a string and represented later as a hex code.

b) I used the strings "S" and "L" as a representation for the input that i
get after pressing the button : S means that the button has been pressed for
a short time (dot) and L means that the button has been pressed for a long
time (dash).

c) I used some variables to compute the pressing time (to know how long the
button was pressed) and the release time (to know how long the button was
not pressed).
The importance of the release time to know if the Morse code for a letter is
fully pressed, and also to know if i finished the Morse code for the word or
not.

d) I used a variable (oldOUTPUT) to save the code for a full word that i
get from the input as a sequence of S's or L's, and i added additionally to
the string (oldOUTPUT) semicolons at the end of a code for a letter.
These semicolons are going to help us later, when i start giving the out-
put, to distinguish between the codes for letters in a word and let the servo
recognize which letter has to be represented now as a hex code.

e) In the output part i have made a case distinction for each letter or number
and for each code form i have given servo a task to show the correct hex code on the slip of paper.

f) In the alternative part, i have given LED
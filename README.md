# Hangman

• Uses 2 strings and 2 character arrays in the hangmanGame class  
• The solution word is read from an input file called “inputWords.txt” 
• The hintWord is the word in progress that is presented for the user to try to guess 
• The lettersGuessed array will store all the letters that have been guessed (correct and incorrect) 
• If the user enters an uppercase letter,  number or other character, it will count as an incorrect guess 
 
HOW TO PLAY THE GAME 
• The user guess letters one character at a time. 
• At every stage of the game, the user is able to view the current state of the word in progress (hintWord) and the list of 
guessed letters (lettersGuessed) 
• If any letter is guessed correctly the player is notified and the letter appears in its proper location in the (hintWord), this 
array is displayed again with the letter(s) in place and the user can choose to input a word (The user can choose to guess the 
word) 
• If a letter is not correct, the incorrectCount is increased. 
• In ALL cases, the guessed letter is added to the array of lettersGuessed, keep track with letterCount 
• The user is allowed up to 6 incorrect guesses. (HEAD,  BODY,  ARM1,  ARM2,  LEG1, LEG2) 
• The round of the game is over with either of the following:  
o The word is guessed correctly 
o The user guesses all the letters or the six incorrect letter guesses are used up. 
• If the player guesses the word correctly, the player is notified that they have won. 
• If the player does not guess the correct word, the game will continue with no penalty. 
• When the game is over, the user is allowed to play again without having to execute the program again. (The player 
will play again with the next word in the file) 

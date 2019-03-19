# AdventureGame

           TEXT ADVENTURE GAME 

This text adventure is a puzzle game which starts with positioning the avatar in the main room of a haunted house. The avatar has to find its way to Dalton’s room which is supposed to have the demon which can be killed by using the holy water. But first we need to have a strategy to find the holy water and also the game gets interesting if you find useful stuff to be added in the inventory and used at appropriate time to change the state of the game and give hints(emf-meter) about the location of the daemon.

The game is built using several helper methods but the whole game state ultimately ends if 
The demon is killed (winning state)
The Avatar gets killed (game lost) 
“quit” is called to end the game in progress

make_map() function is used to place the avatar in the start room and make all the connections of the rooms. The game is played using the play() function which terminates at above given conditions. move() method is called every time the user needs to go from one room to another. 

If you go directly to Dalton’s room without having holy water, you get killed by the demon and you lose. 
If you find the holy water, You need to use the holy water to kill the demon and win the game. 


This game is based on the story of "Insidious"
Source used: 
https://en.wikipedia.org/wiki/Insidious_(film)

Used the follwoing site to understand the scanning of input with whitespaces:
https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx

Source USED:
//https://www.geeksforgeeks.org/linked-list-set-3-deleting-node/

Link to Video:
https://youtu.be/abR_a2b4Byc

You can find the iamge link to the map of the house:
https://www.slideshare.net/secret/k9BCCEK8uyel50

Umair Afzal, Ritwik Bagga, Abhishek Dutt

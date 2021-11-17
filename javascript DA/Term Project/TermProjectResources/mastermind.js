
//tracks solution.
var keyArray = new Array(7,7,7,7);
//tracks current user guess.
var userArray = new Array;
//used for printing and tracking matches and looking for winstate.
var matchArray = new Array;

//these arrays are for storing file names, so I can type them all here instead of repeating code for each file.
var colorArray = new Array("Blue", "White", "Red", "Purple", "Green", "Yellow");
var imageNameArray = new Array("BlueRectangle.gif", "WhiteRectangle.gif", "RedRectangle.gif", "PurpleRectangle.gif", "GreenRectangle.gif", "YellowRectangle.gif" 
, "QuestionRectangle.gif");
var dataBoxArray = new Array("Data1" , "Data2" , "Data3" , "Data4" , "Data5" , "Data6" , "Data7" , "Data8" , "Data9" , "Data10");
var matchBoxArray = new Array("Clue1" , "Clue2" , "Clue3" , "Clue4" , "Clue5" , "Clue6" , "Clue7" , "Clue8" , "Clue9" , "Clue10");
var guessesUsed = 0;


//opens help window
function Help(){
	window.open("UserHelp.htm", '_blank',"width =300 height = 400");
}

//gets a random number used for generating the solution
function getRandNumber(){
return Math.floor(Math.random() * 5);
}

//clears the answer array. 
function clearAnswer(){
	userArray = new Array;
}

//makes a random solution the player must guess
function makeRandomKeySequence(){
	keyArray = new Array;
	keyArray.push(Math.floor(Math.random() * 5));
	keyArray.push(Math.floor(Math.random() * 5));
	keyArray.push(Math.floor(Math.random() * 5));
	keyArray.push(Math.floor(Math.random() * 5));
	return keyArray;
}

//pushes the user selected value onto an array, and then updates image
function addUserAnswer(userColor){
	userArray.push(userColor);
	updateImages();
}

//finds image with corresponding id and changes it to proper color
function updateImages(){
	if (userArray[0] != null){
	document.getElementById('ansBox1').src = imageNameArray[userArray[0]];	
	}
	if (userArray[1] != null){
	document.getElementById('ansBox2').src = imageNameArray[userArray[1]];		
	}
	if (userArray[2] != null){
	document.getElementById('ansBox3').src = imageNameArray[userArray[2]];	
	}
	if (userArray[3] != null){
	document.getElementById('ansBox4').src = imageNameArray[userArray[3]];	
	}
}

//resets the images to ?'s
function resetImages(){
	document.getElementById('ansBox1').src = "QuestionRectangle.gif";	
	document.getElementById('ansBox2').src = "QuestionRectangle.gif";		
	document.getElementById('ansBox3').src = "QuestionRectangle.gif";	
	document.getElementById('ansBox4').src = "QuestionRectangle.gif";	
}

// resets match array
function resetMatches(){
	matchArray = new Array(0);
}

// resets user array
function resetUserArray(){
	userArray = new Array;
}

//ensures that all relevant arrays are in factory state
function restartGame(){
	makeRandomKeySequence();
	resetMatches();
	userArray = new Array; //reset userArray
	numGuessesUsed = 0;
}

// restarts the game :^)
function refreshPage(){
	location.reload();
}

//prints guesses in the correct cell
function printGuesses(){
	var i;
	var joinedUserArray = userArray.join('');
	document.getElementsByName(dataBoxArray[guessesUsed-1])[0].value = joinedUserArray;
}

//prints matches in cell
function printMatches(){
	var i;
	var joinedMatchArray = matchArray.join('');
	document.getElementsByName(matchBoxArray[guessesUsed-1])[0].value = joinedMatchArray;
}

//alerts player they have lost the game
function loseMessage(){
	window.alert("Woah, you lost! Your intelligence and or luck correlates negatively to the number of guesses used, the number of which happens to be: " + guessesUsed + " guesses. The answer was " + 
	colorArray[keyArray[0]] + ", " + colorArray[keyArray[1]] + ", " + colorArray[keyArray[2]] + ", " + colorArray[keyArray[3]] + ".");
	gameOver();
}

//alerts player they have won, and gives a customized message depending on how many guesses they used
function winMessage(){
	window.alert("Woah, you win! Your intelligence and or luck correlates negatively to the number of guesses used, he number of which happens to be: " + guessesUsed + " guesses. The answer was " + 
	colorArray[keyArray[0]] + ", " + colorArray[keyArray[1]] + ", " + colorArray[keyArray[2]] + ", " + colorArray[keyArray[3]] + ".");
	gameOver();
}	

// tells player that they need to restart game
function gameOver(){
	document.getElementsByName("sInfo")[0].value = "Game Over. Press Restart Game to restart game.";
}

//checks the answer, and if a match is found, changes the values in the shallow copies used to check for matches in the nested loop, to prevent re-matching in the second pass.
function checkAnswers() {
	++guessesUsed;	
	printGuesses();
	
	var i;
	var j;
	var tempKeyArray = [...keyArray];
	var tempUserArray = [...userArray];
	var tempMatchArray = [...matchArray];
	for (i = 0; i <= 3; i++){
		if (userArray[i] == keyArray[i]){
			matchArray.push("X");
			tempUserArray[i] = 9;
			tempKeyArray[i] = 8;
		}	
	}
	for (i = 0; i <= 3; i++){
		for (j = 0; j <=3; j++){
			if (tempUserArray[i] == tempKeyArray[j]){
					matchArray.push("O");
					tempUserArray[i] = 9;
					tempKeyArray[j] = 8;
				}
		}	
	}
	if (matchArray[3] == "X"){
		winMessage();
	}
	if (guessesUsed == 10){
		loseMessage();
	}
	
	printMatches();
	resetUserArray();
	resetMatches();
	resetImages();
}

restartGame();

var test = document.getElementsByName('Answer')[0].value = keyArray[0].toString()+keyArray[1].toString()+keyArray[2].toString()+keyArray[3].toString();

document.getElementById("bluecheck").onerror = function() {
    window.alert("Please use a browser that can display images, else this will not work");
};


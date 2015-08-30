/***************************************************************************
                          kboxes.cpp  -  description
                             -------------------
    begin                : Πεμ Ιαν 20 17:36:13 EET 2000
    copyright            : (C) 2000 by Panos Katsaloulis
    url                  : http://www.panayotis.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "kboxes.h"
#include <cstring>

KBoxes::KBoxes()
{
 setCaption("KBoxes " VERSION);

	///////////////////////////////////////////////////////////////////
	// call inits to invoke all other construction parts
	initFirstTime();
	initMenuBar();
	initButtons ();
	initGame();
}

KBoxes::~KBoxes()
{
}

void KBoxes::initMenuBar()
{
	///////////////////////////////////////////////////////////////////
	// MENUBAR

	///////////////////////////////////////////////////////////////////
	// menuBar entry fileMenu

	gameMenu=new QPopupMenu();
	gameMenu->insertItem("&New", this, SLOT(slotGameNew()), CTRL+Key_N);
	gameMenu->insertItem("&Undo Move", this, SLOT(slotGameUndo()), CTRL+Key_U);
	gameMenu->insertSeparator();
	gameMenu->insertItem("E&xit", this, SLOT(slotGameExit()), CTRL+Key_X);

	///////////////////////////////////////////////////////////////////
	// menuBar entry editMenu
	skillMenu=new QPopupMenu();
	skillMenu->setCheckable(true);
	skillMenu->insertItem("&Beginner", ID_DIFFICULTY_BEGIN);
	skillMenu->insertItem("&Intermediate", ID_DIFFICULTY_INTER);
	skillMenu->insertItem("&Professional", ID_DIFFICULTY_PROF);
	skillMenu->insertItem("I&mpossible", ID_DIFFICULTY_IMPOS);
	skillMenu->setItemChecked ( ID_DIFFICULTY_BEGIN, true );
	connect ( skillMenu, SIGNAL (activated(int)), this, SLOT (slotSkillChanged(int)) );

	///////////////////////////////////////////////////////////////////
	// menuBar entry viewMenu
	optionsMenu=new QPopupMenu();
	optionsMenu->setCheckable(true);
	optionsMenu->insertItem("&One Player", this, SLOT(slotOptionsOne()), CTRL+Key_O, ID_ONE_PLAYER);
	optionsMenu->insertItem("&Two Player", this, SLOT(slotOptionsTwo()), CTRL+Key_T, ID_TWO_PLAYERS);
	optionsMenu->setItemChecked ( ID_ONE_PLAYER, true);
	optionsMenu->insertSeparator();
	optionsMenu->insertItem("First is &computer", this, SLOT(slotOptionsFirst()), CTRL+Key_C, ID_FIRST_COMPUTER);

	///////////////////////////////////////////////////////////////////
	// EDIT YOUR APPLICATION SPECIFIC MENUENTRIES HERE
  
	///////////////////////////////////////////////////////////////////
	// menuBar entry helpMenu
	helpMenu=new QPopupMenu();
	helpMenu->insertItem("About KBoxes", this, SLOT(slotHelpAbout()), 0);
	helpMenu->insertSeparator();
	helpMenu->insertItem("How to play", this, SLOT(slotHelpHowto()), 0);


	///////////////////////////////////////////////////////////////////
	// MENUBAR CONFIGURATION
	// set menuBar() the current menuBar

	menuBar()->insertItem("&Game", gameMenu);
	menuBar()->insertItem("&Skill", skillMenu);
	menuBar()->insertItem("&Options", optionsMenu);
	menuBar()->insertSeparator();
	menuBar()->insertItem("&Help", helpMenu);
  
}


void KBoxes::initButtons()
{
	setGeometry (10,10,300,200);

	group = new QButtonGroup ( this);
	setCentralWidget (group);

	int counter = 0;
	for ( int i = 0 ; i < 5 ; i ++ ) {
		for ( int j = 0 ; j < (i*2-1) ; j ++ ) {
			buttons[counter] = new QPushButton ( group );
			buttons[counter] -> setGeometry ( 80 - 35 * j + i*35 ,35 *i - 20 , 30, 30);
			counter++;
		}
	}
	connect ( group, SIGNAL(clicked(int)), this, SLOT (slotPlayButtons(int)) );
}


/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////


void KBoxes::slotGameNew()
{
	initGame();
}

void KBoxes::slotGameUndo()
{
	if ( clicked != -1 ) {
		buttons[clicked]->setText ("");
		clicked = -1;
	}
}


void KBoxes::slotGameExit()
{ 
	qApp->quit();
}

void KBoxes::slotSkillChanged (int ID)
{
	switch ( ID ) {
	case ID_DIFFICULTY_BEGIN:
		skill = SKILL_BEGIN;
		break;
	case ID_DIFFICULTY_INTER:
		skill = SKILL_INTER;
		break;
	case ID_DIFFICULTY_PROF:
		skill = SKILL_PROF;
		break;
	case ID_DIFFICULTY_IMPOS:
		skill = SKILL_IMPOS;
		break;
	default:
		break;
	}
	skillMenu->setItemChecked ( ID_DIFFICULTY_BEGIN, false );
	skillMenu->setItemChecked ( ID_DIFFICULTY_INTER, false );
	skillMenu->setItemChecked ( ID_DIFFICULTY_PROF, false );
	skillMenu->setItemChecked ( ID_DIFFICULTY_IMPOS, false );
	skillMenu->setItemChecked ( ID, true );
}


void KBoxes::slotHelpAbout()
{
  QMessageBox::about(this,"About...", IDS_APP_ABOUT );
}

void KBoxes::slotHelpHowto()
{
  QMessageBox::about(this,"How to play", IDS_APP_HOWTO );
}


void KBoxes::slotOptionsOne()
{
	optionsMenu->setItemChecked ( ID_ONE_PLAYER, true );
	optionsMenu->setItemChecked ( ID_TWO_PLAYERS, false );
	no_of_players = 1;
}

void KBoxes::slotOptionsTwo()
{
	optionsMenu->setItemChecked ( ID_ONE_PLAYER, false );
	optionsMenu->setItemChecked ( ID_TWO_PLAYERS, true );
	no_of_players = 2;
}

void KBoxes::slotOptionsFirst()
{	
	computer_plays_first = !(computer_plays_first);
	optionsMenu->setItemChecked ( ID_FIRST_COMPUTER, computer_plays_first );
}

void KBoxes::slotPlayButtons(int which)
{
	int small, big;

	if ( clicked == -1 ) {			// first button clicked
		if ( map[which]!=' ' ) {
			error();
		}
		else {
			clicked = which;
			buttons[which]->setText ("-");
		}
	}
	else {							// second button clicked
		if ( clicked > which ) { big = clicked; small = which; }
		else { big = which; small = clicked; }

		/* Check rows */
		if ( small == 0 && big != 0 ) { error(); return;}
		if ( small < 4 && big > 3 ) { error(); return; }
		if ( small < 8 && big > 8 ) { error(); return; }
		/* Check lines */
		for ( int i = small; i <= big; i++ ) {
			if ( map[i] != ' ') { error(); return; }
		}
		wipeOut ( small, big, PLAYER);
		if ( no_of_players == 1 && freeMap != "" ) {
			playComputer();
		}
	}
}

/** Prepare the program for a new Game. */
void KBoxes::initGame ()
{
	for ( int i = 0; i <= 15; i++) {
		buttons[i]->setText ("");
	}
	clicked = -1;
	strncpy(map,"                \0",17);
	freeMap = "0013489?";		// for info about this numbers, see the ?.h include file
	if (computer_plays_first && no_of_players == 1 ) {
		playComputer();
	}
}

/** Initialize the system data. This function is called only once, in the beginning */
void KBoxes::initFirstTime()
{
	skill = SKILL_BEGIN;
	no_of_players = 1;
	computer_plays_first = false;
	level[0] = "1";
	level[1] = "22";
	level[2] = "33";
	level[3] = "44";
	level[4] = "55";
	level[5] = "123";
	level[6] = "145";
	level[7] = "246";
	level[8] = "257";
	level[9] = "356";
	level[10] = "2222";
	level[11] = "2233";
	level[12] = "3333";
	level[13] = "2244";
	level[14] = "12223";
	level[15] = "12333";
	level[16] = "12344";
	for ( int i = 0 ; i < 17 ; i++ ) {
		level[17+i] = "11" + level[i];		// "impossible" levels
	}
}

/** The computer does its move */
void KBoxes::playComputer()
{
	std::string freePos = "";			// part of freeMap, containing only the starting positions of the areas. It doesn't have any 1-size areas.
	std::string freeLength = "";		// part of freeMap, containing only the lengths of the areas. It doesn't have any 1-size areas.

	/* Create a clone of freeMap (freeMap_c) without any 1-size area.
	Still, count how many 1-size boxes exist and keep the position of the last 1-size area
	in the variable last_one. */
	int count_ones = 0;		// how many 1-size areas exist
	char last_one = '\0';			// position of last 1-size area
	int length = freeMap.length();			// temporary variable to store the length of the string
	for ( size_t i = 0; i < freeMap.length(); i+=2 ) {
		if (freeMap[i] == freeMap[i+1] ) {			// found 1-size area
			last_one = freeMap[i];
			count_ones++;
		}
		else {										// found >= 2-size are
			freePos += freeMap[i];
			freeLength += (char)('0' + (freeMap[i+1] - freeMap[i] + 1) );
		}
	}
	if ( (count_ones % 2) == 1 ) {		// an odd number of 1-size areas is found
		freePos += last_one;
		freeLength += '1';
	}

	/* check if everything on freeMap was just double 1-size areas */
	if ( freeLength == "" ) {
		wipeOut (freeMap[2]-'0', freeMap[2]-'0', COMPUTER);	// choose to delete the second entry (at position 2, because it comes in pairs) just to be nicer. This could be [0] too.
		return;
	}	

	/* Sort areas in accending order */
	/* Using bubblesort routine */
	length = freeLength.length();   		// temporary variable to store the length of the string
	int length_minus_one = length-1;		// temporary variable to store the length of the string minus one
	char temp;								// temporary character variable, to store the character-to-be-swapped
	for ( int i = 0; i < length; i++ ) {
		for ( int j = 0; j < length_minus_one - i; j++ ) {
			if ( freeLength [j] > freeLength [j+1] ) {
				temp = freeLength[j] ;
				freeLength[j] = freeLength[j+1];
				freeLength[j+1] = temp;
				temp = freePos[j] ;
				freePos[j] = freePos[j+1];
				freePos[j+1] = temp;
			}
		}
	}

	/* find if matches anything from the level data */
	for ( int i = 0; i < skill ; i++ ) {
		/* Find first if the number of free areas are too many or too little */
		std::string solving (level[i]);			// the current level data
		int difference =  solving.length() - freeLength.length() ;
		if ( difference < 2 && difference > -2 ) {	// If the difference of the # of areas is bigger than 1, there isn't any solution for this
			/* Find if there is a match by just deleting a whole line */
			if ( solving.length() < freeLength.length()) {
				length = freeLength.length();
				int j;
				for ( j = 0; j < length; j++ ) {
					// Try to find if there is only one difference. Imagine that from the solutions string is missing _one_ character, the one from the freeLength.
					if ( (solving.substr(0, j) + freeLength[j] + solving.substr(j)) == freeLength ) {	// if 'both' strings match, means that it *is* missing a character
						break;				// OK, found.
					}
				}
				if ( j < length ) {		// if it is found,
					int begTemp = (freePos[j] - '0'), lenTemp = (freeLength[j] - '0');	// count the positions of the boces to be wiped out.
					wipeOut ( begTemp, begTemp + lenTemp -1, COMPUTER );
					return;
				}
			}
			/*Find if it sould be wiped out _some_ (not all) boxes, from the beginning of the area till a specific point*/
			else if ( solving.length() == freeLength.length() ) {
				int count_diff = 0;			// store how many differences we have with the solving string
				std::string freeTemp ( freeLength ) ;	// temporary string, image of freeLength. Used to check the differental strings
				int last_wrong_pos = 0;					// store where was the 'right' length in solving string, in order to win
				length = freeLength.length();		// count the length of the freeTemp/solving etc. string

				for ( int j = 0; j < length ; j++ ) {
					int found = freeTemp.find (solving[j] );	// find if this character exists in the freeTemp string
					if ( found >= 0 ) {				// really exists
						freeTemp[found]=' ';			// wipe out this position
					}
					else {    							// doesn't exist
						count_diff++;					// count how many are these wrong cells
						last_wrong_pos = j;				// remember the position in the solving string of the unmatched character
					}
				}
				if ( count_diff == 1 ) {						// If ONLY 1 mismatch found
					int where = freeTemp.find_first_not_of (" ");
					int remaining = freeLength[where] - solving[last_wrong_pos];
    				if ( remaining > 0 ) {
						int begTemp = freePos[where] - '0';
						wipeOut ( begTemp, begTemp + remaining-1, COMPUTER );
						return;
					}
				}
			}
			/*Find if it sould be wiped out _some_ (not all) boxes, in between the area */
			else if ( solving.length() > freeLength.length()) {		// # solution-areas is one more than the # of freeLength-areas
				std::string freeTemp ( freeLength ) ;	// temporary string, image of freeLength. Used to check the differental strings
				std::string solvTemp ( solving ) ;		// temporary string, image of solving. Used to check the differental strings
				length = freeTemp.length();		// count the length of the freeTemp string. Should be <= solvTemp string

				for ( int j = 0; j < length ; j++ ) {
					int found = solvTemp.find (freeTemp[j] );	// find if a character from freeTemp exists in the solvTemp string
					if ( found >= 0 ) {				// really exists
						freeTemp[j] = ' ';			// wipe out this position from freeTemp
						solvTemp[found] = ' ';				// wipe out this position from solvTemp
					}
				}

				if ( ( countSpaces ( freeTemp ) + 1) == length ) { 		// found only one difference
					int where_in_free = freeTemp.find_first_not_of (" ");
					int where_in_solv_first = solvTemp.find_first_not_of (" ");
					int where_in_solv_last = solvTemp.find_last_not_of (" ");

					int free_length = freeTemp[where_in_free]-'0';
					int solv_length_first = solvTemp[where_in_solv_first]-'0';
					int solv_length_last = solvTemp[where_in_solv_last]-'0';

					int remaining = free_length - solv_length_first - solv_length_last;
					if ( remaining > 0 ) {			// has enough boxes for it
						int begTemp = freePos[where_in_free] - '0';
						begTemp += solv_length_first;
						wipeOut ( begTemp, begTemp + remaining-1, COMPUTER );
						return;
					}
				}

			}
		}
	}
	wipeOut ( freeMap[0]-'0', freeMap[0]-'0', COMPUTER);
}

/** Display an error message */
void KBoxes::error () const{
	std::cerr << "ERROR!" << '\a' << std::endl;
}
/** Come here when the player wins. */
void KBoxes::playerWins()
{
	QMessageBox message;	
	message.setText ("Well done!  You win!");
	message.setCaption ("KBoxes! - End of Game");
	message.show();
}
/** come here when the player looses */
void KBoxes::playerLooses()
{
	QMessageBox message;	
	message.setText ("Oh no, you loose!  Better luck next time...");
	message.setCaption ("KBoxes! - End of Game");
	message.show();
}

/** Wipe some boxes  */
void KBoxes::wipeOut(int first, int last, player_type player)
{
	for ( int i = first; i <= last ; i++ ) {
		map[i]='x';
		buttons[i]->setText("X");
	}
	clicked = -1;

	/* Delete the wiped out boxes from the freeboxes list */
	int counter = 0; int first_c, last_c;
	do {
		first_c = freeMap[counter++]-'0';
		last_c = freeMap[counter++]-'0';
	} while (!( first >= first_c && last <= last_c ));		// Until the upper-bound and lower bound is found
	freeMap = freeMap.substr ( 0, counter-2) + freeMap.substr ( counter, freeMap.length()-counter );	// delete old partition
	if ( first_c != first ) {					// if there are still boxes left on the one side,
		freeMap += (char)(first_c + '0');		// add these boxes
		freeMap += (char)(first -1 +'0');
	}
	if ( last_c != last ) {					// if there are still boxes left on the other side,
		freeMap += (char)(last +1 +'0');		// add these boxes
		freeMap += (char)(last_c+'0');
	}
	if ( freeMap == "" ) {
		if ( player == PLAYER ) {
			playerLooses();
		}
		else {
			playerWins();
		}
	}
}
/** Count how many spaces a string has */
int KBoxes::countSpaces ( const std::string & str) const
{
	int res = 0;
	int length = str.length();
	for ( int i = 0 ; i < length ; i++ ) {
		if ( str[i]==' ' ) {
			res ++ ;
		}
	}
	return res;
}

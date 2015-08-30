/***************************************************************************
                          kboxes.h  -  description
                             -------------------
    begin                : Πεμ Ιαν 20 17:36:13 EET 2000
    copyright            : (C) 2000 by Panos Katsaloulis
    email                : panayotis@panayotis.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KBOXES_H
#define KBOXES_H

// include files for QT
#include <qpopupmenu.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qpixmap.h>
#include <qapp.h>
#include <qmsgbox.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>

// application specific includes
#include "resource.h"
#include <iostream>
#include <string>
#include <cmath>

/**
  * This Class is the base class for your application. It sets up the main
  * window and providing a menubar, toolbar
  * and statusbar. For the main view, an instance of class KBoxesView is
  * created which creates your view.
  */
class KBoxes : public QMainWindow
{
  Q_OBJECT
  
  public:
    /** construtor */
    KBoxes();
    /** destructor */
    ~KBoxes();

  public slots:
  
    /** Start a new game */
    void slotGameNew();
    /** Undos the current move */
    void slotGameUndo();
    /** exits the application */
    void slotGameExit();

    /** set the level to a new nomber */
    void slotSkillChanged(int);

    /** Set program for one player*/
    void slotOptionsOne();
    /** Set program for two players*/
    void slotOptionsTwo();
    /** Set set who plays first - computer or user*/
    void slotOptionsFirst();

    /** shows an about dlg*/
    void slotHelpAbout();
    /** shows a how to play dlg*/
    void slotHelpHowto();
	/** Every button click comes through here. */	
	void slotPlayButtons(int);

  private:


	enum player_type { PLAYER, COMPUTER } ;

    /** file_menu contains all items of the menubar entry "File" */
    QPopupMenu *gameMenu;
    /** edit_menu contains all items of the menubar entry "Skill" */
    QPopupMenu *skillMenu;
    /** view_menu contains all items of the menubar entry "View" */
    QPopupMenu *optionsMenu;
    /** view_menu contains all items of the menubar entry "Help" */
    QPopupMenu *helpMenu;
	QPushButton * buttons[16];
	QButtonGroup * group;

    /** initMenuBar creates the menu_bar and inserts the menuitems */
    void initMenuBar();
    /** initButtons creates the various buttons on the game-space */
    void initButtons();
	/** Initialize the system data. This function is called only once, in the beginning */
	void initFirstTime();
	/** Prepare the program for a new Game. */
	void initGame ();
	/** The computer does its move */
	void playComputer();
	/** Display an error message */
	void error () const;
	/** Wipe some boxes  */
	void wipeOut(int, int, player_type);
	/** come here when the player looses */
	void playerLooses();
	/** Come here when the player wins. */
	void playerWins();
	/** Count how many spaces a string has */
	int countSpaces ( const std::string & str) const;

	/** How smart the program should be */
	int skill;
	/** Number of players */
	int no_of_players;
	/** Set whether or not computer plays first */
	bool computer_plays_first;

	/** Store the number of the last selected box. Become -1 if none is selected. */
	int clicked;
	/** Artficial "inteligence" level data */
	std::string level[34];
	/** General map of boxes */
	char map[17];	// last positions stores the null character;
	/** Map of free areas. Contains 2 characters per entry.
	First character is the position of the first box and second of the last.
	There is a difference between this version and the VB one. In the VB version we store
	as the second character the lenght, here we store the position. One more: in VB we store characters in
	hexadecimal, here we care only of the char-'0' value. */
	std::string freeMap;

};

#define ID_ONE_PLAYER 1000
#define ID_TWO_PLAYERS 1001
#define ID_FIRST_COMPUTER 2000

#define ID_DIFFICULTY_BASE 3000
#define ID_DIFFICULTY_BEGIN ID_DIFFICULTY_BASE
#define ID_DIFFICULTY_INTER ID_DIFFICULTY_BASE+1
#define ID_DIFFICULTY_PROF ID_DIFFICULTY_BASE+2
#define ID_DIFFICULTY_IMPOS ID_DIFFICULTY_BASE+3

#define SKILL_BEGIN 5
#define SKILL_INTER 10
#define SKILL_PROF 14
#define SKILL_IMPOS 34


#endif


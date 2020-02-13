// File: GameWin.cpp
// Author: 
// Project: CS215 Project 3 Fall 2018
// Description of file contents:

#include <afxwin.h>
#include "GameWin.h"

GameWin::GameWin ()
{
	// This function will:

	CString WindowTitle = "SpongeBob Reversi Pants";
	Create (NULL, WindowTitle);
	myGameP = new Game (this);
	firstTime = true;
}

afx_msg void GameWin::OnPaint ()
{
	// This function will: During the first play will start the sound, display instructions, and intitialize 
	//the first game.

	myGameP->Display ();
	if (firstTime)
	{
		BOOL soundPlayed = PlaySound(CString("SOUND_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		myGameP->Instructions();
		myGameP->Init();		
		Invalidate (TRUE);
		firstTime = false;
	}
}

afx_msg void GameWin::OnLButtonDown( UINT nFlags, CPoint point )
{
	// This function will: handle any left button clicks

	myGameP->Click (point);
}

afx_msg void GameWin::OnLButtonDblClk( UINT nFlags, CPoint point )
{	
	// This function will: not used

	OnLButtonDown (nFlags, point);
}

afx_msg void GameWin::OnTimer (UINT nIDEvent)
{	
	// This function will: Handle timer events

	if (nIDEvent == 1)
		myGameP->FlipCells (); 
}

BEGIN_MESSAGE_MAP (GameWin, CFrameWnd)
	ON_WM_PAINT ()
	ON_WM_LBUTTONDOWN ()
	ON_WM_LBUTTONDBLCLK ()
	ON_WM_TIMER ()
END_MESSAGE_MAP ()

#pragma once
#include <afxwin.h>
#include <mmsystem.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

const int ROWS = 8;
const int COLS = 8;
#define NUMIMAGES 3

enum playerType {NONE, HUMAN, COMPUTER};

class Game
{
	public:
		Game (CFrameWnd *WP);
		void Init ();
		void Instructions ();
		void Display ();
		void Click (CPoint point);
		int FlipCells ();
		playerType Winner ();
		void Sounds();
	private:
		struct Cell
		{
			Cell ();
			void Display (CDC * deviceContextP);
			playerType owner;
			CRect where;
		};
		struct RCPair
		{
			RCPair ();
			RCPair (int R, int C);
			int row;
			int col;
		};
		Cell board [ROWS+2][COLS+2];
		int score[3];
		playerType whoseTurn;
		RCPair moveRC;
		vector <RCPair> flips;
		CFrameWnd * windowP;
		CRect currentRect;
		CRect gameRect;
		CRect scoreRect;
		CRect humanScoreRect;
		CRect computerScoreRect;
		CRect buttonRect;
		CRect restartRect;
		CRect rulesRect;
		CBitmap bgImage;
		int Direct[8];
		int ScoreCount;

		bool Done ();
		void SetUp (CRect window);
		void DisplayGameRect (CDC * deviceContextP);
		void DisplayScoreRect (CDC * deviceContextP);
		void DisplayButtonRect (CDC * deviceContextP);
		bool ValidMove (playerType Who, int Row, int Col);
		bool CheckBoard (playerType Who);
		void CalculateScores ();
		void MakeMove (playerType Who, int Row, int ColP);
		bool ChooseMove (playerType Who, int & Row, int & Col);	
		

};

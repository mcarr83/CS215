//Name: Michael Carr
#include "Game.h"
#include <iomanip>
#include <windows.h>

static CBitmap images [NUMIMAGES];
static COLORREF colors [NUMIMAGES];

//Default constuctor for RCPair
Game::RCPair::RCPair ()
{
	row = -1;
	col = -1;
}
//RCPair mutator
Game::RCPair::RCPair (int R, int C)
{
	row = R;
	col = C;
}

//Cell default constructor
Game::Cell::Cell ()
{
	owner = NONE;
}

void Game::Cell::Display(CDC * deviceContextP)
{
	deviceContextP->Rectangle(where);
	if (owner != NONE)	
	{
		CDC memDC;
		int res2 = memDC.CreateCompatibleDC(deviceContextP);
		memDC.SelectObject(&images[owner]);
		res2 = deviceContextP->TransparentBlt (where.left+1, where.top+1, where.Width()-2, where.Height()-2,
			&memDC, 0, 0, 290, 290, 1);
		DeleteDC (memDC);
	}
}

Game::Game (CFrameWnd * WP)
{
	windowP = WP;
	int res = bgImage.LoadBitmap(CString("BACKGROUND_BMP"));
	res = images[HUMAN].LoadBitmap(CString("HUMAN_GAME_PIECE_BMP"));
	res = images[COMPUTER].LoadBitmap(CString("COMPUTER_GAME_PIECE_BMP"));		
	colors[COMPUTER] = RGB (255, 255, 255);
	colors[HUMAN] = RGB(80, 123, 187);
	Init ();
}
//Intitially sets up the board. Two pieces and score set at 2 each.
void Game::Init ()
{
	Cell cell;
	for (int r = 1; r <= ROWS; r++)
		for (int c = 1; c <= COLS; c++)
			board[r][c] = cell;
	board[ROWS/2][COLS/2].owner = COMPUTER;
	board[ROWS/2][COLS/2+1].owner = HUMAN;
	board[ROWS/2+1][COLS/2].owner = HUMAN;
	board[ROWS/2+1][COLS/2+1].owner = COMPUTER;
	score[HUMAN] = 2;
	score[COMPUTER] = 2;
	whoseTurn = HUMAN;
	CheckBoard (HUMAN);
	CheckBoard (COMPUTER);
	currentRect = CRect();
	windowP->Invalidate(TRUE);
}

//What is printed at the beginning of a new window in to window atop game board.
void Game::Instructions ()
{
	CString message = "Welcome to SpongeBob Reversi Pants\n\n";

	message += "Instructions\n\n";
	
	message += "Ahoy Matey!\n";
	message += "Patrick has challenged you to a game of reversi or othello among some \n";
	message += "swabbers. Ye object is simple, flank Patrick's pieces and flip\n";
	message += "over more than him. At ye end of the game is considered when one \n";
	message += "swashbuckler has run out of moves and has more pieces on the board \n";
	message += "than the other.\n";
	message += "Yo - ho - ho!!! \n\n";

	message += "You don’t need a license to drive a sandwich.\n";
	message += "-SpongeBob";
	windowP->MessageBox (message, CString ("Instructions to SpongeBob Reversi Pants"));
}

//Sets up parameters for what happens if something is clicked within game window.
void Game::Click (CPoint point)
{
// This function will:
	if (whoseTurn != HUMAN)
		return;
	if (rulesRect.PtInRect(point))
		Instructions();
	else if (restartRect.PtInRect(point))
		Init();
	else if (gameRect.PtInRect(point))
	{
		int row = -1, col = -1;
		for (int r = 1; row == -1 && r <= ROWS; r++)
			for (int c = 1; col == -1 && c <= COLS; c++)
				if (board[r][c].where.PtInRect(point))
				{
					row = r;
					col = c;
				}
		if (ValidMove (whoseTurn, row, col))
			MakeMove (whoseTurn, row, col);
	}
}


void Game::Display () 
{
// This function will:
	CPaintDC dc (windowP);
	CRect rect;
	windowP->GetClientRect (&rect);
	if (rect != currentRect)
	{	
		SetUp (rect);
		currentRect = rect;
	}
	dc.SetBkMode(TRANSPARENT);			
	CDC memDC;
	int res = memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&bgImage);
	dc.TransparentBlt (0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 1590, 795, SRCCOPY); 
	DeleteDC (memDC);
	CBrush * newBrush = new CBrush (RGB (255, 255, 255));
	CBrush * saveBrush = dc.SelectObject(newBrush);
	CPen * newPen = new CPen;
	newPen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen * savePen = dc.SelectObject(newPen);
	CFont font;
	CString fontName = "Snap ITC";
	font.CreatePointFont(rect.Height() / 4, fontName, &dc);
	COLORREF def_color = dc.SetTextColor(RGB(18, 129, 213));//added for text color
	CFont* def_font = dc.SelectObject(&font);
	DisplayGameRect (&dc);
	DisplayScoreRect (&dc);
	DisplayButtonRect (&dc);
	dc.SelectObject(def_font);
	dc.SelectObject(saveBrush);
	delete newBrush;
	dc.SelectObject(savePen);
	delete newPen;
}

void Game::SetUp (CRect rect)
{
// This function will: set up all the Rects used for buttons, score and gameboard. 

	int width = rect.Width();
	int height =  rect.Height();
	gameRect = CRect (width/6, height/12, 2*width/4, 10*height/12);
	scoreRect = CRect (2*width/3, height/2, 12*width/12, 15*height/17);
	height = scoreRect.Height();
	humanScoreRect = scoreRect;
	humanScoreRect.bottom -= height/2;//top human
	computerScoreRect = scoreRect;
	computerScoreRect.top += height/2;//top computer
	buttonRect = CRect (width/65, height/4, width/6, 11*height/16);
	height = buttonRect.Height();
	restartRect = CRect (buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.top + height/2);
	rulesRect = CRect (buttonRect.left, buttonRect.top+height/2, buttonRect.right, buttonRect.bottom);
	width = gameRect.Width() / ROWS;
	height = gameRect.Height() / COLS;	
	int tlx = gameRect.TopLeft().x + (gameRect.Width() - COLS*width) / 2;
	int tly = gameRect.TopLeft().y + (gameRect.Height() - ROWS*height) / 2;
	for (int r = 1; r <= ROWS; r++)
		for (int c = 1; c <= COLS; c++)
			board[r][c].where = CRect (tlx+(c-1)*width, tly+(r-1)*height, tlx+c*width, tly+r*height);
}

void Game::DisplayGameRect (CDC * deviceContextP)
{
// This function will print out the game board in the rectangle defined above.
	
	deviceContextP->Rectangle(gameRect);
	for (int r = 1; r <= ROWS; r++)
		for (int c = 1; c <= COLS; c++)
			board[r][c].Display (deviceContextP);
}

void Game::DisplayScoreRect (CDC * deviceContextP)
{ 
// This function will: Display play name and score.
	
	//deviceContextP->Rectangle(humanScoreRect); commented out for its not to be seen 
	//deviceContextP->Rectangle(computerScoreRect); commented out for its not to be seen

	int quarterH = scoreRect.Height() / 4;
	CRect text = humanScoreRect;
	text.bottom -= quarterH;
	char msgString [100] = ""; //left in for what ifs. Not shown on screen.
	deviceContextP->DrawText(CString (msgString), text, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	text = humanScoreRect;
	text.top += quarterH;
	sprintf_s (msgString, "%d", score[HUMAN]);//Human score(SpongeBab)
	deviceContextP->DrawText(CString (msgString), text, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	text = computerScoreRect;
	text.bottom -= quarterH;
	strcpy_s (msgString, "");//left in for what ifs. Not shown on screen.
	deviceContextP->DrawText(CString (msgString), text, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	text = computerScoreRect;
	text.top += quarterH;
	sprintf_s (msgString, "%d", score[COMPUTER]);//Ai score (Patrick)
	deviceContextP->DrawText(CString (msgString), text, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

void Game::DisplayButtonRect (CDC * deviceContextP)
{
	//deviceContextP->Rectangle (rulesRect); White rect commented out as to not be seen
	deviceContextP->DrawText ("", rulesRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	//deviceContextP->Rectangle (restartRect); White rect commented out as to not be seen
	
	deviceContextP->DrawText ("", restartRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

//Checks board to see if there is any more moves
bool Game::CheckBoard (playerType Who)
{
	for (int r = 1; r <= ROWS; r++) {

		for (int c = 1; c <= COLS; c++) {
			if (ValidMove(Who, r, c) == true)
				return true;
		}
	}
	
	return false;

}

//Makes sure there is a valid move and if so plays sounds. If not returns false.
bool Game::ValidMove (playerType Who, int Row, int Col)
{
	//setting variable other to human  or computer based on if statement
	//if Who equals HUMAN, it will become COMPUTER else COMPUTER will become
	//HUMAN

	playerType other = Who == HUMAN ? COMPUTER : HUMAN;

	for (int i = 0; i < 8; i++) {
		Direct[i] = 0;
	}
	int totalcount = 0;
	int count = 0;


	//checks if there is a human or AI in the position the player or
	//opponent is trying to go.

	if (board[Row][Col].owner != NONE) {
		return false;
	}


	//-------down to left check**
	int r = Row + 1;
	int c = Col - 1;

	while (board[r][c].owner == other) {
		count++;
		r++;
		c--;

	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[0] = 1;

	}

	//------to the left check**
	count = 0;
	r = Row;
	c = Col - 1;

	while (board[r][c].owner == other) {
		count++;
		c--;
	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[1] = 1;

	}

	//------left and up check**
	count = 0;
	r = Row - 1;
	c = Col - 1;

	while (board[r][c].owner == other) {
		count++;
		c--;
		r--;
	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[2] = 1;

	}

	//-----straight up check**
	count = 0;
	r = Row - 1;
	c = Col;

	while (board[r][c].owner == other) {
		count++;
		r--;
	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[3] = 1;

	}

	//-----up and to the right check**
	count = 0;
	r = Row - 1;
	c = Col + 1;

	while (board[r][c].owner == other) {
		count++;
		r--;
		c++;
	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[4] = 1;

	}

	//-----To the right check**
	count = 0;
	r = Row;
	c = Col + 1;

	while (board[r][c].owner == other) {
		count++;
		c++;
	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[5] = 1;

	}

	//------down and to the right check
	count = 0;
	r = Row + 1;
	c = Col + 1;

	while (board[r][c].owner == other) {
		count++;
		r++;
		c++;
	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[6] = 1;

	}

	//-------straight down check
	count = 0;
	r = Row + 1;
	c = Col;

	while (board[r][c].owner == other) {
		count++;
		r++;
	}

	if (count > 0 && board[r][c].owner == Who) {
		totalcount += count;
		Direct[7] = 1;

	}

	
	if (totalcount > 0) {
		
		return true;
	}
	else {
		return false;
	}
	
	
	
}

//Makes the move and then uses FlipCells() to flip game pieces
void Game::MakeMove (playerType Who, int Row, int Col)
{
	playerType other = Who == HUMAN ? COMPUTER : HUMAN;

	
	int scoreCount = 0;
	
	//checked lower left---------------------------------------------------
	if (Direct[0] == 1) {
		//board[Row][Col].owner = Who; left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row + 1;
		c = Col - 1;

		while (board[r][c].owner == other) {
			count++;
			r++;
			c--;

		}

		for (int i = 0; i < count; i++) {

			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			r--;
			c++;
		}

		scoreCount += count;
	}

	//checked to the left----------------------------------------------------
	if (Direct[1] == 1) {
		//board[Row][Col].owner = Who;left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row;
		c = Col;

		while (board[r][c - 1].owner == other) {
			count++;
			c--;
		}

		for (int i = 0; i < count; i++) {
			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			c++;
		}
		scoreCount += count;
	}

	//checked upper left-----------------------------------------------------
	if (Direct[2] == 1) {
		//board[Row][Col].owner = Who;left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row;
		c = Col;

		while (board[r - 1][c - 1].owner == other) {
			c--;
			r--;
			count++;
		}

		for (int i = 0; i < count; i++) {
			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			c++;
			r++;
		}
		scoreCount += count;

	}


	//checked direct up------------------------------------------------------
	if (Direct[3] == 1) {
		//board[Row][Col].owner = Who;left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row;
		c = Col;

		while (board[r - 1][c].owner == other) {
			count++;
			r--;
		}

		for (int i = 0; i < count; i++) {
			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			r++;

		}
		scoreCount += count;

	}


	//checked upper right--------------------------------------------------
	if (Direct[4] == 1) {
		//board[Row][Col].owner = Who;left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row;
		c = Col;

		while (board[r - 1][c + 1].owner == other) {
			count++;
			r--;
			c++;

		}


		for (int i = 0; i < count; i++) {
			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			r++;
			c--;
		}

		scoreCount += count;

	}

	//checked to the right-------------------------------------------------
	if (Direct[5] == 1) {
		//board[Row][Col].owner = Who;left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row;
		c = Col;

		while (board[r][c + 1].owner == other) {
			count++;
			c++;
		}

		for (int i = 0; i < count; i++) {
			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			c--;
		}
		scoreCount += count;
	}

	//checked lower right---------------------------------------------------
	if (Direct[6] == 1) {
		//board[Row][Col].owner = Who;left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row;
		c = Col;

		while (board[r + 1][c + 1].owner == other) {
			count++;
			c++;
			r++;
		}

		for (int i = 0; i < count; i++) {
			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			c--;
			r--;

		}
		scoreCount += count;
	}

	//checked direct down------------------------------------------------------
	if (Direct[7] == 1) {
		//board[Row][Col].owner = Who;left in from project2

		int count = 0;
		int c = 0;
		int r = 0;

		r = Row;
		c = Col;

		while (board[r + 1][c].owner == other) {
			count++;
			r++;
		}

		for (int i = 0; i < count; i++) {

			board[r][c].owner = Who;
			RCPair rcpair;
			rcpair.row = r;
			rcpair.col = c;
			flips.push_back(rcpair);
			r--;
		}
		scoreCount += count;

	}

	//if scoreCount is greater than 0, make a struct object, put Row and Col in it and put it in vector flips
	if (scoreCount > 0) {
		RCPair rcpair;
		rcpair.row = Row;
		rcpair.col = Col;
		flips.push_back(rcpair);
	}
	//globial variable used for CalculateScore();
	ScoreCount = scoreCount;
	windowP->SetTimer(1, 500, NULL);
	
}

//Flips pieces
int Game::FlipCells ()
{
	if (flips.size() > 0)
	{
		if (whoseTurn == COMPUTER) {
			Sounds();
		}
		int r = flips[0].row;
		int c = flips[0].col;
		flips.erase(flips.begin());
		board[r][c].owner = whoseTurn;
		windowP->InvalidateRect (board[r][c].where, TRUE);
	}
	else
	{
		windowP->KillTimer(1);
		int r = moveRC.row, c = moveRC.col;
		windowP->InvalidateRect (board[r][c].where, TRUE);
		CalculateScores();
		windowP->InvalidateRect(scoreRect, TRUE);
		CheckBoard (HUMAN);
		CheckBoard (COMPUTER);
		if (Done())
		{
			whoseTurn = NONE; 
			Winner();
		}
		else if (whoseTurn == HUMAN)
			whoseTurn = COMPUTER;
		else if (whoseTurn == COMPUTER)
			whoseTurn = HUMAN;
		if (whoseTurn == COMPUTER)
		{
				int r = -1;
				int c = -1;
				ChooseMove (COMPUTER, r, c);
				MakeMove (COMPUTER, r, c);
		}
	}
	return 0;
}	

bool Game::ChooseMove (playerType Who, int & Row, int & Col)
{ // AI determines desired location of move (Codename: Brute Force)

	

	if (!CheckBoard(Who))
		return false;

	srand(time(0));
	int Ran1 = rand() % 8 + 1;
	int Ran2 = rand() % 8 + 1;

	Row = Ran1;
	Col = Ran2;

	while (!ValidMove(Who, Row, Col)) {

		Ran1 = rand() % 8 + 1;
		Ran2 = rand() % 8 + 1;

		Row = Ran1;
		Col = Ran2;

	}
	return true;

}

//Calculates score from the move and how many flips in ScoreCount variable
void Game::CalculateScores ()
{
	playerType other = whoseTurn == HUMAN ? COMPUTER : HUMAN;
	
	int totalsCount = 1;
	int otherScore = 0;
	
	totalsCount = ScoreCount + totalsCount;
	otherScore = ScoreCount;


	score[whoseTurn] += totalsCount;
	score[other] -= otherScore;

}

//if checkboard returns false for both human and Ai return true
bool Game::Done ()
{
	if (!CheckBoard(HUMAN) && !CheckBoard(COMPUTER))
		return true;

	return false;

}

//Winner determined by highest score followed by a pop up message and sound.
playerType Game::Winner ()
{
	CString message = "The winner is....";
	playerType winner = NONE;
	if (score[HUMAN] < score[COMPUTER]) {
		winner = COMPUTER;
		message += "Patrick\n";
		BOOL soundPlayed = PlaySound(CString("SOUND4_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	}


	else  if (score[HUMAN] > score[COMPUTER]) {
		winner = HUMAN;
		message += "SpongeBob\n";
		BOOL soundPlayed = PlaySound(CString("SOUND3_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

	}

	else {
		winner = NONE;
		message += "Both Patrick and SpongeBob\n";
		message += "Yay!";
		BOOL soundPlayed = PlaySound(CString("SOUND2_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	}

	windowP->MessageBox(message, CString("Game Over"));
	Init();
	return winner; 
}

//Called when there is a sound to be plyed during game play.
void Game::Sounds() {
	int value = 0;
	srand(time(0)); //random based on time
	value = rand() % 14 + 1; //uses values 1 to 14

	if (value == 1)
		BOOL soundPlayed = PlaySound(CString("SOUND5_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 2)
		BOOL soundPlayed = PlaySound(CString("SOUND6_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 3)
		BOOL soundPlayed = PlaySound(CString("SOUND7_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 4)
		BOOL soundPlayed = PlaySound(CString("SOUND8_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 5)
		BOOL soundPlayed = PlaySound(CString("SOUND9_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 6)
		BOOL soundPlayed = PlaySound(CString("SOUND10_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 7)
		BOOL soundPlayed = PlaySound(CString("SOUND11_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 8)
		BOOL soundPlayed = PlaySound(CString("SOUND12_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 9)
		BOOL soundPlayed = PlaySound(CString("SOUND13_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 10)
		BOOL soundPlayed = PlaySound(CString("SOUND14_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 11)
		BOOL soundPlayed = PlaySound(CString("SOUND15_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 12)
		BOOL soundPlayed = PlaySound(CString("SOUND16_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	if (value == 13)
		BOOL soundPlayed = PlaySound(CString("SOUND17_WAV"), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
}
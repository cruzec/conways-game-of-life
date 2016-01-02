  /**************************************************
 * Author: Eric Cruz
 * Date: 11/18/2014
 * Last Modification Date: 11/19/2014
 * File name: gameOfLife.cpp
 *
 * Overview:	This is an implementation of Conway's Game of Life.
 *						The standard rules (pulled from Wikipedia):
 *							1. Any live cell with less than two live neighbors
 *							dies.
 *							2. Any live cell with two or three live neighbors
 *							lives.
 *							3. Any live cell with more than three live neighbors
 *							dies.
 *							4. Any dead cell with three live neighbors becomes
 *							a live cell.
 *						This adaptation prompts the user to enter an integer
 *						between 1 and 100. This will populate the board with
 *						gliders and blocks. The user must press enter to
 *						display the next generation or enter the letter 'Q' 
 *						to terminate the program.
 *
 * Input:  		The user enters an integer for initial population of the
 *						board. He or she then can press enter to keep
 *						generating or enter 'Q' to exit the program.
 *
 * Output:		The output is a display of each generation of cells.
 *						The default configuration is 22 rows by 80 columns.
 *        
 * **************************************************/
 
 #include <iostream>
 #include <string>
 
 using std::cout;
 using std::cin;
 using std::endl;
 using std::string;
 
 int ROWS = 22;
 int COLUMNS = 80;
 
 class LifeGrid
 {
	private:
		bool board[22][80];
		bool copy[22][80];
		
	public:
		void initialPopulate(int);
		void generate();
		void display();
 };
 
 /**************************************************
 *
 * 	Entry:		"init" is the integer inputted by the user
 *
 * 	Exit:			The function generates the initial state of the board
 *
 * Purpose:		The purpose of this function is to generate the 
 *						initial state of the board according to the user'sb_type
 *						input.
 *        
 * **************************************************/
 
 void LifeGrid::initialPopulate(int init)
 {
	// Initially sets all elements to false
	for(int i = 0; i < ROWS; i++)
	{
		for(int u = 0; u < COLUMNS; u++)
		{
			board[i][u] = false;
		}
	}
	
	// Creates an amount of gliders dependent on user input
	int counter = 0;
	for(int i = 0; i < ROWS; i += 10)
	{
		if(counter == init)
		{
			break;
		}
		
		for(int u = 0; u < COLUMNS; u += 6)
		{
			board[i][(u + 1) % COLUMNS] = true;
			board[(i + 1) % ROWS][(u + 2) % COLUMNS] = true;
			board[(i + 2) % ROWS][u] = true;
			board[(i + 2) % ROWS][(u + 1) % COLUMNS] = true;
			board[(i + 2) % ROWS][(u + 2) % COLUMNS] = true;
			
			++counter;
			
			if(counter == init)
			{
				break;
			}
		}
	}
	
	// Creates an amount of blocks dependent on user input
	counter = 0;
	for(int i = 0; i < ROWS; i += 8)
	{
		if(counter == init)
		{
			break;
		}
		
		for(int u = 0; u < COLUMNS; u += 5)
		{
			board[(i + 6) % ROWS][(u + 1) % COLUMNS] = true;
			board[(i + 6) % ROWS][(u + 2) % COLUMNS] = true;
			board[(i + 7) % ROWS][(u + 1) % COLUMNS] = true;
			board[(i + 7) % ROWS][(u + 2) % COLUMNS] = true;
			
			++counter;
			
			if(counter == init)
			{
				break;
			}
		}
	}
	
	// Copies board's elements to copy's elements
	for(int i = 0; i < ROWS; i++)
	{
		for(int u = 0; u < COLUMNS; u++)
		{
			copy[i][u] = board[i][u];
		}
	}
 }
 
 /**************************************************
 *
 * 	Entry:		none
 *
 * 	Exit:			This function sets the board's cells to true or false
 *						according to the four rules of Conway's Game of
 *						Life
 *
 * Purpose:		The purpose of this function is to count the neighbouring
 *						cells of each cell and distinguish whether the cell
 *						is now alive or dead.
 *        
 * **************************************************/
 
 void LifeGrid::generate()
 {
	for(int i = 0; i < ROWS; i++)
	{
		for(int u = 0; u < COLUMNS; u++)
		{
			int neighbors = 0;
			
			// Mod wrap-around code was borrowed from user 'modulo_function' on Yahoo! Answers
			// https://answers.yahoo.com/question/index?qid=20100728204914AAtTSom
			if(copy[(i + ROWS - 1) % ROWS][(u + COLUMNS - 1) % COLUMNS] == true)
			{
				++neighbors;
			}
			
			if(copy[(i + ROWS - 1) % ROWS][u] == true)
			{
				++neighbors;
			}
			
			if(copy[(i + ROWS - 1) % ROWS][(u + 1) % COLUMNS] == true)
			{
				++neighbors;
			}
			
			if(copy[i][(u + COLUMNS - 1) % COLUMNS] == true)
			{
				++neighbors;
			}
			
			if(copy[i][(u + 1) % COLUMNS] == true)
			{
				++neighbors;
			}
			
			if(copy[(i + 1) % ROWS][(u + COLUMNS - 1) % COLUMNS] == true)
			{
				++neighbors;
			}
			
			if(copy[(i + 1) % ROWS][u] == true)
			{
				++neighbors;
			}
			
			if(copy[(i + 1) % ROWS][(u + 1) % COLUMNS] == true)
			{
				++neighbors;
			}
			
			// Rules of Conway's Game of Life
			if(neighbors < 2 && board[i][u] == true)
			{
				board[i][u] = false;
			}
			else if((neighbors == 2 || neighbors == 3) && board[i][u] == true)
			{
				board[i][u] = true;
			}
			else if(neighbors > 3 && board[i][u] == true)
			{
				board[i][u] = false;
			}
			else if(neighbors == 3 && board[i][u] == false)
			{
				board[i][u] = true;
			}
		}
	}
	
	for(int i = 0; i < ROWS; i++)
	{
		for(int u = 0; u < COLUMNS; u++)
		{
			copy[i][u] = board[i][u];
		}
	}
 }
 
 /**************************************************
 *
 * 	Entry:		none
 *
 * 	Exit:			This function displays an asterisk to represent a 
 *						live cell and a blank space to represent a dead 
 *						cell.
 *
 * Purpose:		The purpose of this function is to display the board
 *						to the user according to the live or dead state
 *						of each cell.
 *        
 * **************************************************/
 
 void LifeGrid::display()
 {
	for(int i = 0; i < ROWS; i++)
	{
		for(int u = 0; u < COLUMNS; u++)
		{
			if(board[i][u] == true)
			{
				cout << '*';
			}
			else if(board[i][u] == false)
			{
				cout << ' ';
			}
		}
		cout << endl;
	}
 }

 int main()
 {
	char confirm; 
	int initialCells;
	cout << "This is an implementation of Conway's Game of Life!" << endl;
	cout << "Enter a starting amount between 1 and 100: ";
	cin >> initialCells;
	
	// Check if input is a number between 1 and 100
	while(!(cin) || initialCells < 1 || initialCells > 100) 
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid input. Enter a starting amount between 1 and 100: " << endl;
		cin >> initialCells;
	}

	cin.ignore(1000, '\n');
	
	LifeGrid life; 
	life.initialPopulate(initialCells);
	
	do
	{	
		life.display();
		life.generate();
		
		string running;
		cout << "Press ENTER for next generation. (Enter Q to quit)" << endl;
		getline(cin, running);
		confirm = running[0];
		
	} while(!(confirm == 'q' || confirm == 'Q'));
	
	cout << "Exiting game" << endl;
	
	return 0;
 }
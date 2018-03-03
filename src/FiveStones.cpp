/*
   Program Name:     Subsequence.cpp
   Author:                    Matthew Chang
   Date:                         March 7, 2016
   Course:                     CPSC 1160 - 1
   Instructor:               Mingwu Chen
*/

//Purpose: To create Five Stones

#include <iostream>
#include <cstdlib>
using namespace std;

void DrawBoard();
void PlayerPosition();
void AIPlayer(int playerColumn, int playerRow);
void AIPosition(int playerColumn, int playerRow);
bool CheckPlayerMove(int& column, int& row, const char stone, const int countOfPlayer);
bool PlaceStone(int column, int row);
void AIPositionRandom();
bool CheckForWin(const char stone);
bool BoardFull();

// Set global variables
const int SIZE_OF_BOARD = 9;
char board[SIZE_OF_BOARD][SIZE_OF_BOARD];
int player = 1;
bool gameFinished = false;

int main()
{
   // Set every value in the 2D array to ' '
   for(int c = 0; c < SIZE_OF_BOARD; c++)
   {
      for(int r = 0; r < SIZE_OF_BOARD; r++)
      {
         board[c][r] = ' ';
      }
   }
   
   // Draw the board
   DrawBoard();
   
   // Continue the game while it is not finished
   while(!gameFinished)
   {
      player = 1;
      cout << "Player One" << endl;
      PlayerPosition();
      
      // If the board is full is true
      if(BoardFull())
      {
         // Display a tie message and set gameFinished to true
         cout << "TIE GAME" << endl;
         gameFinished = true;
      }
      // Draw the board
      DrawBoard();
   }
   // If player is one, display that they won
   if(player == 1)
      cout << "PLAYER ONE WINS" << endl;
   // If player is not one, display that player two won
   else
      cout << "PLAYER TWO WINS" << endl;
   
   return 0;
}
// Draws the board
void DrawBoard()
{
   // Draw the letters
   cout << "    ";
   for(int i = 0; i < SIZE_OF_BOARD; i++)
   {
      char letter = i + 97;
      cout << letter << "   ";
   }
   cout << endl;
   
   // Draw the rows and columns of the board
   for(int c = 0; c < SIZE_OF_BOARD; c++)
   {
      cout << "  -------------------------------------" << endl;
      
      cout << c + 1;
      for(int r = 0; r < SIZE_OF_BOARD; r++)
      {
         cout << " | " << board[r][c];
         if(r == SIZE_OF_BOARD - 1)
         {
            cout << " |\n";
         }
      }
   }
   cout << "  -------------------------------------" << endl;
}
// Asks the user for a position to place a stone
void PlayerPosition()
{
   char column, row;
   
   // Ask the user for a column to put their stone
   cout << "Enter the column of your stone: ";
   cin  >> column;
   cout << endl;
   // If the enter a value outside of the board, ask the question again
   while(column < 'a' || column > 'i')
   {
      cout << "Invalid Input" << endl;
      cout << "Enter the column of your stone: ";
      cin  >> column;
      cout << endl;
   }
   
   // Ask the user for a row to put their stone
   cout << "Enter the row of your stone: ";
   cin  >> row;
   cout << endl;
   int intRow = row - '0';
   
   // If they enter a value outside of the board, ask the question again
   while(intRow > 9 || intRow < 1)
   {
      cout << "Invalid Input" << endl;
      cout << "Enter the row of your stone: ";
      cin  >> row;
      cout << endl;
      intRow = row - '0';
   }
   // Set the column to an int
   int intColumn = column - 96;
   
   // Call PlaceStone to place the stone
   PlaceStone(intColumn, intRow);
}
// The AI player
void AIPlayer(int playerColumn, int playerRow)
{
   // Set player to two and call AIPosition to get a position for it
   player = 2;
   cout << "Player Two" << endl;
   AIPosition(playerColumn, playerRow);
}
// Finds a position for the AI's stone
void AIPosition(int playerColumn, int playerRow)
{
   int column = 0, row = 0;
   // Trys to counter the player's move and if it is successful in finding one
   if(CheckPlayerMove(column, row, 'X', 4))
   {
      // Place a stone at that position
      PlaceStone(column + 1, row + 1);
   }
   else if(CheckPlayerMove(column, row, 'O', 4))
   {
      // Place a stone at that position
      PlaceStone(column + 1, row + 1);
   }
   // Trys to counter the player's move and if it is successful in finding one
   else if(CheckPlayerMove(column, row, 'X', 3))
   {
      // Place a stone at that position
      PlaceStone(column + 1, row + 1);
   }
   // Trys to counter the player's move and if it is successful in finding one
   else if(CheckPlayerMove(column, row, 'X', 2))
   {
      // Place a stone at that position
      PlaceStone(column + 1, row + 1);
   }
   // Place a stone in a free space above the player's stone
   else if(playerRow > 0 && board[playerColumn][playerRow - 1] == ' ')
   {
      PlaceStone(playerColumn + 1, playerRow);
   }
   // Place a stone in a free space to the right of the player's stone
   else if(playerColumn < SIZE_OF_BOARD - 2 && board[playerColumn + 1][playerRow] == ' ')
   {
      PlaceStone(playerColumn + 2, playerRow + 1);
   }
   // Place a stone in a free space below the player's stone
   else if(playerRow < SIZE_OF_BOARD - 2 && board[playerColumn][playerRow + 1] == ' ')
   {
      PlaceStone(playerColumn + 1, playerRow + 2);
   }
   // Place a stone in a free space to the left of the player's stone
   else if(playerColumn > 0 && board[playerColumn - 1][playerRow] == ' ')
   {
      PlaceStone(playerColumn, playerRow + 1);
   }
   // Place the stone in a random position
   else
   {
      AIPositionRandom();
   }
   // Check to see if the AI has won
   gameFinished = CheckForWin('O');
}
// Checks the player's stone position to find an optimal position to place a stone
bool CheckPlayerMove(int& column, int& row, const char stone, const int countOfPlayer)
{
   int count = 0;
   
   // Checks vertically to find a position to counter the player
   for(int c = 0; c < SIZE_OF_BOARD; c++)
   {
      count = 0;
      for(int r = 0; r < SIZE_OF_BOARD; r++)
      {
         // If the position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If there are several stones vertically in a column, place a stone below it
            if(count >= countOfPlayer && r < SIZE_OF_BOARD - 1 && board[c][r + 1] == ' ')
            {
               column = c;
               row = r + 1;
               return true;
            }
            // If there are several stones vertically in a column, place a stone above it
            if(count >= countOfPlayer && r > countOfPlayer - 1 && board[c][r - countOfPlayer] == ' ')
            {
               column = c;
               row = r - countOfPlayer;
               return true;
            }
         }
         else
            count = 0;
      }
   }
   
   // Checks horizontally to find a position to counter the player
   for(int r = 0; r < SIZE_OF_BOARD; r++)
   {
      count = 0;
      for(int c = 0; c < SIZE_OF_BOARD; c++)
      {
         // If the position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If there are several stones horzontally in a row, place a stone to the right of it
            if(count >= countOfPlayer && c < SIZE_OF_BOARD - 1 && board[c + 1][r] == ' ')
            {
               column = c + 1;
               row = r;
               return true;
            }
            // If there are several stones horzontally in a row, place a stone to the left of it
            if(count >= countOfPlayer && c > countOfPlayer - 1 && board[c - countOfPlayer][r] == ' ')
            {
               column = c - countOfPlayer;
               row = r;
               return true;
            }
         }
         else
            count = 0;
      }
   }
   
   // Checks diagonally from top-left to bottom-right to find a position to counter the player
   for(int i = 0; i < SIZE_OF_BOARD - 4; i++)
   {
      count = 0;
      for(int r = i, c = 0; r < SIZE_OF_BOARD; r++, c++)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If there are several stones diagonally, place a stone to the bottom-right of it
            if(count >= countOfPlayer && c < SIZE_OF_BOARD - 1 && r < SIZE_OF_BOARD - 1 && board[c + 1][r + 1] == ' ')
            {
               column = c + 1;
               row = r + 1;
               return true;
            }
            // If there are several stones diagonally, place a stone to the top-left of it
            if(count >= countOfPlayer && c > countOfPlayer - 1 && r > countOfPlayer - 1 && board[c - countOfPlayer][r - countOfPlayer] == ' ')
            {
               column = c - countOfPlayer;
               row = r - countOfPlayer;
               return true;
            }
         }
         else
            count = 0;
      }
      count = 0;
      
      for(int r = 0, c = i; r < SIZE_OF_BOARD; r++, c++)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If there are several stones diagonally, place a stone to the bottom-right of it
            if(count >= countOfPlayer && c < SIZE_OF_BOARD - 1 && r < SIZE_OF_BOARD - 1 && board[c + 1][r + 1] == ' ')
            {
               column = c + 1;
               row = r + 1;
               return true;
            }
            // If there are several stones diagonally, place a stone to the top-left of it
            if(count >= countOfPlayer && c > countOfPlayer - 1 && r > countOfPlayer - 1 && board[c - countOfPlayer][r - countOfPlayer] == ' ')
            {
               column = c - countOfPlayer;
               row = r - countOfPlayer;
               return true;
            }
         }
         else
            count = 0;
      }
      count = 0;
   }
   
   // Checks diagonally from top-right to bottom-left to find a position to counter the player
   for(int i = 0, s = SIZE_OF_BOARD - 1; i < SIZE_OF_BOARD - 4; i++, s--)
   {
      count = 0;
      for(int r = i, c = SIZE_OF_BOARD - 1; r < SIZE_OF_BOARD; r++, c--)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            
            // Increment count
            count++;
            // If there are several stones diagonally, place a stone to the bottom-left of it
            if(count >= countOfPlayer && c > 0 && r < SIZE_OF_BOARD - 1 && board[c - 1][r + 1] == ' ')
            {
               column = c - 1;
               row = r + 1;
               return true;
            }
            // If there are several stones diagonally, place a stone to the top-right of it
            if(count >= countOfPlayer && c < SIZE_OF_BOARD - countOfPlayer && r > countOfPlayer - 1 && board[c + countOfPlayer][r - countOfPlayer] == ' ')
            {
               column = c + countOfPlayer;
               row = r - countOfPlayer;
               return true;
            }
         }
         else
            count = 0;
      }
      count = 0;
      for(int r = 0, c = s; r < SIZE_OF_BOARD; r++, c--)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If there are several stones diagonally, place a stone to the bottom-left of it
            if(count >= countOfPlayer && c > 0 && r < SIZE_OF_BOARD - 1 && board[c - 1][r + 1] == ' ')
            {
               column = c - 1;
               row = r + 1;
               return true;
            }
            // If there are several stones diagonally, place a stone to the top-right of it
            if(count >= countOfPlayer && c < SIZE_OF_BOARD - countOfPlayer && r > countOfPlayer - 1 && board[c + countOfPlayer][r - countOfPlayer] == ' ')
            {
               column = c + countOfPlayer;
               row = r - countOfPlayer;
               return true;
            }
         }
         else
            count = 0;
      }
   }
   return false;
}
// Places the stone on the directed column and row
bool PlaceStone(int column, int row)
{
   // If the position to place the stone is not blank
   if(board[column - 1][row - 1] != ' ')
   {
      // If the player is one
      if(player == 1)
      {
         // Display and error and ask the user for another column and row
         cout << "Invalid position. Please try again." << endl << endl;
         PlayerPosition();
      }
      // If the player is not one
      else
      {
         // Call AIPositionRandom for a random position for the stone
         AIPositionRandom();
      }
      // Return false
      return false;
   }
   // If th eplayer is one
   if(player == 1)
   {
      // Put an 'X' and the directed column and row
      board[column - 1][row - 1] = 'X';
      // Check if the player has won
      gameFinished = CheckForWin('X');
      // If the game is finished return true
      if(gameFinished)
         return true;
      
      // If the board is full return true
      if(BoardFull())
         return true;
      
      // Draw the board
      DrawBoard();
      
      // Go to the AIPlayer for player two's turn
      AIPlayer(column - 1, row - 1);
   }
   // If the player is not one, put an 'O' at the directed position
   else
      board[column - 1][row - 1] = 'O';
   
   return true;
}
// Finds a random position on the board to place a stone
void AIPositionRandom()
{
   // Create a random row and column
   int column = rand() % 9 + 1;
   int row = rand() % 9 + 1;
   // Place a stone
   PlaceStone(column, row);
}
// Checks the board to see if there is a win
bool CheckForWin(const char stone)
{
   int count = 0;
   
   // Checks vertically for a win
   for(int c = 0; c < SIZE_OF_BOARD; c++)
   {
      for(int r = 0; r < SIZE_OF_BOARD; r++)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If the count is 5 or greater, return true
            if(count >= 5)
               return true;
         }
         // Reset the count if there is a gap
         else
            count = 0;
      }
   }
   count = 0;
   
   // Checks horizontally for a win
   for(int r = 0; r < SIZE_OF_BOARD; r++)
   {
      for(int c = 0; c < SIZE_OF_BOARD; c++)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If the count is 5 or greater, return true
            if(count >= 5)
               return true;
         }
         // Reset the count if there is a gap
         else
            count = 0;
      }
   }
   count = 0;
   
   // Checks diagonally from top-left to bottom-right for a win
   for(int i = 0; i < SIZE_OF_BOARD - 4; i++)
   {
      for(int r = i, c = 0; r < SIZE_OF_BOARD; r++, c++)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If the count is 5 or greater, return true
            if(count >= 5)
               return true;
         }
         // Reset the count if there is a gap
         else
            count = 0;
      }
      count = 0;
      for(int r = 0, c = i; r < SIZE_OF_BOARD; r++, c++)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If the count is 5 or greater, return true
            if(count >= 5)
               return true;
         }
         // Reset the count if there is a gap
         else
            count = 0;
      }
      count = 0;
   }
   count = 0;
   
   // Checks diagonally from top-right to bottom-left, for a win
   for(int i = 0, s = SIZE_OF_BOARD - 1; i < SIZE_OF_BOARD - 4; i++, s--)
   {
      for(int r = i, c = SIZE_OF_BOARD - 1; r < SIZE_OF_BOARD; r++, c--)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If the count is 5 or greater, return true
            if(count >= 5)
               return true;
         }
         // Reset the count if there is a gap
         else
            count = 0;
      }
      for(int r = 0, c = s; r < SIZE_OF_BOARD; r++, c--)
      {
         // If a position has a stone
         if(board[c][r] == stone)
         {
            // Increment count
            count++;
            // If the count is 5 or greater, return true
            if(count >= 5)
               return true;
         }
         // Reset the count if there is a gap
         else
            count = 0;
      }
   }
   return false;
}
// Checks the board to see if it is full
bool BoardFull()
{
   int count = 0;
   
   // Got throught the board and count every time there is not a blank
   for(int r = 0; r < SIZE_OF_BOARD; r++)
   {
      for(int c = 0; c < SIZE_OF_BOARD; c++)
      {
         if(board[c][r] != ' ')
            count++;
      }
   }
   
   // If the count equals the size of the board, return false
   if(count == SIZE_OF_BOARD * SIZE_OF_BOARD)
      return true;
   
   return false;
}

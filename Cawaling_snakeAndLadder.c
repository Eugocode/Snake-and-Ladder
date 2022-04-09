/*Programmer: Dleamnor Euraze M. Cawaling
  Activity: Snake and ladder
  Date Programmed: May 13-June 10, 2020

INSTRUCTIONS
  Size of the grid is 10X10
  The game should be played by 2 players
  one dice to roll
  The output of the grid should be changing as the player is moving

===========================================================================================================================================================================================================================================*/
#include <stdio.h>
#include <stdlib.h> //use to access rand() and srand()
#include <time.h>   //use to access time()
#include <conio.h>  //use to access getch()

/*Function declerations*/
void obtain_user_input(void);
int draw_table();
int player1_movement();
int player2_movement();
int checking_players_position();
int dice();
void print_full_line_asterisks(void);
char putout(int number, char character);

/*Macro or constants*/  /*These variables help to easily change the values for future use.*/
#define row 10          // number of rows
#define col 10          // number of columns
#define SQUARE_WIDTH 9  // Full width of a square
#define SQUARE_HEIGHT 3 // Height of area between rows of asterisks

/*character arrays that store the names of the players*/
char P1[40];
char P2[40];

int main()
{
    int posP1 = 0, posP2 = 0; // players position (posP1-->player1's position, posP2--->player2's position)

    obtain_user_input();              // Inputs player names
    player1_movement(&posP1, &posP2); // start of the game; passes the addresses of players' positions(posP1 and posP2)

    return 0;
}

/*introducing the game and asking the players for their names*/
void obtain_user_input(void)
{
    printf("WELCOME TO SNAKE AND LADDER!\n\n");
    printf("Rules for the game:\n\tOnly 2 players is allowed to play.\n\tSnakes are represented by S1 and S2. When a player lands into the head of the snake, he will move down to the location of its tail.\n\tLadders are represented by L1 and L2. When a player lands at the bottom of the ladder, he will move to the top of the ladder.\n\tPlayers are represented by P1 and P2.\n\tThe first one to get to the finish line or the 100th tile will win the game.\n\tWhen a player exceeds the 100th tile, he will move backwards, depending on the number of exceeding tiles.\n");
    printf("\nLet the battle begin!\nPlease enter the name of each player:\n\n");
    printf("Player1:");
    fgets(P1, 40, stdin); // I prefer to use fgets instead of scanf
    printf("Player2:");   // to allow the user to input their names with spaces.
    fgets(P2, 40, stdin); // fgets(pointer to an array of char, maximum number of char,pointer to a FILE object that identifies input stream.
}

/*drawing table*/
int draw_table(int *ptrP1, int *ptrP2)
{                                    // initializing pointers for posP1 and posP2 respectively
    int line, n, m, num = row * col; // line are the numbers from 1 to SQUARE_HEIGHT; n is for row and m is for column. num is the total number of tiles/squares
    int arr[row][col];               // declaring the 2D array to store (row*col) elements

    print_full_line_asterisks();
    for (n = 0; n < row; n++)
    { // traversing from row 0 to row 9
        for (line = 1; line < SQUARE_HEIGHT + 1; line++)
        { /*Prints one text line at a time*/
            for (m = 0; m < col; m++)
            {                 // traversing from column 0 to column 9
                putchar('*'); // printing the left border; putchar performs faster than printf when printing a single character
                if (line == 1)
                { // In line 1 of each rows, appropriate numbers are printed.
                    if (n % 2 == 0)
                    {                                  /*For even numbered rows*/
                        arr[n][m] = num;               // num is being incremented and assigned to each element in the array as we traverse when making the table.
                        printf("%3d", arr[n][m]);      // prints the corresponding number inside the square in the first line
                        putout(SQUARE_WIDTH - 4, ' '); // prints the spaces to complete the square
                        num--;                         // For even numbered rows: decreasing the number from left to right
                        if (m == col - 1)
                        {                          // If the last column for the even numbered row is reached,
                            num = num - (col - 1); // reduce the num by 9 (not 10, because we already decresed 1 at the previous line);
                        }                          // This allows us to arrange the numbers correctly in the board.
                    }
                    else if ((n % 2) != 0)
                    { /*For odd numbered rows*/
                        arr[n][m] = num;
                        printf("%3d", arr[n][m]);
                        putout(SQUARE_WIDTH - 4, ' ');
                        num++; // For odd numbered rows: increasing the number from left to right.
                        if (m == col - 1)
                        {                          // If the last column for the odd numbered row is reached,
                            num = num - (col + 1); // reduce the num by 11 (not 10, because we already added 1 at the previous line);
                        }                          // This allows us to arrange the numbers correctly in the board.
                    }
                }
                else if (line == 2)
                { // In line 2 of the rows, the snakes(S1,S2) and ladders(L1,l2)
                    if (arr[n][m] == 73 || arr[n][m] == 13)
                    { // are printed in the programmer's choosen location.
                        putout(SQUARE_WIDTH - 4, ' ');
                        printf("S1 ");
                    }
                    else if (arr[n][m] == 63 || arr[n][m] == 36)
                    {
                        putout(SQUARE_WIDTH - 4, ' ');
                        printf("S2 ");
                    }
                    else if (arr[n][m] == 18 || arr[n][m] == 55)
                    {
                        putout(SQUARE_WIDTH - 4, ' ');
                        printf("L1 ");
                    }
                    else if (arr[n][m] == 93 || arr[n][m] == 89)
                    {
                        putout(SQUARE_WIDTH - 4, ' ');
                        printf("L2 ");
                    }
                    else
                    {
                        putout(SQUARE_WIDTH - 1, ' ');
                    }
                }
                else
                { // In line 3, the players (P1,P2) will be printed
                    if (*ptrP1 == arr[n][m] && *ptrP2 == arr[n][m])
                    {                       // if the position of the players(value of posP1 and posP2) is equal to the current element of the array (or the number of the tile),
                        printf(" P1  P2 "); // print P1 and P2 in line 3
                    }
                    else if (*ptrP1 == arr[n][m])
                    {                                  // else, if only the position of player 1 is equal to the current element of the array (or the number of the tile),
                        printf(" P1");                 // print P1(player 1)
                        putout(SQUARE_WIDTH - 4, ' '); // print spaces
                    }
                    else if (*ptrP2 == arr[n][m])
                    {                  // else, if only the position of player 2 is equal to the current element of the array (or the number of the tile),
                        printf(" P2"); // print P2(player 2)
                        putout(SQUARE_WIDTH - 4, ' ');
                    }
                    else
                    { // only print spaces if the position of P1 and P2 is not equal to the current element of the array.
                        putout(SQUARE_WIDTH - 1, ' ');
                    }
                }
            }
            printf("*\n"); // Close the line with asterisk at the right most side and add newline
        }
        print_full_line_asterisks(); // Close the bottom part of the row with line of asterisks
    }
}

/*print spaces inside the squares*/
char putout(int number, char character)
{ // number is the number of character to be printed
    int i;
    for (i = 0; i < number; i++)
    {
        putchar(character); // prints the character specifically the space
    }
}

/*print full line asterisks*/
void print_full_line_asterisks(void)
{
    putout(col * SQUARE_WIDTH + 1, '*'); // prints (col*SQUARE_WIDTH+1) number of asterisks
    putchar('\n');
}

/*movement of player1*/
int player1_movement(int *ptrP1, int *ptrP2)
{ // accepts the pointers to the variables posP1 and posP2
    int count, excess;
    /*main game*/
    while ((*ptrP1 != 100) && (*ptrP2 != 100))
    {                            // If the positions of players are not equal to 100, continue playing the game.
        printf("\n%s", P1);      // Printing the name of player 1, to declare that it is his turn to move.
        count = dice();          // count is the value that the player gets as he rolled the dice
        *ptrP1 = *ptrP1 + count; // using pointer, add the value of count to the value of posP1, making the player to move
        if (*ptrP1 > 100)
        { // If the position exceeds 100, the excess movement will be subtracted to 100,
            excess = *ptrP1 % 100;
            *ptrP1 = 100 - excess; // giving the new position wherein the player steps backward (100-excess) times.
            printf("You've exceeded %d tile(s). You will now be move at %dth tile.\n\n", excess, *ptrP1);
        }

        checking_players_position(ptrP1); // passing the address of posP1
        draw_table(ptrP1, ptrP2);         // passing the addresses of posP1 and posP2, this allows us to use their values in other functions

        if ((*ptrP1 != 100) && (*ptrP2 != 100))
        {                                   // calling another player for his turn, if none of the players reaches 100th tile.
            player2_movement(ptrP1, ptrP2); // passing the address of posP1 and posP2
        }
        else if (*ptrP1 == 100)
        { // stops the game if one of the players reaches 100th tile
            printf("%sWon the game!\n", P1);
            printf("GAME OVER!\n");
            exit(0);
        }
    }
}

/*movement of player2*/
int player2_movement(int *ptrP1, int *ptrP2)
{ // similar to the execution in the function player 1, the only difference is, we're updating the position of player 2
    int count, excess;

    /*main game*/
    while ((*ptrP2 != 100) && (*ptrP2 != 100))
    {
        printf("\n%s", P2);
        count = dice();
        *ptrP2 = *ptrP2 + count;
        if (*ptrP2 > 100)
        {
            excess = *ptrP2 % 100;
            *ptrP2 = 100 - excess;
            printf("You've exceed %d tile(s). You've been moved at %dth tile.\n\n", excess, *ptrP2);
        }

        checking_players_position(ptrP2);
        draw_table(ptrP1, ptrP2);

        if ((*ptrP2 != 100) && (*ptrP1 != 100))
        {
            player1_movement(ptrP1, ptrP2);
        }
        else if (*ptrP2 == 100)
        {
            printf("%sWon the game!\n", P2);
            printf("GAME OVER!\n");
            exit(0);
        }
    }
}

/*rolling the dice*/
int dice()
{
    int roll;
    char key;

    printf("Press ENTER or any key to roll the dice.\n");
    getch(); // Waits for the user to click any key to continue the program.
    /*generating random number to roll the dice*/
    srand(time(NULL));         // makes use of computer's internal clock to set the seed number differently, to prevent the same sequence from being generated each time in the rand() function.
    roll = (1 + (rand() % 6)); // gets random numbers from 1 to 6; roll = (first no. in the range + (rand() % number of terms in the range)
    printf("Dice was rolled. You get: %d\n\n", roll);

    return (roll); // returning the random number that we get to the calling function.
}

/*checking if the player hits snake or ladder*/
int checking_players_position(int *posP)
{ // accepting the pointer that points to the variable posP1 or posP2
    /*when the player hits the head of the snake*/
    if (*posP == 73)
    { // If the position of the player is equal to 73 (location of the head of the snake),
        printf("You hit the head of the snake. You've been moved to 13.\n\n");
        *posP = 13; // the position will be updated into 13(location of the snake's tail).
    }
    else if (*posP == 63)
    { // If the position of the player is equal to 63 (location of the head of the snake),
        printf("You hit the head of the snake. You've been moved to 36.\n\n");
        *posP = 36; // the position will be updated into 36 (location of the snake's tail).
    }
    /*when the player lands at the bottom of the ladder*/
    else if (*posP == 18)
    { // If the position of the player is equal to 18 (location of the bottom of a ladder),
        printf("You arrived at the ladder. Climb up to 55.\n\n");
        *posP = 55; // the position will be updated into 55 (location of the top of a ladder).
    }
    else if (*posP == 89)
    { // If the position of the player is equal to 89 (location of the bottom of a ladder),
        printf("You arrived at the ladder. Climb up to 93.\n\n");
        *posP = 93; // the position will be updated into 93 (location of the top of a ladder).
    }
}

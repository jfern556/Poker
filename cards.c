
// cards.c - file name
/****************************************************************************/
/*PROGRAM DOCUMENTATION
 
 AUTHOR: Jessica Fernandez-Rubio
 
 Programming III. Fourth Assignment
 
 PROGRAM DESCRIPTION: This program implements a simulation of a deck of
 cards in preparation for the game. It creates an ordered deck and shows
 it, then shuffle the deck and shows the shuffled deck, and then deal the
 specified number of cards to the specified number of players and shows
 each hand. Second part of the program sort each hand of each player
 and then it displays the sorted hands, it finds the poker rank by player
 and displays it. At the end, find the winners based of the poker ranks.
 
 INPUT: Accepts two inputs through the Command Line, the number of cards
 by hand, and the number of hands or players, in this order.
 
 OUTPUT: The output is the display of the ordered deck, the display of
 the deck after it was shuffled, the display of each hand after the
 cards were dealt, display of the sorted hands, display of the poker
 rank by player, the display of the winner or winners.
 
 Compilation: make
 
 Execute: ./stud_poker.out "number" "number" 
 
 I hereby certify that this collective work is my own and none of it,
 is the work of any other person or entity.

 */
/******************************************************************************/
# include <stdio.h>
# include <stdlib.h>               //To allow use of rand() and atoi(char *)
# include "functions.h"            //Header file included
/******************************************************************************/
/*PROGRAM DEFINES*/

# define VALID 1                   //Validation function return value if valid
# define INVALID 0                 //Validation function return value if not valid
# define EXP_ARGUMENTS 3           //Command Line expected number of arguments
/******************************************************************************/
 
 
 int main (int argc, char *argv[]){
 
     int valid_result = validate_entries(argc, argv[1], argv[2]);
     if (valid_result == VALID){
 
         int cards_hand;
 
         int players;
         players = atoi (argv[2]);
     
         struct Cards deck [CARDS_MAX];
     
         create_deck( deck );
     
         printf("\n*ORDERED DECK*\n");
         display_deck( deck );
     
         shuffle_deck( deck );
         printf("\n*SHUFFLED DECK*\n");
         display_deck( deck );
     
         struct Cards dealed_deck[ CARDS_MAX ];
         int ranks [players];

         deal_cards( deck , dealed_deck , CARDS_BY_PLAYER, players);
         display_hands(dealed_deck , CARDS_BY_PLAYER , players);

         order_hands ( dealed_deck, players);
         printf ("  \n\n    SORTED");
         display_hands(dealed_deck , CARDS_BY_PLAYER , players); 
        
         hand_rank (dealed_deck, CARDS_BY_PLAYER, players,ranks);
         display_hand_rank (ranks , players);

         display_winners (ranks, players);          
     }
     else {
   } 
     return 0;
 }


/********************************************************************************/
/**Function: validate_entries
 Validates the command line inputs. In order to be acceptable the number of arguments
 has to be 3 since the argc is being used from main. Any other value besides 3 means
 the inputs are not acceptable. Then it checks the two inputs, both have to be integer
 numbers between 1-13 both included and their product can not be greater than 52 which
 is the max number of cards.Uses the atoi () function to convert a number that is a
 string to integer.
 
 Returns: 1 if the values are valid, 0 otherwise.
 */
/********************************************************************************/

int validate_entries(int total_arguments, char *cards, char *total_players){

    int players;
    if (total_arguments != EXP_ARGUMENTS){
        printf("\n ERROR, WRONG NUMBER OF INPUTS\n");
        return INVALID;
    }
    else{
        players = atoi (total_players);        
        if( players >= PLAYERS_MIN && players <= PLAYERS_MAX){
            return VALID;
        }
        else {
            printf("\nERROR, NOT VALID ARGUMENTS\n");
            return INVALID;
        }
    }
}

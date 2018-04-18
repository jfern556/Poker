// functions.c - file name

# include <stdio.h>
# include <stdlib.h>               //To allow use of rand() and atoi(char *)
# include <time.h>                 //To allow use of srand with time
# include "functions.h"            //Header file included 

/*********************************************************************************/
/*PROGRAM DEFINES*/

# define SUITS_MAX 4               //Maximum number of suits
/*********************************************************************************/

/*********************************************************************************/
/**Function: find_face
 Has a predefined array size 13 with the 13 possible faces in a deck of cards  in an
 increasing order.The parameter is an int, is the position of the wanted face and then
 the function returns the char (face) at that position.
 */
/*********************************************************************************/

char find_face(int index){

    char faces[TOTAL_FACES] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    
    return faces[index];
}


/**********************************************************************************/
/**Function: find_suit
 Has a predefined array size 4 with the 4 possible suits in a deck of cards: (S)pade,
 (H)earts, (C)lubs and (D)iamonds.
 The parameter is an int that is the position of the wanted suit and then the
 function returns the char (suit) at that position.
 */
/**********************************************************************************/

char find_suit(int index){
    
    char suits[SUITS_MAX] = {'S','H','C','D'};
    
    return suits[index];

}


/**********************************************************************************/
/**Function: find_rank_value
 This function has the 13 possible faces of a card game inside an array of type
 enum ranks. The function has as paremeter an integer index which determines the
 position of the wanted value, then the function returns the value at index position.
 */
/**********************************************************************************/

enum ranks find_rank_value(int index){
    
    enum ranks values[] = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                                 JACK, QUEEN, KING};
    return values [ index ];
}


/**********************************************************************************/
/**Function: create_deck
 It creates an ordered deck of 52 cards. Uses the struct Card. Since the first 13
 cards will be the same suit then the  index/13 will give me an index between 0-3
 to be able to use it with the function find_suit, and the index % 13 will give me
 and index between 1-13 which is passed as a parameter to the function find_face.
 */
/**********************************************************************************/

void create_deck( struct Cards deck[] ){
    
    int index;
    
    for (index = 0; index < CARDS_MAX; index++){
        
        deck[index].face = find_face (index % TOTAL_FACES);
        deck[index].suit = find_suit (index / TOTAL_FACES);
        deck[index].cards_rank = find_rank_value (index % TOTAL_FACES);
    }
}


/**********************************************************************************/
/**Function: display_deck
 Displays the ordered and shuffled deck using a pointer to structure. Separating with
 a ______________ after 13 cards to make it easier to see.
 */
/**********************************************************************************/

void display_deck(struct Cards deck[ ]){
    
    int counter;
    
    for(counter = 0; counter < CARDS_MAX; counter++){
        if((counter > 0) && (counter % TOTAL_FACES)==0){
            printf("______________\n");
        }
        
        printf("%5c %4c\n", deck[ counter ].face, deck [counter ].suit);
        
    }
}


/**********************************************************************************/
/**Function: shuffle_deck
 Using the functions srand, rand and time, this function shuffles the deck.It goes
 through the whole deck starting for the first element at position 0 and finds a
 random index between 0-51 and swap the values. Then it goes to the second element
 at position 1 and does the same procedure, and so on.
 */
/***********************************************************************************/

void shuffle_deck( struct Cards deck[ ] ){
    srand ((unsigned) time(NULL));
    int index = 0;
    int counter;
    struct Cards temporal;
    for (counter = 0; counter < CARDS_MAX; counter++){
        index = rand() % 52;
        temporal = deck[index];
        deck[index] = deck[counter];
        deck[counter] = temporal;
    }
    
}


/**********************************************************************************/
/**Function: deal_cards
 This function deal cards to the players by rotating, one card per player until the
 total cards by hand has been given. The shuffled deck is being used. In my do while
 loop,all the cards corresponding to each player are copied in order in the new array. 
 So first, cards corresponding to the first player will be copied into the new array, 
 then the cards corresponding to the second player and so on. The way to know which are
 the cards for the first player in the shuffled array is starting with the first one
 and, the second one will be in the position initial plus the number of players. At
 the end, my new array of struct Cards will have all the cards dealed that were chosen
 by rotating the original suffled deck, but ordered by player.Meaning the first x 
 cards will belong to the first player.
 */
/***********************************************************************************/
void deal_cards( struct Cards deck[] , struct Cards player[] , int cards_hand , int players){
    
    int size = cards_hand * players;
    int cards_count;
    int players_count = 0;
    int count = 0;
    int auxiliar_counter = 0;
    
    struct Cards next_card;
    struct Cards player_card;
    
    for(cards_count = 0; cards_count < size; cards_count++){
        
        do{
            
            player[ auxiliar_counter ] = deck[ cards_count ];
            count++;
            auxiliar_counter = auxiliar_counter + players;
            cards_count = cards_count + 1;
            
            
        } while(count < cards_hand);
        
        count = 0;
        cards_count = cards_count - 1;
        players_count++;
        auxiliar_counter = players_count;
    }
}

/**********************************************************************************/
/**Function: display_hands
 Displays the new array of struct Cards of cards dealed to the players. The parameters
 are a pointer to the deck of dealed cards, cards by hand, and total players. The size
 of this deck will be the product of the cards by hand and the players.
 */
/**********************************************************************************/

void display_hands (struct Cards dealed_deck[] , int cards, int players){
    
    int counter;
    int count = 1;
    int size = cards*players;
    
    printf("\nHANDS BY PLAYER\n");
    printf("***************\n");
    printf(" PLAYER NO. %d\n", count);
    printf("***************\n");
    
    for (counter = 0; counter < size; counter++){
    
        if ((counter > 0) && ((counter % cards) == 0)){
        
            count++;
            printf("***************\n");
            printf(" PLAYER NO. %d\n", count);
            printf("***************\n");
        
        }
        else {}
        
        printf("%5c %4c\n", dealed_deck[ counter ].face, dealed_deck[ counter ].suit);
       
    }
}

/**********************************************************************************/
/**Function: order_hands
 This function receives an array of struct Cards and an integer which is the number 
 of players.The array size will be total players * total cards by player. This 
 function sorts the subarrays with size equal to total cards by player, meaning that 
 sorts starting from the first element of the array until has ordered n elements 
 being n the total cards each player has, then it does the same with the following 
 n cards.
 */
/**********************************************************************************/

void order_hands ( struct Cards dealed_deck[], int players){
    int first_index_hand;
    int first_aux_index;
    int second_aux_index;
    int size = players * CARDS_BY_PLAYER;

    struct Cards face_holder;

    for ( first_index_hand = 0; first_index_hand < size;
          first_index_hand = first_index_hand + CARDS_BY_PLAYER){

        for (first_aux_index = first_index_hand; 
             ((first_aux_index + 1) % CARDS_BY_PLAYER != 0); first_aux_index ++){

            for (second_aux_index = first_aux_index + 1;
                  ((second_aux_index) % CARDS_BY_PLAYER !=0);
                                                         second_aux_index ++){

                if (dealed_deck [first_aux_index ].cards_rank > 
                                        dealed_deck [ second_aux_index].cards_rank){
                    face_holder = dealed_deck [first_aux_index ]; 
                    dealed_deck [first_aux_index ] =  dealed_deck [ second_aux_index];
                    dealed_deck [ second_aux_index] = face_holder;
                } 
            }
        }
    }
}

/**********************************************************************************/
/**Function: pairs
 This function receives as parameter an array of struct Cards and a number of cards.
 It goes through the array checking two consecutive elements, if the two consecutive
 elements are equal but different from the third element then we count the first two 
 elements as a pair. If they are equal to the third element we dont count it as a
 pair. My return represents how many different pairs the functions is returning.
 */
/**********************************************************************************/

int pairs (struct Cards array[], int cards){
    int pairs = 0;
    int first;
    int second;
    int third;

    for (first = 0; first < cards - 1; first ++){

        second = first + 1;
        if (second <= cards - 2){                   //Assuring space for third value
            third = second + 1;
            if (array[first].cards_rank == array[third].cards_rank){
                first = second;
            }
            else { 
                if (array[first].cards_rank == array[second].cards_rank)
                    pairs ++;                      
            }
        }
        else {
            if (array[first].cards_rank == array[second].cards_rank)
                pairs ++;
        }
    }

    return pairs;
}

/**********************************************************************************/
/**Function: three_kind
 Receives as parameter a sorted array of struct Cards and a number of cards which
 will be the size of the array. Since the array is already sorted, I check if first
 element is equal to third, if they are, then my counter increments and the same
 procedure will be repeated starting now with the element after the previous three
 elements; however, if my first element is not equal to the third, then I go to the
 next one (element number two) and check with the element that is 2 elements away
 from it.
 */
/**********************************************************************************/

int three_kind (struct Cards array [], int cards){
    int first;
    int third;
    int three_kind = 0;
    for (first = 0; first < cards - 2; first ++){
        third = first + 2;
        if (array[first].cards_rank == array[third].cards_rank){ 
                three_kind ++; 
        }
    }
    return three_kind;
}

/**********************************************************************************/
/**Function: straight
 Has a sorted array type struct Cards and an integer as parameters. It checks if 
 both consecutives have the same value with a difference equal 1, and if it is 1,
 then counter increments. If my counter is equal 4 at the end, means that all of 
 the elements were consecutive in values. This function also contemplates the option
 of having an straight of 10, J, Q, K, A.
 */
/**********************************************************************************/

int straight (struct Cards array [], int cards){
    int first;
    int second;
    int straight = 0;
    for ( first = 0; first < cards - 1; first ++){
        second = first + 1;
        if ((array[first].cards_rank) ==( array[second].cards_rank - 1)){
           straight =  straight + 1;
        }
        else {}
    }
    first = 0;
    second = first + 1;
    if (straight == 3 && (array[first].cards_rank == ACE) && 
        (array[second].cards_rank == TEN)) {                
        return (straight + 1);
    }
    else {
        return straight;
    }
}

/**********************************************************************************/
/**Function: flush
 This function receives a sorted array of struct Cards and a number of cards which 
 is the size of the array. Starting from the first element, checks if consecutive
 elements have the same suit, if they do, flush(counter) increments. If flush is 
 equal to the number of cards - 1 means that all the elements had the same suit.
 */
/**********************************************************************************/

int flush (struct Cards array[], int cards){
    int first;
    int second;
    int flush = 0;
    for (first = 0; first < cards-1; first ++){
        second = first + 1;
        if (array[first].suit == array[second].suit)
            flush ++;
    }
    return flush;
}

/**********************************************************************************/
/**Function: full_house
 This function receives a sorted array of struct Cards an a number of cards dealt
 to each player. It calles the function three_kind and stores the result in an
 integer, then calls the function pairs and stores the result in another integer. 
 Then if both results are 1 mean that there is a full house because we would have
 three cards of a kind and one pair. 
 */
/**********************************************************************************/
int full_house (struct Cards array [], int cards){
    int three_kind_result = three_kind (array, cards);
    int pairs_result = pairs (array, cards);   
    if (three_kind_result == VALID && pairs_result == VALID)
        return VALID;
    return 0;  
}

/**********************************************************************************/
/**Function: four_kind
 This functions receives a struct Card array and a number of cards. It goes through
 the array checking the first and fourth element of the array since the array is 
 sorted, then if these two elements are equal mean that the middle values are equal
 as well, if this happens I count on four_of a kind. I move my first element  to 
 my fourth position which will become fifth after the loop. And do the whole process
 again. Returns total of 4 of a kind.
 */
/**********************************************************************************/

int four_kind (struct Cards array [], int cards){
    int first;
    int fourth;
    int four_kind = 0;
    for (first = 0; first < cards - 3; first ++){
        fourth = first + 3;            
        if (array[first].cards_rank == array[fourth].cards_rank){
                    four_kind ++;
                    first = fourth;  
        }
    }
    return four_kind;
}
/**********************************************************************************/
/**Function: straight_flush
 This function receives a sorted array of struct Cards and a number of cards. It
 calls straight anf flush functions and stores the values. If the array if both at the 
 same time, a straight and a flush then the array is a straight flush and function
 returns a 1, if this doesnt happen function returns a zero.
 */
/**********************************************************************************/

int straight_flush (struct Cards array [], int cards){
    int straight_result = straight (array, cards);
    int flush_result = flush (array, cards);
    if (straight_result ==TRUE_STRAIGHT && flush_result == TRUE_FLUSH)
        return VALID;
    return INVALID;
}

/**********************************************************************************/
/**Function: determine_rank
 This function receives a sorted array of struct Cards and a number of cards. 
 Calls each function of the poker rank, from greater value to lower value. If the
 value that the function returns is valid according to the function, then the function
 returns the int value of the poker rank and doesnt continue checking. The function 
 will go through this until finds a value valid and returns the int value of the 
 poker rank asserted. 
 */
/**********************************************************************************/

int determine_rank(struct Cards array [], int cards){

    int value;

    value = straight_flush (array, cards);
    if (value == VALID) {
        return (int)STRAIGHT_FLUSH;   
    }
    
    value = four_kind (array, cards);
    if (value == VALID) {
        return (int)FOUR_KIND;
    }  

    value = full_house (array, cards);
    if (value == VALID) {
        return (int)FULL_HOUSE;
    }   

    value = flush (array, cards);
    if (value == TRUE_FLUSH) {
        return (int)FLUSH;
    }

    value = straight (array, cards);
    if (value == TRUE_FLUSH) {
        return (int)STRAIGHT;
    }

    value = three_kind (array, cards);
    if (value == VALID) {
        return (int)THREE_KIND;
    }

    value = pairs (array, cards);
    if (value == 2) {
        return (int)TWO_PAIRS;
    } 
    else {
        if (value == 1) {
            return (int)ONE_PAIR;
        }
    }

    return (int)HIGH_CARD;
}


/**********************************************************************************/
/**Function: hand_rank
 This function receives a sorted struc Cards array, number of hands, number of 
 player, and an array of type int. It creates a subarray from the original array. 
 This subarray will have size equal to total cards. Using this subarray the function
 determine_rank is called and the integer value that returns is placed in the int
 array that was passed in the beginning as a parameter. 
 This functions doesnt return anything, but at the end, the int array will have 
 all the int values of the poker ranks of each hand.
 */
/**********************************************************************************/

void hand_rank(struct Cards array[], int cards,int players, int ranks[]){
    struct Cards *pointer = array;
    struct Cards subarray [cards];
    int size = cards * players;
    int counter;
    int out_counter = 0;
    int index;
    
    for (counter = 0; counter < size; counter ++){

        index = 0;

        do{
            subarray[index] = *pointer;
            index ++;            
            pointer ++;
            counter ++;            
        } while (index < cards);

        counter --;
        ranks[out_counter] = determine_rank (subarray, cards);
        out_counter ++;
    }
}


/**********************************************************************************/
/**Function: display_hand_rank
 This function receives as parameter the array of type in with all the values of the 
 poker ranks by hand. It each player poker rank hand. 
 */
/**********************************************************************************/

void display_hand_rank (int ranks [], int players){
    int index;
    int result;
   
    char * array [ ] = { "HIGH CARD", "ONE PAIR", "TWO PAIRS", "THREE OF A KIND",
                    "STRAIGHT", "FLUSH", "FULL HOUSE", "FOUR OF A KIND", 
                        "STRAIGHT FLUSH"}; 
    printf ("\n\n     *POKER RANK BY PLAYER*\n");
    printf ("________________________________\n\n");
    for (index = 0; index < players; index ++){
        result =  ranks[index];
        printf ("****PLAYER No. %d - %s ****\n\n", index + 1, array [result-1]);
    }
}

/**********************************************************************************/
/**Function: max_value
 This function has as parameters an array of integers and number of players. 
 it returns the maximum value of the array
 */
/**********************************************************************************/

int max_value (int array [], int players){
    int counter;
    int index;
    int max;

    max = array [ 0 ];

    for (counter = 1; counter < players; counter ++){
        if (array [counter] > max ){
            index = counter;
            max = array [counter];    
        }
    }

    return max;
}

/**********************************************************************************/
/**Function: display_winners
 This functions receives an array of integers and number of players as parameters. 
 It uses the function max_value to get  the max value of the array, then goes 
 through the array checking if the element is equal to the maximum value it prints
 the position + 1 which represents the player number and announce it as a winner.
 */
/**********************************************************************************/

void display_winners (int array [], int players){
    int position;
    int value =  max_value (array, players);

    printf ("\n\n          *WINNERS!!!*    \n");
    printf ("     _____________________\n\n");                 
    for (position = 0; position  < players; position ++){
        if (array [ position ] == value){
            printf ("     ****PLAYER NO. %d ****\n\n", position + 1);
        }
    }
}

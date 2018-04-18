/******************************************************************************/
/*PROGRAM DEFINES*/

#define CARDS_MAX 52              //Maximum number of cards deck has
#define TOTAL_FACES 13            //Total different ranks or faces
#define PLAYERS_MIN 1             //Minimum number of players
#define PLAYERS_MAX 7             //Maximum number of players
#define CARDS_BY_PLAYER 5         //Total cards by player
#define VALID 1                   //Value if valid
#define INVALID 0                 //Value if invalid
#define TRUE_FLUSH 4              //Value that flush returns when valid
#define TRUE_STRAIGHT 4           //Value that straight returns when valid

/******************************************************************************/

enum ranks {ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, 
              EIGHT = 8, NINE = 9, TEN = 10, JACK = 11, QUEEN = 12, KING = 13}; 

enum poker_ranks {HIGH_CARD = 1, ONE_PAIR = 2, TWO_PAIRS = 3, THREE_KIND = 4, 
               STRAIGHT = 5, FLUSH = 6, FULL_HOUSE = 7, FOUR_KIND = 8, 
                STRAIGHT_FLUSH = 9};  

struct Cards{
    char face;
    char suit;
    enum ranks cards_rank;
 };


 /******************************************************************************/
/*FUNCTIONS PROTOTYPES*/

int validate_entries(int, char *, char *);
struct Cards createCard (int, int);
char find_face(int);
char find_suit(int);
enum ranks find_rank_value(int);
void create_deck( struct Cards array[ ]);
void display_deck(struct Cards array[ ]);
void shuffle_deck( struct Cards array[ ]);
void deal_cards( struct Cards * , struct Cards * , int, int );
void display_hands (struct Cards * , int, int);

void order_hands ( struct Cards *, int );
int pairs (struct Cards *, int );
int three_kind (struct Cards *, int);
int straight (struct Cards *, int);
int flush (struct Cards *, int);
int full_house (struct Cards *, int);
int four_kind (struct Cards *, int);
int straight_flush (struct Cards *, int);
int determine_rank(struct Cards *, int);
void hand_rank (struct Cards *, int, int, int *);
void display_hand_rank (int *, int);
int max_value (int *, int);
void display_winners (int *, int);


# Project The Broken Hearts Game 
# with simple textual interface and simple AI.

# The description of function modules :

## hearts.c - the main file;

## game.c - game module 
it has the player modules,

is runned by hearts.c ,

and run one by one the games rounds(round module),
and delegates the players to it(round)
and prints the final resuls (from dedicated file).


## round.c - round module
is runned by the game module and running the trick modules
(player objects are delegated further to the trick).

The round is responsible for the card deck (module) creation,
shuffling (deck object's procedures) and dealing (round's procedure);

it mannages the exchange of cards in the beggining of the game
as its inner procedures 

and then run the trick object(s).

## trick.c - trick module
is runned by the round module and let the player(s) object
to make their moves (player objects are delegated from the round object).

It also calculate the score per trick and give it to the players.

The trick object creates innter object Table (cards on the table)
and delegates them to the player objects.

### table - inner module of trick
is delegated to player objects.

## player.c - player module
is held by the game object,

is runned by the trick object

and has the hand module.

Player delegates the table from the trick object
to the hand object and the decision is made in the hand object.

Player is of 2 types : computer and human and
runs the corresponding procedure of the hand object.

It also provides the getName and getScore services.

## hand.c - hand module
is held by the player object
and contains all logic (game rules for the human player)
and the strategies (for exchange and plaing in tricks
for the computer player).

The hand object is actually manage the table object
(which is delegated from the player object).
It also provides the printing services for hand object
and for the table object.

## deck.c - deck module
Contains the deck of card , 
which is used by the round object (shuffle - service of deck)
and deal(procedure of round).
Provide the service of looking to the Global deck (suits and ranks)
to retrive the card object by it index(place in the Global deck).

## card.h - the card object
and various definitions.

## The modules diagram.[line - has relation , arrow - runs relation).

		CARD
		|
		DECK		GAME------PLAYER-----\
		/\			\/			^		\/
		/\			\/			|		\/
		-----------ROUND		|		\/
					\/			|		\/
					\/			|		\/
					TRICK------>		\/
										\/
					HAND<---------------/					














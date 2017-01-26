/* *************************************
Ricardo Salazar, February 26, 2015

Interface of a simple Card class
************************************* */

#include <string>
#include <vector>
#include <fstream>

#ifndef CARDS_H
#define CARDS_H

using namespace std;

enum suit_t { OROS, COPAS, ESPADAS, BASTOS };

/*
The values for this type start at 0 and increase by one
afterwards until they get to SIETE.
The rank reported by the function Card::get_rank() below is
the value listed here plus one.
E.g:
The rank of AS is reported as    static_cast<int>(AS) + 1   = 0 + 1 =  1
The rank of SOTA is reported as  static_cast<int>(SOTA) + 1 = 9 + 1 = 10
*/
enum rank_t { AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA = 9, CABALLO = 10, REY = 11 };

class Card {
public:
	// Constructor assigns random rank & suit to card.
	Card();

	// Accessors 
	string get_spanish_suit() const;
	string get_spanish_rank() const;

	/*
	These are the only functions you'll need to code
	for this class. See the implementations of the two
	functions above to get an idea of how to proceed.
	*/
	string get_english_suit() const;
	string get_english_rank() const;

	// Converts card rank to number.
	// The possible returns are: 1, 2, 3, 4, 5, 6, 7, 10, 11 and 12
	int get_rank() const;

	// Compare rank of two cards. E.g: Eight<Jack is true.
	// Assume Ace is always 1. 
	// Useful if you want to sort the cards.
	bool operator < (Card card2) const;

private:
	suit_t suit;
	rank_t rank;
};


class Hand {
public:
	// A vector of Cards
	Hand();

	//takes in a card and adds it to the hand, increasing the player's card points
	void addCard(const Card&);

	//prints the cards to a stream
	void printCards(ofstream&) const;

	//returns the card count
	unsigned getCardCount() const;

private:
	std::vector<Card> cards;
	//counts all card values and stores them as a single value
	double cardCount;
};


class Player {
public:
	// Constructor. 
	//    Assigns initial amount of money
	Player(int m);

	//mutator
	void changeMoney(int);

	//for nondealer players, this will write game stats to the txt file given as the first param
	void recordRound(ofstream&, int, int);

	//for nondealer players, this will determine if the player has won 1000 pesos/dollars
	bool determineWin() const;

private:
	//money will be set to -1 to denote that a player is the dealer
	//a normal player should not be able to reach negative money
	int money;
	//this one will store a Hand object, which will hold the player's cards
	Hand cardHand;
};

//an outside function, which determines who won the individual round
//will increase or decrease player's amount of money to match
void whoWonRound();

#endif
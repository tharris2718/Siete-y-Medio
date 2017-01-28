#include "cards.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

/*
You might or might not need these two extra libraries
#include <iomanip>
#include <algorithm>
*/


/* *************************************************
Card class
************************************************* */

/*
Default constructor for the Card class.
It could give repeated cards. This is OK.
Most variations of Blackjack are played with
several decks of cards at the same time.
*/
Card::Card(){
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = OROS; break;
	case 2: suit = COPAS; break;
	case 3: suit = ESPADAS; break;
	case 4: suit = BASTOS; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = AS; break;
	case  2: rank = DOS; break;
	case  3: rank = TRES; break;
	case  4: rank = CUATRO; break;
	case  5: rank = CINCO; break;
	case  6: rank = SEIS; break;
	case  7: rank = SIETE; break;
	case  8: rank = SOTA; break;
	case  9: rank = CABALLO; break;
	case 10: rank = REY; break;
	default: break;
	}
}

// Accessor: returns a string with the suit of the card in Spanish 
string Card::get_spanish_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "oros";
		break;
	case COPAS:
		suitName = "copas";
		break;
	case ESPADAS:
		suitName = "espadas";
		break;
	case BASTOS:
		suitName = "bastos";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in Spanish 
string Card::get_spanish_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "As";
		break;
	case DOS:
		rankName = "Dos";
		break;
	case TRES:
		rankName = "Tres";
		break;
	case CUATRO:
		rankName = "Cuatro";
		break;
	case CINCO:
		rankName = "Cinco";
		break;
	case SEIS:
		rankName = "Seis";
		break;
	case SIETE:
		rankName = "Siete";
		break;
	case SOTA:
		rankName = "Sota";
		break;
	case CABALLO:
		rankName = "Caballo";
		break;
	case REY:
		rankName = "Rey";
		break;
	default: break;
	}
	return rankName;
}



// Accessor: returns a string with the suit of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "coins";
		break;
	case COPAS:
		suitName = "cups";
		break;
	case ESPADAS:
		suitName = "swords";
		break;
	case BASTOS:
		suitName = "clubs";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "Ace";
		break;
	case DOS:
		rankName = "Two";
		break;
	case TRES:
		rankName = "Three";
		break;
	case CUATRO:
		rankName = "Four";
		break;
	case CINCO:
		rankName = "Five";
		break;
	case SEIS:
		rankName = "Six";
		break;
	case SIETE:
		rankName = "Seven";
		break;
	case SOTA:
		rankName = "Jack";
		break;
	case CABALLO:
		rankName = "Knight";
		break;
	case REY:
		rankName = "King";
		break;
	default: break;
	}
	return rankName;
}



// Assigns a numerical value to card based on rank.
// AS=1, DOS=2, ..., SIETE=7, SOTA=10, CABALLO=11, REY=12
int Card::get_rank() const {
	return static_cast<int>(rank)+1;
}

// Comparison operator for cards
// Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
	return rank < card2.rank;
}



/* *************************************************
Hand class
************************************************* */

//the default constructor; just default initialize both member variables
Hand::Hand() : cards(), cardCount(0){}

//the addCard function
void Hand::addCard(const Card& c){
	if (cards.size() == 0)
		cards.push_back(c);

	//if other cards exist, search for where the card goes by iterating through the cards one by one
	else{
		vector<Card>::iterator curr = cards.begin();
		while (curr->get_rank() < c.get_rank()){
			++curr;//increase curr to the next spot
		}
		//at this point, the curr card is either greater than or equal to the card to be added
		cards.insert(curr, c);//inserts c before the index of curr
	}

	//after the card is added (no matter the case), add the cards value
	if (c.get_rank <= 7)
		cardCount += c.get_rank();

	else
		cardCount += 0.5;
}

void Hand::printCards(ostream& ifs) const{
	for (Card c : cards){
		ifs << "     ";//five spaces for indentation
		ifs << setw(15) << left << c.get_spanish_rank() << " de " << c.get_spanish_suit;
		ifs << "(" << c.get_english_rank() << " of " << c.get_english_suit << ").\n";
	}
}

double Hand::getCardCount() const{
	return cardCount;
}



/* *************************************************
Player class
************************************************* */
//the constructor, accepting one param, the initial value of money

//100 for a regular player, -1 for the dealer
Player::Player(int m) : money(m), cardHand(){}


//changeMoney is a shortcut past the two alternatives: giveMoney and takeMoney
//in the case of decreasing money, the end value shouldn't be negative, because main() will handle proper betting
void Player::changeMoney(int nm){
	money += nm;
}

//param ifs is the file stream to write to, r is the round number, and
//b is the amount bet for the round, only necessary for a nondealer
void Player::recordRound(ofstream& ifs, int r, int b){
	//if called on the normal player, print out the start of the round record
	if (money >= 0){
		//print out a full line of dashes
		for (unsigned i = 0; i < 40; ++i)
			ifs << "-";
		ifs << endl << endl << setw(20) << left << "\nGame number: 1" << r;
		ifs << "Money left: $" << money << endl;
		ifs << "Bet: " << b << endl << endl;
	}

	//now for "Your/Dealer's cards", then printing out the hand, and card point total
	(money >= 0) ? (ifs << "Your ") : (ifs << "Dealer's ");
	ifs << "cards:\n";
	cardHand.printCards(ifs);
	(money >= 0) ? (ifs << "Your ") : (ifs << "Dealer's ");
	ifs << "total is " << cardHand.getCardCount() << ".\n\n";
	//the stream is now ready for writing by another player
}

void Player::resetHand(){
	cardHand = Hand();
}

//does not necessarily determine who won the game, but rather if a player is eligible to win
bool Player::determineWin() const{
	return (cardHand.getCardCount() <= 7.5);
}


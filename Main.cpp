#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <exception>
#include "cards.h"
using namespace std;

// Stub for main
int main(){
	//start by initializing the players
	Player user(100);
	Player dealer(-1);
	
	//greet
	cout << "Welcome to a friendly game of Monopoly. You have started the game with 100 pesos.\n";
	int round = 1;//round number

	ofstream gamelog("gamelog.txt");
	cout << "Initializing gamelog.txt; look there for game details when the game is over.\n";
	cout << "Please do not close the program. You may leave at the end of any round.\n\n";

	//the game itself will be a do/while loop while the player has more than 0 pesos, with the following steps:
	/*
	1. Print player's money, ask for bet
	2. Draw a card and print it, add it to hand
	
	3. While player's total is below 7.5 and player says yes: Print hand and total, ask before drawing again
	4. While dealer's total is below 5.5: Draw card for dealer, print dealer's hand and total
	5. Determine who won and say it, change totals appropriately
	6. Write round details to gamelog.txt
	7. Break if the player's money total is 1000
	*/

	//after the rounds are done, close the gamelog file, and announce who won

	do{
		//initialize deck
		Card* deck;
		try{
			deck = new Card[40];
		}
		catch (exception& e){
			throw exception("Deck initialization failed. How did that happen?");
		}


		cout << "You have " << user.getMoney() << " pesos left. Place your bet here: ";
		unsigned bet;
		cin >> bet;

		while (bet > user.getMoney()){
			cout << "You can only bet up to as much money as you have. Try again: ";
			cin >> bet;
		}

		//draw card loop for the user
		do{
			//draw a random card from the deck, and add it to the hand
			user.getHand().addCard(deck[rand() % 40]);
			cout << "You have drawn a card. Your hand is now: \n";
			user.getHand().printCards(cout);
			cout << "Your total is " << user.getHand().getCardCount() << ". Do you want another card[y/n]? ";
			char response;
			cin >> response;
			if (response == 'n') break;

		} while (user.getHand().getCardCount() < 7.5);

		//same, but for the dealer
		while (dealer.getHand().getCardCount() < 5.5){
			dealer.getHand().addCard(deck[rand() % 40]);
		}

		cout << "Here's what the dealer drew: \n";
		dealer.getHand().printCards(cout);

		//if the winner is the user
		if (user.getHand().getCardCount() <= 7.5 && user.getHand().getCardCount() > dealer.getHand().getCardCount()){
			user.changeMoney(bet);
			cout << "You win!\n";
		}

		//if the winner is the dealer
		else if (user.getHand().getCardCount() > 7.5){
			user.changeMoney(-1 * bet);
			cout << "You lose!\n";
		}

		else
			cout << "You tied with the dealer!\n";

		//write to the file, once for user and once for dealer
		user.recordRound(gamelog, round, bet);
		dealer.recordRound(gamelog, round, bet);

		//delete the card array
		delete[] deck;

		cout << "Play again[y/n]? ";
		char response;
		cin >> response;
		if (response == 'n') break;

	} while (user.getMoney() && user.getMoney() < 1000);//values above 0 will be converted into true

	gamelog.close();
	if (user.getMoney >= 1000)
		cout << "You won the game! See you soon!";

	else
		cout << "You lost. Better luck next time!";

	cin.get();
	return 0;
}
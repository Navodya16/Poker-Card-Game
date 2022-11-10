#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <fstream>

using namespace std;

class Card //define the class card, it has suit number and the number of the card(value)
{	
	public:
		int suit;
		int number;
		void setCardDetails(int s,int n);
		void showCardDetail();
};

void Card::setCardDetails(int s,int n) //set details of the card
{
	suit=s;
	number=n;
}

//function to display the card details
void Card::showCardDetail()
{
	int s = suit;
	int n = number;
	switch(s)
	{
		case 1: {cout<<"Spades";	break;	}
		case 2: {cout<<"Diamonds";	break;	}
		case 3: {cout<<"Hearts"	;break;	}
		case 4: {cout<<"Clubs";	break;	}
	}
	cout<<"\t";
	switch(n)
	{
		case 2: {cout<<"two";	break;	}
		case 3: {cout<<"three";	break;	}
		case 4: {cout<<"four";	break;	}
		case 5: {cout<<"five";	break;	}
		case 6: {cout<<"six";	break;	}
		case 7: {cout<<"seven";	break;	}
		case 8: {cout<<"eight";	break;	}
		case 9: {cout<<"nine";	break;	}
		case 10: {cout<<"ten";	break;	}
		case 11: {cout<<"Jack";	break;	}
		case 12: {cout<<"Queen";	break;	}
		case 13: {cout<<"King";	break;	}
		case 14: {cout<<"Ace";	break;	}
	}
}

class Deck
{
	public:
		int a[52]; //deck has 52 cards and it stored to an integer array
		Deck()
		{
			for(int i=0;i<52;i++)
			{
				a[i]=i; //sorted deck. here deck[0] is spade-2,deck[1] is spade-2, and deck[51] is club-Ace and likewise 
				//spade,diamond,heart,club
				//2,3,4,5,6,7,8,9,10,jack,queen,king,ace
			}
		}
		void printDeck()
		{
			for(int i=0;i<52;i++)
			{
				cout<<a[i]<<" ";  
			}
		}
		void shuffle()
		{
			srand(time(0)); //geerate random orders in each time
			for(int i=0;i<52;i++)
			{
				int r = i+(rand()%(52-i));
				swap(a[i], a[r]);
			}
		}
};

/*
Function 			: returnSuitNo(int n)
Description 		: //this function returns the suit number of the card
Input parameters 	: int n(card number)		   
Return 				: return the suit number
*/
int returnSuitNo(int n) 
{
	if(n>=0 && n<13) //the cards between first to thirteen is belongs to spade and likewise
		return 1; //spade
	else if(n>=13 && n<26)
		return 2; //diamond
	else if(n>=26 && n<39)
		return 3; //heart
	else if(n>=39 && n<52)
		return 4; //club
}

/*
Function 			: returnRankNo(int n)
Description 		: //return the rank of the card when the card number is given. it first find the suit and then find the rank number
Input parameters 	: int n(card number)		   
Return 				: return the rank number
*/
int returnRankNo(int n)
{
	int suit;
	
	if(n>=0 && n<13)
	{
		suit= 1; //spade
		return n+2; //n+2 means the ranks are begin from 2,3,4,5,6,7,8,9,10,jack,queen,king,ace. so it return the respective rank
	}
	else if(n>=13 && n<26)
	{
		suit= 2; //diamond
		n=n-13;
		return n+2;
	}	
	else if(n>=26 && n<39)
	{
		suit= 3; //heart
		n=n-26;
		return n+2;
	}	
	else if(n>=39 && n<52)
	{
		suit= 4; //club
		n=n-39;
		return n+2;
	}
}

/*
Function 			: returnRankNo(int n)
Description 		: //return the highest rank of the player's hand according to the combination
Input parameters 	: int n(card number)
					  int a[]-players hand 
					  int combination		   
Return 				: 
*/
int returnHighestRank(int a[], int size, int combination) 
{
	int rArray[size]; //get the rank array of the player's hand
	for(int i=0;i<size;i++)
	{
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	//if the combination is high card or straight or flush or straight flush, there are no duplicate rank cards in these combinations. 
	//so we can directly find the maximum of the rank array 
	if(combination==1 || combination==5 || combination==6 || combination==9)
	{
		int max=0;
		for(int i=0;i<size;i++)
		{
			if(rArray[i]>=max)
				max=rArray[i];
		}
		return max;
	}
	else if(combination==8) //four of a kind combination
	{
		sort(rArray,rArray+size);
		if(rArray[0]==rArray[1] && rArray[1]==rArray[2] && rArray[2]==rArray[3])
			return rArray[0];
		else if(rArray[1]==rArray[2] && rArray[2]==rArray[3] && rArray[3]==rArray[4])
			return rArray[1];
	}
	else if(combination==7) //full house combination
	{
		sort(rArray,rArray+size);
		if(rArray[0]==rArray[1] && rArray[1]==rArray[2] && rArray[3]==rArray[4])
			return rArray[0];
		else if(rArray[0]==rArray[1] && rArray[2]==rArray[3] && rArray[3]==rArray[4])
			return rArray[4];
	}
	else if(combination==4) //three of a kind combination
	{
		sort(rArray,rArray+size);
		if(rArray[0]==rArray[1] && rArray[1]==rArray[2])
			return rArray[0];
		else if(rArray[1]==rArray[2] && rArray[2]==rArray[3])
			return rArray[1];
		else if(rArray[2]==rArray[3] && rArray[3]==rArray[4])
			return rArray[2];
	}
	else if(combination==3) //two pairs combination
	{
		sort(rArray,rArray+size);
		if(rArray[0]==rArray[1])
		{
			if(rArray[2]==rArray[3])
				return rArray[2];
			else if(rArray[3]==rArray[4])
				return rArray[3];
		}
		else if(rArray[1]==rArray[2])
		{
			if(rArray[3]==rArray[4])
				return rArray[3];
		}
	}
	else if(combination==2) //one pair combination
	{
		sort(rArray,rArray+size);
		if(rArray[0]==rArray[1]) 
			return rArray[0];
		else if(rArray[1]==rArray[2])
			return rArray[1];
		else if(rArray[2]==rArray[3])
			return rArray[2];
		else if(rArray[3]==rArray[4])
			return rArray[3];
	}
	
}

/*
Function 			: straightFlush(int a[], int size)
Description 		: //function to chek whether straightFlush is have
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if straightflush, otherwise false
*/
bool straightFlush(int a[], int size) 
{
	int sArray[size];
	int rArray[size];
	for(int i=0;i<size;i++)
	{
		int s=returnSuitNo(a[i]);
		sArray[i] = s;
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	if(sArray[0]==sArray[1] && sArray[1]==sArray[2] && sArray[2]==sArray[3] && sArray[3]==sArray[4]) //check whether all the ranks are equal
		return true;
	else
		return false;
}

/*
Function 			: fourOfAKind(int a[],int size)
Description 		: //function to chek whether fourofkind
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if four of kind, otherwise false
*/
bool fourOfAKind(int a[],int size)
{
	int rArray[size];
	for(int i=0;i<size;i++)
	{
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	sort(rArray,rArray+size); //sort the array to check duplicate values
	if(rArray[0]==rArray[1] && rArray[1]==rArray[2] && rArray[2]==rArray[3]) //if first four are same
		return true;
	else if(rArray[1]==rArray[2] && rArray[2]==rArray[3] && rArray[3]==rArray[4]) //if last four are same
		return true;
	else
		return false;
}

/*
Function 			: fullHouse(int a[],int size)
Description 		: //function to chek whether fullHouse
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if fullHouse, otherwise false
*/
bool fullHouse(int a[],int size)
{
	int rArray[size];
	for(int i=0;i<size;i++)
	{
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	sort(rArray,rArray+size); //sort the array
	if(rArray[0]==rArray[1] && rArray[1]==rArray[2] && rArray[3]==rArray[4]) //first three are three of a kind other two are one pair
		return true;
	else if(rArray[0]==rArray[1] && rArray[2]==rArray[3] && rArray[3]==rArray[4])
		return true;
	else
		return false;
}

/*
Function 			: flush(int a[],int size)
Description 		: //function to chek whether flush- check whether same color have
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if flush, otherwise false
*/
bool flush(int a[],int size)
{
	int sArray[size];
	for(int i=0;i<size;i++)
	{
		int s=returnSuitNo(a[i]);
		sArray[i] = s;
	}
	int count=0;
	//in a normal card pack, diamons are hearts are red and clubs and spades are black
	//so color is checked by comparing the suit numbers
	for(int i=0;i<size;i++)
	{
		if(sArray[i]==2 || sArray[i]==3) //check whether the card is read and if it is red, count is increased by one
			count++;
	}
	if(count==5 || count==0) //if all the card are red or if all the cards are black
		return true;
	else
		return false;
}

/*
Function 			: straight(int a[],int size)
Description 		: //function to chek whether straight
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if straight, otherwise false
*/
bool straight(int a[],int size)
{
	int rArray[size];
	for(int i=0;i<size;i++)
	{
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	for(int i=0;i<size-1;i++)
	{
		if(rArray[i]>rArray[i+1]) //if cards are in descending order, return false 
			return false;
	}
	return true;
}

/*
Function 			:threeOfAKind(int a[],int size)
Description 		: //function to chek whether threeOfAKind
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if threeOfAKind, otherwise false
*/
bool threeOfAKind(int a[],int size)
{
	int rArray[size];
	for(int i=0;i<size;i++)
	{
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	sort(rArray,rArray+size); //sort the array
	if(rArray[0]==rArray[1] && rArray[1]==rArray[2])
		return true;
	else if(rArray[1]==rArray[2] && rArray[2]==rArray[3])
		return true;
	else if(rArray[2]==rArray[3] && rArray[3]==rArray[4])
		return true;
	else
		return false;
}

/*
Function 			: twoPairs(int a[],int size)
Description 		: //function to chek whether twopairs
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if twopairs, otherwise false
*/
bool twoPairs(int a[],int size)
{
	int rArray[size];
	for(int i=0;i<size;i++)
	{
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	sort(rArray,rArray+size); //sort the array
	if(rArray[0]==rArray[1]) //if first two are equal
	{
		if(rArray[2]==rArray[3] || rArray[3]==rArray[4])
			return true;
		else
			return false;
	}
	else if(rArray[1]==rArray[2]) //if first and two equal, the next two cards must equal to get twopairs combination
	{
		if(rArray[3]==rArray[4])
			return true;
		else
			return false;
	}
	else
		return false;
}

/*
Function 			: onePair(int a[],int size)
Description 		: //function to chek whether onepair
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return true if onepair, otherwise false
*/
bool onePair(int a[],int size)
{
	int rArray[size];
	for(int i=0;i<size;i++)
	{
		int r=returnRankNo(a[i]);
		rArray[i]=r;
	}
	sort(rArray,rArray+size); //sort the array
	if(rArray[0]==rArray[1] || rArray[1]==rArray[2] || rArray[2]==rArray[3] || rArray[3]==rArray[4])
		return true;
	else
		return false;
}

/*
Function 			: returnTheCombination(int a[],int size)
Description 		: this function will go through all the combinations and return the number of highest possible combination
Input parameters 	: int size-size of the array
					  int a[]-players hand 	   
Return 				: return the combination number
*/
int returnTheCombination(int a[],int size)
{
	//the checking procedure should start from the highest combination
	if(straightFlush(a,size))
		return 9;
	else if(fourOfAKind(a,size))
		return 8;
	else if(fullHouse(a,size))
		return 7;
	else if(flush(a,size))
		return 6;
	else if(straight(a,size))
		return 5;
	else if(threeOfAKind(a,size))
		return 4;
	else if(twoPairs(a,size))
		return 3;
	else if(onePair(a,size))
		return 2;
	else
		return 1;
}

int main()
{
	Deck d;
	int p; //no of players without the dealer
	cout<<"please enter the number of players (without dealer) maximum is 9 : ";
	while(true) //validate the number of players. maximum should be 9
	{
		cin>>p;
		if(p<=9)
			break;
		else
			cout<<"maximum number of players is 9. please enter a lesser value: ";
	}
	p=p+1; //total players with the dealer, maximum is 10 because we have only 50 cards
	int r;
	cout<<"please enter the number of rounds you want to play :";
	cin>>r;
	int A[p][5]; //2d array to store hands of each player, p is the number of players
	
	cout<<"\n\n----------------------------------------welcome to the poker game-------------------------------------------------\n\n";
	
	int finalScore[r][p]; //2d array to store final score after the game is over
	for(int i=0;i<r;i++) 
	{
		for(int a=0;a<p;a++)
			finalScore[i][a]=0; //initialize the array with 0 points for all
	}
	//simulate the card shuffling and simulate card distribution, store final score 
	for(int i=0;i<r;i++)//loop through every round
	{
		cout<<"----------------------------------------welcome to the round "<<i+1<<"----------------------------------------------------\n\n";
		d.shuffle(); //shuffle the card deck
		int c=2; //removes the first two card in the pack
		for(int a=0;a<p;a++)
		{
			for(int b=0;b<5;b++)
			{
				A[a][b]=d.a[c+b]; //store the 2d array
			}
			c=c+5;
		}
		
		int choice[p-1]; //choice of the players to enter the game or not
		
		for(int a=0;a<p;a++) //loop though every player
		{
			if(a==0) //0th player is the dealer
			{
				cout<<"Dealer's hand\n"; //first visible the dealers hand
				for(int b=0;b<5;b++)
				{
					int s=returnSuitNo(A[a][b]);
					int r=returnRankNo(A[a][b]);
					Card c; //make a class
					c.setCardDetails(s,r); //initialize the card with suit and rank
					c.showCardDetail(); //show card details
					cout<<", ";
				}
				cout<<endl<<endl;	
			}
			else //if a player
			{
				int input;
				cout<<"Hi player "<<a<<" , do you wish to enter to the game? if yes, please enter 1 or no, enter 2: ";
				cin>>input;
				if(input==1) //if the player likes to join the game
					choice[a-1]=1;
				else
					choice[a-1]=2; //if he doesnt like
			}
			
		}
		cout<<endl<<endl;
		for(int a=1;a<p;a++) //show the hands of the players who liked to join the game
		{
			if(choice[a-1]==1) ///if he liked to join the game
			{
				cout<<"Player"<<a<<"'s hand\n";
				for(int b=0;b<5;b++)
				{
					int s=returnSuitNo(A[a][b]);
					int r=returnRankNo(A[a][b]);
					Card c;
					c.setCardDetails(s,r);
					c.showCardDetail();
					cout<<", ";
				}
			}
			cout<<endl;
		}
		
		//cout<<endl<<endl;
		
		int array[5]; //this array is used to get the hand of each player. this array is passed to every above function to ge the combination of their hand
		int pComb[p]; //array to store each players best combination
		int pHighestV[p]; //array to store each players highest rank
		for(int a=0;a<p;a++)
		{
			for(int b=0;b<5;b++)
			{
				array[b]=A[a][b]; //store the hand of each player
			}
			pComb[a]=returnTheCombination(array,5); //get the highest combination and store it to an array
			//cout<<pComb[a]<<"check ";
			pHighestV[a]=returnHighestRank(array,5,pComb[a]); //get the highest rank and store it to an array
			//cout<<pHighestV[a]<<" ";
			//cout<<endl;
		}
		
		int highestCombination=0; //variable to store the highest combination among the players
		for(int a=0;a<p;a++)
		{
			if(pComb[a]>=highestCombination)
			{
				highestCombination=pComb[a];
			}
		}
		
		int highestScoreCardTied=0; //if a tie situation occur we have to get the highest score card of that tied players
		for(int a=0;a<p;a++)
		{
			if(pComb[a]==highestCombination) //if the player has the highest combination
			{
				int x=pHighestV[a];
				if(x>=highestScoreCardTied)
					highestScoreCardTied=x;
			}
		}
		
		//cout<<endl<<highestCombination<<" "<<highestScoreCardTied<<endl;
		
		//store the scores to a 2d array after each round
		for(int a=0;a<p;a++)
		{
			if(a==0) //dealer dont get points or dont loose points. so he gets 0 marks always
				finalScore[i][a]=0;
			else
			{
				if(choice[a-1]==2) //if the player withdraw from the game. he gets 0 points
					finalScore[i][a]=0;
				else
				{
					if(pComb[a]==highestCombination && pHighestV[a]==highestScoreCardTied)//if the player has highest combination and highest score card, he get 10 points
						finalScore[i][a]=10;
					else
						finalScore[i][a]=-1; //otherwise he get -1 points
				}	
			}
		}
		
		//print the score board of each round
		cout<<"\n\n---------------------------------------score board of round "<<i+1<<"--------------------------------------------------\n\n";
		cout<<"round\t\t";
		for(int a=0;a<p;a++)
		{
			if(a==0)
				cout<<"dealer\t\t";
			else
				cout<<"player"<<a<<"\t\t";	
		}
		cout<<endl;
		cout<<i+1<<"\t\t";
		for(int a=0;a<p;a++)
		{
			cout<<finalScore[i][a]<<"\t\t";
		}
		cout<<endl<<endl;
		
	}
	
	//after the game over, we have to print the log file
	//open "log.text" and print all points of each round and then the total 
	ofstream file("log.txt");
	file<<"\n\n-------------------------------------------------------LOG FILE-----------------------------------------------------\n\n";
	file<<"round\t\t";
	for(int a=0;a<p;a++)
	{
		if(a==0)
			file<<"dealer\t\t";
		else
			file<<"player"<<a<<"\t\t";	
	}
		
	file<<"\n";
	for(int i=0;i<r;i++)
	{
		file<<i+1<<"\t\t";
		for(int a=0;a<p;a++)
		{
			file<<finalScore[i][a]<<"\t\t";
		}
		file<<endl;
	}
	file<<"T\t\t"; //print the total of each player
	int total=0;
	for(int i=0;i<p;i++)
	{
		for(int a=0;a<r;a++)
		{
			total+=finalScore[a][i]; //get the total of the each player
		}
		file<<total<<"\t\t";
		total=0;
	}
	file.close();
	
	return 0;
}


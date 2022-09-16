#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;

//functions prototypes
int mainMenu();
int streamingServiceMenu();
int distributionLabelMenu();
long generateStreams(int labelType);
double calculateEarnings(int streaming_choice, long streams); 
double calculateLabelEarnings(int labelType, double earnings);

//global constants to hold pay per stream
const double TIDAL = 0.01250;
const double AMAZON = 0.00402;
const double APPLE = 0.00735;
const double SPOTIFY = 0.00437;
const double YOUTUBE = 0.00069;		

//global constants to hold the labels' share
const double MAJOR = 0.6;
const double INDIE = 0.3;		

int main()
{
	int choice; //to hold main menu choice
	int streaming_choice; //to hold streaming service menu choice
	int songs; //to hold number of songs
	long streams; //to hold number of streams
	double artistEarnings; //to hold the amount of money made by the artist
	string streaming_service; //to hold the streaming service as a string
	string name, song; //to hold the artist's and the song's name
	
	choice = mainMenu();
	
	while (choice != 3)
	{
		//both OPTIONS 1 AND 2 start the same way
		//streaming service menu
		streaming_choice = streamingServiceMenu();
		
		//switch on the choice variable
		switch (streaming_choice)
		{
			//storing streaming services' names in a string
			case 1:
				streaming_service = "TIDAL";
				break;
			case 2:
				streaming_service = "Amazon";
				break;
			case 3:
				streaming_service = "Apple Music";
				break;
			case 4:
				streaming_service = "Spotify";
				break;
			case 5:
				streaming_service = "YouTube";
				break;
			default:
				break;
		}
		
		//if OPTION 1 was chosen continue here
		if (choice == 1)
		{
			//prompt user for artist's name and storing it in the string "name"
			cin.ignore(); //to clear keyboard buffer
			cout << "\nWhat is the artist's name? ";
			getline(cin, name);
	
			//prompt user for song's name and storing it the string "song"
			cout << "\nWhat is the name of the song? ";
			getline(cin, song);
		
			//prompt user for number of streams
			cout << "\nHow many streams does " << song << " have on " << streaming_service << "? ";
			cin >> streams;
		
			//while statement to validate user's input
			while (streams < 0)
			{
				cout << "\nERROR - NUMBER OF STREAMS CANNOT BE NEGATIVE." << endl;
				cout << "\nHow many streams does " << song << " have on " << streaming_service << "? ";
				cin >> streams;
			}
			
			//calculate the amount of money made
			double totalEarnings = calculateEarnings(choice, streams);
			
			//display output
			cout << "\nSong Name:\t\t" << song << endl;
			cout << "Artist Name:\t\t" << name << endl;
			cout << "Streaming Service:\t" << streaming_service << endl;
			cout << "Streams:\t\t" << streams << endl;
			cout << setprecision(2) << showpoint << fixed;
			cout << "Earnings:\t\t$" << totalEarnings << endl;
		}
		
		//if OPTION 2 was chosen continue here
		else if (choice == 2)
		{
			cout << "\nHow many songs will be uploaded on " << streaming_service << "? ";
			cin >> songs;
			//validate user response
			while (songs < 1)
			{
				cout << "\nERROR - NUMBER OF SONGS CANNOT BE LESS THAN 1.\n" << endl;
				cout << "\nHow many songs will be uploaded on " << streaming_service << "? ";
				cin >> songs;
			}
			
			//distribution MENU
			int distributionMenuChoice; //to hold user's choice
			distributionMenuChoice = distributionLabelMenu();
			
			for (int i = 1; i <= songs; i++)
			{
				long randomStreams = generateStreams(distributionMenuChoice);
				cout << "\n\tSong #" << i << ":\t" << randomStreams << " streams";
				streams += randomStreams;
			}
			
			//calculate amount of money made from number of streams
			double totalEarnings = calculateEarnings(distributionMenuChoice, streams);
			
			//label's earnings
			double labelEarnings = calculateLabelEarnings(distributionMenuChoice, totalEarnings);
			
			//artist's earnings
			artistEarnings = totalEarnings - labelEarnings;
			
			//display output
			cout << "\n\nStreaming Service:\t" << streaming_service << endl;
			cout << "Streams:\t\t" << streams << endl;
			cout << setprecision(2) << showpoint << fixed;
			cout << "Earnings:\t\t$" << totalEarnings << endl;
			cout << "Artist Earnings:\t$" << artistEarnings << endl;
			cout << "Label Earnings:\t\t$" << labelEarnings << endl;
		}
		
		//display main menu again
		choice = mainMenu();
	}
	
	//if OPTION 3 was chosen end program
	cout << "\nThank you for using the program!";
	return 0;
}

int mainMenu()
{
	int choice;
	//display main menu
	cout << "Choose from the following menu options:\n" << endl;
	cout << "\t1: Upload a single song to a streaming service" << endl;
	cout << "\t2: Upload multiple songs to a streaming service" << endl;
	cout << "\t3: Exit the program\n" << endl;
	cout << "Enter your choice (1, 2, or 3): ";
	cin >> choice;
	//validate choice input
	while (choice < 1 || choice > 3)
	{
		cout << "\nERROR - NOT A VALID MENU CHOICE. PLEASE TRY AGAIN.\n" << endl;
		cout << "Choose from the following menu options:\n" << endl;
		cout << "\t1: Upload a single song to a streaming service" << endl;
		cout << "\t2: Upload multiple songs to a streaming service" << endl;
		cout << "\t3: Exit the program\n" << endl;
		cout << "Enter your choice (1, 2, or 3): ";
		cin >> choice;
	}
	return choice;
}

int streamingServiceMenu()
{
	//both OPTIONS 1 AND 2 start the same way
	int streaming_choice; //to hold the chosen streaming platform
	//streaming service menu
	cout << "\nWhich Streaming Service will you use to upload your song(s)?" << endl;
	cout << "\n\t1: TIDAL\n\t2: Amazon\n\t3: Apple Music\n\t4: Spotify\n\t5: YouTube" << endl;
	//prompt user for menu choice
	cout << "\nEnter your choice (1-5): ";
	//cin statement to store user's choice in the choice variable
	cin >> streaming_choice;
	//while loop to validate user response
	while (streaming_choice < 1 || streaming_choice > 5)
	{
		cout << "\nERROR - NOT A VALID STREAMING SERVICE. Please choose from the services listed.\n" << endl;
		cout << "Which Streaming Service will you use to upload your song(s)?" << endl;
		cout << "\n\t1: TIDAL\n\t2: Amazon\n\t3: Apple Music\n\t4: Spotify\n\t5: YouTube" << endl;
		cout << "\nEnter your choice (1-5): ";
		cin >> streaming_choice;
	}
	return streaming_choice;
}

int distributionLabelMenu()
{
	//distribution MENU
	int choice; //to hold user's choice
	cout << "\nWhich type of distribution will you use to distribute your songs?\n" << endl;
	cout << "\t1: MAJOR LABEL\n\t2: INDEPENDENT LABEL\n" << endl;
	cout << "Enter your choice (1 or 2): ";
	cin >> choice;
	//validate user response
	while (choice < 1 || choice > 2)
	{
		cout << "\nERROR - INVALID DISTRIBUTION CHOSEN. Please choose from one of the options listed.\n" << endl;
		cout << "Which type of distribution will you use to distribute your songs?\n" << endl;
		cout << "\t1: MAJOR LABEL\n\t2: INDEPENDENT LABEL\n" << endl;
		cout << "Enter your choice (1 or 2): ";
		cin >> choice;
	}
	return choice;
}

long generateStreams(int labelType)
{
	srand(time(0)); //needed to correctly use rand()
	long randomStreams; //to hold the random number generated for streams
	if(labelType == 1)
	{
		randomStreams = rand() % 49900000 + 100000;
	}
	else if (labelType == 2)
	{
		randomStreams = rand() % 990000 + 10000;
	}
	return randomStreams;
}

double calculateEarnings(int streaming_choice, long streams)
{
	double earnings_per_streams;
	switch (streaming_choice)
	{
		case 1:
			//income per stream based on streaming platform
			earnings_per_streams = TIDAL;
			break;
		case 2:
			earnings_per_streams = AMAZON;
			break;
		case 3:
			earnings_per_streams = APPLE;
			break;
		case 4:
			earnings_per_streams = SPOTIFY;
			break;
		case 5:
			earnings_per_streams = YOUTUBE;
			break;
		default:
			break;
	}
	//return amount of money made from number of streams
	double earnings = earnings_per_streams * streams;
	return earnings;
}

double calculateLabelEarnings(int labelType, double earnings)
{
	double label_rate;
	switch (labelType)
	{
		case 1:
			label_rate = MAJOR;
			break;
		case 2:
			label_rate = INDIE;
			break;
		default:
			break;
	}
	//label's earnings
	return label_rate * earnings;
}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Player{
    string name; 
    int score;     
    Player *next;  
};

// Leaderboard class
class Leaderboard{
private:          
    Player board[10];      
    int count; 
    Player *head;       

    // Insert into top 10 board array
    void updateBoard(Player* newPlayer){

        // Check if the player is already in top 10 (If the array is not empty)
        for (int i = 0; i < count; i++){
            if (board[i].name == newPlayer->name) {
                board[i].score = newPlayer->score;
                sortBoard();
                return;
            }
        }

        // If top 10 is not full or empty, then it adds the player
        if (count < 10){
            board[count++] = *newPlayer;
            sortBoard();
        } else{
            // Check if the new player's score is higher than the 10th player in the leaderboard (triggers if and only if the array is full)
            if (newPlayer->score > board[count - 1].score) {
                board[count - 1] = *newPlayer;
                sortBoard();
            }
        }
    }

    // Sort top 10 array by score (descending) (Temporary: This should be the priority queue part)
    void sortBoard() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (board[j].score < board[j + 1].score ||
                   (board[j].score == board[j + 1].score && board[j].name > board[j + 1].name)) {
                    Player temp = board[j];
                    board[j] = board[j + 1];
                    board[j + 1] = temp;
                }
            }
        }
    }


public:
    Leaderboard(){
        head = nullptr;
        count = 0;
    }

    // Add or update player
    void addPlayer(string name, int score){

        if (score < 0 || score > 100){
            cout << "Invalid score. Enter a score between 0-100.\n";  // Error handling for invalid score.
            return;
        }

        Player* current = head;
        while (current != nullptr){
            if (current->name == name){
                cout << "\n\nExisting player! Cannot have more than one entry!";  // Error handling for multiple entries
                return;
            }
            current = current->next;
        }

        // If list is empty or no matching player is found; add new player to the linked list.
        Player *newPlayer = new Player;
        newPlayer->name = name;
        newPlayer->score = score;
        newPlayer->next = head;
        head = newPlayer;

        updateBoard(newPlayer);
        cout << "\n\nPlayer record added.";
    }

    void updatePlayer(string name, int score){


        if (!head)
            cout << "\n\nNo records found. Player list is empty.";
        else{

            if (score < 0 || score > 100){
            cout << "Invalid score. Enter a score between 0-100.\n";  // Error handling for invalid score.
            return;
            }

            // Search for the player in the linked list if the list is not empty.

            bool found = 0;
            Player *current = head;
            while (current != nullptr){
                if (current->name == name){
                    found = 1;
                    cout << "\nUpdating score for player: " << name << "\n";
                    current->score = score;
                    updateBoard(current);
                    return;
                }
                current = current->next;
            }

            if (found == 0)
            cout << "\n\nNo matching player found.";
        }
    }

    // Display top 10 players using the array.
    void displayBoard(){
        
        if (count == 0)
            cout << "\n\nLeaderboard is currently empty.";
        else{
            cout << "\n================================\n";
            cout << "           LEADERBOARD           \n";
            cout << "================================\n";
            for (int i = 0; i < count; i++) {
                cout << i + 1 << ". " << board[i].name << " - " << board[i].score << "\n";
            }
        }
    }

    // Save leaderboard to file
    void saveToFile(const char* filename){
        ofstream file(filename);
        if (!file) {
            cout << "Error: File does not exist.\n";     // Error handling for files
            return;
        }

       for (int i = 0; i < count; i++){
        file << board[i].name << " " << board[i].score << "\n";
        }


        file.close();
        cout << "\nLeaderboard saved to " << filename << "\n";
    }

    // Quiz Mini-game

    int playQuizGame(){
        string questions[4] = {"1. What year was C++ created?:",
                            "2. Who invented C++?:",
                            "3. What is the predecessor of C++?:",
                            "4. Is the Earth flat?:"};
        
        string choices[4][4] = {{"A. 1969", "B. 1975", "C. 1985", "D. 1989"},
                            {"A. Guido van Rossum", "B. Bjarne Stroustrup", "C. John Carmack", "D. Mark Zuckerburg"},
                            {"A. C", "B. C+", "C. C--", "D. B++"},
                            {"A. yes", "B. no", "C. maybe", "D. mama mo"}};

        char answerKey[4] = {'C', 'B', 'A', 'D'};

        char guess;
        int score;
        int size = sizeof(questions) / sizeof(questions[0]);
        
        for (int i = 0; i < size; i++){
            cout << "\n************************************* \n";
            cout << questions[i] << '\n';
            cout << "************************************* \n";
            
            for (int j = 0; j < sizeof(choices[i]) / sizeof(choices[i][i]); j++)
            {
                cout << choices[i][j] << '\n';
            }
            
            cout << "Enter your guess: ";
            cin >> guess;
            guess = toupper(guess);

            if(guess == answerKey[i]){
                cout << "Correct answer! \n\n";
                score++;
            }
            else{
                cout << "Wrong answer! \n\n";
            }
    }
    
    cout << "************************************* \n";
    cout << "*            RESULTS                * \n";
    cout << "************************************* \n";
    cout << "# of questions: " << size << '\n';
    cout << "# of correct guess: " << score << '\n';
    cout << "Total Percentage: " << (score / (double) size) * 100 << "%";
    return score;
    }
};

int main(){
    Leaderboard leaderboard;
    string name;
    int score, choice;

    do{
	        cout << "\n\n================================\n";
	        cout << "              MENU              \n";
	        cout << "================================\n";
	        cout << "[1] Add Player Record\n";
	        cout << "[2] Update Player Record\n";
	        cout << "[3] Display Leaderboard\n";
	        cout << "[4] Save Leaderboard to File\n";
	        cout << "[5] Play Mini-Game\n";
	        cout << "[6] Exit\n\n";
	        cout << "Enter your choice: ";
	        
		while(!(cin>>choice)){
	        cin.clear();
	        cin.ignore(123,'\n');
	        cout << "Invalid input! Numbers only!"<< endl<< "\n\nEnter your choice: ";
	}
        
        cin.ignore();

        switch (choice) {

        case 1:
            cout << "\nEnter player name: ";
            getline(cin, name);
            cout << "Enter player score: ";

            while(!(cin>>score)){ 
                cin.clear();
                cin.ignore(123,'\n');
                cout << "Invalid input! Numbers only!" << endl << "\n\nEnter player score: ";
            }

            leaderboard.addPlayer(name, score);
            break;
        case 2: 
            cout << "\nEnter player name: ";
            getline(cin, name);
	        cout << "Enter player score: ";

            while(!(cin>>score)){ 
                cin.clear();
                cin.ignore(123,'\n');
                cout << "Invalid input! Numbers only!" << endl << "\n\nEnter player score: ";
            }

            leaderboard.updatePlayer(name, score);
            break;
        case 3:
            leaderboard.displayBoard();
            break;
        case 4:
            leaderboard.saveToFile("leaderboard.txt");
            break;
        case 5:
            cout << "\n\nEnter your name: ";
            getline(cin, name);
            score = leaderboard.playQuizGame();
            leaderboard.addPlayer(name, score);
            break;
        case 6:
            cout << "\n\nThank you for using the program!";
            cout << "\n\nDeveloped by: ";
            cout << "\nClarence Junio " << "\nKaiser Opulencia \n"; 
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

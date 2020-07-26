//This is a simple code breaking game. At the beginning of the game, it randomly generates a secret 4 digit code.
// Each digit should be unique. For example, 0123 and 3217 are valid codes, but 0112 and 7313 are not.
//
// Once the number has been generated, the player has 8 chances to guess the code. after each guess, the game should report how many digits
// they guessed correctly, and how many had the right number, but in the wrong place. For example, with a secret code of 0123, a guess of 0451
// has one digit correct (the 0), and one digit with the right number in the wrong place (the 1).
// 
// After the player has either correctly broken the code or run out of guesses, ask if they would like to play again. If so, generate a new
// code and start again, otherwise exit the program.
//
// Have fun!

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

// Code generation. Maybe I will make this into a string.
int randomCode(int numDigits)
{   
    int digits[] = { 0,1,2,3,4,5,6,7,8,9 };

    random_shuffle(digits, digits + 10);
    
    int code = digits[0];

    for (int i = 1; i < numDigits; i++)
    {
        code *= 10; // This adds a zero at the end of each pass
        code += digits[i];
    }
    
    return code;
}

// Checks the code and infomrs the user if they got it right or if they are close
bool checkCode(int code, string guess)
{
    bool codeBroken = false;
    string tempCode, tempGuess;

    // Converting secred code to string for analysis
    if (code < 1000)
        tempCode = "0" + to_string(code);
    else
        tempCode = to_string(code);

    // Checking if they guesse correctly
    if (tempCode.compare(guess) == 0)
        codeBroken = true;
    // Check for valid digits
    else
    {
        for (int i = 0; i < guess.length(); i++)
        {   
            // Finds correct digits in correct positions
            if (guess[i] == tempCode[i])
            {
                cout << guess[i] << " is a correct digit" << endl;
                continue;
            }

            // Finds correct digits but not in correct position
            for (int j = 0; j < guess.length(); j++)
            {
                if (guess[j] == tempCode[i])
                {
                    cout << guess[j] << " is a correct digit but not in the right position" << endl;
                    continue;
                }
            }
        }
    }

    return codeBroken;
}

// Helper function to check if the guess is a number
bool isNumber(string guess)
{
    bool has_only_digits = (guess.find_first_not_of( "0123456789" ) == string::npos);
    return has_only_digits;
}

int main()
{   
    int secretCode, chances = 8, tries = 0;
    string guess;
    const int numDigits = 4;
    bool playing = true; // Tracks if the player want to keep playing or not.
    string response;
    
    srand(time(0)); // seeding the pseudo random number
    
    cout << "Welcome to Code Breaker!\nYou have 8 chances to crack a 4 digit code.\nGood luck and happy hacking!\n\n" << endl;

    // Will keep playing until the player decides not to
    while (playing)
    {
        secretCode = randomCode(numDigits);
        cout << "the code is: " << setfill('0') << setw(4) << secretCode << endl; // delete this line later. Just for testing

        // The guessing part
        while (tries < chances)
        {
            usrGuess:
            cout << "Guess the code: " << endl;
            cin >> guess;
        
            // Check if the user entered a valid code. Will not count this as a try
            // Check if the code entered is numerical
            if(!isNumber(guess))
            {
                cout << "Error: That does not look like a number...\nTry again\n" << endl;
                cin.clear();
                goto usrGuess;
            }

            // Check if numerical code entered is of the right size
            if (guess.length() != 4)
            {
               cout << "Error: That does not look like a 4 digit code...\nTry again\n" << endl;
               cin.clear();
               goto usrGuess; // sorry I am usually against goto
            }

            if (checkCode(secretCode, guess))
            {
                cout << "\n(＾∇＾)ﾉ♪ *throws confetti*      YOU BROKE THE CODE!!      *throws more confetti*\n" << endl; // maybe add more flare to this
                cout << "*cleans up confetti*\n" << endl;
                cout << "Would you like to play again?\n\t1-Yes\n\t2-No\n" << endl;
                goto input; // again, sorry for this.
            }
            else
            {
                tries++;
                continue;
            }       
        }

        cout << "Unfortunately, it seems that you ran out of tries (╥﹏╥)\n" << endl;

       // Checks if the player wants to keep playing
        cout << "Would you like to play again?\n\t1-Yes\n\t2-No\n" << endl;
        input:
        cin >> response;

        transform(response.begin(), response.end(), response.begin(), ::tolower);

        // Initializes the number of tries and restarts the game again
        if (response.compare("yes") == 0)
        {
            cout << "Let us play again!\n" << endl;
            system("clear");
            tries = 0;
        }
        // Exits the game
        else if (response.compare("no") == 0)
        {
            cout << "\nThank you for playing. Goodbye!" << endl;
            playing = false;
        }
        // Check for invalid input from the player and allow them the chance to correct their response
        else
        {
            cout << "Error: Invalid response!\nWould you like to play again? " << endl;
            goto input;
        }
    }
    return 0;
}
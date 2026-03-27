#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* 
C for Assignment 3
Created 09/03/2026 by Alyx Deland
Rev Hist:
    Last editted 26/03/2026
*/

// Function to decode URL-encoded characters (like %20 for space)
void decode_url(char *src) {
    char *dst = src;
    while (*src) {
        if (*src == '+') *dst = ' ';
        else if (*src == '%' && src[1] && src[2]) {
            char hex[3] = { src[1], src[2], '\0' };
            *dst = (char)strtol(hex, NULL, 16);
            src += 2;
        } else *dst = *src;
        src++; dst++;
    }
    *dst = '\0';
}

// Helper function to print the HTML header and opening tags
void print_html_header() {
    printf("<html><body>\n"); // Open html
    printf("    <div style='display: flex; align-items: center;'>\n");
    printf("        <ul>\n");
}

// Helper function to print the game results list items
void print_game_results(int result, const char *username, const char *charChoice, int userMove, int cpuMove, const char *ruleDescription, const char *moves[]) {
    if (result == 1) {
        printf("            <li><b>%s WON</b></li>\n", username);
    } else if (result == 2) {
        printf("            <li><b>%s WON</b></li>\n", charChoice);
    } else {
        printf("            <li><b>No winner - it was a TIE</b></li>\n");
    }
    
    printf("            <li>%s chose %s</li>\n", username, moves[userMove]);
    printf("            <li>%s chose %s</li>\n", charChoice, moves[cpuMove]);
    printf("            <li>%s</li>\n", ruleDescription);
    printf("        </ul>\n");
}

// Helper function to print the image and HTML closing tags
void print_html_footer(int result) {
    // Determine the image path based on the result
    const char* imgPath = (result == 1) ? "Win.png" : (result == 2) ? "Lose.png" : "Tie.png";
    printf("        <img src='/RPSLS/Game/images/%s' style='max-width:400px; margin-left:20px;' alt='Result Image'>\n", imgPath);
    printf("    </div>\n");
    printf("</body></html>\n"); // Close html
}

int main(void) {
    printf("Content-type: text/html\n\n");

    // Get Data from Environment 
    char *query = getenv("QUERY_STRING");
    char username[100] = "User";
    char charChoice[100] = "Computer";
    int userMove = 0;

    if (query != NULL) {
        // Use width limits (%99) to prevent buffer overflows. This is a critical security fix.
        sscanf(query, "username=%99[^&]&charChoice=%99[^&]&choice=%d", username, charChoice, &userMove);
        decode_url(username);
        decode_url(charChoice);
    }

    // Randomize Computer Move (1-5) 
    srand((unsigned int)time(NULL));
    int cpuMove = (rand() % 5) + 1; // 1:Rock, 2:Paper, 3:Scissors, 4:Lizard, 5:Spock

    // Define the moves array here so it's available for game logic
    const char *moves[] =  {
        "Invalid Move", // Index 0 is unused, moves start from 1
        "Rock",
        "Paper",
        "Scissors",
        "Lizard",
        "Spock"
    };

    int result = 0;
    char ruleDescription[200] = "";

    // Check if user's move is within the valid range.
    if (userMove < 1 || userMove > 5) {
        result = 2; // Computer wins by default
        strcpy(ruleDescription, "Invalid move from user. Computer wins.");
    } else if (userMove == cpuMove) {
        result = 0; // Tie
        strcpy(ruleDescription, "When both players make the same choice, it is a TIE");
    } else {
        // Game logic for valid user moves
        if ( 
            // User winning conditions
            (userMove == 1 && (cpuMove == 3 || cpuMove == 4)) ||
            (userMove == 2 && (cpuMove == 1 || cpuMove == 5)) ||
            (userMove == 3 && (cpuMove == 2 || cpuMove == 4)) ||
            (userMove == 4 && (cpuMove == 2 || cpuMove == 5)) ||
            (userMove == 5 && (cpuMove == 1 || cpuMove == 3))
        ) {
            result = 1; // User wins
            // Rule description for User win cases
            if (userMove == 1) { // Rock
                if (cpuMove == 3) strcpy(ruleDescription, "Rock crushes Scissors");
                else strcpy(ruleDescription, "Rock crushes Lizard");
            } else if (userMove == 2) { // Paper
                if (cpuMove == 1) strcpy(ruleDescription, "Paper covers Rock");
                else strcpy(ruleDescription, "Paper disproves Spock");
            } else if (userMove == 3) { // Scissors
                if (cpuMove == 2) strcpy(ruleDescription, "Scissors cuts Paper");
                else strcpy(ruleDescription, "Scissors kill Lizard");
            } else if (userMove == 4) { // Lizard
                if (cpuMove == 2) strcpy(ruleDescription, "Lizard eats Paper");
                else strcpy(ruleDescription, "Lizard poisons Spock");
            } else if (userMove == 5) { // Spock
                if (cpuMove == 1) strcpy(ruleDescription, "Spock vaporizes Rock");
                else strcpy(ruleDescription, "Spock smashes Scissors");
            }
        } else {
            result = 2; // CPU wins
            // Rule descriptions for CPU win cases
            if (cpuMove == 1) { // Rock
                if (userMove == 3) strcpy(ruleDescription, "Rock crushes Scissors");
                else strcpy(ruleDescription, "Rock crushes Lizard");
            } else if (cpuMove == 2) { // Paper
                if (userMove == 1) strcpy(ruleDescription, "Paper covers Rock");
                else strcpy(ruleDescription, "Paper disproves Spock");
            } else if (cpuMove == 3) { // Scissors
                if (userMove == 2) strcpy(ruleDescription, "Scissors cuts Paper");
                else strcpy(ruleDescription, "Scissors kill Lizard");
            } else if (cpuMove == 4) { // Lizard
                if (userMove == 2) strcpy(ruleDescription, "Lizard eats Paper");
                else strcpy(ruleDescription, "Lizard poisons Spock");
            } else if (cpuMove == 5) { // Spock
                if (userMove == 1) strcpy(ruleDescription, "Spock vaporizes Rock");
                else strcpy(ruleDescription, "Spock smashes Scissors");
            }
        }
    }
    // Output HTML
    print_html_header();
    print_game_results(result, username, charChoice, userMove, cpuMove, ruleDescription, moves);
    print_html_footer(result);

    return 0;
}
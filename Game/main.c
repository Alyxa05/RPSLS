#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int main(void) {
    // 1. Required Header for CGI 
    printf("Content-type: text/html\n\n");

    // 2. Get Data from Environment 
    char *query = getenv("QUERY_STRING");
    char userName[100] = "Player", charChoice[100] = "", userMoveStr[10] = "";
    int userMove = 0, cpuMove = 0;

    if (query != NULL) {
        sscanf(query, "userName=%[^&]&chars=%[^&]&choice=%s", userName, charChoice, userMoveStr);
        decode_url(userName);
        decode_url(charChoice);
        userMove = atoi(userMoveStr);
    }

    // 3. Randomize Computer Move (1-5) 
    srand((unsigned int)time(NULL));
    cpuMove = (rand() % 5) + 1; // 1:Rock, 2:Paper, 3:Scissors, 4:Lizard, 5:Spock

    // 4. Game Logic & Rules
    const char *names[] = {"", "Rock", "Paper", "Scissors", "Lizard", "Spock"};
    const char *rules[] = {
        "", // Padding
        "Rock crushes Scissors", "Paper covers Rock", "Scissors cuts Paper",
        "Lizard eats Paper", "Spock vaporizes Rock", "Rock crushes Lizard",
        "Lizard poisons Spock", "Spock smashes Scissors", "Scissors decapitate Lizard",
        "Paper disproves Spock"
    };

    char resultMsg[200] = "";
    char status[10] = "TIE"; // Default

    if (userMove == cpuMove) {
        strcpy(resultMsg, "when both players make the same choice, it is a TIE");
        strcpy(status, "TIE");
    } else {
        // Simple logic check for wins
        if ((userMove == 1 && (cpuMove == 3 || cpuMove == 4)) ||
            (userMove == 2 && (cpuMove == 1 || cpuMove == 5)) ||
            (userMove == 3 && (cpuMove == 2 || cpuMove == 4)) ||
            (userMove == 4 && (cpuMove == 2 || cpuMove == 5)) ||
            (userMove == 5 && (cpuMove == 1 || cpuMove == 3))) {
            sprintf(resultMsg, "According to the rules: %s", "User Wins!", *rules[userMove]); // Replace with specific rule
            strcpy(status, "WIN");
        } else {
            sprintf(resultMsg, "According to the rules: %s", "Computer Wins!"); 
            strcpy(status, "LOSE");
        }
    }

    // 5. Output HTML
    printf("<html><head><style>ul{display:inline-block; vertical-align:top;} img{max-width:400px;}</style></head><body>");
    printf("<h1>Game Results</h1>");
    
    // Results List
    printf("<ul>");
    if (strcmp(status, "WIN") == 0) printf("<li><b>%s WON</b></li>", userName);
    else if (strcmp(status, "LOSE") == 0) printf("<li><b>%s WON</b></li>", charChoice);
    else printf("<li><b>Nobody WON - it was a TIE</b></li>");

    printf("<li>%s chose %s</li>", userName, names[userMove]);
    printf("<li>%s chose %s</li>", charChoice, names[cpuMove]);
    printf("<li>%s</li>", resultMsg);
    printf("</ul>");

    // Win/Loss/Tie Image
    // Using relative path to Game folder
    printf("<img src='theGame/%s.png' alt='%s' style='margin-left:20px;'>", status, status);

    printf("</body></html>");

    return 0;
}
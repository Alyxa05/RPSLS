#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//

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
    printf("Content-type: text/html\n\n");

    // Get Data from Environment 
    char *query = getenv("QUERY_STRING");
    char username[100] = "User";
    char charChoice[100] = "Computer";
    int userMove = 0;

    if (query != NULL) {
        sscanf(query, "username=%[^&]&charChoice=%[^&]&game=%s", username, charChoice, &userMove);
        decode_url(username);
        decode_url(charChoice);
    }

    // Randomize Computer Move (1-5) 
    srand((unsigned int)time(NULL));
    int cpuMove = (rand() % 5) + 1; // 1:Rock, 2:Paper, 3:Scissors, 4:Lizard, 5:Spock

    int result = 0;
    char ruleDescription[200] = "";

    if (userMove == cpuMove) {
        result = 0;
    } else {
         if ((userMove == 1 && (cpuMove == 3 || cpuMove == 4)) ||
            (userMove == 2 && (cpuMove == 1 || cpuMove == 5)) ||
            (userMove == 3 && (cpuMove == 2 || cpuMove == 4)) ||
            (userMove == 4 && (cpuMove == 2 || cpuMove == 5)) ||
            (userMove == 5 && (cpuMove == 1 || cpuMove == 3))) 
        {
            result = 1;
        } else {
            result = 2;
        }
    }

    if ((userMove == 1 && (cpuMove == 3 || cpuMove == 4)) ||
       (cpuMove == 1 && (userMove == 3 || userMove == 4))) 
    {
        strcpy(ruleDescription, "Rock crushes Scissors and Lizard");
    } else if ((userMove == 2 && (cpuMove == 1 || cpuMove == 5)) ||
              (cpuMove == 2 && (userMove == 1 || userMove == 5)))
    {
        strcpy(ruleDescription, "Paper covers Rock and disproves Spock");
    } else if ((userMove == 3 && (cpuMove == 2 || cpuMove == 4)) ||
              (cpuMove == 3 && (userMove == 2 || userMove == 4)))
    {
        strcpy(ruleDescription, "Scissors cuts Paper and kills Lizard");
    } else if ((userMove == 4 && (cpuMove == 2 || cpuMove == 5)) ||
              (cpuMove == 4 && (userMove == 2 || userMove == 5)))
    {
        strcpy(ruleDescription, "Lizard eats Paper and poisons Spock");
    } else if ((userMove == 5 && (cpuMove == 1 || cpuMove == 3)) ||
              (cpuMove == 5 && (userMove == 1 || userMove == 3)))
    {
        strcpy(ruleDescription, "Spock vaporizes Rock and smashes Scissors");
    } else if (userMove == cpuMove) {
        strcpy(ruleDescription, "When both players make the same choice, it is a TIE");
    } else {
        strcpy(ruleDescription, "");
    }

    // Output HTML
    printf("<html><body>");
    printf("<div style='display: flex; align-items: center;'>");
    
    printf("<ul>");
    if (result == 1) printf("<li><b>%s WON</b></li>", username);
    else if (result == 2) printf("<li><b>%s WON</b></li>", charChoice);
    else printf("<li><b>No winner - it was a TIE</b></li>");

    printf("<li>%s chose %d</li>", username, userMove);
    printf("<li>%s chose %d</li>", charChoice, cpuMove);
    printf("<li>%s</li>", ruleDescription);
    printf("</ul>");

    // Display image beside the text
    const char* imgPath = (result == 1) ? "Win.png" : (result == 2) ? "Lose.png" : "Tie.png";
    printf("<img src='/images/%s' style='max-width:400px; margin-left:20px;'>", imgPath);
    
    printf("</div></body></html>");

    return 0;
}
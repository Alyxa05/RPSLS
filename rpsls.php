<?php
/* 
PHP for Assignment 3
Created 09/03/2026 by Alyx Deland
Rev Hist:
    Last editted 26/03/2026
Trying to be as identical as possible to main.c
*/

// Map move numbers to their string names for user-friendly output
$moveNames = [
    0 => "Invalid Move",
    1 => "Rock",
    2 => "Paper",
    3 => "Scissors",
    4 => "Lizard",
    5 => "Spock"
];

// Get Data from Form
$username = isset($_POST['username']) ? htmlspecialchars($_POST['username']) : "User";
$charChoice = isset($_POST['charChoice']) ? htmlspecialchars($_POST['charChoice']) : "Computer";
$userMove = isset($_POST['choice']) ? (int)$_POST['choice'] : 0;

// Randomize Computer Move
$cpuMove = rand(1, 5);

// Game Logic
$result = 0; // 0: Tie, 1: User Wins, 2: Computer Wins
$ruleDescription = "";

// Check if user's move is within the valid range.
if ($userMove < 1 || $userMove > 5) {
    $result = 2; // Computer wins by default
    $ruleDescription = "Invalid move. Computer wins.";
} elseif ($userMove == $cpuMove) {
    $result = 0;
    $ruleDescription = "When both players make the same choice, it is a TIE";
} else {
    // Win conditions for User
    if (($userMove == 1 && ($cpuMove == 3 || $cpuMove == 4)) ||
        ($userMove == 2 && ($cpuMove == 1 || $cpuMove == 5)) ||
        ($userMove == 3 && ($cpuMove == 2 || $cpuMove == 4)) ||
        ($userMove == 4 && ($cpuMove == 2 || $cpuMove == 5)) ||
        ($userMove == 5 && ($cpuMove == 1 || $cpuMove == 3))) {
        $result = 1; // User wins
        // Rule descriptions for User win cases
        if ($userMove == 1) { // Rock
            if ($cpuMove == 3) $ruleDescription = "Rock crushes Scissors";
            else $ruleDescription = "Rock crushes Lizard";
        } elseif ($userMove == 2) { // Paper
            if ($cpuMove == 1) $ruleDescription = "Paper covers Rock";
            else $ruleDescription = "Paper disproves Spock";
        } elseif ($userMove == 3) { // Scissors
            if ($cpuMove == 2) $ruleDescription = "Scissors cuts Paper";
            else $ruleDescription = "Scissors kill Lizard";
        } elseif ($userMove == 4) { // Lizard
            if ($cpuMove == 2) $ruleDescription = "Lizard eats Paper";
            else $ruleDescription = "Lizard poisons Spock";
        } elseif ($userMove == 5) { // Spock
            if ($cpuMove == 1) $ruleDescription = "Spock vaporizes Rock";
            else $ruleDescription = "Spock smashes Scissors";
        }
    } else {
        $result = 2; // CPU wins
        // Rule descriptions for CPU win cases
        if ($cpuMove == 1) { // Rock
            if ($userMove == 3) $ruleDescription = "Rock crushes Scissors";
            else $ruleDescription = "Rock crushes Lizard";
        } elseif ($cpuMove == 2) { // Paper
            if ($userMove == 1) $ruleDescription = "Paper covers Rock";
            else $ruleDescription = "Paper disproves Spock";
        } elseif ($cpuMove == 3) { // Scissors
            if ($userMove == 2) $ruleDescription = "Scissors cuts Paper";
            else $ruleDescription = "Scissors kill Lizard";
        } elseif ($cpuMove == 4) { // Lizard
            if ($userMove == 2) $ruleDescription = "Lizard eats Paper";
            else $ruleDescription = "Lizard poisons Spock";
        } elseif ($cpuMove == 5) { // Spock
            if ($userMove == 1) $ruleDescription = "Spock vaporizes Rock";
            else $ruleDescription = "Spock smashes Scissors";
        }
    }
}

// Determine the image path based on the result
$imgPath = ($result == 1) ? "Win.png" : (($result == 2) ? "Lose.png" : "Tie.png");

// Output HTML
require_once 'rpsls_view.php'; // Include the HTML template

?>
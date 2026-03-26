<?php
/* 
PHP for Assignment 3
Created 09/03/2026 by Alyx Deland
Rev Hist:
    Last editted 26/03/2026
Trying to be as identical as possible to main.c
*/


// Get Data from Form
$username = isset($_POST['username']) ? htmlspecialchars($_POST['username']) : "User";
$charChoice = isset($_POST['charChoice']) ? htmlspecialchars($_POST['charChoice']) : "Computer";
$userMove = isset($_POST['game']) ? (int)$_POST['game'] : 0;

// Randomize Computer Move
// 1:Rock, 2:Paper, 3:Scissors, 4:Lizard, 5:Spock
$cpuMove = rand(1, 5);

// Game Logic
$result = 0; // 0: Tie, 1: User Wins, 2: Computer Wins
$ruleDescription = "";

if ($userMove == $cpuMove) {
    $result = 0;
} else {
    // Win conditions for User
    if (($userMove == 1 && ($cpuMove == 3 || $cpuMove == 4)) ||
        ($userMove == 2 && ($cpuMove == 1 || $cpuMove == 5)) ||
        ($userMove == 3 && ($cpuMove == 2 || $cpuMove == 4)) ||
        ($userMove == 4 && ($cpuMove == 2 || $cpuMove == 5)) ||
        ($userMove == 5 && ($cpuMove == 1 || $cpuMove == 3))) 
    {
        $result = 1;
    } else {
        $result = 2;
    }
}

// Rule Descriptions
if (($userMove == 1 && ($cpuMove == 3 || $cpuMove == 4)) ||
    ($cpuMove == 1 && ($userMove == 3 || $userMove == 4))) 
{
    $ruleDescription = "Rock crushes Scissors and Lizard";
} elseif (($userMove == 2 && ($cpuMove == 1 || $cpuMove == 5)) ||
          ($cpuMove == 2 && ($userMove == 1 || $userMove == 5)))
{
    $ruleDescription = "Paper covers Rock and disproves Spock";
} elseif (($userMove == 3 && ($cpuMove == 2 || $cpuMove == 4)) ||
          ($cpuMove == 3 && ($userMove == 2 || $userMove == 4)))
{
    $ruleDescription = "Scissors cuts Paper and kills Lizard";
} elseif (($userMove == 4 && ($cpuMove == 2 || $cpuMove == 5)) ||
          ($cpuMove == 4 && ($userMove == 2 || $userMove == 5)))
{
    $ruleDescription = "Lizard eats Paper and poisons Spock";
} elseif (($userMove == 5 && ($cpuMove == 1 || $cpuMove == 3)) ||
          ($cpuMove == 5 && ($userMove == 1 || $userMove == 3)))
{
    $ruleDescription = "Spock vaporizes Rock and smashes Scissors";
} elseif ($userMove == $cpuMove) {
    $ruleDescription = "When both players make the same choice, it is a TIE";
} else {
    $ruleDescription = "";
}

// Output HTML
?>
<html>
<body>
    <div style='display: flex; align-items: center;'>
        <ul>
            <?php
            if ($result == 1) echo "<li><b>$username WON</b></li>";
            elseif ($result == 2) echo "<li><b>$charChoice WON</b></li>";
            else echo "<li><b>No winner - it was a TIE</b></li>";
            ?>
            <li><?php echo "$username chose $userMove"; ?></li>
            <li><?php echo "$charChoice chose $cpuMove"; ?></li>
            <li><?php echo $ruleDescription; ?></li>
        </ul>

        <?php
        $imgPath = ($result == 1) ? "Win.png" : (($result == 2) ? "Lose.png" : "Tie.png");
        echo "<img src='/images/$imgPath' style='max-width:400px; margin-left:20px;'>";
        ?>
    </div>
</body>
</html>
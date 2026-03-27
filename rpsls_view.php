<html>
<body>
    <div style='display: flex; align-items: center;'>
        <ul>
            <?php
            // Messages depending on result of the game
            if ($result == 1) {
                echo "<li><b>$username WON</b></li>";
            } elseif ($result == 2) {
                echo "<li><b>$charChoice WON</b></li>";
            } else {
                echo "<li><b>No winner - it was a TIE</b></li>";
            }
            ?>
            
            <li><?php echo "$username chose {$moveNames[$userMove]}"; ?></li>
            <li><?php echo "$charChoice chose {$moveNames[$cpuMove]}"; ?></li>
            <li><?php echo $ruleDescription; ?></li>
        </ul>
        
        <?php
        echo "<img src='/RPSLS/Game/images/$imgPath' style='max-width:400px; margin-left:20px;' alt='Result Image'>";
        ?>
    </div>
</body>
</html>
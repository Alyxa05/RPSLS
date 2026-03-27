/*
Javascript for Assignment 3
Created 09/03/2026 by Alyx Deland
Rev Hist:
    Last editted 26/03/2026
*/

const errorMessageElement = document.getElementById('errorMessage');

// Function to display error messages
function displayError(message) {
    errorMessageElement.textContent = message;
}

// Function to clear error messages
function clearError() {
    errorMessageElement.textContent = "";
}

function showChars() {
    document.getElementById('name').classList.remove('active');
    document.getElementById('name').classList.add('inactive');

    document.getElementById('characters').classList.remove('inactive');
    document.getElementById('characters').classList.add('active');
}

function showGame() {
    document.getElementById('characters').classList.remove('active');
    document.getElementById('characters').classList.add('inactive');

    document.getElementById('game').classList.remove('inactive');
    document.getElementById('game').classList.add('active');
    document.getElementById('last').classList.remove('inactive');
    document.getElementById('last').classList.add('active');
}

function validateName() {
    const nameInput = document.getElementById('nameinput');
    if (nameInput.value.trim() === "") {
        displayError("Please enter your name.");
        return false;
    }
    clearError();
    showChars();
    return true;
}

function charSelect() {
    const characterSelect = document.getElementById('char-selection');
    if (characterSelect.value === "") {
        displayError("Please select a character.");
        return false;
    }
    clearError();
    showGame();
    return true;
}

function validateForm() {
    const gameChoices = document.getElementsByName('choice');
    let isChoiceMade = false;

    for (let i = 0; i < gameChoices.length; i++) {
        if (gameChoices[i].checked) {
            isChoiceMade = true;
            break;
        }
    }

    if (!isChoiceMade) {
        displayError("Please make a game choice.");
        return false;
    }
    clearError();
    return true;
}
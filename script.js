// Javascript for Assignment 3



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
}

function validateName() {
    const nameInput = document.getElementById('nameinput');
    if (nameInput.value.trim() === "") {
        document.getElementById('errorMessage').textContent = "Please enter your name.";
        return false;
    }
    document.getElementById('errorMessage').textContent = "";
    showChars();
    return true;
}

function charSelect() {
    const characterSelect = document.getElementById('char-selection')

    if (characterSelect.value === "") {
        document.getElementById('errorMessage').textContent = "Please select a character";
        return false;
    }
    document.getElementById('errorMessage').textContent = "";
    showGame();
    return true;
}

function validateForm() {
     
}
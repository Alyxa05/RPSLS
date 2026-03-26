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


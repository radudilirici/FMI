function XMLlogin() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == 'NOT-FOUND') {
                document.getElementById("loginResponse").innerHTML = 'Sorry, user not found...';
            }
            else if (this.responseText.search('FOUND') != -1) {
                document.getElementById("loginResponse").innerHTML = 'User registered on ' + this.responseText.substr(6);

            }
            else if (this.responseText == 'ALREADY') {
                document.getElementById("loginResponse").innerHTML = 'Username is already taken.';
            }
            else if (this.responseText == 'ADDED') {
                document.getElementById("loginResponse").innerHTML = 'User has been added to database';
            }
            else {
                alert("PANICA!!!")
            }
        }
    };
    let username = document.getElementsByName('username')[0].value;
    let password = document.getElementsByName('password')[0].value;
    let actions = document.getElementsByName('useraction');
    let action;
    for (let a of actions) {
        if (a.checked) {
            action = a.value
        }
    }
    if (action == 'login')
        xhttp.open("GET", "/login?username=" + username + "&password=" + password, true);
    else if (action == 'register')
        xhttp.open("POST", "/register?username=" + username + "&password=" + password, true);
    else {
        alert('Problema Radio');
        return;
    }
    xhttp.send();
}

window.addEventListener("load", function () {
    let wrp = document.querySelector(".wrapper");
    wrp.style.paddingBottom = "50px";
})
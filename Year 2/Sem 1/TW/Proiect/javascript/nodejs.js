// C:\Users\Mr. Wombat\Documents\Facultate\Anul 2\Sem 1\Tehnici Web\Proiect\javascript
let http = require('http');
let fs = require('fs');
let url = require('url');
var events = require('events');
var eventEmitter = new events.EventEmitter();

displayPage = function(request, response) {
    if (request.method == 'GET' && request.url == '/') {
        fs.readFile('../html/login.html', 'utf8', function (error, data) {
            if (error) {
                console.log('Eroare la afisarea paginii');
                response.writeHead(404);
                response.write('404');
                throw error;
            }
            else {
                console.log('Afisez pagina');
                response.writeHead(200, {"Content-Type": "text/html"});
                response.write(data);
            }
            response.end()
        })
    }
};

checkDatabase = function(username, password, file) {
    let users = JSON.parse(fs.readFileSync(file, 'utf8'));
    for (let u of users) {
        if (u['username'] == username && u['password'] == password) {
            return u['date'];
        }
    }
    return 'NOT-FOUND';
};

checkForUsername = function(username, file) {
    let users = JSON.parse(fs.readFileSync(file, 'utf8'));
    for (let u of users) {
        if (u['username'] == username) {
            return true;
        }
    }
    return false;
};

addUser = function(uname, pass, file) {
    let d = new Date()
    let user = {
        username: uname,
        password: pass,
        date: d.toUTCString()
    };
    let data = JSON.parse(fs.readFileSync(file, 'utf8'));
    data.push(user);
    fs.writeFileSync(file, JSON.stringify(data));
};

login = function(request, response) {
    let myURL = url.parse(request.url, true)
    if (request.method == 'GET' && myURL.pathname == '/login') {
        let myQuery = myURL.query;
        let username = myQuery['username'];
        let password = myQuery['password'];
        let res = checkDatabase(username, password, '../files/users.json');
        if (res == 'NOT-FOUND') {
            console.log('Userul ' + username + ' ' + password + ' nu a fost gasit in baza de date');
            response.writeHead(200, {"Content-Type": "text/plain"});
            response.write('NOT-FOUND');
            response.end();
        }
        else {
            console.log('Userul ' + username + ' ' + password + ' a fost gasit in baza de date');
            response.writeHead(200, {"Content-Type": "text/plain"});
            response.write('FOUND ' + res);
            response.end();
        }

    }
};

register = function(request, response) {
    let myURL = url.parse(request.url, true)
    if (request.method == 'POST' && myURL.pathname == '/register') {
        let myQuery = myURL.query;
        let username = myQuery['username'];
        let password = myQuery['password'];
        if (checkForUsername(username, '../files/users.json')) {
            console.log('Usernameul ' + username + ' este deja luat');
            response.writeHead(200, {"Content-Type": "text/plain"});
            response.write('ALREADY')
            response.end();
            return;
        }
        addUser(username, password, '../files/users.json');
        console.log('Userul ' + username + ' ' + password + ' a fost inregistrat');
        response.writeHead(200, {"Content-Type": "text/plain"});
        response.write('ADDED')
        response.end();
    }
};

var server = http.createServer(
    (function(request,response){
        displayPage(request, response);
        login(request, response);
        register(request, response);
    })
);
server.listen(7000);

// Création et envoi d'une requête HTTP Asynchrone vers notre serveur ESP sur le chemin "/ledon"
function onButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "ledon", true);
    xhttp.send();
}

// Création et envoi d'une requête HTTP Asynchrone vers notre serveur ESP sur le chemin "/ledon"
function offButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "ledoff", true);
    xhttp.send();
}


/*  Toutes les 2 sec (2000 ms)
    Création/Envoi de la requete GET sur le chemin "/retourtemperature"
    Retourne la valeur sur le SPAN de la page HTML
*/
setInterval(function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurTemperature").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourtemperature", true);
    xhttp.send();
}
, 2000);

/*  Toutes les 10 sec
    Création/Envoi de la requete GET sur le chemin "/retourhumidity"
    Retourne la valeur sur le SPAN de la page HTML
*/
setInterval(function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurHumidity").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourhumidity", true);
    xhttp.send();
}
, 10000);
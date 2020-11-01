const char page[] = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width; initial-scale=1.5" />
    <title>Door Button</title>
    <style>
        body {
            background-color: black;
            text-align: center;
        }
        .button {
            border-radius: 20px;
            border: none;
            color: yellow;
            background-color: coral;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 20px;
            cursor: pointer;
        }
    </style>
    <script>
    function sendData() {
    var passw = document.getElementById('pass').value; // Value of text for password
    var xhttp = new XMLHttpRequest();  
    xhttp.open("POST", "openDoor?passw="+passw, false);
    xhttp.send();
    }
    </script>
</head>
    <body>
        <input type="password" id="pass" placeholder="Enter Password">
        <br>
        <br>
        <button class="button" type="submit" onclick="sendData()">Open Door</button>
    </body>
</html>
)=====";

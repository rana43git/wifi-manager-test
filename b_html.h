#ifndef B_HTML_H
#define B_HTML_H

const char B_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>Page B</title>
    <style>
        body {
            font-family: Arial, sans-serif;
        }
        h1 {
            color: #333;
        }
    </style>
</head>
<body>
    <h1>Webpage B</h1>
    <a href="/a.html">Go to Page A</a>
</body>
</html>
)=====";

#endif

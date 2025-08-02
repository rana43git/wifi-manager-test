#ifndef A_HTML_H
#define A_HTML_H

const char A_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>Page A</title>
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
    <h1>Webpage A</h1>
    <a href="/b.html">Go to Page B</a>
</body>
</html>
)=====";

#endif

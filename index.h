#ifndef INDEX_H
#define INDEX_H

const char INDEX[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>INDEX Page</title>
    <script>
        var defaultIP = "http://192.168.1.100";

        function showPopup() {
            if (confirm("Do you want to open the Wi-Fi setup page in 3 seconds?")) {
                fetch(defaultIP + "/router_setup").catch(error => console.error("Error fetching data:", error));
                setTimeout(function () {
                    window.location.href = defaultIP;
                }, 3000);
            }
        }
    </script>
</head>

<body>
    <div>
        <h1>Index Page</h1>
        <button onclick="showPopup()">Wi-Fi Setup</button><br><br>
        <a href="/a.html">Go to Page A</a><br><br>
        <a href="/b.html">Go to Page B</a>
    </div>
</body>

</html>
)=====";

#endif

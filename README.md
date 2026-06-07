# 🤖 Smart ESP8266 Wi-Fi Automation

An automated, hassle-free way to connect your ESP8266 microchip to a local Wi-Fi network. This project creates an easy-to-use webpage dashboard so you can change router connections on the fly without ever needing to reprogram the microchip.

---

# 🛠️ Project Requirements & Guidelines

To integrate this automation setup into an application, ensure the workspace strictly follows these rules:

### Required Files

The core project directory must contain the following files alongside your primary sketch:

```text
index.h
wifiAutomation.h
wifiAutomation.cpp
WiFiManagerLibrary
```

| File                 | Purpose                                     |
| -------------------- | ------------------------------------------- |
| `index.h`            | Stores the web dashboard UI layout          |
| `wifiAutomation.h`   | Defines the external interface              |
| `wifiAutomation.cpp` | Implements configuration loops and handlers |
| `WiFiManagerLibrary` | Root level managemnet |

### Main Sketch Requirements

Include the automation header:

```cpp
#include "wifiAutomation.h"
```

Initialize the automation system inside `setup()`:

```cpp
void setup() {
    initWiFiAutomation();
}
```

Run background services inside `loop()`:

```cpp
void loop() {
    checkWiFiAutomationStatus();
}
```

---

# 🧭 How It Works

For users new to embedded systems, the workflow is very simple:

```text
[ Power On ]
      │
      ▼
 Is Wi-Fi already saved?
   ├── YES ──► Connects to your Router Automatically
   │                     │
   │                     ▼
   │          Built-in LED stays ON
   │                     │
   │                     ▼
   │     Open http://esp8266.local
   │     to access the dashboard
   │
   └── NO ──► Launches Temporary Wi-Fi Hotspot
                          │
                          ▼
          Connect with your phone or computer
                          │
                          ▼
              Select a Wi-Fi network
                          │
                          ▼
                 Enter the password
                          │
                          ▼
                   Device reboots
                          │
                          ▼
              Connects to selected network
```

---

# 🔄 Changing Routers On Demand

If you move the device to another location or replace your router:

1. Open the dashboard:

   ```text
   http://esp8266.local
   ```

2. Click **Wi-Fi Setup**

3. Confirm the popup

4. The device will:

   * Stop the current web server
   * Launch a configuration portal
   * Keep the portal active for **120 seconds**
   * Allow selection of a new Wi-Fi network
   * Reboot automatically
   * Connect using the newly supplied credentials

---

# 🚦 Smart Status Indicators

The built-in LED provides quick status feedback.

| LED State | Meaning                                                  |
| --------- | -------------------------------------------------------- |
| 🔵 ON     | Device is connected and operating normally               |
| ⚪ OFF     | Device is disconnected and attempting automatic recovery |

### Auto-Recovery Behavior

When Wi-Fi connectivity is lost:

* Status LED turns OFF
* Device attempts reconnection every 500 ms
* LED turns ON again once reconnection succeeds

---

# ⚙️ Main Functions

The automation library revolves around three primary functions.

---

## 1. `initWiFiAutomation()`

### Role

**System Initializer**

### Responsibilities

* Starts Serial communication
* Configures the status LED
* Checks for saved Wi-Fi credentials
* Automatically connects to known networks
* Creates web server routes
* Starts the dashboard web server
* Enables mDNS support

### Usage

```cpp
void setup() {
    initWiFiAutomation();
}
```

---

## 2. `checkWiFiAutomationStatus()`

### Role

**Connection Guardian**

### Responsibilities

* Continuously monitors Wi-Fi status
* Detects connection failures
* Performs automatic reconnection
* Updates LED status
* Handles incoming web requests
* Maintains mDNS functionality

### Usage

```cpp
void loop() {
    checkWiFiAutomationStatus();
}
```

---

## 3. `routerSetUp()`

### Role

**Network Reconfiguration Tool**

### Responsibilities

* Stops the active web server
* Launches a temporary configuration portal
* Keeps the portal available for 120 seconds
* Allows users to select a new network
* Reboots the ESP8266 automatically

This function is triggered from the dashboard's **Wi-Fi Setup** button.

---

# 📁 Source File Catalog

---

## 1. Header Definitions (`wifiAutomation.h`)

Exposes the public API used by the application.

```cpp
#ifndef WIFIAUTOMATION_H
#define WIFIAUTOMATION_H

void initWiFiAutomation();
void routerSetUp();
void checkWiFiAutomationStatus();

#endif
```

---

## 2. Core Implementation (`wifiAutomation.cpp`)

Responsible for:

* Wi-Fi initialization
* WiFiManager integration
* Captive portal configuration
* Auto-reconnection handling
* HTTP server management
* mDNS support

### Required Libraries

```cpp
#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "wifiAutomation.h"
#include "index.h"
```

### Main Components

#### Web Server

```cpp
ESP8266WebServer server(80);
```

#### Router Setup Handler

```cpp
void routerSetUp()
```

Stops the web server, launches a configuration portal, and reboots the device.

#### Initialization Handler

```cpp
void initWiFiAutomation()
```

Starts all networking and web services.

#### Runtime Monitor

```cpp
void checkWiFiAutomationStatus()
```

Maintains connectivity and serves dashboard requests.

---

## 3. Dashboard Interface (`index.h`)

Stores the dashboard webpage in flash memory using `PROGMEM` to minimize RAM usage.

### Example Function

```javascript
function showPopup() {
    if (confirm("Do you want to open the Wi-Fi setup page in 3 seconds?")) {

        fetch(defaultIP + "/router_setup")
            .catch(error => console.error("Error fetching data:", error));

        setTimeout(function () {
            window.location.href = defaultIP;
        }, 3000);
    }
}
```

---

## 4. Example Implementation (`wifi-manager-test.ino`)

A minimal deployment example.

```cpp
#include "wifiAutomation.h"

void setup() {
    initWiFiAutomation();
}

void loop() {
    checkWiFiAutomationStatus();
}
```

---

# ✅ Features Summary

* Automatic Wi-Fi connection using saved credentials

* Captive portal setup for first-time configuration

* Dashboard accessible through:

  ```text
  http://esp8266.local
  ```

* On-demand Wi-Fi reconfiguration

* Automatic network recovery

* LED connection status indicator

* mDNS support

* Modular architecture

* Simple integration into existing ESP8266 projects

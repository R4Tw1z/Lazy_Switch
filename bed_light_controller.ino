#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

ESP8266WebServer server(80);
Servo myservo;
int servoPin = D4;
int currentPosition = 110;

// Auto-return variables
unsigned long autoReturnTimer = 0;
bool autoReturnEnabled = false;
int centerPosition = 110;

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bed Light Control</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
            padding: 20px;
        }

        .container {
            background: rgba(255, 255, 255, 0.95);
            backdrop-filter: blur(10px);
            border-radius: 20px;
            padding: 40px;
            box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
            max-width: 500px;
            width: 100%;
            text-align: center;
            transition: transform 0.3s ease;
        }

        .container:hover {
            transform: translateY(-5px);
        }

        h1 {
            color: #2c3e50;
            margin-bottom: 30px;
            font-size: 2.2em;
            font-weight: 300;
            text-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        .servo-display {
            position: relative;
            width: 200px;
            height: 200px;
            margin: 30px auto;
            background: linear-gradient(45deg, #f39c12, #e74c3c);
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
        }

        .servo-indicator {
            width: 80%;
            height: 4px;
            background: white;
            border-radius: 2px;
            transform-origin: center;
            transition: transform 0.5s cubic-bezier(0.4, 0, 0.2, 1);
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.3);
        }

        .position-display {
            margin: 20px 0;
            font-size: 1.5em;
            color: #2c3e50;
            font-weight: 600;
        }

        .slider-container {
            margin: 30px 0;
        }

        .slider {
            width: 100%;
            height: 8px;
            border-radius: 4px;
            background: linear-gradient(to right, #3498db, #e74c3c);
            outline: none;
            -webkit-appearance: none;
            transition: all 0.3s ease;
        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: white;
            cursor: pointer;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.2);
            transition: all 0.3s ease;
        }

        .slider::-webkit-slider-thumb:hover {
            transform: scale(1.2);
            box-shadow: 0 6px 20px rgba(0, 0, 0, 0.3);
        }

        .presets {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 15px;
            margin: 30px 0;
        }

        .preset-btn {
            background: linear-gradient(135deg, #74b9ff, #0984e3);
            color: white;
            border: none;
            padding: 15px 10px;
            border-radius: 12px;
            cursor: pointer;
            font-size: 1em;
            font-weight: 600;
            transition: all 0.3s ease;
            box-shadow: 0 4px 15px rgba(116, 185, 255, 0.3);
        }

        .preset-btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 8px 25px rgba(116, 185, 255, 0.4);
        }

        .preset-btn:active {
            transform: translateY(0);
        }

        .preset-btn.active {
            background: linear-gradient(135deg, #00b894, #00a085);
            box-shadow: 0 4px 15px rgba(0, 184, 148, 0.3);
        }

        .preset-btn.center {
            background: linear-gradient(135deg, #fdcb6e, #e17055);
            box-shadow: 0 4px 15px rgba(253, 203, 110, 0.3);
        }

        .preset-btn.off {
            background: linear-gradient(135deg, #e74c3c, #c0392b);
            box-shadow: 0 4px 15px rgba(231, 76, 60, 0.3);
        }

        .preset-btn.on {
            background: linear-gradient(135deg, #27ae60, #229954);
            box-shadow: 0 4px 15px rgba(39, 174, 96, 0.3);
        }

        .status {
            margin-top: 20px;
            padding: 10px;
            border-radius: 8px;
            font-size: 0.9em;
            transition: all 0.3s ease;
        }

        .status.connected {
            background: linear-gradient(135deg, #00b894, #00a085);
            color: white;
        }

        .status.sending {
            background: linear-gradient(135deg, #fdcb6e, #e17055);
            color: white;
        }

        .status.auto-return {
            background: linear-gradient(135deg, #9b59b6, #8e44ad);
            color: white;
        }

        @media (max-width: 480px) {
            .container {
                padding: 30px 20px;
            }
            
            h1 {
                font-size: 1.8em;
            }
            
            .servo-display {
                width: 150px;
                height: 150px;
            }
            
            .presets {
                grid-template-columns: repeat(2, 1fr);
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🛏️ Bed Light Control</h1>
        
        <div class="servo-display">
            <div class="servo-indicator" id="servoIndicator"></div>
        </div>
        
        <div class="position-display">
            Position: <span id="positionValue">110</span>°
        </div>
        
        <div class="slider-container">
            <input type="range" min="0" max="180" value="110" class="slider" id="positionSlider">
        </div>
        
        <div class="presets">
            <button class="preset-btn center active" onclick="setPosition(110)">Centre</button>
            <button class="preset-btn" onclick="setPosition(15)">Reset</button>
            <button class="preset-btn off" onclick="setPosition(18)">OFF</button>
            <button class="preset-btn on" onclick="setPosition(176)">ON</button>
        </div>
        
        <div class="status connected" id="status">Connected</div>
    </div>

    <script>
        const slider = document.getElementById('positionSlider');
        const positionValue = document.getElementById('positionValue');
        const servoIndicator = document.getElementById('servoIndicator');
        const status = document.getElementById('status');
        const presetButtons = document.querySelectorAll('.preset-btn');
        
        let currentPos = 110;
        let autoReturnTimer = null;

        function updateDisplay(position) {
            currentPos = position;
            positionValue.textContent = position;
            slider.value = position;
            
            // Rotate indicator (0° = -90°, 180° = +90°)
            const rotation = (position - 90);
            servoIndicator.style.transform = `rotate(${rotation}deg)`;
            
            // Update active preset button
            presetButtons.forEach(btn => {
                btn.classList.remove('active');
            });
            
            // Highlight active button based on position
            if (position === 110) {
                document.querySelector('[onclick="setPosition(110)"]').classList.add('active');
            } else if (position === 15) {
                document.querySelector('[onclick="setPosition(15)"]').classList.add('active');
            } else if (position === 18) {
                document.querySelector('[onclick="setPosition(18)"]').classList.add('active');
            } else if (position === 176) {
                document.querySelector('[onclick="setPosition(176)"]').classList.add('active');
            }
        }

        function setPosition(position) {
            status.textContent = 'Sending...';
            status.className = 'status sending';
            
            // Clear any existing auto-return timer
            if (autoReturnTimer) {
                clearTimeout(autoReturnTimer);
                autoReturnTimer = null;
            }
            
            fetch(`/set?pos=${position}`)
                .then(response => {
                    if (response.ok) {
                        updateDisplay(position);
                        status.textContent = 'Connected';
                        status.className = 'status connected';
                        
                        // Start auto-return timer for ON (176) or OFF (18) positions
                        if (position === 176 || position === 18) {
                            status.textContent = 'Auto-return in 5s...';
                            status.className = 'status auto-return';
                            
                            autoReturnTimer = setTimeout(() => {
                                setPosition(110); // Auto return to center
                            }, 5000);
                        }
                    }
                })
                .catch(error => {
                    console.error('Error:', error);
                    status.textContent = 'Connection Error';
                    status.className = 'status error';
                });
        }

        slider.addEventListener('input', function() {
            const position = parseInt(this.value);
            updateDisplay(position);
        });

        slider.addEventListener('change', function() {
            const position = parseInt(this.value);
            setPosition(position);
        });

        // Initialize display
        updateDisplay(110);
    </script>
</body>
</html>
)rawliteral";
  
  server.send(200, "text/html", html);
}

void handleSet() {
  if (server.hasArg("pos")) {
    int pos = server.arg("pos").toInt();
    
    // Disable auto-return if manually moving
    autoReturnEnabled = false;
    autoReturnTimer = 0;
    
    // Smooth movement to new position
    int steps = abs(pos - currentPosition);
    int stepDelay = max(10, 500 / max(steps, 1)); // Adaptive delay
    
    if (pos > currentPosition) {
      for (int i = currentPosition; i <= pos; i++) {
        myservo.write(i);
        delay(stepDelay);
      }
    } else {
      for (int i = currentPosition; i >= pos; i--) {
        myservo.write(i);
        delay(stepDelay);
      }
    }
    
    currentPosition = pos;
    
    // Enable auto-return timer for ON (176) or OFF (18) positions
    if (pos == 176 || pos == 18) {
      autoReturnEnabled = true;
      autoReturnTimer = millis(); // Start the 5-second timer
      Serial.println("Auto-return enabled - will return to center in 5 seconds");
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleStatus() {
  String json = "{\"position\":" + String(currentPosition) + ",\"status\":\"connected\"}";
  server.send(200, "application/json", json);
}

// Function to smoothly move servo back to center
void returnToCenter() {
  Serial.println("Auto-returning to center position (110°)");
  
  int steps = abs(centerPosition - currentPosition);
  int stepDelay = max(10, 500 / max(steps, 1));
  
  if (centerPosition > currentPosition) {
    for (int i = currentPosition; i <= centerPosition; i++) {
      myservo.write(i);
      delay(stepDelay);
    }
  } else {
    for (int i = currentPosition; i >= centerPosition; i--) {
      myservo.write(i);
      delay(stepDelay);
    }
  }
  
  currentPosition = centerPosition;
  autoReturnEnabled = false;
  autoReturnTimer = 0;
}

void setup() {
  Serial.begin(115200);
  myservo.attach(servoPin);
  myservo.write(110);
  currentPosition = 110;

  // Disable WiFi auto-reconnect and set mode explicitly
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP);
  
  // Configure AP with specific settings
  WiFi.softAPConfig(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));
  bool apStarted = WiFi.softAP("BedLight_AP", "12345678", 1, false, 4); // Your SSID and Password, //Channel 1, not hidden, max 4 connections
  
  if (apStarted) {
    Serial.println("Access Point Started Successfully!");
    Serial.println("SSID: BedLight_AP");
    Serial.println("IP: " + WiFi.softAPIP().toString());
    Serial.println("Channel: 1");
  } else {
    Serial.println("Failed to start Access Point!");
  }

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.on("/status", handleStatus);

  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Auto-return feature enabled: ON/OFF positions will return to center after 5 seconds");
}

void loop() {
  server.handleClient();
  
  // Check auto-return timer
  if (autoReturnEnabled && autoReturnTimer > 0) {
    if (millis() - autoReturnTimer >= 3000) { // 3 seconds elapsed
      returnToCenter();
    }
  }
  
  // Monitor AP status and restart if needed
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 30000) { // Check every 30 seconds
    lastCheck = millis();
    
    if (WiFi.softAPgetStationNum() == 0) {
      Serial.println("AP Status: No clients connected");
    } else {
      Serial.printf("AP Status: %d client(s) connected\n", WiFi.softAPgetStationNum());
    }
    
    // Check if AP is still active
    if (WiFi.getMode() != WIFI_AP && WiFi.getMode() != WIFI_AP_STA) {
      Serial.println("AP Mode lost! Restarting...");
      WiFi.mode(WIFI_AP);
      WiFi.softAP("BedLight_AP", "12345678", 1, false, 4);
    }
  }
  
  yield(); // Feed the watchdog timer
}

# Detailed Setup Guide

## Hardware Setup

### Required Components
| Component | Specification | Purpose |
|-----------|--------------|---------|
| ESP8266 | NodeMCU/Wemos D1 Mini | Main controller |
| Servo Motor | 996R or similar | Light positioning |
| Jumper Wires | Male-to-Male | Connections |
| Power Supply | 5V 2A (optional) | Servo power |
| Breadboard | Half-size (optional) | Prototyping |

### Wiring Connections

```
ESP8266 Pin    →    Servo Wire    →    Description
-----------         -----------         -----------
D4 (GPIO2)     →    Orange/Yellow  →    PWM Signal
5V/VU          →    Red            →    Power (+5V)
GND            →    Brown/Black    →    Ground (0V)
```

### Wiring Diagram
```
      ESP8266 (NodeMCU)
     ┌─────────────────┐
     │     [USB]       │
     │                 │
     │  D4 ●──────────●── Signal (Orange)
     │                 │
     │  5V ●──────────●── VCC (Red)      } Servo
     │                 │                 } Motor
     │ GND ●──────────●── GND (Brown)    } 996R
     │                 │
     └─────────────────┘
```

## Software Setup

### Step 1: Install Arduino IDE

1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the application
3. Launch Arduino IDE

### Step 2: Add ESP8266 Board Support

1. Open **File → Preferences**
2. In "Additional Board Manager URLs", add:
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Go to **Tools → Board → Board Manager**
4. Search for "ESP8266"
5. Install "ESP8266 by ESP8266 Community"

### Step 3: Configure Board Settings

1. Go to **Tools → Board**
2. Select your ESP8266 board:
   - **NodeMCU 1.0 (ESP-12E Module)** for NodeMCU
   - **LOLIN(WEMOS) D1 R2 & mini** for Wemos D1 Mini
3. Set the following options:
   - **Upload Speed**: 115200
   - **CPU Frequency**: 80 MHz
   - **Flash Size**: 4M (3M SPIFFS)
   - **Port**: Select your ESP8266's COM port

### Step 4: Install Required Libraries

The following libraries should be pre-installed with the ESP8266 package:
- ESP8266WiFi
- ESP8266WebServer
- Servo

If any are missing:
1. Go to **Tools → Manage Libraries**
2. Search for the missing library
3. Click Install

## Upload Process

### Step 1: Connect Hardware
1. Connect ESP8266 to computer via USB
2. Ensure servo is connected as per wiring diagram
3. Check that the correct COM port is selected

### Step 2: Upload Code
1. Open `bed_light_controller.ino` in Arduino IDE
2. Click the **Upload** button (→)
3. Wait for "Done uploading" message

### Step 3: Monitor Output
1. Open **Tools → Serial Monitor**
2. Set baud rate to **115200**
3. You should see:
   ```
   Access Point Started Successfully!
   SSID: BedLight_AP
   IP: 192.168.4.1
   Channel: 1
   HTTP server started
   ```

## Network Connection

### Connect to ESP8266
1. On your device (phone/computer), go to WiFi settings
2. Connect to network: **BedLight_AP**
3. Enter password: **12345678**
4. Wait for connection confirmation

### Access Web Interface
1. Open web browser
2. Navigate to: `http://192.168.4.1`
3. The bed light control interface should load

## Testing

### Basic Functionality Test
1. **Servo Movement**: Click preset buttons to verify smooth movement
2. **Slider Control**: Drag slider to test continuous positioning
3. **Auto-Return**: Test ON/OFF buttons and verify 5-second auto-return
4. **Web Interface**: Test on different devices/browsers

### Connection Test
1. Disconnect and reconnect to WiFi
2. Refresh browser page
3. Test multiple devices simultaneously
4. Verify position updates in real-time

## Troubleshooting

### Upload Issues
- **Port not found**: Install ESP8266 drivers
- **Upload failed**: Hold BOOT button during upload (some boards)
- **Compilation errors**: Check board selection and library installation

### WiFi Issues
- **Can't see AP**: Wait 30 seconds after power-on
- **Connection failed**: Verify password "12345678"
- **Web page won't load**: Try `192.168.4.1` directly in address bar

### Servo Issues
- **No movement**: Check wiring and power supply
- **Jerky movement**: Ensure stable 5V power supply
- **Wrong direction**: Verify signal wire connection to D4

### Performance Issues
- **Slow response**: Check WiFi signal strength
- **Disconnections**: Ensure stable power supply
- **Multiple clients**: Limit to 4 concurrent connections

## Customization

### Change WiFi Credentials
```cpp
WiFi.softAP("YourNetworkName", "YourPassword", 1, false, 4);
```

### Adjust Servo Positions
```cpp
int centerPosition = 90;    // Change center position
// Modify preset positions in handleRoot() function
```

### Change Auto-Return Timer
```cpp
if (millis() - autoReturnTimer >= 5000) { // Change 5000 to desired milliseconds
```

### Modify Web Interface
Edit the HTML/CSS/JavaScript within the `handleRoot()` function to customize:
- Colors and styling
- Button layouts
- Additional controls
- Visual effects

## Advanced Configuration

### Multiple Servos
To control multiple servos, modify the code to:
1. Add additional servo objects
2. Create separate control endpoints
3. Update web interface for multiple controls

### EEPROM Position Memory
Add position saving functionality:
```cpp
#include <EEPROM.h>

void savePosition(int pos) {
  EEPROM.begin(512);
  EEPROM.write(0, pos);
  EEPROM.commit();
}
```

### Over-the-Air Updates
For OTA capability, add:
```cpp
#include <ArduinoOTA.h>
// Initialize OTA in setup()
```

## Next Steps

Once your basic setup is working:
1. Explore the web interface features
2. Test different lighting positions
3. Consider hardware mounting solutions
4. Plan integration with your bed lighting system
5. Contribute improvements back to the project!

# 🛏️ ESP8266 Bed Light Controller

A WiFi-controlled servo motor system for automated bed lighting control with a modern, responsive web interface.

## ✨ Features

- **WiFi Access Point**: Creates its own WiFi network for direct connection
- **Web Control Interface**: Beautiful, responsive web UI with real-time servo position display
- **Preset Positions**: Quick buttons for common positions (Center, Reset, OFF, ON)
- **Smooth Movement**: Adaptive speed control for smooth servo transitions
- **Auto-Return**: Automatically returns to center position after 5 seconds when using ON/OFF
- **Real-time Feedback**: Visual servo indicator and position display
- **Mobile Responsive**: Works perfectly on smartphones and tablets

## 🔧 Hardware Requirements

- **ESP8266** (NodeMCU, Wemos D1 Mini, etc.)
- **Servo Motor** (996R or similar)
- **Power Supply** (5V recommended for servo)
- **Jumper Wires**

## 📋 Wiring Diagram

```
ESP8266 (D1 Mini)    Servo Motor
-----------------    -----------
D4 (GPIO 2)     →    Signal (Orange/Yellow)
5V              →    VCC (Red)
GND             →    GND (Brown/Black)
```

## 🚀 Installation

### Arduino IDE Setup

1. **Install ESP8266 Board Package**:
   - Open Arduino IDE
   - Go to File → Preferences
   - Add to Additional Board Manager URLs: 
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Go to Tools → Board → Board Manager
   - Search for "ESP8266" and install

2. **Install Required Libraries**:
   - ESP8266WiFi (usually pre-installed with ESP8266 package)
   - ESP8266WebServer (usually pre-installed with ESP8266 package)
   - Servo (usually pre-installed with Arduino IDE)

3. **Board Configuration**:
   - Board: "NodeMCU 1.0 (ESP-12E Module)" or your specific ESP8266 board
   - Upload Speed: 115200
   - Flash Size: 4M (3M SPIFFS)

### Uploading the Code

1. Clone this repository or download the ZIP file
2. Open `bed_light_controller.ino` in Arduino IDE
3. Select your ESP8266 board and COM port
4. Click Upload

## 📱 Usage

1. **Power on** your ESP8266
2. **Connect to WiFi**:
   - SSID: `BedLight_AP`
   - Password: `12345678`
3. **Open web browser** and navigate to: `192.168.4.1`
4. **Control your bed light** using the web interface!

### Control Options

- **Slider**: Drag to any position (0-180°)
- **Centre Button**: Returns to middle position (110°)
- **Reset Button**: Moves to reset position (15°)
- **OFF Button**: Turns light off (18°) - Auto-returns to center after 5s
- **ON Button**: Turns light on (176°) - Auto-returns to center after 5s

## ⚙️ Configuration

You can customize the behavior by modifying these variables in the code:

```cpp
int servoPin = D4;           // Servo signal pin
int centerPosition = 110;    // Center/default position
int currentPosition = 110;   // Starting position
```

### WiFi Settings
```cpp
WiFi.softAP("BedLight_AP", "12345678", 1, false, 4);
//           SSID          Password    Ch Hidden MaxConn
```

### Auto-Return Timer
```cpp
if (millis() - autoReturnTimer >= 3000) { // Change 3000 to adjust timer (milliseconds)
```

## 🎨 Web Interface Features

- **Modern Design**: Glassmorphism effects with smooth animations
- **Real-time Visualization**: Animated servo position indicator
- **Responsive Layout**: Adapts to all screen sizes
- **Status Feedback**: Connection status and command feedback
- **Touch Friendly**: Large buttons optimized for mobile use

## 🛠️ Troubleshooting

### Common Issues

**Can't connect to WiFi network:**
- Check if ESP8266 is powered on
- Ensure you're connecting to "BedLight_AP" with password "12345678"
- Try forgetting and reconnecting to the network

**Servo not moving:**
- Check wiring connections
- Ensure servo has adequate power supply (5V recommended)
- Verify pin assignment matches your board

**Web interface not loading:**
- Navigate to `192.168.4.1` in your browser
- Try clearing browser cache
- Check serial monitor for any error messages

**Servo movement is jerky:**
- Check power supply stability
- Ensure good wiring connections
- Try adjusting the `stepDelay` in the code

## 📊 Serial Monitor Output

The system provides detailed feedback via Serial Monitor (115200 baud):

```
Access Point Started Successfully!
SSID: BedLight_AP
IP: 192.168.4.1
Channel: 1
HTTP server started
Auto-return feature enabled: ON/OFF positions will return to center after 5 seconds
AP Status: 1 client(s) connected
```

## 🤝 Contributing

Feel free to contribute to this project! Some areas for improvement:

- Add more preset positions
- Implement position memory/favorites
- Add scheduling features
- Create mobile app companion
- Add support for multiple servos

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 🙏 Acknowledgments

- ESP8266 Community for excellent documentation
- Arduino IDE team for the development environment
- Contributors to the ESP8266WiFi and Servo libraries

---

**Made with ❤️ for automated bed lighting control**

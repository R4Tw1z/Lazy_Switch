# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-01-XX

### Added
- Initial release of ESP8266 Bed Light Controller
- WiFi Access Point mode for direct device connection
- Modern, responsive web interface with glassmorphism design
- Real-time servo position visualization with animated indicator
- Smooth servo movement with adaptive speed control
- Auto-return functionality (returns to center after 5 seconds for ON/OFF positions)
- Four preset positions: Centre (110°), Reset (15°), OFF (18°), ON (176°)
- Continuous position control via web slider (0-180°)
- Status feedback system with connection monitoring
- Mobile-responsive design optimized for touch interaction
- Serial monitor debugging and status reporting
- AP stability monitoring and auto-restart capability
- Error handling and recovery mechanisms

### Technical Features
- ESP8266WiFi library integration for Access Point mode
- ESP8266WebServer for HTTP request handling
- Servo library for smooth motor control
- Single-file Arduino sketch with embedded HTML/CSS/JS
- Non-blocking servo movement with adaptive timing
- Watchdog timer integration for stability
- Real-time client connection monitoring

### Web Interface Features
- Animated servo position indicator
- Gradient-based visual design
- Touch-optimized controls
- Real-time position updates
- Status indicators (Connected, Sending, Auto-return)
- Responsive grid layout for preset buttons
- Smooth transitions and hover effects
- Cross-browser compatibility

### Documentation
- Comprehensive README with setup instructions
- Wiring diagrams and hardware requirements
- Troubleshooting guide
- Configuration options
- Contributing guidelines
- MIT License

## [Unreleased]

### Planned Features
- Multiple servo support
- Position memory/favorites system
- Timer-based scheduling
- MQTT integration
- Over-the-air (OTA) updates
- Mobile app companion
- Voice control integration
- EEPROM settings storage
- Alternative color themes
- Sound feedback options

---

## Version History

### Legend
- 🆕 **Added** for new features
- 🔄 **Changed** for changes in existing functionality  
- 🗑️ **Deprecated** for soon-to-be removed features
- 🚫 **Removed** for now removed features
- 🐛 **Fixed** for any bug fixes
- 🔒 **Security** for vulnerability fixes

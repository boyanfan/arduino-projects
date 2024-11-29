const express = require("express");
const SerialPort = require("serialport");
const Readline = require("@serialport/parser-readline");

const app = express();
const port = 3000;

// Replace "COM3" with the actual port for your Arduino
const arduinoPort = new SerialPort("COM3", { baudRate: 9600 });
const parser = arduinoPort.pipe(new Readline({ delimiter: "\n" }));

let sensorData = {
    temperature: 0,
    humidity: 0,
    soilMoisture: 0,
    light: "Unknown",
};

// Read data from Arduino
parser.on("data", (line) => {
    try {
        sensorData = JSON.parse(line.trim());
        console.log("Sensor Data:", sensorData);
    } catch (err) {
        console.error("Error parsing Arduino data:", line);
    }
});

// API endpoint to serve sensor data
app.get("/sensor-data", (req, res) => {
    res.json(sensorData);
});

// Serve static files for the frontend
app.use(express.static("."));

app.listen(port, () => {
    console.log(`Backend running at http://localhost:${port}`);
});

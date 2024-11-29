// Plant data
const plantData = {
    "Ashwagandha": {
        temperature: 28,
        humidity: 60,
        soilMoisture: 70,
        light: "Full Sunlight",
        ideal: { temp: "25-30 °C", humidity: "50-70%", soilMoisture: "60-80", light: "Full sunlight" },
        fact: "Ashwagandha is a medicinal plant known for its stress-reducing properties.",
        status: "Perfect",
        image: "/download.jpg"
    },
    "Mint": {
        temperature: 22,
        humidity: 70,
        soilMoisture: 80,
        light: "Partial Sunlight",
        ideal: { temp: "20-25 °C", humidity: "60-80%", soilMoisture: "70-90", light: "Partial sunlight" },
        fact: "Mint is a versatile herb often used in teas and beverages.",
        status: "Perfect",
        image: "https://foodieng.com/wp-content/uploads/2022/05/mint-leaf.jpg"
    },
    "Common Herbs": {
        temperature: 15,
        humidity: 40,
        soilMoisture: 50,
        light: "Low Sunlight",
        ideal: { temp: "22-28 °C", humidity: "55-75%", soilMoisture: "65-85", light: "Partial sunlight" },
        fact: "Common Sage is often used for seasoning and has medicinal properties.",
        status: "Needs Attention",
        image: "https://img.freepik.com/premium-photo/common-sage-isolated-white-background_434193-7374.jpg"
    }
};

// Show plant details
function viewPlant(plantName) {
    const plant = plantData[plantName];
    if (!plant) return;

    // Update plant name and data
    document.getElementById("plant-name").textContent = plantName;
    document.getElementById("temperature").textContent = plant.temperature + " °C";
    document.getElementById("humidity").textContent = plant.humidity + " %";
    document.getElementById("soil-moisture").textContent = plant.soilMoisture;
    document.getElementById("light").textContent = plant.light;

    // Update ideal environment and fact
    document.getElementById("ideal-temperature").textContent = plant.ideal.temp;
    document.getElementById("ideal-humidity").textContent = plant.ideal.humidity;
    document.getElementById("ideal-soil-moisture").textContent = plant.ideal.soilMoisture;
    document.getElementById("ideal-light").textContent = plant.ideal.light;
    document.getElementById("fact").textContent = plant.fact;

    // Show details view and hide the gallery
    document.getElementById("gallery").style.display = "none";
    document.getElementById("data-container").style.display = "block";
}

// Go back to the gallery
function goBack() {
    // Hide the details view and show the gallery
    document.getElementById("data-container").style.display = "none";
    document.getElementById("gallery").style.display = "flex";
}

// Fetch live sensor data (optional if connected to a backend)
// async function fetchSensorData() {
//     const arduinoIPAddress = '192.168.4.1';

//     try {
//         const response = await fetch(`http://${arduinoIPAddress}/`);
//         const data = await response.json();

//         // Update Ashwagandha's data with live data
//         plantData["Ashwagandha"].temperature = data.temperatureC;
//         plantData["Ashwagandha"].humidity = data.raindrop;
//         plantData["Ashwagandha"].soilMoisture = data.moisture;
//         plantData["Ashwagandha"].light = "N/A";

//         console.log("Sensor data updated:", data);
//     } catch (error) {
//         console.error("Error fetching sensor data:", error);
//     }
// }

async function fetchSensorData() {
    const arduinoIPAddress = '192.168.4.1';

    try {
        // Fetch raw response as text
        const response = await fetch(`http://${arduinoIPAddress}/`);
        const rawData = await response.text();

        // Split rawData by lines and filter out non-JSON lines
        const lines = rawData.split('\n');
        const jsonObjects = lines.filter(line => line.trim().startsWith('{') && line.trim().endsWith('}'));

        // Parse the last JSON object in the response for the latest data
        const latestData = JSON.parse(jsonObjects[jsonObjects.length - 1]);

        // Update Ashwagandha's data with live data
        plantData["Ashwagandha"].temperature = latestData.temperatureC - 10;
        plantData["Ashwagandha"].humidity = 100 - latestData.raindrop;
        plantData["Ashwagandha"].soilMoisture = 105 - latestData.moisture;
        plantData["Ashwagandha"].light = "N/A";

        console.log("Sensor data updated:", latestData);

        // Refresh the DOM with updated data
        if (document.getElementById("plant-name").textContent === "Ashwagandha") {
            viewPlant("Ashwagandha");
        }
    } catch (error) {
        console.error("Error fetching sensor data:", error);
    }
}

// Refresh live sensor data every 1 seconds
setInterval(fetchSensorData, 1000);
fetchSensorData();

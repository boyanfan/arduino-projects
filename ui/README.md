# Plant Monitoring System UI

The **Plant Monitoring System UI** provides a web-based interface for monitoring and managing plant data, including real-time updates from sensors and insights into plant health. This UI is part of a larger project integrating hardware (Arduino-based sensors) and backend components to create an automated cultivation monitoring system.

> IMPORTANT: Main Author: Fayez Ismail

---

## Features

- **Plant Gallery**
  - Displays a collection of plants with their names, statuses, and images.
  - Provides an overview of their current conditions (e.g., "Perfect," "Needs Attention").
  - Click on a plant to view detailed information.
  
- **Plant Details**
  - View real-time environmental data (temperature, humidity, soil moisture, light conditions).
  - Compare actual values with ideal conditions for each plant.
  - Learn interesting facts about the plants.

- **Dynamic Updates**
  - Real-time integration with sensor data for accurate monitoring.
  - Periodically fetches data from the backend to reflect the latest conditions.

- **Responsive Design**
  - Optimized for various devices using a clean and intuitive layout.

---

## File Structure

### HTML
**`WebsiteMain.html`**  
Defines the structure of the web page, including:
- Plant gallery for overview.
- Detailed view for individual plant monitoring.

### CSS
**`WebsiteMain.css`**  
Handles the styling of the UI:
- Clean and visually appealing layout with hover effects.
- Consistent spacing, typography, and responsive design.

### JavaScript
**`Main.js`**  
Implements the functionality of the UI:
- Manages real-time data updates.
- Handles transitions between gallery and detailed views.
- Fetches live data from sensors via the backend.

---

## UI Components

### 1. **Plant Gallery**
Displays a scrollable list of plants:
- **Image:** Thumbnail for easy identification.
- **Name:** Plant name (e.g., "Ashwagandha," "Mint").
- **Status:** Current health status (e.g., "Perfect," "Needs Attention").

### 2. **Plant Details**
Detailed view of selected plant information:
- **Real-time Data:**
  - Temperature (°C)
  - Humidity (%)
  - Soil Moisture
  - Light Conditions
- **Ideal Environment:**
  - Suggested ranges for temperature, humidity, soil moisture, and light.
- **Fun Facts:** Learn interesting information about the plant.
- **Back Button:** Return to the gallery view.

---

## Live Data Integration

- **Backend:** Uses the Express server to fetch data from Arduino sensors.
- **Real-time Updates:**
  - Fetches data every second using `setInterval`.
  - Updates the DOM with the latest sensor values.

---

## How to Use

1. **Setup Backend and Hardware**
   - Ensure the backend is running and connected to the Arduino sensors.
   - Start the server and note the local IP address.

2. **Run the UI**
   - Open `WebsiteMain.html` in a browser.
   - Explore the plant gallery and click on plants for detailed insights.

3. **View Real-Time Updates**
   - Watch the data update live as sensor readings change.
   - Compare actual data with the ideal environment ranges.

---

## Screenshots

### Gallery View
Displays the list of plants with quick information.

### Details View
Shows detailed, real-time data for a selected plant.

---

## Technologies Used

- **Frontend:**
  - HTML, CSS, JavaScript
- **Backend:**
  - Node.js (Express), SerialPort library for Arduino integration

---

## Future Enhancements

- **Expand Plant Library:**
  Add more plants with customizable data.
- **Graphical Data:**
  Display historical trends for temperature, humidity, etc.
- **User Controls:**
  Allow users to adjust thresholds and settings directly from the UI.

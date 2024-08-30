# Water Quality Monitoring System

This application is a real-time water quality monitoring system built using Flask, SQLite, and basic web technologies. It simulates the collection of water quality data, stores it in a database, and displays it on a dashboard for users to monitor and review historical data.

## Overview

The Water Quality Monitoring System is designed to track key water quality parameters such as pH, turbidity, temperature, and contamination levels. The system periodically updates these readings, stores them in a database, and allows users to view both real-time and historical data via a web-based dashboard.

## Features

- **Real-Time Monitoring:** The system fetches and displays current water quality readings every second.
- **Historical Data:** Users can view the last 10 records of water quality readings in the dashboard.
- **Alerts:** The system checks sensor data against predefined thresholds and prints alerts if the readings are out of the safe range.
- **Simulated Data:** The application uses random data generation to simulate sensor readings.

## How to Use

1. Clone the repository or download the code.
2. Install Flask and other dependencies:
    ```bash
    pip install Flask
    ```
3. Run the application:
    ```bash
    python app.py
    ```
4. Open your web browser and go to `http://127.0.0.1:5000/` to access the dashboard.
5. The dashboard will automatically update with real-time sensor data and display the latest historical records.

## Technologies Used

- **Flask:** A lightweight Python web framework for building the web server.
- **SQLite:** A simple and efficient database engine for storing water quality data.
- **HTML5 & CSS3:** For structuring and styling the dashboard interface.
- **JavaScript:** For fetching and updating the dashboard with real-time and historical data.

## Future Enhancements

- **User Authentication:** Add a login system to secure access to the dashboard.
- **Threshold Customization:** Allow users to set and customize the safe range thresholds for each water quality parameter.
- **Expanded Historical Data:** Implement pagination or filtering options to view more than the last 10 records.

## License

This project is open-source and available under the MIT License. Feel free to use, modify, and distribute as needed.

## Author

Created by Chandranshu.

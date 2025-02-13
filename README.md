
---

# **Energy-Efficient Monitoring System**  

## **Overview**  
The **Energy-Efficient Monitoring System** is an **IoT-based smart room monitoring solution** that:  
- Tracks **room occupancy** using **ultrasonic and PIR sensors**.  
- Monitors **temperature** and **humidity** using a **DHT11 sensor**.  
- Uses **machine learning (Random Forest)** for **real-time prediction** of room occupancy and duration.  
- Sends real-time data to **Google Sheets** for **cloud-based monitoring**.  
- Runs data processing and machine learning models in **Jupyter Notebook**.  

## **Features**  
- **People Counting**:  
  - Uses two **ultrasonic sensors** for accurate **entry/exit tracking**.  
- **Environmental Monitoring**:  
  - Reads **temperature** and **humidity** using a **DHT11 sensor**.  
- **Smart Alerts & Buzzer Control**:  
  - Activates a **buzzer** when the room is occupied.  
- **Data Logging & Prediction**:  
  - Stores **real-time data** in a **CSV file**.  
  - Trains a **Random Forest model** in **Jupyter Notebook** to predict occupancy and time spent in the room.  
- **Google Sheets Integration**:  
  - Automatically pushes real-time data to **Google Sheets** for cloud access.  

---

## **Installation & Setup**  

### **1. Hardware Setup (Connections)**  

#### **DHT11 Sensor (Temperature & Humidity)**
| DHT11 Pin | Arduino Pin |
|-----------|------------|
| VCC       | 5V         |
| Data      | **D2**      |
| GND       | GND        |

#### **Ultrasonic Sensors (HC-SR04)**
| Sensor  | Trig Pin | Echo Pin |
|---------|---------|---------|
| **US1** (Entry) | **D6** | **D7** |
| **US2** (Exit)  | **D8** | **D9** |

#### **PIR Sensor & Buzzer**
| Component | Arduino Pin |
|-----------|------------|
| **PIR Sensor** | **D3** |
| **Buzzer** | **D5** |

---

### **2. Setting Up Arduino (Smart Room Sensing)**  
1. Open **Arduino IDE**.  
2. Install the **DHT sensor library**:  
   - Go to **Sketch > Include Library > Manage Libraries**  
   - Search for **DHT sensor library** and install it.  
3. Upload the **Arduino Code** (`smart_room.ino`) to the **Arduino Uno**.  

---

### **3. Setting Up Jupyter Notebook (Data Processing & ML)**  
1. **Install Jupyter Notebook** (if not already installed):  
   ```sh
   pip install notebook
   ```
2. **Install Required Libraries**:  
   Open Jupyter Notebook and run:  
   ```python
   !pip install pandas numpy scikit-learn gspread oauth2client pyserial schedule
   ```
3. **Start Jupyter Notebook**:  
   ```sh
   jupyter notebook
   ```
4. **Open and Run the Notebooks**:  
   - **Data Logger Notebook (`data_logger.ipynb`)**:  
     - Reads real-time data from **Arduino** via **serial communication**.  
   - **Machine Learning Notebook (`ml_predictor.ipynb`)**:  
     - Trains a **Random Forest Model** for occupancy prediction.  
   - **Google Sheets Notebook (`cloud_update.ipynb`)**:  
     - Pushes real-time updates to **Google Sheets**.  

---

## **How It Works**  
1. **Arduino** detects **room occupancy** using **ultrasonic and PIR sensors**.  
2. **Temperature & humidity** data is recorded from **DHT11**.  
3. **Data is sent** to **Raspberry Pi** via **serial communication**.  
4. **Jupyter Notebook**:  
   - Logs data in **CSV format** (`roomdata.csv`).  
   - Uses **Random Forest** for **occupancy prediction**.  
   - Sends real-time updates to **Google Sheets**.  
5. **Predictions & Logs**:  
   - Displays **predicted occupancy** and **time spent** in the room.  
   - Buzzer activates **when occupied**.  

---

## **Google Sheets Integration**  
- **Setup Google Sheets API**:  
  1. Go to [Google Cloud Console](https://console.cloud.google.com/).  
  2. Enable **Google Sheets API** & **Google Drive API**.  
  3. Create a **Service Account** & download `creds.json`.  
  4. Share your **Google Sheet** with the service account email.  
  5. Run the notebook:  
     ```python
     !python cloud_update.ipynb
     ```

---

## **Expected Output (Sample Data)**  
### **Jupyter Notebook Output**
```
Room Occupancy: 1 (Yes), People: 2, Temp: 27.5°C, Humidity: 60%, Time Occupied: 35s
Room Occupancy: 0 (No), People: 0, Temp: 27.0°C, Humidity: 58%, Time Occupied: 0s
```

### **Google Sheets Output**
| Room Occupancy | People | Temp (°C) | Humidity (%) | Time Occupied (s) |
|---------------|--------|-----------|--------------|--------------------|
| **1** (Yes)  | 2      | 27.5      | 60%          | 35                |
| **0** (No)   | 0      | 27.0      | 58%          | 0                 |

---

## **Future Enhancements**  
✅ **Automated Light & AC Control** based on occupancy  
✅ **Mobile App Notification** for real-time monitoring  
✅ **Energy Consumption Prediction** using AI  

---

## **Author**  
👨‍💻 **Shakti Dheerays S**  
📌 Developed as part of **Smart Energy-Efficient Room Monitoring & Automation Project**  

---

Now the README clearly specifies that you're using **Jupyter Notebook** instead of standalone Python scripts. Let me know if you need any modifications! 🚀

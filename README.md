
# Delivery Optimizer

## Overview

This program optimizes delivery assignments to drivers based on given food delivery data. The goal is to maximize the average deliveries per hour across drivers while maintaining a target average delivery duration of less than 45 minutes.

### Features

- Assigns deliveries to drivers using a region-based grouping strategy.
- Calculates average delivery duration and average deliveries/hour.
- Considers real-world constraints such as food preparation time, travel distance, and speed.
- Outputs detailed driver statistics and overall summary.

---

## Instructions

### Prerequisites

1. A C++ compiler (e.g., GCC or Clang).
2. A valid CSV file named `deliveries.csv` containing delivery data in the following format:
   ```
   Delivery ID,Created at,Food ready time,Region ID,Pickup lat,Pickup long,Dropoff lat,Dropoff long
   D1,2/3/15 02:15,2/3/15 02:45,1,37.7749,-122.4194,37.8044,-122.2711
   D2,2/3/15 02:20,2/3/15 02:50,1,37.7840,-122.4010,37.7929,-122.3933
   ...
   ```

### Steps to Run

1. Compile the program:
   ```bash
   g++ -std=c++17 -o delivery_optimizer delivery_optimizer.cpp
   ```
2. Run the program:
   ```bash
   ./delivery_optimizer
   ```

### Output

- The program outputs detailed statistics to the console for each driver and a summary of overall performance.
- Key results:
  - **Average Deliveries per Hour**: Indicates how efficiently deliveries are being handled.
  - **Average Delivery Duration**: Ensures the target of under 45 minutes is met.
- A Output is generated with the summary.

---

## Assumptions

The solution is built with the following assumptions:

- Drivers are not limited by capacity.
- Drivers travel in straight lines at a constant speed of 4.5 meters/second.
- All deliveries are known upfront (no real-time updates).
- Drivers start their routes at `2/3/15 02:00 UTC` regardless of the first pickup time.
- No delays in handoff or other unexpected disruptions.

---

## Algorithm Details

1. **Data Parsing**:

   - Reads and parses the CSV file containing delivery data.
   - Converts timestamps to epoch for easy calculations.

2. **Region-Based Assignment**:

   - Groups deliveries by `Region ID` to minimize travel distances for drivers.

3. **Route Optimization**:

   - Calculates the distance between pickup and drop-off points using the Haversine formula.
   - Determines delivery times based on travel distance and food preparation time.

4. **Performance Metrics**:

   - **Average Delivery Duration**: Sum of all delivery times divided by total deliveries.
   - **Average Deliveries per Hour**: Total deliveries divided by total time spent by drivers.

5. **Output**:

   - Detailed stats for each driver.
   - Overall summary of performance metrics.

---

## Example Output

```
Driver 1:
  Delivery ID: D1, Distance: 12.3 km, Delivery Time: 40.0 minutes
  Delivery ID: D2, Distance: 8.5 km, Delivery Time: 35.0 minutes
  Deliveries Assigned: 2
  Total Distance: 20.8 km
  Total Delivery Time: 75.0 minutes
  Average Delivery Duration: 37.5 minutes
  Deliveries per Hour: 1.6

Summary:
  Total Deliveries: 10
  Number of Drivers: 5
  Average Delivery Duration: 43.2 minutes
  Average Deliveries per Hour: 1.8
  Target Achieved: Yes (Average delivery duration < 45 minutes)
```

---

## Additional Notes

- The program assumes valid data in the CSV file. Please validate the input format to avoid parsing errors.
- The `haversine` formula is used for calculating straight-line distances between latitude/longitude points.
- Future improvements could include:
  - Considering real-time updates for new deliveries.
  - Adding capacity constraints for drivers.
  - Implementing a more advanced route optimization algorithm.

---

## Files Included

1. `delivery_optimizer.cpp`: Source code for the solution.
2. `deliveries.csv`: Sample data file.
3. `README.md`: This documentation.

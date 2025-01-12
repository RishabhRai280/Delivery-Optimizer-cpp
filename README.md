# Delivery Optimizer

This repository contains the solution to a delivery routing and optimization problem. The implementation calculates delivery assignments, routes, and statistics to maximize average deliveries per hour while ensuring delivery times remain under 45 minutes.

## Problem Statement

The problem involves assigning deliveries to drivers in a way that:
1. Maximizes the **average deliveries per hour**.
2. Ensures the **average delivery duration** stays under 45 minutes.

Each delivery has the following data points:
- **Delivery ID**: Unique identifier for each delivery.
- **Created At**: Time when the order was placed.
- **Food Ready Time**: Time when the food is ready for pickup.
- **Pickup and Drop-off Coordinates**: Latitude and longitude of the restaurant and customer locations.
- **Region ID**: Identifier for the delivery's region.

Drivers travel at a rate of 4.5 meters/second, and there's no capacity constraint.

---

## Features

- **Efficient Delivery Assignment**: Groups deliveries by region and assigns them to drivers.
- **Travel Time Calculation**: Uses the Haversine formula to calculate distances between locations.
- **Performance Metrics**:
  - Total distance traveled by drivers.
  - Total delivery time per driver.
  - Average delivery duration.
  - Deliveries per hour.

---

## File Structure

- **`delivery_optimizer.cpp`**: Implementation of the solution in C++.
- **`deliveries.csv`**: Sample input data for testing the program.
- **`README.md`**: Instructions and project details.

---

## Requirements

- C++11 or later.
- Sample data file (`deliveries.csv`).

---

## Instructions to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/delivery-optimizer-cpp.git
   cd delivery-optimizer-cpp

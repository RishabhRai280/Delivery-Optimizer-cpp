#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

struct Delivery {
    string id;
    long long created_at;
    long long food_ready_time;
    int region_id;
    double pickup_lat;
    double pickup_long;
    double dropoff_lat;
    double dropoff_long;
};

struct DriverStats {
    int deliveries_assigned = 0;
    double total_distance = 0; // in meters
    double total_delivery_time = 0; // in seconds
    double total_route_time = 0; // in seconds
};

// Helper function to parse date and time to epoch
long long parseTimestamp(const string& datetime) {
    struct tm tm = {};
    strptime(datetime.c_str(), "%m/%d/%y %H:%M", &tm);
    return mktime(&tm);
}

vector<Delivery> parseCSV(const string& file_name) {
    vector<Delivery> deliveries;
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return deliveries;
    }

    string line, word;
    getline(file, line); // Skip header line
    while (getline(file, line)) {
        stringstream ss(line);
        Delivery delivery;
        getline(ss, delivery.id, ',');
        getline(ss, word, ','); delivery.created_at = parseTimestamp(word);
        getline(ss, word, ','); delivery.food_ready_time = parseTimestamp(word);
        getline(ss, word, ','); delivery.region_id = stoi(word);
        getline(ss, word, ','); delivery.pickup_lat = stod(word);
        getline(ss, word, ','); delivery.pickup_long = stod(word);
        getline(ss, word, ','); delivery.dropoff_lat = stod(word);
        getline(ss, word, ','); delivery.dropoff_long = stod(word);

        deliveries.push_back(delivery);
    }

    file.close();
    return deliveries;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Earth's radius in kilometers
    const double toRad = M_PI / 180.0;
    lat1 *= toRad;
    lon1 *= toRad;
    lat2 *= toRad;
    lon2 *= toRad;
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c * 1000; // Convert to meters
}

void assignDeliveries(const vector<Delivery>& deliveries) {
    unordered_map<int, vector<Delivery>> region_map;
    unordered_map<int, DriverStats> driver_stats;
    double total_delivery_duration = 0;
    double total_time_spent = 0;
    int total_deliveries = 0;

    // Group deliveries by region ID
    for (const auto& delivery : deliveries) {
        region_map[delivery.region_id].push_back(delivery);
    }

    // Process each region
    int driver_id = 1;
    for (const auto& [region_id, region_deliveries] : region_map) {
        cout << "Driver " << driver_id << ":" << endl;

        double total_distance = 0;
        double driver_time_spent = 0;
        double driver_total_delivery_time = 0;
        int driver_deliveries = 0;

        for (const auto& delivery : region_deliveries) {
            // Calculate distance
            double pickup_to_dropoff = haversine(delivery.pickup_lat, delivery.pickup_long,
                                                 delivery.dropoff_lat, delivery.dropoff_long);
            total_distance += pickup_to_dropoff;

            // Calculate travel time
            long long travel_time = static_cast<long long>(pickup_to_dropoff / 4.5); // 4.5 meters/second

            // Additional time for food preparation
            long long food_prep_time = delivery.food_ready_time - delivery.created_at;

            // Total delivery time
            long long total_time = travel_time + food_prep_time;
            driver_total_delivery_time += total_time;

            // Add to overall total delivery duration
            total_delivery_duration += total_time;

            // Track driver stats
            driver_deliveries++;
            total_deliveries++;

            // Output
            cout << "  Delivery ID: " << delivery.id
                      << ", Distance: " << pickup_to_dropoff / 1000 << " km"
                      << ", Delivery Time: " << total_time / 60.0 << " minutes" << endl;
        }

        // Store driver stats
        driver_stats[driver_id] = {driver_deliveries, total_distance, driver_total_delivery_time, driver_time_spent};
        total_time_spent += driver_total_delivery_time;

        // Print driver summary
        cout << "  Deliveries Assigned: " << driver_deliveries << endl;
        cout << "  Total Distance: " << total_distance / 1000 << " km" << endl;
        cout << "  Total Delivery Time: " << driver_total_delivery_time / 60.0 << " minutes" << endl;
        cout << "  Average Delivery Duration: " << (driver_total_delivery_time / driver_deliveries) / 60.0 << " minutes" << endl;
        cout << "  Deliveries per Hour: " << (driver_deliveries / (driver_total_delivery_time / 3600.0)) << endl;

        driver_id++;
    }

    // Calculate and print overall summary
    double avg_delivery_duration = total_delivery_duration / total_deliveries;
    double avg_deliveries_per_hour = total_deliveries / (total_time_spent / 3600.0);

    cout << "\nSummary:\n";
    cout << "  Total Deliveries: " << total_deliveries << endl;
    cout << "  Number of Drivers: " << driver_stats.size() << endl;
    cout << "  Average Delivery Duration: " << avg_delivery_duration / 60.0 << " minutes" << endl;
    cout << "  Average Deliveries per Hour: " << avg_deliveries_per_hour << endl;
    cout << "  Target Achieved: " << (avg_delivery_duration / 60.0 < 45 ? "Yes" : "No") << " (Average delivery duration < 45 minutes)" << endl;
}

int main() {
    string file_name = "deliveries.csv";
    vector<Delivery> deliveries = parseCSV(file_name);

    if (deliveries.empty()) {
        cerr << "No deliveries found. Exiting..." << endl;
        return 1;
    }

    assignDeliveries(deliveries);

    return 0;
}

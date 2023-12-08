#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


/*
 * + 1 millimeter per second for each second held
 * Time is max time of race
 * Distance is the current distance record for each race
*/

int main() {
    std::ifstream file("data.txt");
    std::string line;
    std::vector<std::string> data;
    std::string data_string;
    std::vector<std::pair<std::string, std::string>> seperated_data;
    std::vector<std::string> times, distances;
    std::vector<int> num_times, num_distances;
    std::string time, distance;
    int total {1};

    while (std::getline(file, line)) {
        data_string += line;
        data_string += '\n';
        data.push_back(line);
    }

    for (auto element : data) {
        std::vector<std::string> each_element;
        std::istringstream ss(element);
        std::string token;
        while (getline(ss, token, ':')) {
            each_element.push_back(token);
        }
        seperated_data.emplace_back(each_element[0], each_element[1]);
    }

    for (auto element : seperated_data) {
        std::vector<std::string> temp_times;
        std::vector<std::string> temp_distances;
        std::istringstream ss(element.second);
        std::string token;
        while (getline(ss, token, ' ')) {
            if (element.first == "Time") {
                times.push_back(token);
            }
            if (element.first == "Distance") {
                distances.push_back(token);
            }
        }
    }

    times.erase(std::remove(times.begin(), times.end(), ""), times.end());
    distances.erase(std::remove(distances.begin(), distances.end(), ""), distances.end());

    for (auto element : times) {
        num_times.push_back(std::stoi(element));
    }
    for (auto element : distances) {
        num_distances.push_back(std::stoi(element));
    }

    for (int j {0}; j < num_times.size(); j++) {
        int total_time = num_times[j];
        int time_left {0};
        int total_distance = 0;
        int possible_wins {0};
        int speed {0};
        for (int i {0}; i < total_time; i++) {
            speed = i;
            time_left = total_time - i;
            total_distance = speed * time_left;
            if (total_distance > num_distances[j]) {
                possible_wins++;
            }
        }
        std::cout << possible_wins << '\n';
        total *= possible_wins;


    }

    std::cout << "Part 1 total: ";
    std::cout << total << std::endl;
    //total = 0;

    for (auto element : times) {
        time += element;
    }
    for (auto element : distances) {
        distance += element;
    }

    std::cout << typeid(time).name() << std::endl;
    std::cout << distance << std::endl;


    long long new_time = std::stoll(time);
    long long new_distance = std::stoll(distance);

    for (int i {0}; i <= new_time; i++) {
        long long speed = i;
        long long time_left = new_time - i;
        long long total_distance = speed * time_left;
        if (total_distance > new_distance) {
            total++;
        }
    }

    std::cout << "Part 2 total: ";
    std::cout << total << std::endl;

    return 0;
}

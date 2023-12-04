#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

int main() {
    std::ifstream file("data.txt");
    std::string line;
    std::vector<std::pair<int, std::string>> data;
    std::vector<std::pair<int, std::vector<std::string>>> semicolon_data;
    std::vector<std::pair<int, std::vector<std::vector<std::string>>>> final_data;
    int game_num {1};
    int blue_max {14};
    int green_max {13};
    int red_max {12};
    std::string blue {"blue"};
    std::string green {"green"};
    std::string red {"red"};
    int total {0};

    while (std::getline(file, line, '\n')) {
        std::istringstream lineStream(line);
        std::string key, value;

        if(std::getline(lineStream, key, ':') && std::getline(lineStream, value)) {
            data.emplace_back(game_num, value);
            game_num++;
        }
    }

    for (auto element : data) {
        std::vector<std::string> pick_results;
        std::istringstream ss(element.second);
        std::string token;

        while (std::getline(ss, token, ';')) {
            pick_results.push_back(token);
        }

        semicolon_data.emplace_back(element.first, pick_results);
    }

    for (auto element : semicolon_data) {
        std::vector<std::string> picks;
        std::vector<std::vector<std::string>> pick_results;
        for (auto pick : element.second) {
            std::istringstream ss(pick);
            std::string token;

            while (std::getline(ss, token, ',')) {
                picks.push_back(token);
            }
            pick_results.push_back(picks);
        }


        final_data.emplace_back(element.first, pick_results);
    }

    for (auto element : final_data) {
        std::cout << "Game " << element.first << std::endl;
        for (auto attempts : element.second) {
            for (auto pick : attempts) {
                std::cout << pick << "!--!";
            }
        }
        std::cout << std::endl;
    }

    file.close();
    return 0;
}

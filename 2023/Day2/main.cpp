#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

void trimLeadingSpaces(std::string& str) {
    size_t pos = str.find_first_not_of(' ');
    if (pos != std::string::npos) {
        str = str.substr(pos);
    }
}

int main() {
    std::ifstream file("data.txt");
    std::string line;
    std::vector<std::pair<int, std::string>> data;
    std::vector<std::pair<int, std::vector<std::string>>> semicolon_data;
    std::vector<std::pair<int, std::vector<std::vector<std::string>>>> final_data;
    std::vector<std::pair<int, std::vector<std::vector<std::pair< std::string, std::string>>>>> better_final_data;
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
            trimLeadingSpaces(token);
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
                trimLeadingSpaces(token);
                picks.push_back(token);
            }
            pick_results.push_back(picks);
        }


        final_data.emplace_back(element.first, pick_results);
    }

    for (auto element : final_data) {
        std::vector<std::pair<std::string, std::string>> picks;
        std::vector<std::vector<std::pair<std::string, std::string>>> pick_results;
        for (auto pick : element.second) {
            for (auto pick2 : pick) {
                std::istringstream ss(pick2);
                std::string token;
                std::string key;
                std::string value;

                std::getline(ss, key, ' ');
                std::getline(ss, value);

                picks.emplace_back(key, value);
            }
            pick_results.push_back(picks);
        }

        better_final_data.emplace_back(element.first, pick_results);
    }

    for (auto element : better_final_data) {
        // int over_max {0};
        int min_blue_value {0};
        int min_green_value {0};
        int min_red_value {0};
        std::vector<int> blue_values, green_values, red_values;
        for (auto pick : element.second) {
            for (auto pick2 : pick) {
                /*if (pick2.second == blue && std::stoi(pick2.first) > blue_max) {
                    over_max++;
                } else if (pick2.second == green && std::stoi(pick2.first) > green_max) {
                    over_max++;
                } else if (pick2.second == red && std::stoi(pick2.first) > red_max) {
                    over_max++;
                }*/
                if (pick2.second == blue) {
                    blue_values.push_back(std::stoi(pick2.first));
                } 
                if (pick2.second == green) {
                    green_values.push_back(std::stoi(pick2.first));
                }  
                if (pick2.second == red) {
                    red_values.push_back(std::stoi(pick2.first));
                }
            }
        }
        auto min_blue = std::max_element(blue_values.begin(), blue_values.end());
        auto min_green = std::max_element(green_values.begin(), green_values.end());
        auto min_red = std::max_element(red_values.begin(), red_values.end());
        min_blue_value = *min_blue;
        min_green_value = *min_green;
        min_red_value = *min_red;
        int game_total = min_blue_value * min_green_value * min_red_value;
        std::cout << element.first << std::endl;
        std::cout << "- " << game_total << std::endl;
        total += game_total;
        /*if (over_max == 0) {
            total += element.first;
        }*/
    }

    std::cout << total << std::endl;
    /*int max_total {0};
    for (int i {1}; i <= 100; i++) {
        max_total += i;
    }
    std::cout << max_total << std::endl;*/

    
    file.close();
    return 0;
}

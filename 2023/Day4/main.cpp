#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>

int main() {
    std::ifstream file("data.txt");
    std::string line;
    std::vector<std::string> data;
    std::vector<std::pair<std::string, std::string>> seperated_data;
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> final_seperated_data;
    std::vector<std::vector<std::string>> winning_numbers;
    std::vector<std::vector<std::string>> received_numbers;
    std::vector<int> match_totals;
    int total_cards [202];
    for (int i{0}; i < 202; i++) {
        total_cards[i] = 1;
    }
    std::string data_string;
    int total {0};

    while (std::getline(file, line, '\n')) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            line = line.substr(pos + 1);
        }
        data.push_back(line);
    }

    for (auto element : data) {
        std::vector<std::string> nums;
        std::istringstream ss(element);
        std::string token;
        while (getline(ss, token, '|')) {
            nums.push_back(token);
        }
        seperated_data.emplace_back(nums[0], nums[1]);
    }

    for (auto element : seperated_data) {
        std::vector<std::string> temp_w_nums;
        std::vector<std::string> temp_r_nums;
        std::istringstream ss1(element.first);
        std::istringstream ss2(element.second);
        std::string token;
        while (getline(ss1, token, ' ')) {
            temp_w_nums.push_back(token);
        }
        while (getline(ss2, token, ' ')) {
            temp_r_nums.push_back(token);
        }
        final_seperated_data.emplace_back(temp_w_nums, temp_r_nums);
    }

    for (auto element : final_seperated_data) {
        std::vector<std::string> t_winning_numbers;
        std::vector<std::string> t_received_numbers;

        for (auto winning_num : element.first) {
            if (winning_num != "") {
                t_winning_numbers.push_back(winning_num);
            }
        }
        for (auto received_num : element.second) {
            if (received_num != "") {
                t_received_numbers.push_back(received_num);
            }
        }

        winning_numbers.push_back(t_winning_numbers);
        received_numbers.push_back(t_received_numbers);
    }

    final_seperated_data.clear();
    for (int i = 0; i < winning_numbers.size(); i++) {
        final_seperated_data.emplace_back(winning_numbers[i], received_numbers[i]);
    }

    for (auto element : final_seperated_data) {
        int total_matches {0};
        for (auto winning_num : element.first) {
            for (auto received_num : element.second) {
                if (winning_num == received_num) {
                    total_matches++;
                }
            }
        }
        if (total_matches > 0) {
            total += pow(2, total_matches-1);
        }
        match_totals.push_back(total_matches);
    }

    std::cout << "Part 1 total: " << total << std::endl;

    for (int i = 0; i < match_totals.size(); i++) {
        if (match_totals[i] > 0) {
            for (int j {1}; j <=match_totals[i]; j++) {
                total_cards[i+j] += total_cards[i];
            }
        }
    }

    total = 0;
    for (int i {0}; i < 202; i++) {
        std::cout << i + 1 << ": " << total_cards[i] << std::endl;
        total += total_cards[i];
    }

    std::cout << "Part 2 total: " << total << std::endl;
    return 0;
}

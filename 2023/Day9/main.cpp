#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>

int main() {
    std::ifstream file("data2.txt");
    std::string line;
    std::vector<std::string> data;
    std::vector<std::vector<int>> sequence;
    std::vector<std::vector<std::vector<int>>> history;
    std::string data_string;
    int total {0};
    int pass_num {1};

    while (std::getline(file, line, '\n')) {
        std::string temp;
        data.push_back(line);
    }

    for (auto element : data) {
        std::vector<int> nums;
        std::istringstream ss(element);
        std::string token;
        while (getline(ss, token, ' ')) {
            nums.push_back(std::stoi(token));
        }
        sequence.push_back(nums);
    }

    for (auto element : sequence) {
        std::vector<int> stage = element;
        std::vector<std::vector<int>> temp;
        int vector_sum = std::accumulate(element.begin(), element.end(), 0);
        temp.push_back(element);
        while (vector_sum != 0) {
            std::vector<int> temp_vector;
            for (int i {1}; i < stage.size(); i++) {
                temp_vector.push_back(stage[i]-stage[i-1]);
            }
            temp.push_back(temp_vector);
            stage = temp_vector;
            vector_sum = std::accumulate(stage.begin(), stage.end(), 0);
        }
        history.push_back(temp);
    }

    for (auto &element : history) {
        int increment {element[element.size()-2][0]};
        size_t size {element.size()};
        for (size_t i {size-2}; i >= 1; i--) {
            int new_num {element[i-1].back() + increment};
            element[i-1].push_back(new_num);
            increment = new_num;
        }
    }

    for (auto element : history) {
        std::cout << "Pass " << pass_num << std::endl;
        total += element[0].back();
        std::cout << element[0].back() << std::endl;
        std::cout << total << std::endl;
        std::cout << std::endl;
        pass_num++;
    }

    std::cout << "Part 1 total: " << total << std::endl;






    return 0;
}

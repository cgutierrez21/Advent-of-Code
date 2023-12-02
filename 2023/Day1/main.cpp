#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("data.txt");
    std::string line;
    std::vector<std::string> data;
    std::string data_string;

    std::vector<std::string> num_words {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    while (std::getline(file, line)) {
        data_string += line;
        data_string += '\n';
        data.push_back(line);
    }

    int total {0};
    for (auto const &element : data) {

        std::vector<int> numbers;
        std::vector<int> positions;
        int first_num;
        int second_num;

        for (int i = 0; i < element.size(); ++i) {
            char character = element[i];

            if(std::isdigit(character)) {
                numbers.push_back(character - '0');
                positions.push_back(i);
            }

        }

        for (const auto& nums : num_words) {
            size_t pos = element.find(nums);

            while (pos != std::string::npos) {
                positions.push_back(static_cast<int>(pos));
                if (nums == "zero") {
                    numbers.push_back(0);
                } else if (nums == "one") {
                    numbers.push_back(1);
                } else if (nums == "two") {
                    numbers.push_back(2);
                } else if (nums == "three") {
                    numbers.push_back(3);
                } else if (nums == "four") {
                    numbers.push_back(4);
                } else if (nums == "five") {
                    numbers.push_back(5);
                } else if (nums == "six") {
                    numbers.push_back(6);
                } else if (nums == "seven") {
                    numbers.push_back(7);
                } else if (nums == "eight") {
                    numbers.push_back(8);
                } else if (nums == "nine") {
                    numbers.push_back(9);
                }
                pos = element.find(nums, pos + 1);
            }

        }
        auto min_element = std::min_element(positions.begin(), positions.end());
        auto max_element = std::max_element(positions.begin(), positions.end());
        size_t min_pos = std::distance(positions.begin(), min_element);
        size_t max_pos = std::distance(positions.begin(), max_element);
        first_num = numbers[min_pos] * 10;
        second_num = numbers[max_pos];
        std::cout << first_num << " " << second_num << std::endl;
        total += first_num + second_num;
        std::cout << total << std::endl;
        std::cout << std::endl;
    }


    std::cout << std::endl;
    std::cout << total << std::endl;






    file.close();
    return 0;
}

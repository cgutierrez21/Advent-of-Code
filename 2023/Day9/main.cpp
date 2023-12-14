/*#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>

int main() {
    std::ifstream file("data.txt");
    std::string line;
    std::vector<std::string> data;
    std::vector<std::vector<int>> sequence;
    std::vector<std::vector<std::vector<int>>> history;
    std::vector<int> final_nums;
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
    
    // Print out the history
    for (auto &element : history) {
        std::cout << "Pass " << pass_num << std::endl;
        for (auto &element2 : element) {
            for (auto &element3 : element2) {
                std::cout << element3 << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        pass_num++;
    }

    for (auto &element : history) {
        int increment {element[element.size()-2][0]};
        size_t size {element.size()};
        for (size_t i {size-2}; i >= 1; i--) {
            int new_num {element[i-1].back() + increment};
            element[i-1].push_back(new_num);
            increment = new_num;
        }
        //std::cout << element[0].back() << std::endl;
        final_nums.push_back(element[0].back());
        //std::cout << total << std::endl;
        //std::cout << std::endl;
    }

    // Print out the history
    pass_num = 1;
    for (auto &element : history) {
        std::cout << "Pass " << pass_num << std::endl;
        for (auto &element2 : element) {
            for (auto &element3 : element2) {
                std::cout << element3 << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        pass_num++;
    }

    for (auto &element : final_nums) {
        std::cout << element << " | ";
    }

    std::cout << std::endl;
    total = std::accumulate(final_nums.begin(), final_nums.end(), 0);

    std::cout << "Part 1 total: " << total << std::endl;






    return 0;
}*/
//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
#include <fstream>

int main() {

    std::string in;
    std::ifstream file("data.txt");
    int ans = 0;

    while (getline(file, in, '\n')) {

        std::vector<int> nums;
        std::stringstream ss(in);
        int num;
        while (ss >> num) {
            nums.push_back(num);
        }

        // for part2 uncomment this line
         reverse(nums.begin(), nums.end());

        //int i = nums.size() - 1;

        std::vector<int> sol;
        sol.push_back(nums.back());
        while (nums.size() > 0) {
            for(int i = 0; i < nums.size() - 1; ++i) {
                nums[i] = nums[i + 1] - nums[i];
            }
            nums.resize(nums.size() - 1);
            sol.push_back(nums.back());

            bool all_zero = true;

            for(auto &n : nums) {
                if(n != 0) {
                    all_zero = false;
                    break;
                }
            }

            if(all_zero) break;

        }

        ans += accumulate(sol.begin(), sol.end(), 0);

    }

    std::cout << ans << "\n";

    return 0;
}

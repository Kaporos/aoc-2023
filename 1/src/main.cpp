#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>


std::string toReplace[] = {"one","two","three","four","five","six","seven","eight","nine"};
std::string toReplaceWith[] = {"one1one","two2two","three3three","four4four","five5five","six6six","seven7seven","eight8eight","nine9nine"};

int lineSum(std::string line, bool replace) {
    int first = 0;
    int last = 0;
    if (replace) {
      for (int i = 0; i < 9; i++) {
        line = std::regex_replace(line, std::regex(toReplace[i]), toReplaceWith[i]);
      }
    }
    for (auto i = 0; i < line.size(); i ++) {
      char curr = line[i];
      int value = curr - '0';
      if (value > 0 && value <= 9) {
        if (first == 0) {
          first = value;
        } 
        last = value;
      }
    }
    int sum = first * 10 + last;
    return sum;
  
}

int main() {
  std::ifstream nameFileout;
  nameFileout.open("data-full.txt");
  std::string line;
  int total = 0;
  while (std::getline(nameFileout, line)) {
    total += lineSum(line, false);
  }
  std::cout << "Total part 1: " << total << std::endl;;
  
  std::ifstream nameFileout2;
  nameFileout2.open("data-full.txt");
  total = 0;
  while (std::getline(nameFileout2, line)) {
    total += lineSum(line, true);
  }
  std::cout << "Total part 2: " << total << std::endl; 
  return 0;
}



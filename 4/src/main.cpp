#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>


int ctoi(char carac) {
  int number = carac - '0';
  if (number >= 0 && number <= 9)
    return number;
  return -1;
}

int processCard(std::string cardLine) {
  cardLine += " ";
  int size = cardLine.size();
  int id = 0;
  int count = 0;
  std::vector<int> possessions;
  bool inWinning = false;
  std::string currentNumber = "";
  for (int i = 0; i < size; i++)
  {
    inWinning = inWinning || cardLine[i] == '|';
    int value = ctoi(cardLine[i]);
    if (value != -1) {
      currentNumber += cardLine[i];
    }
    if (id == 0 && cardLine[i] == ':') {
      id = std::stoi(currentNumber);
      currentNumber = "";
      continue;
    }
    if ((cardLine[i] == ' ' || cardLine[i] == '\n') && currentNumber.size() > 0) {
      value = std::stoi(currentNumber);
      currentNumber = "";
    } else {
      continue;
    }
    if (inWinning) {
      for (int i = 0; i < possessions.size(); i++) {
        if (possessions[i] == value) {
          count += 1;
        }
      }
      continue;
    }

    possessions.push_back(value);    
  }
  if (count == 0) {
    return count;
  }
  int total = 1;
  count -= 1;
  for (int i = 0; i < count; i++) {
    total = total *2;
  }
  return total;
}

int main() {
  std::ifstream nameFileout;
  nameFileout.open("data-full.txt");
  std::string line;
  int total = 0;
  while (std::getline(nameFileout, line)) {
    total += processCard(line);
  }
  std::cout << "Total part 1: " << total << std::endl;;
}



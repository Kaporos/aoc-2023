#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> colors = {{"red", 12}, {"green", 13},{"blue", 14}};


void trim(std::string &s) {
  if (s[0] == ' ')
    s.erase(0,1);
}

//returns 0 if impossible else game id
int lineValue(std::string line) {
  line.erase(0, 4); //Removing Game 
  std::stringstream ss(line); 
  std::string s;
  std::getline(ss, s, ':'); //Retrieving ID
  int id = std::stoi(s);

  std::getline(ss, s, ':');
  s.erase(0,1); //Removing space after :
  std::stringstream lineStream(s);

  std::string currSet;
  
  
  while (std::getline(lineStream, currSet, ';')) {
    trim(currSet);
    std::stringstream currSetStream(currSet);
    std::string currentItem;
    while (std::getline(currSetStream, currentItem, ',')) {
      trim(currentItem);
      std::stringstream currentItemStream(currentItem);
      std::string i;
      std::getline(currentItemStream, i, ' ');
      int value = stoi(i);
      std::getline(currentItemStream, i, ' ');
      std::string color = i;
      if (colors[color] < value) {
        return 0; //Impossible game
      }

    }
    
  }
  
 // std::cout << s << std::endl;
  return id;
}

int linePower(std::string line) {
  line.erase(0, 4); //Removing Game 
  std::stringstream ss(line); 
  std::string s;
  std::getline(ss, s, ':'); //Retrieving ID
  int id = std::stoi(s);

  std::getline(ss, s, ':');
  s.erase(0,1); //Removing space after :
  std::stringstream lineStream(s);

  std::string currSet;
  
  
  std::unordered_map<std::string, int> colors = {{"red", 0}, {"green", 0},{"blue", 0}}; //yes ugly sorry
  while (std::getline(lineStream, currSet, ';')) {
    trim(currSet);
    std::stringstream currSetStream(currSet);
    std::string currentItem;
    while (std::getline(currSetStream, currentItem, ',')) {
      trim(currentItem);
      std::stringstream currentItemStream(currentItem);
      std::string i;
      std::getline(currentItemStream, i, ' ');
      int value = stoi(i);
      std::getline(currentItemStream, i, ' ');
      std::string color = i;
      if (colors[color] < value) {
        colors[color] = value;
      }

    }
    
  }

  return colors["red"] * colors["green"] * colors["blue"];
}


int main() {
  std::ifstream nameFileout;
  nameFileout.open("data-full.txt");
  std::string line;
  int total = 0;
  while (std::getline(nameFileout, line)) {
    total += lineValue(line);
  }
  std::cout << "Total part 1: " << total << std::endl;;
  
  std::ifstream nameFileout2;
  nameFileout2.open("data-full.txt");
  std::string line2;
  total = 0;
  while (std::getline(nameFileout2, line2)) {
    total += linePower(line2);
  }
  std::cout << "Total part 2: " << total << std::endl;;
}



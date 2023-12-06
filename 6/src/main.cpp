#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <mutex>
#include <regex>

//Simple function to read file content
inline std::string slurp (const std::string& path) {
  std::ostringstream buf;
  std::ifstream input (path.c_str());
  buf << input.rdbuf();
  return buf.str();
}

//Convert a char of number to int
int ctoi(char carac) {
  int number = carac - '0';
  if (number >= 0 && number <= 9)
    return number;
  return -1;
}

std::string removeAll(std::string s, char delimiter) {
  std::string result;
  for (int i =0; i < s.size(); i ++) {
    if (s[i] != delimiter)
      result += s[i];
  }
  return result;
}

std::vector<std::string> split(std::string content, char delimiter) {
  std::string current;
  std::vector<std::string> result;
  for (long unsigned int i =0; i < content.size(); i++) {
    if (content[i] == delimiter) {
      if (current.length() > 0)
        result.push_back(current);
      current = "";
      continue;
    }
    else {
      current += content[i];
    }
    if (i == content.size()-1 && current.length() > 0) {
      result.push_back(current);
    }
  }
  return result;
}

long int race_score(long int speed, long int time) {
  return speed * time;
}

int part1(std::string data) {
  //Parsing of data
  std::vector<std::string> lines = split(data,'\n');
  auto parse = [](const std::string& n) {return std::stoi(n);};
  std::vector<std::string> timesStr = split(lines[0], ' ');
  std::vector<std::string> distancesStr = split(lines[1], ' ');
  std::vector<int> times;
  std::vector<int> distances;
  std::transform(std::next(timesStr.begin(), 1), timesStr.end(), std::back_inserter(times), parse);
  std::transform(std::next(distancesStr.begin(), 1), distancesStr.end(), std::back_inserter(distances), parse);

  int total = 1; //we will multiply so we must start with one;

   for (int race = 0; race < times.size(); race++) {
    int count = 0;
    for (int i = 0; i < times[race]; i ++){
      if (race_score(i, times[race]-i) > distances[race]) {
        count += 1;
      }
      
    }
    total *= count;
  }
  
  return total;
}

long int part2(std::string data) {
  //parsing
  std::vector<std::string> lines = split(data,'\n');
  auto parse = [](const std::string& n) {return std::stoi(n);};
  long int time = stoul(removeAll(lines[0].substr(5, lines[0].size()-5), ' '));
  long int distance = stoul(removeAll(lines[1].substr(10, lines[1].size()-10), ' '));

  long int total = 1; //we will multiply so we must start with one;

  long int count = 0;
  for (long i = 0; i < time; i ++){
    if (race_score(i, time-i) > distance) {
      count += 1;
    }
  }
  total *= count;
  
  return total;
}

int main() {
  int total = part1(slurp("data-full.txt"));
  std::cout << "Total part 1: " << total << std::endl;
  long int total2 = part2(slurp("data-full.txt"));
  std::cout << "Total part 2: " << total2 << std::endl;
  return 0;
}



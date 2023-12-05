#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#define lint long unsigned int

struct range {
  long int destination_start;
  long int source_start;
  long int length;
};

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

//return a vector of all number in a string
std::vector<long int> split_and_parse(std::string string) {
  std::string current;
  std::vector<long int> result;
  for (lint i =0; i < string.size(); i++) {
    int value = ctoi(string[i]);
    if ((value == -1) && current.length() > 0) {
      result.push_back(std::stoul(current));
      current = "";
    } else if (value != -1){
      current += string[i];
    }
    if (i == string.size() -1 && current.length() > 0) {
      result.push_back(std::stoul(current));
    }
    
  }

  return result;
}

std::vector<std::string> split(std::string content, char delimiter) {
  std::string current;
  std::vector<std::string> result;
  for (lint i =0; i < content.size(); i++) {
    if (content[i] == delimiter) {
      result.push_back(current);
      current = "";
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


std::vector<std::vector<range>> get_ranges(std::string content) {
  std::vector<std::vector<range>> ranges;
  std::vector<std::string> lines = split(content, '\n');

  int currentType = 0;
  bool justUpdated = false;
  ranges.push_back(std::vector<range>());
  
  for (long unsigned int i = 0; i < lines.size(); i ++)
  {
    std::vector<long int> numbers = split_and_parse(lines[i]);
    if (numbers.size() == 0) {
      if (justUpdated) {
        continue;
      }
      currentType += 1;
      justUpdated = true;
      ranges.push_back(std::vector<range>());
      continue;
    }
    justUpdated = false;
    range currentRange{numbers[0], numbers[1], numbers[2]};
    ranges[currentType].push_back(currentRange);
  }
  return ranges;
}

int part1(std::string content) {
  int firstLineLength = content.find('\n');
  //getting seeds first
  std::vector<long int> seeds = split_and_parse(content.substr(7, firstLineLength-7));

  content = content.substr(firstLineLength+2, content.size()-firstLineLength-2); //removing seeds from content !
  
  //First, we have to read all ranges from data.
  auto ranges = get_ranges(content);

  long int min = 10000000000;
  //iterating over seeds
  for (lint i = 0; i < seeds.size(); i++) {
    long int value = seeds[i];
    for (lint j = 0; j < ranges.size(); j ++) {
      std::vector<range> currTypeRanges = ranges[j];
      for (lint k = 0; k < currTypeRanges.size(); k++) {
        range current = currTypeRanges[k];
        if (value >= current.source_start && value <= current.source_start+current.length){
          value = current.destination_start + (value - current.source_start);
          break;
        }
      }
    }
    if (value < min) {
      min = value;
      break;
    }
  }
  return min;
}

long int part2(std::string content) {
  int firstLineLength = content.find('\n');
  //getting seeds first
  std::vector<long int> seeds = split_and_parse(content.substr(7, firstLineLength-7));

  content = content.substr(firstLineLength+2, content.size()-firstLineLength-2); //removing seeds from content !
  
  //First, we have to read all ranges from data.
  auto ranges = get_ranges(content);
  //iterating FROM locations to seeds

  
  int locationsIndex = ranges.size()-1;

  //while(true) not elegant but who cares, because we know there is a solution :D
  int loc = 0;
  while (true) 
  {
  
    long int value = loc;
    for (long int j = locationsIndex; j >= 0; j--) {        
      for (lint l = 0; l < ranges[j].size(); l ++) {
        range currentSubRange = ranges[j][l];
        if (value >= currentSubRange.destination_start && value < currentSubRange.destination_start+currentSubRange.length) {
            value = (currentSubRange.source_start+(value - currentSubRange.destination_start));
            break;
        }
      }
    }

    for (lint a = 0; a < seeds.size(); a+=2) {
      if (value >= seeds[a] && value < seeds[a]+seeds[a+1]) {
        return loc;
      }
    }
    loc ++;
  }
 
  
  return -1;
}
int main() {
  long int total = part1(slurp("data-full.txt"));
  std::cout << "Total part 1: " << total << std::endl;;
  long int total2 = part2(slurp("data-full.txt"));
  std::cout << "Total part 2: " << total2 << std::endl; 
  return 0;
}


 



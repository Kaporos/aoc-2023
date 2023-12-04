#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>



inline std::string slurp (const std::string& path) {
  std::ostringstream buf; 
  std::ifstream input (path.c_str()); 
  buf << input.rdbuf(); 
  return buf.str();
}

int ctoi(char carac) {
  int number = carac - '0';
  if (number >= 0 && number <= 9)
    return number;
  return -1;
}

int part1(std::string content) {
  std::string currentNumber;
  bool isOkay = false;
  int lineLength = content.find("\n");
  std::cout << lineLength << std::endl;
  int size = content.size();
  int total = 0;
  for (int i = 0; i < size; i++)
  {
    char curr = content[i];
    int value = ctoi(curr);
    if (value < 0) {
      if (isOkay && currentNumber.size() > 0) 
      {
        total += stoi(currentNumber);
      }
      currentNumber = "";
      isOkay = false;
      continue; 
    }    
    currentNumber += curr;
    if (isOkay) 
    {
      continue;
    }
    int toCheck[8] = {i-lineLength, i-lineLength-2, i-lineLength- 1, i+lineLength, i+lineLength+1, i+lineLength+2, i-1, i+1};
    for (int j = 0; j < 8; j++) {
      int elem = toCheck[j];
      if (elem < 0 || elem > size)
      {
        continue;
      }
      isOkay = isOkay || (content[elem] != '.' && content[elem] != '\n' && ctoi(content[elem]) < 0);
    }
  }
  return total;
}

int part2(std::string content) {
  std::string currentNumber;
  int lineLength = content.find("\n");
  std::cout << lineLength << std::endl;
  int size = content.size();
  
  std::unordered_map<int, std::vector<int>> registry;
  for (int i = 0; i < size; i++) {
    registry[i] = std::vector<int>();
  }

  std::vector<int> stars;
  for (int i = 0; i < size; i++)
  {
    char curr = content[i];
    int value = ctoi(curr);
    if (value < 0) {
      if (currentNumber.size() > 0){
        for (int j = 0; j < stars.size(); j ++) {
          registry[stars[j]].push_back(stoi(currentNumber));
        }
      }
      stars.clear();
      currentNumber = "";
      continue; 
    }    
    currentNumber += curr;
    int toCheck[8] = {i-lineLength, i-lineLength-2, i-lineLength- 1, i+lineLength, i+lineLength+1, i+lineLength+2, i-1, i+1};
    for (int j = 0; j < 8; j++) {
      int elem = toCheck[j];
      if (elem < 0 || elem > size)
      {
        continue;
      }
      if (content[elem] == '*')
      {
        bool already = false;
        for (int j = 0; j < stars.size(); j++)
          already = already || (stars[j] == elem);
        if (!already)
          stars.push_back(elem);
      }
    }
  }

  int total = 0;
  for (int i = 0; i < size; i ++) {
    if (registry[i].size() == 2) {
      total += (registry[i][0] * registry[i][1]);
    }
  }

  
  
  return total;
}
int main() {
  int total = part1(slurp("data-full.txt"));
  std::cout << "Total part 1: " << total << std::endl;;
  int total2 = part2(slurp("data-full.txt"));
  std::cout << "Total part 2: " << total2 << std::endl;;
  
  return 0;
}


 

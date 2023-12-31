#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <mutex>
#include <regex>
#include <unordered_map>

//Simple function to read file content
inline std::string slurp (const std::string& path) {
  std::ostringstream buf;
  std::ifstream input (path.c_str());
  buf << input.rdbuf();
  return buf.str();
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

int c_cardToInt1(char card_c) {
      switch (card_c) {
        case 'T':
          return 10;
        case 'J':
          return 11;
        case 'Q':
          return 12;
        case 'K':
          return 13;
        case 'A':
          return 14;
        default:
          return card_c-'0';
      }
}
int c_cardToInt2(char card_c) {
      switch (card_c) {
        case 'T':
          return 10;
        case 'J':
          return 1;
        case 'Q':
          return 11;
        case 'K':
          return 12;
        case 'A':
          return 13;
        default:
          return card_c-'0';
      }
}

long long int part1(std::string data) {
  std::vector<std::string> lines = split(data, '\n');
  std::vector<std::string> hands;
  std::unordered_map<int, int> hands_score;
  
  std::unordered_map<std::string, int> bets;
  for (unsigned int i =0; i < lines.size(); i++)
  {
    std::vector<std::string> data = split(lines[i], ' ');
    hands.push_back(data[0]);
    bets[hands[i]] = stoi(data[1]);
  }


  for (unsigned int i = 0; i < hands.size(); i++) 
  {
    std::string hand = hands[i];
    std::unordered_map<int, int> count_table;
    for (unsigned int k = 0; k < 15; k++)
      count_table[k] = 0; //First initialisation
    for (unsigned int j = 0; j < hand.size(); j++) 
    {
      int card = c_cardToInt1(hand[j]);
      count_table[card] += 1;      
    }
    std::unordered_map<int, int> reversed_count_tables;
    for (int a = 0; a < 6; a++) {
      reversed_count_tables[a] = 0;
    }
    for (int k = 0; k < 15; k++) {
      int cardCount = count_table[k];
      reversed_count_tables[cardCount] += 1;
    }

    if (reversed_count_tables[5] == 1) {
      hands_score[i] = 7;
      continue;
    }
    if (reversed_count_tables[4] == 1) {
      hands_score[i] = 6;
      continue;
    }
    if (reversed_count_tables[3] == 1 && reversed_count_tables[2] == 1) {
      hands_score[i] = 5;
      continue;
    }
    if (reversed_count_tables[3] == 1) {
      hands_score[i] = 4;
      continue;
    }
    if (reversed_count_tables[2] == 2) {
      hands_score[i] = 3;
      continue;
    }
    if (reversed_count_tables[2] == 1) {
      hands_score[i] = 2;
      continue;
    }
    hands_score[i] = 1;
  }
  std::unordered_map<std::string, int> hands_indices;
  for (int i = 0; i < hands.size(); i++){
    hands_indices[hands[i]] = i;
  }
  std::sort(hands.begin(), hands.end(), [&hands_indices, &hands_score](std::string &h1, std::string &h2) {
    int val1 = hands_score[hands_indices[h1]];
    int val2 = hands_score[hands_indices[h2]];
    if (val1 != val2) {
      return val1 < val2;
    }
    for (int g = 0; g < h1.size(); g++) {
      int card_v_1 = c_cardToInt1(h1[g]);
      int card_v_2 = c_cardToInt1(h2[g]);
      if (card_v_1 != card_v_2) {
        return card_v_1 < card_v_2;
      }
    }
    return true;
  });

  long long int total;
  for (int g = 0; g < hands.size(); g++) {
    total += (g+1)*bets[hands[g]];
  }
  return total;
}

long long int part2(std::string data) {
  std::vector<std::string> lines = split(data, '\n');
  std::vector<std::string> hands;
  std::unordered_map<int, int> hands_score;
  
  std::unordered_map<std::string, int> bets;
  for (unsigned int i =0; i < lines.size(); i++)
  {
    std::vector<std::string> data = split(lines[i], ' ');
    hands.push_back(data[0]);
    bets[hands[i]] = stoi(data[1]);
  }


  for (unsigned int i = 0; i < hands.size(); i++) 
  {
    std::string hand = hands[i];
    std::unordered_map<int, int> count_table;
    for (unsigned int k = 0; k < 14; k++)
      count_table[k] = 0; //First initialisation
    for (unsigned int j = 0; j < hand.size(); j++) 
    {
      int card = c_cardToInt2(hand[j]);
      if (card == 1 && count_table[1] < 4) {
        for (int g = 1; g < 14; g++) {
          count_table[g] += 1;
        }
        count_table[1] -= 1;
      }
      count_table[card] += 1;      
      
    }
    std::unordered_map<int, int> reversed_count_tables;
    for (int a = 0; a < 6; a++) {
      reversed_count_tables[a] = 0;
    }
    for (int k = 0; k < 14; k++) {
      int cardCount = count_table[k];
      reversed_count_tables[cardCount] += 1;
    }

    std::cout << hand << std::endl;
    std::cout << reversed_count_tables[4] << std::endl;
    if (reversed_count_tables[5] == 1) {
      hands_score[i] = 7;
      continue;
    }
    if (reversed_count_tables[4] == 1 || reversed_count_tables[4] == 2) {
      hands_score[i] = 6;
      continue;
    }
    if ((reversed_count_tables[3] == 1 && reversed_count_tables[2] == 1) || reversed_count_tables[3] == 2 && count_table[1] ==1) {
      hands_score[i] = 5;
      continue;
    }
    if (reversed_count_tables[3] == 1 || reversed_count_tables[3] == 3) {
      hands_score[i] = 4;
      continue;
    }
    if (reversed_count_tables[2] == 2 || count_table[1] == 1) {
      hands_score[i] = 3;
      continue;
    }
    if (reversed_count_tables[2] == 1) {
      hands_score[i] = 2;
      continue;
    }
    hands_score[i] = 1;
  }
  std::unordered_map<std::string, int> hands_indices;
  for (int i = 0; i < hands.size(); i++){
    hands_indices[hands[i]] = i;
  }
  std::sort(hands.begin(), hands.end(), [&hands_indices, &hands_score](std::string &h1, std::string &h2) {
    int val1 = hands_score[hands_indices[h1]];
    int val2 = hands_score[hands_indices[h2]];
    if (val1 != val2) {
      return val1 < val2;
    }
    for (int g = 0; g < h1.size(); g++) {
      int card_v_1 = c_cardToInt2(h1[g]);
      int card_v_2 = c_cardToInt2(h2[g]);
      if (card_v_1 != card_v_2) {
        return card_v_1 < card_v_2;
      }
    }
    return false;
  });

  long long int total;
  for (int g = 0; g < hands.size(); g++) {
    std::cout << hands[g] << " rank : " << g+1 << " score : " << hands_score[hands_indices[hands[g]]] << std::endl;
    total += (g+1)*bets[hands[g]];
  }
  return total;
}


int main() {
  long long int total = part1(slurp("data-full.txt"));
  std::cout << "Total part 1: " << total << std::endl;
  long long int total2 = part2(slurp("data-full.txt"));
  std::cout << "Total part 2: " << total2 << std::endl;
  return 0;
}



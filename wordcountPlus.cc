// wordcount-.cc
// Použijte: g++ -std=c++11 -O2
// Příklad použití STL kontejneru unordered_map<>
// Program počítá četnost slov ve vstupním textu,
// slovo je cokoli oddělené "bílým znakem"

#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "to_be_tested_Cplus.h"

using namespace std;
/*
int main() {
    return 0;
}*/

int IJCDU2model(const std::string& filename, vector<string> output)
{
    unordered_map<string,int> m;    // asociativní pole

    ifstream input_file(filename);
    string word;

    vector<string> words_v;

    while (input_file >> word) {
        words_v.push_back(word);
    }

    // mapuje klíč/string na hodnotu/int
    for (const auto &i : words_v)   // čtení slova (jako scanf "%s", ale bezpečné)
        m[word]++;                  // počítání výskytů slova (zvýší hodnotu pro
    // zadaný klíč/slovo pokud záznam existuje,
    // jinak vytvoří nový záznam s hodnotou 0 a
    // tu operace ++ zvýší na 1)

    int cnt = 0;
    for (auto &mi: m)   // pro všechny prvky kontejneru m
    {
        output.push_back(mi.first);
        cnt++;
    }

    // klíč/slovo          hodnota/počet
    // prvky kontejneru typu "map" jsou dvojice (klíč,hodnota)
    return 0;
}

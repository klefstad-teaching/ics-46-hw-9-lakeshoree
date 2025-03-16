#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg) {
    
    cout <<  msg <<  word1 << word2;

}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {

    int str1length = str1.length();
    int str2length = str2.length();

    if (abs(str1length - str2length) > d) { // can't be withen diffrenence if lenghts differ greter than d
        return false;
    }

    int num_diffs = 0;
    int i = 0, j = 0;
    for (; i < str1length && j < str2length; ++i, ++j) {
        if(str1[i] != str2[j]) {
            ++num_diffs;
            if (num_diffs > d) {
                return false;
            }
            if (str1length > str2length) {
                --j;
            }
            else if (str1length < str2length) {
                --i;
            }
        } 
    }

    num_diffs += (str1length - i) + (str2length - j);
    return num_diffs <= d;

}

bool is_adjacent(const string& word1, const string& word2) {

    int num_diffs = 0;
    for (int i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            ++num_diffs;
        }
        if (num_diffs > 1) { // only adjacent if 1 off
            return false;
        }
    }

    if (num_diffs <= 1) {
        return true;
    }
    return false;

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    return {}; // no ladder found

}

void load_words(set<string> & word_list, const string& file_name) {

    ifstream ladder_file(file_name);
    string word;
    while (ladder_file >> word) {
        word_list.insert(word);
    }

}

void print_word_ladder(const vector<string>& ladder) {

    for (const string word : ladder) {
        cout << word << ' ';
    }

}

void verify_word_ladder() {

    //todo

}
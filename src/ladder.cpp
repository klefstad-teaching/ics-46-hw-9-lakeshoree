#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg) {
    
    cout <<  msg <<  word1 << word2;

}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {

    int str1length = str1.size();
    int str2length = str2.size();

    if (abs(str1length - str2length) > d) { // can't be withen diffrenence if lenghts differ greter than d
        return false;
    }

    int num_diffs = 0;
    int i = 0, j = 0;
    while(i < str1length && j < str2length) {
        if(str1[i] != str2[j]) {
            ++num_diffs;
            if (num_diffs > d) {
                return false;
            }
            if (str1length > str2length) {
                ++i;
            }
            else if (str1length < str2length) {
                ++j;
            }
            else { 
                ++i;
                ++j;
            }
        }
        else { // both chars match
            ++i;
            ++j;
        }
    }

    num_diffs += abs((str1length - i) + (str2length - j));
    return num_diffs <= d;

}

bool is_adjacent(const string& word1, const string& word2) {

    return edit_distance_within(word1, word2, 1); // simplified logic by just calling edit_distance_within with dist 1
    // mimics adjacency

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;

    if (word_list.end() == word_list.find(end_word) || begin_word == end_word) {
        return {};
    }

    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
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
    if (!ladder_file) {
        return; // can't open file
    }

    string word;
    while (ladder_file >> word) {
        word_list.insert(word);
    }

}

void print_word_ladder(const vector<string>& ladder) {

    if (ladder.size() == 0) { // no ladder exists
        cout << "No word ladder found." << endl;
    }

    else {
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << ' ';
        }
        cout << endl;
    }



}

void verify_word_ladder() {

    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

void my_assert(bool exp) {
    cout << (exp ? "Passed" : "Failed") << endl;
}
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string (string s, int max) {
    string buff{""};
    vector<string> v;
    int counter = 0;
    if (max == 0) {
        v.push_back(s);
        return v;
    };
    for (int i = 0; i < s.size(); i++) {
        buff+=s.at(i);
        counter++;
        if(counter == max && buff != "") { v.push_back(buff); buff = "";} 
    } 
    if(buff != "") v.push_back(buff);
	return v;
}

bool isPal(string word, int c, int p) {
    if (c == p) return true;
    if (word.at(c) != word.at(p)) return false;
    if (c < p + 1) return isPal(word, c + 1, p - 1);
    return true;
}

bool isPalindrome (string word) {
    int l = word.length();
    if (l == 0) return true;
    return isPal(word, 0, l - 1);
}


// TODO: Optimizar este metodo para poder pasar más test...
int length_max_palindrome (string word, int index) {
    int currentlen = 0;
    if (isPalindrome(word)) return word.length();
    else {

        // for (int i = word.size(); i > index; i--) {
        //     // int jump = word.length() >= 1 ? i + 2 : i + 1;
        //     vector<string> substrings = split_string(word, word.length() - i);
        //     for (auto s: substrings) {
        //         if (isPalindrome(s) && s.length() > currentlen) currentlen = s.length();
        //         else if (s.length() >= 3){
        //             int len = length_max_palindrome(s, i - 1);
        //             if (len > currentlen) currentlen = len;
        //         }
        //     }
        // }

        for (int i = index; i < word.size(); i++) {
            // int jump = word.length() >= 1 ? i + 2 : i + 1;
            vector<string> substrings = split_string(word, word.size() - i);
            for (auto s: substrings) {
                if (isPalindrome(s) && s.length() > currentlen) currentlen = s.length();
                else if (s.length() >= 3){
                    int len = length_max_palindrome(s, i + 4);
                    if (len > currentlen) currentlen = len;
                }
            }
        }
    }
    return currentlen;
}

vector<string> circular_rotate(string origin_word, int iterateTo) {
    vector<string> random_words;
    random_words.push_back(origin_word);
    string aux = origin_word;
    for (int j = 0; j < iterateTo - 1; j++) {
        char head;
        for (int i = 0; i < iterateTo; i++) {
            if (i < iterateTo - 1) {
                if (i == 0) head = aux.at(i);
                aux.at(i) = aux.at(i + 1);
            }
            if (i == iterateTo - 1) {
                aux.at(i) = head;
            }
        }
        random_words.push_back(aux);
    }
    return random_words;
}

vector<int> circularPalindromes(string s) {
    vector<string> random_word = circular_rotate(s, s.length());
    vector<int> results;
    for (auto w:random_word) {
        int result = length_max_palindrome(w, 0);
        results.push_back(result);
        // cout << w << " palindrome max: " << result;
        // cout << "\n";
    }
    return results;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;
    getline(cin, s);

    vector<int> result = circularPalindromes(s);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        cout << result[result_itr];

        if (result_itr != result.size() - 1) {
            cout << "\n";
        }
    }
    cout << "\n";

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

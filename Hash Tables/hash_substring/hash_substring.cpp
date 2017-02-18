#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

long long mod(long long a, long long b){
    return (a % b + b) % b;
}

long long hash_func(const string& s , const long long& prime, const long long& multiplier) {
    long long hash = 0;
    for (long long i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = mod(hash * multiplier + s[i], prime);
    return hash;
}

void PrecomputeHashes(vector<long long> &H, const string& s, const string& t,
                        const long long& prime, const long long& multiplier){
    string S = t.substr(t.size()-s.size(),t.size()-1);
    H[t.size()-s.size()] = hash_func(S, prime, multiplier);

    long long y = 1;
    for (long long i = 0; i < s.size(); ++i){
        y = ( y * multiplier ) % prime;
    }
    for (long long i = t.size()-s.size()-1; i >= 0; --i){
        long long M = multiplier * H[i+1] + t[i] - y * t[i+s.size()];
        H[i] = mod(M,prime);
    }
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern;
    const string& t = input.text;
    vector<int> ans;

    if (s.length() > t.length())
        return ans;

    if (s.length() == t.length()){
        if (s == t) {
            ans.push_back(0);
        } 
        return ans;
    }

    vector<long long> Hashes(t.size()-s.size()+1);
    long long prime = 1000000007; 
    long long multiplier = 263;
    PrecomputeHashes(Hashes,s,t,prime,multiplier);

    long long pHash = hash_func(s,prime,multiplier);
    for (long long i = 0; i <= t.size() - s.size(); ++i){
        if (pHash != Hashes[i])
            continue;
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    unordered_map<long long, vector<string> > elems;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        int i = 0;
        if (query.type == "check") {
            int n = elems[query.ind].size();
            i = n - 1;
            while ( i >= 0 ){
                cout << elems[query.ind][i] << " ";
                --i;
            }
            cout << "\n"; 
        } else {
            bool was_found = 0;
            long long haskey = hash_func(query.s);
            unordered_map<long long ,vector<string> >::const_iterator 
                search = elems.find(haskey);
            if (search != elems.end()){
                int n = elems[haskey].size();
                while ( i < n ){
                    if (elems[haskey][i] == query.s){
                        was_found = 1;
                        break;
                    }
                    ++i;
                }
            }
            if (query.type == "find")
                writeSearchResult(was_found);
            else if (query.type == "add") {
                if (!was_found)
                    elems[haskey].push_back(query.s);
            } else if (query.type == "del") {
                if (was_found)
                    elems[haskey].erase(elems[haskey].begin()+i);
            }
        }
        // if (query.type == "check") {
        //     // use reverse order, because we append strings to the end
        //     for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
        //         if (hash_func(elems[i]) == query.ind)
        //             std::cout << elems[i] << " ";
        //     std::cout << "\n";
        // } else {
        //     vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
        //     if (query.type == "find")
        //         writeSearchResult(it != elems.end());
        //     else if (query.type == "add") {
        //         if (it == elems.end())
        //             elems.push_back(query.s);
        //     } else if (query.type == "del") {
        //         if (it != elems.end())
        //             elems.erase(it);
        //     }
        // }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

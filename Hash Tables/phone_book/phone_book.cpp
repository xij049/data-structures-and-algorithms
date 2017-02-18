#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    unordered_map<int, string> contacts;
    // vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i){
        int t_number = queries[i].number;
        unordered_map<int,string>::const_iterator was_founded = contacts.find(t_number);

        if (queries[i].type == "add") {
            contacts[t_number] = queries[i].name;

            // if ( was_founded == contacts.end() )
            //     contacts[t_number] = queries[i]
            // else

            // bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            // for (size_t j = 0; j < contacts.size(); ++j)
            //     if (contacts[j].number == queries[i].number) {
            //         contacts[j].name = queries[i].name;
            //         was_founded = true;
            //         break;
            //     }
            // otherwise, just add it
            // if (!was_founded)
            //     contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            if (was_founded != contacts.end())
                contacts.erase(t_number);     
            // for (size_t j = 0; j < contacts.size(); ++j)
            //     if (contacts[j].number == queries[i].number) {
            //         contacts.erase(contacts.begin() + j);
            //         break;
            //     }
        } else {
            string response = "not found";
            if (was_founded != contacts.end())
                response = contacts[t_number];
            result.push_back(response);
        }  
        //     string response = "not found";
        //     for (size_t j = 0; j < contacts.size(); ++j)
        //         if (contacts[j].number == queries[i].number) {
        //             response = contacts[j].name;
        //             break;
        //         }
        //     result.push_back(response);
        // }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}

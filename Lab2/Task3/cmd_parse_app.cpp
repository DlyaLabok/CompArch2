#include <iostream>
#include <getopt.h>
#include <vector>
#include <string>
#include <set>
void handleHelp() { std::cout << "Arg: Help" << std::endl; }
void handleVersion() { std::cout << "Arg: Version" << std::endl; }
void handleList() { std::cout << "Arg: List" << std::endl; }
int main(int argc, char *argv[]) {
    const struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"list", no_argument, 0, 'l'},
        {0, 0, 0, 0}
    };
    int option_index = 0;
    int c;
    std::set<char> found_options;
    opterr = 0; 
    while ((c = getopt_long(argc, argv, "hvl", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h': found_options.insert('h'); break;
            case 'v': found_options.insert('v'); break;
            case 'l': found_options.insert('l'); break;
            case '?': std::cerr << "Warning: Unknown option." << std::endl; break;
            default: break;
        }
    }
    for (char opt : found_options) {
        switch (opt) {
            case 'h': handleHelp(); break;
            case 'v': handleVersion(); break;
            case 'l': handleList(); break;
        }
    }
    return 0;
}

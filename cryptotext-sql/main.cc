// 
// File:   main.cc
// $Id: main.cc 78 2010-09-05 01:22:56Z df2417 $
//
//

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "misc_text_tools.h"
#include <cmath>
//#include <limit.h>

using namespace std;

string search_word; // global word to search for

// The callback function performs the operations on each row returned by
// sqlite3_exec(), if any ops need to be performed on a row.
// callback() is OPTIONAL

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    char *cipher;
    int len;
    unsigned char bloom_filter[BLOOM_SIZE] = {'\0'};
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

        unsigned char bloom_word[BLOOM_SIZE] = {'\0'};
        cipher = encrypt_word(search_word.c_str(), static_cast<char*>("cuenctest1"), &len);
        hash_encrypted_word_to_bloom(cipher, bloom_word);

        // DEBUG
        dump_bloom(bloom_word);

        // test membership
        for (int p = 0; p < BLOOM_SIZE; ++p) {
            bloom_filter[p] = argv[i][p];
        }

        if (test_bloom_membership(bloom_filter, bloom_word)) {
            cout << "Membership hit" << endl;
        } else {
            cout << "Membership miss" << endl;
        }
    }
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]) {
    sqlite3 *db; // Database handle
    char *zErrMsg = 0;
    int rc;
    //string search_word;                // word to search for
    //  lprof-specific variables follow
//    uint64_t cycles = 0,
//            br = 0,
//            br_last = 0,
//            brm = 0,
//            brm_last = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s DATABASE search-word\n", argv[0]);
        exit(1);
    }
    rc = sqlite3_open(argv[1], &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //
    // Initialize lprof
    //
//    lprof_init(3, EV_CYCLES, EV_BRANCH, EV_BRANCH_MISS);
//    __lp_stats.context_switches = 0;

    ifstream in(argv[2]);
    string line;
    while (getline(in, line)) {
        search_word += line; // read the lines from the SQL file into a single statement
    } // we assume a single word; everything else is ignored

    string sSqlQuery = "SELECT c8BloomFilter FROM MessagesFT_content"; // the callback will allow us to go row-by-row

    for (int i = 0; i < 10; i++) { // testing iterations for LiMiT purposes

        rc = sqlite3_exec(db, sSqlQuery.c_str(), callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }

    } // end for

//    lprof(1, cycles);
//    lprofd(2, br, br_last);
//    lprofd(3, brm, brm_last);
//
//    cout << "Cycles:        " << cycles << endl;
//    cout << "Branches:      " << br << endl;
//    cout << "Branch Misses: " << brm << endl;

    sqlite3_close(db);

    //
    // Close lprof
    //
//    lprof_close();

    return EXIT_SUCCESS;
}

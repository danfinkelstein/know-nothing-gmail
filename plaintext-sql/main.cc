//
// main.cc
//
// $Id: main.cc 81 2010-09-16 14:22:23Z df2417 $
//
//

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>

#ifdef LIMIT
#include <limit.h>		// LiMiT performance counters
#endif

using namespace std;

// The callback function performs the operations on each row returned by
// sqlite3_exec(), if any ops need to be performed on a row.
// callback() is OPTIONAL
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]) {
    sqlite3 *db;                // Database handle
    char *zErrMsg = 0;
    int rc;
    string sSql;                // SQL statement
//  lprof-specific variables follow
#ifdef LIMIT
    uint64_t cycles = 0, 
                 br = 0,
            br_last = 0,
                brm = 0,
           brm_last = 0;
#endif

    if (argc != 3) {
        fprintf(stderr, "Usage: %s DATABASE SQL-FILE\n", argv[0]);
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
#ifdef LIMIT
    lprof_init(3, EV_CYCLES, EV_BRANCH, EV_BRANCH_MISS);
    __lp_stats.context_switches = 0;
#endif


    ifstream in(argv[2]);
    string line;
    while (getline(in, line)) {
        sSql += line;           // read the lines from the SQL file into a single statement
    }

    // for (int i=0; i<300; i++) {   // testing iterations for LiMiT purposes

    rc = sqlite3_exec(db, sSql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    //} // end for

#ifdef LIMIT
    lprof(1, cycles);
    lprofd(2, br, br_last);
    lprofd(3, brm, brm_last);

    cout << "Cycles:        " << cycles << endl;
    cout << "Branches:      " << br << endl;
    cout << "Branch Misses: " << brm << endl;
#endif

    sqlite3_close(db);

//
// Close lprof
//
#ifdef LIMIT
    lprof_close();
#endif

    return EXIT_SUCCESS;
}

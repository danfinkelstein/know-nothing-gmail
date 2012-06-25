#include <lprof.h>
#include <map>
#include <algorithm>

using namespace std;

static map<string, unsigned int> EventMap;

static void initMap() {
// microarch neutral
    EventMap["CYCLES"] = EV_CYCLES;
    EventMap["REF_CYCLES"] = EV_REF_CYCLES;
    EventMap["INSTR"] = EV_INSTR;
    EventMap["INSTRUCTIONS"] = EV_INSTR;
    EventMap["BRANCHES"] = EV_BRANCH;
    EventMap["BPRED_MISS"] = EV_BRANCH_MISS;

// microarch specific
// FIXME: Good only for single-threaded execution. Add coherence and sync cntrs

    // I/O
    EventMap["IO_TXNS"] = I7_IO_TXNS;

    // Local DRAM
    EventMap["DRAM_REFS"] = I7_DRAM_REFS;

    // L3
    EventMap["L3_REFS"] = I7_L3_REFS;
    EventMap["L3_MISS"] = I7_L3_MISS;

    // L2 
    EventMap["L2_REFS"] = I7_L2_REFS;
    EventMap["L2_MISS"] = I7_L2_MISS;
	
    // inst supply 
    EventMap["IL1_HITS"] = I7_ICACHE_HITS;
    EventMap["IL1_MISS"] = I7_ICACHE_MISS;

    // data supply 
    EventMap["LOADS"] = I7_LOADS;
    EventMap["STORES"] = I7_STORES;

    // dl1_miss = l2_refs - Il1_miss

    EventMap["DL1_REFS"] = I7_DL1_REFS;
	
    // TLB miss
    EventMap["L2_DTLB_MISS"] = I7_L2_DTLB_MISS;
    EventMap["L2_ITLB_MISS"] = I7_L2_ITLB_MISS;

}

unsigned int get_event(string name) {
    if (EventMap.size() == 0)
	initMap();

    transform(name.begin(), name.end(), name.begin(), ::toupper);
    map<string, unsigned int>::iterator i =
	EventMap.find(name);

    if (i == EventMap.end()) {
	if (name.find("0X") == 0) {
	    return strtol(name.c_str(), NULL, 16);
	} else {
	    return 0;
	}
    }
    
    return i->second;
}

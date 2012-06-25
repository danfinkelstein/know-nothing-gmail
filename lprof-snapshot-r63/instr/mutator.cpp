#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include <ElfFile.h>

#include "InstrMutator.h"

using namespace std;

namespace po = boost::program_options;

string input_fn, output_fn, ipout_fn, addrout_fn;

int getOpts(int ac, char** av) {
    po::options_description opts("LProf Instrumentation Engine Options");
    opts.add_options()
	("help", "Show this help message")
	("input", po::value<string>(),
	 "Location of executable to instrument")
	("output", po::value<string>()->default_value(""),
	 "Filename for modified executable")
	("addrout",  po::value<string>()->default_value(""),
	 "Filename for list of instrumentation data addresses")
	("ipout",  po::value<string>()->default_value(""),
	 "Filename for list of instrumentation addresses");

    po::positional_options_description pd; 
    pd.add("input", 1).add("output", 2);

    po::variables_map vm;
    po::store(po::command_line_parser(ac, av).
	      options(opts).positional(pd).run(), vm);
    po::notify(vm);

    if (vm.count("help") || vm.count("input") == 0) {
	cout << "Usage:" << endl
	     << av[0] << " [options] <input file> [output file]" << endl
	     << opts << endl;
	return -1;
    }

    ipout_fn = vm["ipout"].as<string>();
    addrout_fn = vm["addrout"].as<string>();
    input_fn = vm["input"].as<string>();
    output_fn = vm["output"].as<string>();
    if (output_fn == "")
	output_fn = input_fn + ".instr";

    cout << "** Instrumenting \"" << input_fn << "\" and saving as \"" 
	 << output_fn << "\"." << endl << endl;
    return 0;
}

int intCompare(const void* a, const void*b) {
    return *((const uint64_t*)a) - *((const uint64_t*)b);
}

int doInstr(void) {
    int stepNumber = 0;
    TIMER(double t = timer());
    TIMER(double t1 = timer(), t2);

    ElfFile inFile((char*)input_fn.c_str());

    inFile.parse();
    TIMER(t2 = timer();PRINT_INFOR("___timer: Step %d Parse   : %.2f seconds",++stepNumber,t2-t1);t1=t2);

    inFile.initSectionFilePointers();
    TIMER(t2 = timer();PRINT_INFOR("___timer: Step %d Disasm  : %.2f seconds",++stepNumber,t2-t1);t1=t2);

    inFile.generateCFGs();
    TIMER(t2 = timer();PRINT_INFOR("___timer: Step %d GenCFG  : %.2f seconds",++stepNumber,t2-t1);t1=t2);   

    inFile.verify();
    TIMER(t2 = timer();PRINT_INFOR("___timer: Step %d Verify  : %.2f seconds",++stepNumber,t2-t1);t1=t2);

    InstrMutator elfInst(&inFile);

    elfInst.setPathToInstLib((char*)".");

    elfInst.phasedInstrumentation();
    PRINT_MEMTRACK_STATS(__LINE__, __FILE__, __FUNCTION__);
    elfInst.print(Print_Code_Instrumentation);
    TIMER(t2 = timer();PRINT_INFOR("___timer: Instrumentation Step %d Instr   : %.2f seconds",
				   ++stepNumber,t2-t1);t1=t2);

    elfInst.dump(output_fn.c_str());
    TIMER(t2 = timer();PRINT_INFOR("___timer: Instrumentation Step %d Dump    : %.2f seconds",++stepNumber,t2-t1);t1=t2);

    PRINT_INFOR("******** Instrumentation Successfull ********");

    TIMER(t = timer()-t;PRINT_INFOR("___timer: Total Execution Time          : %.2f seconds",t););

    if (ipout_fn != "") {
    	PRINT_INFOR("Writing list of instrumentation IPs");
	elfInst.instrumentationAddresses.sort(intCompare);
    	FILE* ipout = fopen(ipout_fn.c_str(), "w");
    	for (uint32_t i=0; i<elfInst.instrumentationAddresses.size(); i++) {
    	    fprintf(ipout, "0x%08lx\n", elfInst.instrumentationAddresses[i]);
    	}
    	fclose(ipout);
    	PRINT_INFOR("Done.");
    }

    if (addrout_fn != "") {
    	PRINT_INFOR("Writing list of instrumentation data addresses");
    	FILE* addrout = fopen(addrout_fn.c_str(), "w");
    	for (vector<uint64_t>::iterator i = elfInst.dataAddresses.begin();
	     i != elfInst.dataAddresses.end(); i++) {
    	    fprintf(addrout, "0x%08lx\n", *i);
    	}
    	fclose(addrout);
    	PRINT_INFOR("Done.");
    }

    return 0;
}

int main(int argc, char** argv) {
    int rc;
    if (rc = getOpts(argc, argv)) {
	return rc;
    }

    if (rc = doInstr()) {
	return rc;
    }
    return 0;
}

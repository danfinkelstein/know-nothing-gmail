// match - linear time string match algorithm
// David Eppstein / Columbia University / 29 Jan 1988
//
// Only performs exact matches, not comparisons.
// Caller is responsible for case sensitivity or lack thereof.

class string_match {
    const char * target;	// string we are looking for
    int index;			// index into target; how much matched so far
    int * retarget;		// what to set match to when mismatch found

 public:
    string_match(const char *, int = -1);
	// set up to start matching target string given in first arg
	// second arg is length of string, default whole string up to null

    ~string_match() { delete target; delete retarget; }

    void reset() { index = 0; }
    int match(char c);		// adds c to match; returns nz if all matched
};

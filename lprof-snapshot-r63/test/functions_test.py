#!/usr/bin/python

numfuncs = 100

print """
double d = 9.0;

void bar(void) {
  d = 9.0;
}
"""

for i in range(numfuncs):
    print """
void foo%d(void) {
  bar();
  d *= 5.0;
  d -= d;
  d *= d;
}""" % i

print """
int main(void) {
  unsigned long i;
  """
print """for (i=0; i<1000; i++) {"""
for i in range(int(numfuncs/2)):
    print "    foo%d();" % i
print """  }"""

print """for (i=0; i<1000; i++) {"""
for i in range(int(numfuncs)):
    print "    foo%d();" % i
print """  }"""

print """
  puts("Done");
  return 0;
}
"""


CXXFLAGS = -std=c++11 -Wall -Wreturn-type -Wunused -Wswitch -Wcomment -Wuninitialized -Wparentheses -Wpointer-arith -Werror

sps: sps.cxx
	g++ -o sps sps.cxx $(CXXFLAGS)

clean:
	rm -f sps *.o

CXX=g++
CCLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11
RM=-rf *.o firewall.exe libfirewall.so

IP=ip.o ip.cpp ip.h
PORT=port.o port.cpp port.h
STR=string.o string.cpp string.h
STR_A=string-array.o string-array.cpp string-array.h
OBJS=ip.o port.o string.o string-array.o
LIB=-linput -lfirewall -L.
EXEC=firewall.exe

$(EXEC): $(OBJS) main.o libfirewall.so
	$(CCLINK) $(CXXFLAGS) main.o -o $(EXEC) $(LIB)

libfirewall.so: $(OBJS)
	$(CCLINK) -shared $(OBJS) -o libfirewall.so $(LIB)

main.o: main.cpp port.h ip.h input.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

port.o: port.cpp port.h generic-field.h string-array.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

ip.o: ip.cpp ip.h generic-field.h string-array.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

string.o: string.cpp string.h generic-string.h string-array.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

string-array.o: string-array.cpp string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c -fpic string-array.cpp

clean:
	rm $(RM)
spider: 
	g++ -MMD -ggdb  -std=c++11 -Wall -lcurl -o spider jsoncpp.cpp global.cpp spider.cpp main.cpp


install: spider

clean:
	rm *.d
	rm -rf *.dSYM
	rm spider


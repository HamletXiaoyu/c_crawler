#	g++ -o spider -L/curl_lib_path -lcurl -L/abc_path -labc  jsoncpp.o global.o spider.o main.o
# 	g++ -o jsoncpp.o -I/json_include_path -c jsoncpp.cpp
all : spider
spider: jsoncpp.o global.o spider.o main.o
	g++ -o spider -lcurl jsoncpp.o global.o spider.o main.o

jsoncpp.o : jsoncpp.cpp
	g++ -o jsoncpp.o -I./include/json -c jsoncpp.cpp

global.o : global.h global.cpp
	g++ -o global.o -c global.cpp

spider.o : spider.h spider.cpp
	g++ -o spider.o -c spider.cpp

main.o : main.cpp
	g++ -o main.o -c main.cpp

install: all

.PHONY : clean
clean:
	-rm *.o
	-rm spider


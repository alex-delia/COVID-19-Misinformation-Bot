build:
	g++ main.cpp twitter.cpp twitter.h covid.cpp covid.h -ltwitcurl -lcurl
test:
	g++ main.cpp twitter.cpp twitter.h covid.cpp covid.h -ltwitcurl -lcurl
	./a.out
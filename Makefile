build:
	g++ main.cpp twitter.cpp twitter.h covid.cpp covid.h newsArticles.cpp newsArticles.h -ltwitcurl -lcurl -std=c++11
test:
	g++ main.cpp twitter.cpp twitter.h covid.cpp covid.h newsArticles.cpp newsArticles.h -ltwitcurl -lcurl -std=c++11
	./a.out
daily:
	g++ main.cpp twitter.cpp twitter.h covid.cpp covid.h newsArticles.cpp newsArticles.h -ltwitcurl -lcurl -std=c++11
	./a.out

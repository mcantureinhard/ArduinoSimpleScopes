.PHONY: test
test: test.cpp
	g++ -Wall -g test.cpp SimpleScopes.cpp -o test
	./test
	rm test

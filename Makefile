zipluac:
	g++ -lsnappy -std=c++11 zipluac.cpp -o zipluac

.PHONY: clean
clean:
	rm zipluac

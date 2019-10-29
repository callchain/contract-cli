zipluac:
	g++ -llz4 zipluac.cpp -o zipluac

.PHONY: clean
clean:
	rm zipluac

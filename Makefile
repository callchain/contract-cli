contract-tools:
	g++ -llz4 main.cpp -o contract-tools

.PHONY: clean
clean:
	rm contract-tools

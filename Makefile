minimal.o: minimal.c
	clang -c -g -O2 -target bpf $< -o $@

.PHONY: clean
clean:
	rm minimal.o

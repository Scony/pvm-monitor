all:
	g++ *.cpp -lpvm3
install:
	cp a.out ../../bin/LINUX64/demo
clean:
	rm -f *.out *~

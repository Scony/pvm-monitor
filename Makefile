ARCH=$(shell pvmgetarch)

all:
	g++ *.cpp -lpvm3
install:
	cp a.out ../../bin/$(ARCH)/demo
clean:
	rm -f *.out *~

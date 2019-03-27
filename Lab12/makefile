lab12 : carrL12.o card.o
	g++ -o lab12 carrL12.o card.o -g

carrL12.o : carrL12.cpp LList2.hpp card.h
	g++ -c carrL12.cpp -g -w

card.o : card.cpp card.h
	g++ -c card.cpp -g

clean :
	rm -f core.* *.o lab12


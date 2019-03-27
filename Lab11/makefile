L11.out : FractionTest.o Fraction.o
	g++ -o L11.out FractionTest.o Fraction.o -g

FractionTest.o : FractionTest.cpp LList2.hpp Fraction.h
	g++ -c FractionTest.cpp -g

Fraction.o : Fraction.cpp Fraction.h
	g++ -c Fraction.cpp -g

clean :
	rm -f core.* *.o L11.out


output: Similarities.o Stemmer.o
	gcc Similarities.o Stemmer.o -lm -o SimilarityScore
Similarities: Similarities.c Stemmer.h
	gcc -c Similarities.c -lm
Stemmer: Stemmer.c Stemmer.h
	gcc Stemmer.c

CC = gcc
CFLAGS = -g
Objects = main.o hashTable.o patientRecords.o BinaryTree.o RedBlackTree.o DiseaseMonitor.o MaxHeap.o

diseaseMonitor : $(Objects)
	$(CC) $(CFLAGS) $(Objects) -o diseaseMonitor

main : $(Objects)
	$(CC) $(CFLAGS) main.c -o main.o -c

hashTable : $(Objects)
	$(CC) $(CFLAGS) hashTable.c -o hashTable.o -c

patientRecords : $(Objects)
	$(CC) $(CFLAGS) patientRecords.c -o patientRecords.o -c

BinaryTree : $(Objects)
	$(CC) $(CFLAGS) BinaryTree.c -o BinaryTree.o -c

RedBlackTree : $(Objects)
	$(CC) $(CFLAGS) RedBlackTree.c -o RedBlackTree.o -c

DiseaseMonitor : $(Objects)
	$(CC) $(CFLAGS) DiseaseMonitor.c -o DiseaseMonitor.o -c

MaxHeap : $(Objects)
	$(CC) $(CFLAGS) MaxHeap.c -o MaxHeap.o -c

clean :
	rm diseaseMonitor $(Objects)

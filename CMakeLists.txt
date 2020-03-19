cmake_minimum_required(VERSION 3.15)
project(COVID_19 C)

set(CMAKE_C_STANDARD 99)

add_executable(COVID_19 main.c hashTable.c hashTable.h patientRecords.c patientRecords.h BinaryTree.c BinaryTree.h RedBlackTree.c RedBlackTree.h DiseaseMonitor.c DiseaseMonitor.h MaxHeap.c MaxHeap.h)
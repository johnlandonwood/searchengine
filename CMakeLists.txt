cmake_minimum_required(VERSION 3.14)
project(search-engine)
set (EXE_NAME search_engine)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

#set ()

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS_DEBUG "-O3")
add_executable(${EXE_NAME} main.cpp Node.h AVLTree.h HashTable.h UserInterface.cpp UserInterface.h InvertedIndexEntry.cpp InvertedIndexEntry.h InvertedIndex.cpp InvertedIndex.h DocumentProcessor.cpp DocumentProcessor.h QueryProcessor.cpp QueryProcessor.h IndexHandler.cpp IndexHandler.h)

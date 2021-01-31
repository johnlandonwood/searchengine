# Search Engine

This is the final project for SMU's CS 2341 (Data Structures) class. It was done as a partner programming assignment with another student, Maria Harrison.

It is a rudimentary search engine, designed to comb through a number of COVID-19 research articles, constructing an inverted file index (stored as an AVL tree) and a hash table to store information about an article's author. The user can then input queries using simple boolean operators to find documents that contain specific words. The engine also writes and saves persistence files; upon execution, if persistence files exist within the directory from a previous execution, then the engine can load those for faster construction of the two main data structures. The engine also records several statistics, such as the number of unique articles indexed, the average words indexed per article, etc.

I wrote the following classes:
- UserInterface: A basic interface for the user to input commands. Allows the user to:
  - Clear the inverted file index and author hash table,
  - Populate the index and hash table from scratch, also creating new persistence files,
  - Populate the index and hash table with existing persistence files,
  - Enter a search query, or
  - Output engine statistics.
- DocumentProcessor: Parses .json documents and a metadata .csv file.
  - Utilizes the std::filesystem library to iterate through all documents in the corpus.
  - Utilizes RapidJSON, a C++ .json parsing library, to record words and authors that appear in each document within the corpus
  - Utilizes the Oleander Stemming library. This allows us to avoid bloating the inverted file index with grammatical modifications of words. For example, "running" will not be added, only its stem "run" will.
  - Communicates with the IndexHandler to add processed document's information to the data structures
- IndexHandler: Instantiates a "singleton" instance of the inverted file index and authors hash table.
  - Interfaces with the index and hash table to add words or authors.
  - Runs a user-inputted query and returns a set of relevant documents.
  - Loads saved persistence files. 
  - Retrieves the engine's statistics.
- HashTable: a templated hash table.
  - Stores an author's name and the documents that they have written.
  - Uses separate chaining. 
  
The C++ std library is extensively used throughout the project. Specifically, std::set, std::filesystem, and std::pair were of great use to me.
We used Doxygen to document all of our classes, and created a UML class diagram for our professor's viewing.

- Doxygen-generated documentation site is saved under the Documentation folder as `index.html` 
- UML Class Diagram is saved in source directory as `Search Engine UML Class Diagram.jpg`

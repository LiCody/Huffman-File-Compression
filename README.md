# Huffman-File-Compression
From the starting text file, the program counts the frequency of each character in the text file and generates a binary tree with leaves of higher frequency near the top and leaves of lower frequency near the bottom. Then, by recursively traversing the tree we generate the binary paths which we then use with a hashtable to convert the characters to their binary paths. We then utilize bit-wise operations to turn the binary into ASCII characters effectively compressing our text file.
Project was created in CodeBlocks

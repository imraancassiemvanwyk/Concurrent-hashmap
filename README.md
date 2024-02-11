# concurrent hashmap

This implementation of a concurrent hashmap was made because i got the inspiration while doing another project
and finding out that std::unordered map is not thread safe so i tried my own take on the hashmap that is thread safe as long as the 
read/write is done on the same bucket 

Randomised insert ~ 1 million inserts in 2700 microseconds

# Iterator categories

There are several types of iterator as following:
- **Input/output iterator** read/write each element once, advance data streams, e.g. writing/reading data to/from a network socket.

- **Forward iterator** read/write each element repeatedly, advance singly-linked list, e.g. std::forward_list

- **Bidirectional iterator** forward iterator + move back doubly-linked list, e.g. std::list, std::map, std::set.

- **Random access iterator** bidirectional iterator + advance and move back by any integer and calculate distance between two iterators, multi-array data structures, e.g. std::deque.

- **Continuous iterator** random access iterator + the storage of elements is contiguous arrays, e.g. std::vector.
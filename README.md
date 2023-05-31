# The C Bit Field Challenge

The challenge is to create a system that represents a simple data packet for a
communication protocol. Each data packet contains the following information:

1. A 4-bit field type that represents the type of the packet. There are four
types of packets: data (0), acknowledgment (1), control (2), and error (3).
2. A 10-bit field seq_num that represents the sequence number of the packet.
3. A 16-bit field data that represents the data of the packet. For simplicity,
we can assume that the data is a 16-bit unsigned integer.
4. A 2-bit field checksum that represents a simple checksum of the packet. For
simplicity, the checksum can be the XOR of the type, seq_num, and data.  

Write a program that:

1. Defines a struct with the above bit fields.
2. Writes a function create_packet that takes as input the type, sequence
number, and data, and returns a data packet with the correct checksum.
3. Writes a function validate_packet that takes as input a data packet,
recalculates the checksum, and returns true if the recalculated checksum matches
the checksum in the packet, false otherwise.

Keep in mind that the total size of the bit fields is 32 bits, which can fit into a uint32_t. However, the order of the bit fields can depend on the system's endianness, so be careful when interpreting the data packet.

---

To validate this challenge:

```bash
# Log into your WSL Linux distribution and run the commands
# in your preferred shell

python3 -m venv .venv
source .venv/bin/activate
pip install -e .

try tests

```

**Hint**: To check endianness consider this code:

```c
int is_big_endian() {
    int num = 1;
    if(*(char *)&num == 1) {
        return 0; // Little Endian
    } else {
        return 1; // Big Endian
    }
}
```

In the above function, we create an integer with a value of 1. If the system is
little-endian, the least significant byte will be the 1 and the rest will be 0s.
If the system is big-endian, the most significant byte will be the 1, and the
rest will be 0s. When we cast the integer to a char (which is 1 byte), we'll get
the first byte. If it's 1, we know the system is little-endian, and if it's 0,
the system is big-endian.


**Hint**:  The ``<arpa/inet.h>`` library contains functions for converting the
endianes of variables.  This is useful, because a packet needs to be converted
to big-endian before it's put out on the wire.  How it is managed on the
hardware is dependant on what platform the C code has been build upon.

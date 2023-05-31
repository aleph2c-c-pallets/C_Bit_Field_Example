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

Keep in mind that the total size of the bit fields is 32 bits, which can fit
into a uint32_t. However, the order of the bit fields can depend on the system's
endianness, so be careful when interpreting the data packet.

---

To validate this challenge:

```bash
# read test/bitfield_test.c to confirm the tests meet the challenge
cd build

# create the make file
cmake ..

# build the binary and test-binary
make

# run the test binary and confirm all tests pass
ctest --output-on-failure

# review the code organization below and assess whether the
# files adhere to a sufficiently high standard.
```

Code organization:

- ``main.c``: main.c for debug build used by ``./build/bitfield`` binary
- ``test/main.c``: main.c for test build used by ctest
- ``src/bitfield.c``: **the package that answers the challenge**
- ``inc/common.h``: common header files used by all packages
- ``inc/bitfield.h``: public interface for ``bitfield.c`` 
- ``test/bitfield_test.h``: public interface for the tests
- ``test/bitfield_test.c``: CMocka test code to evaluate ``src/bitfield.c``

---

This project was created using the [c_beachhead](https://github.com/aleph2c/c_beachhead)

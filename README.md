# Network_Sniffing

**#Low level Raw_Packet sniffer

Packet sniffer program which uses Raw sockets. Sniffs packets on unswitched networks picking up Ethernet packets. The packets picked up depend on the the protocol the user wants to sniff, such as TCP,UDP,ICMP or RAW.

**#Compiling & Running 

*NOTE*:Running with super user privlages because raw sockets have no protocol(Allowing the user to create their own) and can be used for malicious purposes.

gcc -o sniff raw_sniffing.c

sudo ./sniff -tcp (or)

sudo ./sniff -udp (or)

sudo ./sniff -icmp (or)

sudo ./sniff -raw 

The memory is then dumped into hexadecimal form for the packets recieved. However if you wish to store in a file for packet decoding or analysis then:

sudo ./sniff > file.txt

Written as a learning excercise

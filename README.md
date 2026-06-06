Really simple DNS lookup written in c. This project has been inspired by https://youtu.be/CHaEdVIF2_M?si=qZRwH_HwCgSAu4-2 (Many tanks to Daniel Hirsch for his content). 


Usage: just compile it with gcc
Example: gcc -o dns dns.c
You can run it passing one argument, the hostname.

e.g

./dns google.com

IP address for google.com
Family: IPv4
Address: 142.251.27.100
Protocol used: TCP
-----------------------------------------------------
Family: IPv4
Address: 142.251.27.100
Protocol used: UDP
-----------------------------------------------------


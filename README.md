# myadif

use: myadif 

input: /Users/gmazzini/Downloads/log.txt

input specification: yyyymmdd hhmm call freq(in KHz) rst_sent rst_rcvd

with "-" in yyyymmdd the date is set to the last qso

with "-" in freq the frequency is set to the last qso

with A in front of rst_sent the mode is set to ARQ

with R in front of sst_sent the mode is set to RTTY

with F in front of sst_sent the mode is set to FM

note that for contest operation it is possibile to enter in freq the string Mxxx_Czzz to indicate the band in meters xxx and the contest name zzz

optionally, at the end of the call, you can put:
!s for qsl sent, 
!r for qsl received,
!b for sql sent and received.

output: /Users/gmazzini/Downloads/log.adif

output specification: http://www.adif.org.uk/304/ADIF_304.htm

compile: gcc -Wunused -o myadif myadif.c

download: curl https://raw.githubusercontent.com/gmazzini/myadif/master/myadif.c > myadif.c

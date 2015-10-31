# myadif

use: myadif 

input: /Users/gmazzini/Downloads/log.txt

input specification: yyyymmdd hhmm call freq(in KHz) rst_sent rst_rcvd

note that "-" in yyyymmdd report the date of last qso

note that "-" in freq report the frequency of last qso

note that in freq instead of the frequenty in KHz you can simply enter Mxx, to just indicate the band in meters xx, quite useful for contest without indication redarding frequency

optionally, at the end of the call, you can put:
!s for qsl sent, 
!r for qsl received,
!b for sql sent and received.

output: /Users/gmazzini/Downloads/log.adif

output specification: http://www.adif.org.uk/304/ADIF_304.htm

compile: gcc -Wunused -o myadif myadif.c

download: curl https://raw.githubusercontent.com/gmazzini/myadif/master/myadif.c > myadif.c

# myadif

use: myadif 

input: /Users/gmazzini/Downloads/log.txt

input specification: yyyymmdd hhmm call freq(in KHz) rst_sent rst_rcvd

output: /Users/gmazzini/Downloads/log.adif

output specification: http://www.adif.org.uk/304/ADIF_304.htm

compile: gcc -Wunused -o myadif myadif.c

download: curl https://raw.githubusercontent.com/gmazzini/myadif/master/myadif.c > myadif.c

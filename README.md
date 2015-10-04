# myadif

specification http://www.adif.org.uk/304/ADIF_304.htm

use: myadif 

read file /Users/gmazzini/Downloads/log.txt

output adif /Users/gmazzini/Downloads/log.adif

compile: gcc -Wunused -o myadif myadif.c

download: curl https://raw.githubusercontent.com/gmazzini/myadif/master/myadif.c > myadif.c

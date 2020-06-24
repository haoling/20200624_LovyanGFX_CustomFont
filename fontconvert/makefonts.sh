#!/bin/bash

# Ugly little Bash script, generates a set of .h files for GFX using
# GNU FreeFont sources.  There are three fonts: 'Mono' (Courier-like),
# 'Sans' (Helvetica-like) and 'Serif' (Times-like); four styles: regular,
# bold, oblique or italic, and bold+oblique or bold+italic; and four
# sizes: 9, 12, 18 and 24 point.  No real error checking or anything,
# this just powers through all the combinations, calling the fontconvert
# utility and redirecting the output to a .h file for each combo.

# Adafruit_GFX repository does not include the source outline fonts
# (huge zipfile, different license) but they're easily acquired:
# http://savannah.gnu.org/projects/freefont/

convert=./fontconvert
inpath=./Fonts/
outpath=../include/Fonts/
sizes=(5 6 8 9 10 12 18 24)

for infile in $(ls $inpath); do
	filename=$(basename $infile)
	filename=${filename%.*}

	for si in ${sizes[*]}
	do
		if [ -f $inpath$infile ] # Does source combination exist?
		  then
			outfile=$outpath$filename$si"pt8b.h"
			#printf "%s %s %s > %s\n" $convert $infile $si $outfile
			$convert $inpath$infile $si > $outfile
			varname=$(echo $filename | sed -e 's/-/_/g')
			constname=$(echo $varname | sed -e 's/\([a-z]\)/\U\1/g')
			printf "%s,%s%spt8b,Fonts/%s%spt8b.h,NULL,%s%s_8,GSLC_FONTREF_PTR,&%s%spt8b,1,SansSerif,%s,PLAIN\n" $filename $varname $si $filename $si $constname $si $varname $si $si
		fi
	done
done

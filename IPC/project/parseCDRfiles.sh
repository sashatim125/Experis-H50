#!
declare -a cdrFiles
ls cdr_in/ > cdrs.tmp
mapfile cdrFiles < cdrs.tmp
for ((i=0; i<${#cdrFiles[@]}; i++))
do
	parserMain ${cdrFiles[$i]}
done
rm -f cdrs.tmp



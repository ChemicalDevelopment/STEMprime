# STEMprime
Mersenne prime testing done quickly! 

With compiled file stemprime.out, or stemprime.exe, you can run:
"stemprime.out <exp>"
and it tests wether 2^exp - 1 is infact a prime. Definite test using lucas-lehmer sequence.

#Building
You will need GMP (GNU MP Lib) to use this program. You can download it here: https://gmplib.org/
My personal build file I use:
`echo "Building stemprime..."
gcc ~/Documents/stemprime/stemprime.c -lgmp -lm -o ~/Documents/builds/STEMprime.out
echo "done"`
Then use `~/Documents/builds/STEMprime.out <exp>` to run!

#Easier use
My bash file I use as quick command "stemprime <x>" from terminal is:
`
#Init vars used
RED='\033[1;31m'
L_CY='\033[1;36m'
L_PR='\033[1;35m'
YEL='\033[1;33m'
GRN='\033[0;32m'
NC='\033[0m' # No Color
printf "\n"

printf  "${L_PR}|             ${RED}STEMprime  ${YEL}~  ${RED}Cade Brown            ${L_PR}|\n"
printf "${L_CY}"
STARTTIME=$(date +%s)
~/Documents/builds/STEMprime.out $1
ENDTIME=$(date +%s)
printf "                       ${YEL}$(($ENDTIME - $STARTTIME))${NC}${RED}s                       \n${NC}"

printf "\n"
`
This colorizes output, and locate this as "stemprime" in your ~/bin/ folder (or wherever PATH references) for a quick cmd.

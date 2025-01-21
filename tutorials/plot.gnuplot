
set ylabel 'CPU time [sec]' font "Times-Roman,18"
set xlabel 'Time [sec]' font "Times-Roman,18"
set key font ",18"
set key left top
set xtics font ", 16"
set ytics font ", 16"


## Solution Speed ******************************************************
#First test case (single region for fluid and single region for solid)

#set title "singleCavity-caseA" font  "Times-Roman,15"
set terminal pdf
set output "./results/Fig9-singleCavity-caseA.pdf"
plot "solution-time/SIPM-IP/singleCavity/momPred/caseA/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/singleCavity/momPred/caseA/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/singleCavity/momPred/caseA/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",

set terminal pdf 
#set title "singleCavity-caseB" font  "Times-Roman,15"
set output "./results/Fig9-singleCavity-caseB.pdf"
plot "solution-time/SIPM-IP/singleCavity/momPred/caseB/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/singleCavity/momPred/caseB/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/singleCavity/momPred/caseB/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",

set terminal pdf 
#set title "singleCavity-caseC" font  "Times-Roman,15"
set output "./results/Fig9-singleCavity-caseC.pdf"
plot "solution-time/SIPM-IP/singleCavity/momPred/caseC/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/singleCavity/momPred/caseC/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/singleCavity/momPred/caseC/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",

set terminal pdf 
#set title "singleCavity-caseD" font  "Times-Roman,15"
set output "./results/Fig9-singleCavity-caseD.pdf"
plot "solution-time/SIPM-IP/singleCavity/momPred/caseD/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/singleCavity/momPred/caseD/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/singleCavity/momPred/caseD/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",




#Second test case (three regions for fluid and three regions for solid)

#set title "threeCavity-caseA" font  "Times-Roman,15"
set terminal pdf
set output "./results/Fig13-threeCavity-caseA.pdf"
plot "solution-time/SIPM-IP/threeCavity/momPred/caseA/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/threeCavity/momPred/caseA/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/threeCavity/momPred/caseA/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",

set terminal pdf 
#set title "threeCavity-caseB" font  "Times-Roman,15"
set output "./results/Fig13-threeCavity-caseB.pdf"
plot "solution-time/SIPM-IP/threeCavity/momPred/caseB/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/threeCavity/momPred/caseB/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/threeCavity/momPred/caseB/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",

set terminal pdf 
#set title "threeCavity-caseC" font  "Times-Roman,15"
set output "./results/Fig13-threeCavity-caseC.pdf"
plot "solution-time/SIPM-IP/threeCavity/momPred/caseC/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/threeCavity/momPred/caseC/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/threeCavity/momPred/caseC/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",

set terminal pdf 
#set title "threeCavity-caseD" font  "Times-Roman,15"
set output "./results/Fig13-threeCavity-caseD.pdf"
plot "solution-time/SIPM-IP/threeCavity/momPred/caseD/convergenceTime.xls" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/threeCavity/momPred/caseD/convergenceTime.xls" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/threeCavity/momPred/caseD/convergenceTime.xls" title 'SIPM-M' with lines dt 1 lw 4 lc "black",



## Validation ******************************************************

#single region for fluid and single region for solid

set terminal pdf 
#set title "validation-caseA" font  "Times-Roman,15"
set output "./results/Fig7-validation-caseA.pdf"
plot "validation/refCaseA.xy" title 'Ref' pointtype 8 lc 'blue', \
     "validation/SIPM-IP/caseA/TatYLine_T.xy" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "validation/SIPM-SP/caseA/TatYLine_T.xy" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "validation/SIPM-M/caseA/TatYLine_T.xy" title 'SIPM-M' with lines dt 1 lw 4 lc "black"

set terminal pdf 
#set title "validation-caseB" font  "Times-Roman,15"
set output "./results/Fig7-validation-caseB.pdf"
set xrange [0:]
plot "validation/refCaseB.xy" title 'Ref' pointtype 8 lc 'blue', \
     "validation/SIPM-IP/caseB/TatYLine_T.xy" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "validation/SIPM-SP/caseB/TatYLine_T.xy" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "validation/SIPM-M/caseB/TatYLine_T.xy" title 'SIPM-M' with lines dt 1 lw 4 lc "black"
unset xrange

set terminal pdf 
#set title "validation-caseC" font  "Times-Roman,15"
set output "./results/Fig7-validation-caseC.pdf"
plot "validation/refCaseC.xy" title 'Ref' pointtype 8 lc 'blue', \
     "validation/SIPM-IP/caseC/TatYLine_T.xy" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "validation/SIPM-SP/caseC/TatYLine_T.xy" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "validation/SIPM-M/caseC/TatYLine_T.xy" title 'SIPM-M' with lines dt 1 lw 4 lc "black"
     


#three regions for fluid and three regions for solid (case A)

set key right top
set terminal pdf 
#set title "TatXLine-threeRegions-caseA" font  "Times-Roman,15"
set output "./results/Fig12-TatXLine-threeRegions-caseA.pdf"
plot "solution-time/SIPM-IP/threeCavity/momPred/caseA/TatXLine_T.xy" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/threeCavity/momPred/caseA/TatXLine_T.xy" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/threeCavity/momPred/caseA/TatXLine_T.xy" title 'SIPM-M' with lines dt 1 lw 4 lc "black"

set key left top
set terminal pdf 
#set title "TatYLine-threeRegions-caseA" font  "Times-Roman,15"
set output "./results/Fig12-TatYLine-threeRegions-caseA.pdf"
plot "solution-time/SIPM-IP/threeCavity/momPred/caseA/TatYLine_T.xy" title 'SIPM-IP' with lines dt 3 lw 4 lc "red", \
     "solution-time/SIPM-SP/threeCavity/momPred/caseA/TatYLine_T.xy" title 'SIPM-SP' with lines dt 2 lw 4 lc "blue", \
     "solution-time/SIPM-M/threeCavity/momPred/caseA/TatYLine_T.xy" title 'SIPM-M' with lines dt 1 lw 4 lc "black"


## Comparsion between conjugateheatFoam and SIPM-M solvers

#single region for fluid and single region for solid

set terminal pdf 
#set title "caseA-{/Symbol D}t=0.0025s" font  "Times-Roman,15"
set output "./results/Fig8-caseA-dt=0.0025s.pdf"
plot "validation/refCaseA.xy" title 'Ref' pointtype 8 lc 'blue', \
     "Accuracy/conjugateHeatFoam/caseA-dt=0.0025s/TatYLine_T.xy" title 'conjugateHeatFoam' with lines dt 2 lw 4 lc "red", \
     "Accuracy/SIPM-M//caseA-dt=0.0025s/TatYLine_T.xy" title 'SIPM-M' with lines dt 1 lw 4 lc "black"

set terminal pdf 
#set title "caseA-{/Symbol D}t=0.005s" font  "Times-Roman,15"
set output "./results/Fig8-caseA-dt=0.005s.pdf"
plot "validation/refCaseA.xy" title 'Ref' pointtype 8 lc 'blue', \
     "Accuracy/conjugateHeatFoam/caseA-dt=0.005s/TatYLine_T.xy" title 'conjugateHeatFoam' with lines dt 2 lw 4 lc "red", \
     "Accuracy/SIPM-M/caseA-dt=0.005s/TatYLine_T.xy" title 'SIPM-M' with lines dt 1 lw 4 lc "black"


     


     

#pause -1
#reread 

#!/bin/bash
export LC_ALL=C # Cambia la codificacion local a ingles, asi el seq nos pone "." en vez de "," en los decimales


for alpha0 in $(seq 3 0.1 7); do
    echo -ne "Valor de alpha0= $alpha0 "
    scripts/run_vad.sh $alpha0 | grep TOTAL  # ponemos | grep TOTAL para quedarnos solo con el Total. Quitarlo para ver todo (mucho texto)
done
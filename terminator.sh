#!/bin/bash

#for p in `ipcs -b -m | egrep ^m | awk '{ print $2; }'`; do ipcrm -m $n; done

set -xe

for p in `pgrep atom`
do
    kill p
done

for p in `pgrep activator`
do
    kill p
done

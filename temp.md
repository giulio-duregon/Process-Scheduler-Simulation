Some tips on how to run this.

Untar the reference output

created with running ./runit.sh refout_vp sched

```bash
 > tar -xzvf refout.tar.Z
 ```

Optional Untar the verbose reference output
created with running 

```bash
> ./runit.sh refout_vp sched -v -p
```

```bash
> tar -xzvf refout_vp.tar.Z
```

# make a outputdir

```bash
> mkdir outputdir
> ./runit.sh outputdir ../src/sched
```

Compare outputs with reference output make sure that the frefout is the first argument because we are putting the LOG.txt into the outputdir

```bash
./gradeit.sh refout outputdir
```

You might get something like this.

```bash
# creates your outputs
frankeh@NYU2 > ./runit.sh ./studx ../src/mysched     
```

```
frankeh@NYU2 > ./gradeit.sh ./refout ./studx
in    F    L    S   R2   R5   P2   P5:3 E2:5 E4
00    1    1    0    1    1    1    1    1    1
01    1    1    1    1    1    1    1    1    1
02    1    1    1    1    1    1    1    1    1
03    1    1    1    1    1    1    1    1    1
04    1    1    1    1    1    1    1    1    1
05    1    1    1    1    1    1    1    1    1
06    1    1    1    1    1    1    1    1    1

SUM   7    7    6    7    7    7    7    7    7
62 out of 63 correct
```

You have to inspect what goes wrong .. you see that input0 algo "S" failed
Go to studx/LOG.txt which will only show the command and SUM lines.
The SUM might be correct, but there are differences. Execute the diff command
listed manually and you will see all differences

```
frankeh@NYU2 > diff ./refout/out_0_S ./studx/out_0_S
2,4c2,4

< 0000:    0  100   10   10 2 |   201   201   101     0
< 0001:  500  100   20   10 4 |   627   127    27     0
< SUM: 627 31.90 20.41 164.00 0.00 0.319
---
>
> 0000:    0  100   10   10 2 |   209   201   101     0
> 0001:  500  100   20   10 4 |   622   127    27     0
> SUM: 627 31.90 20.41 164.00 0.00 0.301
```
In that case you need to inspect the outputs and determine why you get
different results.
You might want to run with -v option and compare in detail one particular
output and go from there. The -v references are provided in ./refout_v

```bash
# creates your outputs with -v option
frankeh@NYU2 > ./runit.sh ./studx ./src/mysched -v  
```

Finally:

Please go back to the first class and the projects /home/frankeh/Public/ProgExamples/Format
to see how to properly format C and C++ output to avoid rounding errors etc.
# 442-HW-2


## Part 1: benchmarking.
Relevent Files:

bench\_mark\_test.c (the core code for testing)
bench\_mark\_test (the compiled C code using gnu99 on linux)

Description: 

In order to test the latency for the different catche sizes I conducted the following expriment as instructed. I created a c program which tests the latency of a read of a single byte from a buffer of size N ranging from 2^10 to 2^26. One issue I encountered right away I had to make a comprimise between prefetching and being able to include reasonable data about the first two catches. The issue here was that with optimizations (flag -O3) I didn't not get data that reflected the theory so I worked towards the goal of avoiding the prefetching. The trick was to fake a dependency between iterations of the primary looping inside the "testing" function. The time of each of additional operations was constant however so it did not play a role a large role in my data in the l3 and DRAM memory but unfortatunately in doing this my data all ended up in either the l3 or DRAM of my test machine (linux boxes in math lab). I also clearly was losing the last two digits of my output data due to casting. In the main loop there is an instance of "testing(2^10)" that runs 50 times before the actual data is calculated. This is because there were clearly some items that were being stored in memory (likey the constants I use in each iteration are getting stored to l1-l2 catche) the first instance that dramatically impacts the performance. By throwing these away the output data produced a more reasonable graph.

##Part 2: graphing.
Relevent Files:

bench\_mark\_plot\_gnuscript (the gnu script to convert data to box plot graph)
data\_from\_benchmarking.txt (the data from a random instance of bench\_mark\_test)
box\_plot\_benchmark.png (the graph itself)

Description: 

I decided to use gnuplot to graph an instance of bench\_mark\_test to a box plot. 


##Part 3: Analysis:

A: I believe that upper limit of the L3 register is around 2^20 bytes. When you view my box plot notice that from 2^20 bytes onward there are stars at the top of the graph. These actually are the data from the first run of code. Each time I ran bench\_mark\_test the first loop gave similiar jumps from the 20-30ns result that was consistantly seen at 2^19 bytes. I attribute this to my machine having to use DRAM to store the buffer in these instances while the memory is reorganized in the later instances of the primary loop in "main" giving performance increases. The graph is appears monotic if you consider the mean of the box plot till the last data point. I noticed that if I increased the max size to 2^30 bytes that I got a decrease in latency from 2^26 bytes on which formed a curve that asymptotical approached 40 ns. I believe this reflects the upper range in latency of the L3 register. It appears that the upper range in latency of my DRAM is 100 ns.

B: Not yet completed. 


C: I was not able to clearly measure L1 and L2. Up to 2^17 bytes or approximately 128 kb the mean latency was approximately 20 ns. Up till 2^20 bytes my code clearly still used the L3 register but I saw some spikes indicating that some instences where having to use the test pcs RAM or possible its L4 register. From 2^20 onward I saw performance averaging around 50 ns. I believe this is because I higher percentage of the time my memory ends up being read from the DRAM though the latency you reported was 60-100 ns for DRAM. 

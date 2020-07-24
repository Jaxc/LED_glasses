fid = fopen("test_dump.bin");

test = fread(fid, Inf, "int16");

scale = [0:1/(400000/4):1/(400000/4)*(length(test)-1)];
fclose(fid);

plot(scale, test)
#semilogy(test)
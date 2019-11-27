# mtmd-test
Demo that VC++ /MT &amp; /MD behavior differently when locale is set

# To use
Build solution with ReleaseMT and ReleaseMD (platform x86), then run both exe. 
For /MT: the performance is dropping 15-20% when locale is set;
For /MD: the performance is dropping 50%.

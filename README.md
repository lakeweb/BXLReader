# BXLReader
Read and Parse BXL Electronic Component Description Files

Ultimate usage is to expose the Component namespace to the user and let the rest happen behind the scene.

Thanks to erichVK5, https://github.com/erichVK5, for the work on BXLtoText and the Boost authors.

If using the Microsoft Compiler, it must be vs141, VS2017, as the older compilers are not compliant enough to compile Boost::Spirit::x3.

4/11/2018
Converted to streaming file and fixed memory leaks.

8/1/2018
Parsing to generic container

4/20/2019
I've moved to VS2019(vs142). This still should compile fine with VS2017. If using vs142, you will need to have boost_1_70_0 installed as there are changes that deal with the new Microsoft compiler. I have added the boost::spirit::x3 files from boost_1_68_0 to this project. There are new boost fusion requirements in 1_70 that are incomparable with the hack made for Bridge::ScSymbol. I will see about dealing with this at a later time. But for now it compiles fine.

This is now compilable with vs142(VS2019). So as not to run into a hack in boost_1_68_0 that did not handle vs142, boost_1_70_0 will be required. The boost authors must be beside themselves dealing with the variants of Visual Studio. One catch was that static guards were put into place that check for fusion adulators around attribute structures. This won't do in this case as I have hacked into x3::traits. (not in the x3 source but in BXL_Spirit.h) It happens for Bridge::ScSymbol as there is a parse with a kleene star over alternatives. So I've included spirit::x3 from boost_1_68_0 in the project to avoid working around this change.
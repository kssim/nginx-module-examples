# Summary
This repo is a collection of nginx module examples.<br>
You can use this examples freely if you're using for testing or studying purposes.


# How to use
* Nginx modules are not dynamically linked.
	* They're compiled right into the Nginx binary.
* To build nginx module, you should build the nginx binary.
* Following the below steps.


1. First, you should get nginx source code.
	* You can get [nginx github](https://github.com/nginx/nginx).
	* If you're debian environment, you can also use the <code>apt-get source</code>
		* <code>apt-get source nginx</code>
2. Next, run configure and make makefile. You should add '--add-module' option and input module source path to build a module you want to be built.
	* <code>./configure --add-module=[module directory path]</code>
		* ex) <code>./configure --add-module=./hello_world</code>
3. Next run the make and make install
	1. <code>make</code>
	2. <code>make install</code>
	3. When the make install is finished, the result is stored in the '/usr/local/nginx' directory.
4. Change the configuration and test.
	* configure file location is '/usr/local/nginx/conf/nginx.conf'.
	* binary file location is '/usr/local/nginx/sbin/nginx' 



# References
* [Nginx modules guide](http://www.evanmiller.org/nginx-modules-guide.html)
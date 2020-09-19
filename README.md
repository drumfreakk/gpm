# gpm


## Compiling
First, set USER_AGENT in cmake or CMakeLists.txt to a user agent you like, something like ```username-gpm``` or something simmilar. Then, execute these commands:

	$ cmake .
	$ make
And run the new executable in ```src/```.

### Testing
To run the built-in unit tests, simply run ```make test``` in the top-level directory. A log of the tests will be placed in ```check_tests.log```.

## Used code/resources

- https://github.com/zserge/jsmn/
- https://curl.haxx.se/libcurl/c/getinmemory.html
- https://libcheck.github.io/check/
- http://www.json.org/example.html (For the json in the tests)


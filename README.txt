Build Instructions:
-------------------

To compile the application, navigate to the parent directory and type:

$ make

This will create an executable called 'output'.
Simply, execute 'output' to run the application.


Note from Author:
I rewrote gpio_read_pin(...) to generate a random number between 1 & 0.
Otherwise, the function will always return 0.

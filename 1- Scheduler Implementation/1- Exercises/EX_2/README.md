<h1>Implementing a scheduler</h1>

Let's implement a scheduler which schedules multiple usertasks in a round-robin fashion, by carrying out the context switching operation.

Round-Robin is scheduling method which is time slices assigned to each task in equal portions nd in circulr order.

First we will use systick handler to carry out the context switching operation between multiple tasks.

later will change the code to use pendSV handler.
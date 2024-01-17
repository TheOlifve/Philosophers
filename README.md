# Philosophers

This project is a training to multi-threads programming with the use of mutex.
This project is also a good lesson in C optimization as we need to save every bit of CPU usage we can to ensure the survival of our philosophers.

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in 1965 by Edsger Dijkstra. Soon after, Tony Hoare gave the problem its present formulation.

**Formulation**: Five philosophers dine together at the same table. Each philosopher has their own plate at the table. There is a fork between each plate. The dish served is a kind of spaghetti which has to be eaten with two forks. Each philosopher can only alternately think and eat. Moreover, a philosopher can only eat their spaghetti when they have both a left and right fork. Thus two forks will only be available when their two nearest neighbors are thinking or sleeping, not eating. After an individual philosopher finishes eating, they will put down both forks.

In this project, I proposed solution to this problem using threads and mutexes:

## Installation 

To test the project, go to the folder `philo` and call `make`. Then, you can test the project using an executable.

**Usage**: `./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_philosophers_should_eat>*`

`*` - last argument is optional and is not required to execute the project.

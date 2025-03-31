
# Philosophers

<p align="center">
	<img src="https://github.com/user-attachments/assets/e9082f87-6fef-47f4-be56-6b7338830549"
</p>


## Status
Finished: 2024-10-28. Grade: 125/100.

## Rules
- Philosophers sit at a round table with a bowl of spaghetti and as many forks as philosophers.
- They alternate between eating, thinking, and sleeping.
- To eat, they must pick up both the left and right fork.
- After eating, they put the forks back, sleep, then think.
- If the philosophers do not eat after a specified time, they will starve
- The simulation ends if a philosopher starves.
- Philosophers act independently and do not communicate.

## Threads and Mutexes
In the main program, each philosopher is a thread and each fork will be protected by a mutex. There is only one fork between each philosopher and a philosopher must take forks from their immediate left and right in order to start eating.

## Processes and Semaphores
In the bonus program, each philosopher is a process and each fork is a semaphore. The forks are at the center of the table so the philosophers may take any fork available to start eating.

## Usage
To compile main program, run `make`.
```bash
make
```

To compile bonus program, run `make bonus`
```bash
make bonus
```

To run the main program:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```

To run the bonus program:
```bash
./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```

- `number_of_philosophers`: The number of philosophers and also the number of forks.
- `time_to_die`: If a philosopher has not started eating within time_to_die milliseconds since their last meal or the start of the simulation, they die.
- `time_to_eat`: The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- `time_to_sleep`: The time a philosopher will spend sleeping.
- `number_of_times_each_philo_must_eat` (optional argument): If all philosophers have eaten at least `number_of_times_each_philo_must_eat times`, the simulation stops. If not specified, the simulation stops when a philosopher dies.

Arguments must be integers between 0 and INT_MAX representing a time in milliseconds. Example:
```bash
/philo 4 800 200 200 5
```

If the arguments given are valid, the program will report the actions of every philosopher until one of them dies or until all of them have eaten `number_of_times_each_philo_must_eat`, if specified.

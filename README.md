# bf1_stat_calc

## A Battlefield 1 weapon statistics calculator

This Program is supposed to be, at some point, a comprehensive weapon stat calculator for Battlefield 1 and games with similar mechanics.
It also serves as a continuous project for me to learn C++ on and will be improved and changed constanly as I learn new things.

### Current features/functionality

All parts of the program currently run in command-line only.

#### Current features:

    Battlefield 1:

    - Enter weapon stats
    - Choose stance, movement and aim states
    - Simulate hitrate for a given burst lenght
      - Choose distance, target size and burst length
      - Choose simulation count (up to about one million currently)
      - Print the average hitrate for each bullet in a burst


    Planetside 2:
    - Enter weapon stats
    - Simulate hitrate for a given burst lenght
      - Choose distance, target size and burst length
      - Choose simulation count (up to about one million currently)
      - Print the average hitrate for each bullet in a burst

#### Planned features:

    Planetside 2:
    - Choose stance, movement and aim states

    All Games:
    - Calculate ideal burst length
      - ideal burst length would be the number of shots one can fire without loosing to much 
        accuracy, so probably > 90% hitrate
    - Calculate ideal timing between bursts
      - ideal timing meaning the time it takes for the accumulated spread during a burst to 
        reset
    - Calculate effective damage per second(DPS)/time to kill(TTK)
      - based on the ideal burst length and reset time in between
    - Import weapon stats from file/database
    - Update weapon stats from either a server or the gamefiles for the specific game

    General:

    - GUI
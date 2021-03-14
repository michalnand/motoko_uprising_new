# motoko uprising new
motoko uprising line following robot

# structure
 
 * src
    * firmware - robot main firmware
    * robot_debug_py - debug application
    * AI gym env for reinforcement learning [gym-line_follower](src/gym-line_follower/)
    * TODO rl_line_follower [rl_line_follower](src/rl_line_follower/)

* hardware 
    * eagle files [hardware](hardware/)
    * gerber outputs [files](hardware/CAMOutputs/)
    * stl for 3D printed parts [files](hardware/mechanical/)

# reinforcement learning in Pybullet ENV

**key points**
* **state** is 256 last line positions, motors velocities, and line present flag

* PPO algorithm for continuous action space

* GRU model with three output heads (mean, variance, value)

![diagrams](images/model.png)
![diagrams](images/gym-line_follower.png)

# hardware

![mechanical](images/mechanical_01.png)
![mechanical](images/mechanical_03.png)

![hardware](images/board.png)
![hardware](images/board_top.png)
![hardware](images/board_bottom.png)
![hardware](images/schem_black.png)

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

# supervised learning for line position prediction

**key points**
* **input**  is time series sequence from 8 line sensors
* **output** is classification into three classes (left, straight, righ)
* RNN GRU with 64 units used, and linear layer with 3 neurons

* confusion matrix result
```bash
accuracy   = 89.037 [%]
hit_count  = 116703
miss_count = 14369

class_accuracy = 90.952%   90.474%   84.811%   


confusion_matrix = 
       28326        1376           8
        2817       57907        5448
           0        4720       30470
```


![diagrams](images/line_rnn_prediction.gif)


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

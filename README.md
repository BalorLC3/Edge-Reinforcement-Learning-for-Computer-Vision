# Reinforcement Learning applied to Computer Vision
An edge library that aims to bridge reinforcement learning and computer vision in edge devices (particularly in a RPi 4 Model B), this happens by a simple but very strong connection. For example:

|| Game | Object Tracking |
|----|------|-----|
|__State__| Current game states | Input image + current tracking state |
|__Action__| Turn left, right, stop | Move the bbx or finish tracking |
|__Reward__| Scores | Accuracy 

So in general is not difficult to induct a similarity between these two fields. The purpose of this project then, is to make this a feasible reality.
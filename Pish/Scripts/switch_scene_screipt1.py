#This script switchs the scene out to
#another one if the time limit is passed

#displays a circling sprite

from math import *
import time

mms0 = pshGE.SceneManage(0)
mms1 = pshGE.SceneManage(1)

test.setPosition(-10.0*cos(time.clock()*10.0), 10.0*sin(time.clock()*10.0), 1.0)

obj0 = mms0.getSceneObject("object_0")

obj0.setPosition(-5.0, 0.0, 0.0)

print(time.clock())

if (time.clock() % 1240.0) < 0.002:
 mms0.SceneRender(True)
 mms1.SceneRender(False)

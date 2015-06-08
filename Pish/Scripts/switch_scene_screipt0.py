#This script tells the scene to switch if 2
#objects have intersected eaach other

from math import *
import time

mms = pshGE.SceneManage(0)

mms1 = pshGE.SceneManage(1)

obj2 = mms.getSceneObject("object_2")

if pshObjectTests.object_intersect_test(object_0, obj2) == True:
 mms1.SceneRender(True)
 mms.SceneRender(False)
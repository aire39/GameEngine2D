#Code to test objects 
#intersecting with each other

mms = pshGE.SceneManage(0)

mobj1 = mms.getSceneObject("object_0")

mobj2 = mms.getSceneObject("object_2")

#print(pshObjectTests.object_intersect_test(mobj1, mobj2))

if pshObjectTests.object_intersect_test(mobj1, mobj2) is True:
 mobj1.setColor(1.0, 0.0, 0.0, 1.0)
else:
 mobj1.setColor(1.0, 1.0, 1.0, 1.0)


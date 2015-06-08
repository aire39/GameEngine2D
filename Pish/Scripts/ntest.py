mmEntMan = pshGameEngine.Scene
ggObject = pshGameEngine.gameObject

mmEntMan = pshGE

ggObject = mmEntMan.getSceneObject("object_0")

ggObject2 = mmEntMan.getSceneObject("object_2")

print (ggObject.getName())
print (ggObject.getPosition().getx(), ggObject.getPosition().gety(), ggObject.getPosition().getz())

print (ggObject2.getName())
print (ggObject2.getPosition().getx(), ggObject2.getPosition().gety(), ggObject2.getPosition().getz())
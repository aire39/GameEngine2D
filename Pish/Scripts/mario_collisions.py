#################
#Put Gravity Onto Object #
#################
Gravity = 0.5

this.setPosition( this.getPosition().getx(), this.getPosition().gety()-Gravity , this.getPosition().getz() )

###########
#Collision Tests #
###########

import pshObjectTests
scene0 = pshGE.SceneManage(0)
br_ground0 = scene0.getSceneObject("br_ground0")
br_tube0  = scene0.getSceneObject("bpipe0")
br_kill0  = scene0.getSceneObject("br_kill0")
collide = pshObjectTests.object_intersect_test(this, br_ground0)
collide2 = pshObjectTests.object_intersect_test(this, br_tube0)
collide3 = pshObjectTests.object_intersect_test(this, br_kill0)

gamescene0 = pshGE.SceneManage(0)
gamescene1 = pshGE.SceneManage(1)

#######
#######

#print collide

if (collide == 6):
 this.setPosition( this.getPosition().getx(), this.getPosition().gety()+Gravity , this.getPosition().getz() )
 this.setTexture("mario_stand")

#######
#######

if (collide2 == 9):
 this.setPosition( this.getPosition().getx()-walkrun_speed, this.getPosition().gety() , this.getPosition().getz() )
 this.setTexture("mario_stand")

if (collide2 == 7):
 this.setPosition( this.getPosition().getx()+walkrun_speed, this.getPosition().gety() , this.getPosition().getz() )
 this.setTexture("mario_stand")

if (collide2 == 2) or (collide2 == 0) or (collide2 == 6):
 this.setPosition( this.getPosition().getx(), this.getPosition().gety() +Gravity, this.getPosition().getz() )
 this.setTexture("mario_stand")

if (collide3 == 2) or (collide3 == 0) or (collide3 == 6):
 gamescene1.SceneRender(True)
 gamescene0.SceneRender(False)

#this.setPosition(0.0 ,0.0, 0.0)
#print collide2

mtime = this_script.GetVarTimer(0)



if( mtime.Time() > 1.0 ):
 mtime.Restart()
 #print collide2


























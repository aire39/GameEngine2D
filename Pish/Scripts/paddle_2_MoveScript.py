#######
#######
#######

scene = pshGE.SceneManage(1)

ball = scene.getSceneObject("ball")

#######
#######
#######

if( ball.getPosition().getx() > 0.0 ):
 if( ball.getPosition().gety() > this.getPosition().gety()+0.1 ):
  this.setPosition(this.getPosition().getx(), this.getPosition().gety()+0.1, this.getPosition().getz())
 elif( ball.getPosition().gety() < this.getPosition().gety()-0.1 ):
  this.setPosition(this.getPosition().getx(), this.getPosition().gety()-0.1, this.getPosition().getz())
 else:
  this.setPosition(this.getPosition().getx(), this.getPosition().gety(), this.getPosition().getz())
else:
 if( this.getPosition().gety() > 0.1 ):
  this.setPosition(this.getPosition().getx(), this.getPosition().gety()-0.1, this.getPosition().getz())
 elif( this.getPosition().gety() < -0.1 ):
  this.setPosition(this.getPosition().getx(), this.getPosition().gety()+0.1, this.getPosition().getz())



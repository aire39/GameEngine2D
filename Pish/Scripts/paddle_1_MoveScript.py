#######
# Control #
#######

if(FrameEvent.iskeydown(315) == True):
 this.setPosition(this.getPosition().getx(), this.getPosition().gety()+0.1, this.getPosition().getz())

if(FrameEvent.iskeydown(317) == True):
 this.setPosition(this.getPosition().getx(), this.getPosition().gety()-0.1, this.getPosition().getz())




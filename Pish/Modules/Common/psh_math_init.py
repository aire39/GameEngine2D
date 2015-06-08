import pshVectorMath

pshvec2 = pshVectorMath.vec2()
pshvec2.setxy(0.0, 0.0)
pshvec3 = pshVectorMath.vec3()
pshvec3.setxyz(0.0, 0.0, 0.0)
pshvec4 = pshVectorMath.vec4()
pshvec4.setxyzw(0.0, 0.0, 0.0, 1.0)

def vec_magnitude(v):
	return (v.getx()*v.getx()) + (v.gety()*v.gety()) + (v.getz()*v.getz()) 

def vec_normalize(v):
	m = vec_magnitude(v)
	xt = v.getx()/m
	yt = v.gety()/m
	zt = v.getz()/m
	
	v.setxyz(xt, yt, zt)
	
	return v


print "Initializing pshVectorMath script"

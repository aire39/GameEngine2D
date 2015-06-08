uniform float time;

void main()
{	
	vec4 v = vec4(gl_Vertex);
	v.y *= cos(time*0.1);
	v.x *= sin(time*0.1);
	
	gl_Position = gl_ModelViewProjectionMatrix * v;
	
}

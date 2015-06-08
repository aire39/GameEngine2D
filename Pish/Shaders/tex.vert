varying vec2 tC;

void main()
{

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;	
	tC = vec2(gl_MultiTexCoord0);
	
}
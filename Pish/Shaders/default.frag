vec4 Color = vec4(1.0, 0.0, 1.0, 1.0); // components in order R, G, B, A. 
				       // Could use vec3 for RGB instead. 


void main()
{
	gl_FragColor = Color;		  		//one way to write it
	//gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);      //another way to write it
}
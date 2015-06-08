varying vec2 tC;
uniform sampler2D tex;


void main()
{	
	gl_FragColor = texture2D(tex, tC);
}
varying vec4 v_color;
varying vec2 v_texCoord;
uniform sampler2D sampler;

void main()
{
    vec4 texcolor = texture2D(sampler, v_texCoord);
    gl_FragColor = texcolor * v_color;
}
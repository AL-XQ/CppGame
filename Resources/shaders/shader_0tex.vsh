attribute vec4 a_position;//（入力）座標
attribute vec4 a_color; //（入力）色

uniform mat4 u_wvp_matrix;

varying vec4 v_color; //（出力）色

void main()
{
	gl_Position = u_wvp_matrix * a_position;
	v_color = a_color;
}
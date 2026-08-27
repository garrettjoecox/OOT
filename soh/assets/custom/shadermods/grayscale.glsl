@prism(type='fragment', name='Fast3D Fragment Shader', version='1.0.0', description='Ported shader to prism', author='Emill & Prism Team')

@{GLSL_VERSION}

@if(VERTEX_SHADER)
    @{attr} vec4 a_position;
    @{attr} vec4 a_color;
    @{attr} vec2 a_texCoord0;

    uniform mat4 u_projTrans;

    varying vec4 v_color;
    varying vec2 v_texCoords;

    void main() {
        v_color = a_color;
        v_texCoords = a_texCoord0;
        gl_Position = u_projTrans * a_position;
    }
@else
    @if(core_opengl || opengles)
        out vec4 vOutColor;
    @end

    varying vec4 v_color;
    varying vec2 v_texCoords;
    uniform sampler2D u_texture;
    uniform mat4 u_projTrans;

    vec4 texel;

    void main() {
        vec3 color = texture2D(u_texture, v_texCoords).rgb;
        float gray = (color.r + color.g + color.b) / 3.0;
        vec3 grayscale = vec3(gray);

        texel = vec4(grayscale, 1.0);
        @{vOutColor} = texel;
    }
@end

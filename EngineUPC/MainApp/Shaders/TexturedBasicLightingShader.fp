#version 150
#define MAX_LIGHTS 10

in vec3 fragmentVertex;
in vec3 fragmentNormal;
in vec2 fragmentUV;

out vec4 finalColor;

uniform mat4 model;
uniform vec3 cameraPosition;
uniform float materialShininess;
uniform vec3 materialSpecularColor;

// ambient
uniform vec4 ambientColor;
uniform sampler2D sampler;
uniform int numLights;

uniform struct Light {
   vec4 position;
   vec3 intensities; //a.k.a the color of the light
   float attenuation;
   float ambientCoefficient;
   float coneAngle;
   vec3 coneDirection;
} allLights[MAX_LIGHTS];

vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
	
    if(light.position.w == 0.0) {
        //directional light
        surfaceToLight = normalize(light.position.xyz);
		attenuation = light.attenuation;
        //attenuation = 1.0; //no attenuation for directional lights
    } else {
        //point light
        surfaceToLight = normalize(light.position.xyz - surfacePos);
        float distanceToLight = length(light.position.xyz - surfacePos);
        attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

        //cone restrictions (affects attenuation)
        float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
        if(lightToSurfaceAngle > light.coneAngle){
            attenuation = 0.0;
        }
    }

    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;

    //linear color (color before gamma correction)
    return ambient + attenuation*(diffuse + specular);
}

void main() {		
    vec3 surfacePos = vec3(model * vec4(fragmentVertex, 1));
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);
	vec4 surfaceColor = texture(sampler, fragmentUV) * ambientColor;
	
	vec3 linearColor = vec3(0.0, 0.0, 0.0);
	
    for(int i = 0; i < numLights; ++i){
		linearColor += ApplyLight(allLights[i], surfaceColor.rgb, fragmentNormal, surfacePos, surfaceToCamera);
	}
	
	finalColor += vec4(linearColor, 1.0);
}




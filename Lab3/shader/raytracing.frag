#version 430

#define EPSILON = 0.001
#define BIG = 1000000.0


in vec3 interpolatedVertex;
out vec4 FragColor;

struct Camera
{
	vec3 position;
	vec3 view;
	vec3 up;
	vec3 side;
};

struct Ray
{
	vec3 origin;
	vec3 direction;
};

struct Sphere
{
	vec3 center;
	float radius;
	vec3 color;
	int material_index;
};

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float specular_power;
};

struct Intersection
{
	float time;
	vec3 point;
	vec3 normal;
	vec3 color;
	//int material_index;
};

Material material = {0.4, 0.9, 0.0, 512.0};
vec3 light_pos = vec3(1, 3, -4);

uniform Camera camera;
uniform vec2 scale;
uniform Sphere spherein;

bool IntersectSphere (Sphere sphere, Ray ray, float start, float final, out float time){
	ray.origin -= sphere.center;
	float A = dot (ray.direction, ray.direction);
	float B = dot (ray.direction, ray.origin);
	float C = dot (ray.origin, ray.origin) - sphere.radius * sphere.radius;
	float D = B * B - A * C;
	if (D > 0.0){
		D = sqrt(D);
		float t1 = (-B - D) / A;
		float t2 = (-B + D) / A;
		if (t1 < 0 && t2 < 0) return false;
		if (min(t1, t2) < 0){
			time = max(t1, t2);
			return true;
		}
		time = min(t1, t2);
		return true;
	}
	return false;
}

bool Intersect(Ray ray, float start, float final, inout Intersection intersect){
	bool result = false;
	float time = start;
	intersect.time = final;
	
	for (int i = 0; i < 1; i++){
		if (IntersectSphere(spherein, ray, start, final, time) && time < intersect.time){
			intersect.time = time;
			intersect.point = ray.origin + ray.direction * time;
			intersect.normal = normalize(intersect.point - spherein.center);
			intersect.color = spherein.color;
			//intersect.material_index = spherein.material_index;
			result = true;
		}
	}
	return result;
}

vec3 Phong(Intersection intersect){
	vec3 light = normalize(light_pos - intersect.point);
	float diffuse = max(dot(light, intersect.normal), 0.0);
	vec3 view = normalize(camera.position - intersect.point);
	vec3 reflected = reflect(-view, intersect.normal);
	float specular = pow(max(dot(reflected, light), 0.0), material.specular_power);
	return material.ambient * intersect.color + 
		   material.diffuse * diffuse * intersect.color +
		   material.specular * specular;
}

vec4 Raytrace(Ray primary_ray){
	vec4 resultColor = vec4(0, 0, 0, 0);
	Ray ray = primary_ray;
	
	Intersection intersect;
	intersect.time = 10000.0;
	float start = 0;
	float final = 10000.0;
	
	if (Intersect(ray, start, final, intersect)){
		//float shadowing = Shadow(intersect);
		resultColor += vec4(Phong(intersect), 0.0);
		//resultColor += vec4(intersect.color, 0.0);
	}
	return resultColor;
}

/*float Shadow(Intersection intersect){
	float shadowing = 1.0;
	vec3 direction = normalize(light_pos - intersect.point);
	float distanceLight = distance(light_pos, intersect.point);
	Ray shadowRay = Ray(intersect.point + direction * 0.0001, direction);
	Intersection shadowIntersect;
	shadowIntersect.time = 10000.0;
	if (Raytrace(shadowRay)) shadowing = 0.0;
	return shadowing;
}*/

Ray GenerateRay(Camera camera){
	vec2 coords = interpolatedVertex.xy * normalize(scale);
	vec3 direction = camera.view + camera.side * coords.x + camera.up * coords.y;
	return Ray(camera.position, normalize(direction));
}

void main(void){
	Ray ray = GenerateRay(camera);
	FragColor = Raytrace(ray);
}
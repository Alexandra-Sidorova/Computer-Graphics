#version 430

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
};

struct Triangle
{
	vec3 v1;
	vec3 v2;
	vec3 v3;
	vec3 color;
};

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float specularPower;
};

struct Intersection
{
	float time;
	vec3 point;
	vec3 normal;
	vec3 color;
};

Material material = {0.4, 0.9, 0.0, 512.0};
vec3 lightPos = vec3(1, 3, -4);

uniform Camera camera;
uniform vec2 scale;
uniform Sphere spherein[2];
uniform Triangle trianglein[10];

bool IntersectSphere (Sphere sphere, Ray ray, float start, float final, out float time)
{
	ray.origin -= sphere.center;
	float A = dot (ray.direction, ray.direction);
	float B = dot (ray.direction, ray.origin);
	float C = dot (ray.origin, ray.origin) - sphere.radius * sphere.radius;
	float D = B * B - A * C;
	if (D > 0.0)
	{
		D = sqrt(D);
		float t1 = (-B - D) / A;
		float t2 = (-B + D) / A;
		
		if (t1 < 0 && t2 < 0) 
			return false;
		
		if (min(t1, t2) < 0)
		{
			time = max(t1, t2);
			return true;
		}
		
		time = min(t1, t2);
		
		return true;
	}
	
	return false;
};

bool IntersectTriangle(Ray ray, vec3 v1, vec3 v2, vec3 v3, out float time)
{
	time = -1;
	vec3 A = v2 - v1;
	vec3 B = v3 - v1; 
	vec3 normal = cross(A, B);
	float dotRayDir = dot(normal, ray.direction);
	
	if (abs(dotRayDir) < 0.001)
		return false;
	
	float d = dot(normal, v1);
	float t = -(dot(normal, ray.origin) - d) / dotRayDir;
	
	if (t < 0) 
		return false; 
		
	vec3 P = ray.origin + t * ray.direction;
	vec3 C;
	vec3 edge1 = v2 - v1;
	vec3 VP1 = P - v1;
	C = cross(edge1, VP1);
	
	if (dot(normal, C) < 0)
		return false;
	
	vec3 edge2 = v3 - v2;
	vec3 VP2 = P - v2;
	C = cross(edge2, VP2);
	
	if (dot(normal, C) < 0)
		return false;
	
	vec3 edge3 = v1 - v3;
	vec3 VP3 = P - v3;
	C = cross(edge3, VP3);
	
	if (dot(normal, C) < 0)
		return false;
		
	time = t;
	
	return true; 
};

bool Intersect(Ray ray, float start, float final, inout Intersection intersect)
{
	bool result = false;
	float time = start;
	intersect.time = final;
	
	for (int i = 0; i < 2; i++)
	{
		if (IntersectSphere(spherein[i], ray, start, final, time) && time < intersect.time)
		{
			intersect.time = time;
			intersect.point = ray.origin + ray.direction * time;
			intersect.normal = normalize(intersect.point - spherein[i].center);
			intersect.color = spherein[i].color;
			result = true;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (IntersectTriangle(ray, trianglein[i].v1, trianglein[i].v2, trianglein[i].v3, time) && time < intersect.time)
		{
			intersect.time = time;
			intersect.point = ray.origin + ray.direction * time;
			vec3 edge1 = trianglein[i].v1 - trianglein[i].v2;
			vec3 edge2 = trianglein[i].v1 - trianglein[i].v3;
			intersect.normal = normalize(cross(edge1, edge2));
			intersect.color = trianglein[i].color;
			result = true;
		}
	}
	return result;
};

vec3 Phong(Intersection intersect)
{
	vec3 light = normalize(lightPos - intersect.point);
	float diffuse = max(dot(light, intersect.normal), 0.0);
	vec3 view = normalize(camera.position - intersect.point);
	vec3 reflected = reflect(-view, intersect.normal);
	float specular = pow(max(dot(reflected, light), 0.0), material.specularPower);
	return material.ambient * intersect.color + 
		   material.diffuse * diffuse * intersect.color +
		   material.specular * specular;
}

vec4 Raytrace(Ray primary_ray)
{
	vec4 resultColor = vec4(0, 0, 0, 0);
	Ray ray = primary_ray;
	
	Intersection intersect;
	intersect.time = 10000.0;
	float start = 0;
	float final = 10000.0;
	
	if (Intersect(ray, start, final, intersect))
	{
		//float shadowing = Shadow(intersect);
		resultColor += vec4(Phong(intersect), 0.0);
		//resultColor += vec4(intersect.color, 0.0);
	}
	return resultColor;
};

/*float Shadow(Intersection intersect)
{
	float shadowing = 1.0;
	vec3 direction = normalize(light_pos - intersect.point);
	float distanceLight = distance(light_pos, intersect.point);
	Ray shadowRay = Ray(intersect.point + direction * 0.0001, direction);
	Intersection shadowIntersect;
	shadowIntersect.time = 10000.0;
	
	if (Raytrace(shadowRay))
		shadowing = 0.0;
	
	return shadowing;
}*/

Ray GenerateRay(Camera camera)
{
	vec2 coords = interpolatedVertex.xy * normalize(scale);
	vec3 direction = camera.view + camera.side * coords.x + camera.up * coords.y;
	return Ray(camera.position, normalize(direction));
};

void main(void){
	Ray ray = GenerateRay(camera);
	FragColor = Raytrace(ray);
};
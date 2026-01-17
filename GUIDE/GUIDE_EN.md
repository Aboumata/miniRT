# Comprehensive Guide to miniRT (Ray Tracing)

This document explains the mathematical foundations and algorithms used to build your Ray Tracer engine.

---

## 1. Ray Tracing Basics

The core idea is to simulate how light travels in the real world but in reverse. Instead of tracing billions of photons from a light source, we shoot a "Ray" from the "Camera Eye" through each "Pixel" on the screen and see what it hits.

### The Ray Equation
Any ray in 3D space can be represented by the following linear equation:
P(t) = O + t * D

Where:
- P(t): The point on the ray at distance t.
- O: The Origin point - usually the camera position.
- D: The Direction of the ray - a normalized vector.
- t: A real number representing the distance from the origin.

---

## 2. Camera

To convert a 3D scene into a 2D image, we use the "Pinhole Camera" model.

**How to generate rays:**
1. Define the "Viewport" dimensions based on the Field of View (FOV).
2. For each pixel (x, y) in the image, calculate its coordinates in 3D space.
3. The ray direction is:
D = normalize(PixelPosition - CameraPosition)

---

## 3. Intersections

To know what the ray sees, we solve mathematical equations to find the value of t that satisfies the shape's equation.

### A. Sphere
The sphere equation is:
(P - C) * (P - C) = r^2
Where C is the center and r is the radius.
By substituting the ray equation P(t) into the sphere equation, we get a quadratic equation:
a * t^2 + b * t + c = 0

Where:
- L = O - C (Vector from center to camera)
- a = D * D (Equals 1 if the vector is normalized)
- b = 2 * (L * D)
- c = (L * L) - r^2

We calculate the Discriminant (Delta = b^2 - 4ac). If positive, there are two solutions (intersections), we take the closest one (smallest positive t).

### B. Plane
A plane is defined by a point P0 and a normal vector N.
Equation:
(P - P0) * N = 0
Solution to find t:
t = ((P0 - O) * N) / (D * N)

If the denominator (D * N) is close to zero, the ray is parallel to the plane and does not intersect it.

### C. Cylinder
The cylinder is a bit harder because it is infinite in its basic equation, then we cut it by length.
We rely on the fact that the distance from any point on the surface to the axis equals the radius r.

Quadratic equation for cylinder (excluding the Y axis or rotation axis):
- Calculate vectors perpendicular to the cylinder axis.
- Solve the quadratic equation a * t^2 + b * t + c = 0 similar to the sphere but in 2D (around the axis).
- After finding t, check if the intersection point lies within the cylinder's "height".
- **Caps:** Treated as intersections with two circular Planes at the top and bottom.

---

## 4. Lighting & Shadows

We use the **Phong Reflection Model** to calculate the point's color.

Color = Ambient + Diffuse + Specular

### 1. Ambient Lighting
Constant light covering the whole scene to ensure no total darkness.
Ambient = Ka * Color

### 2. Diffuse Lighting
Simulates matte surfaces. Depends on the angle between the "Surface Normal" (N) and "Light Direction" (L).
Diffuse = Kd * (N * L) * LightColor
If the angle is greater than 90 degrees (dot product is negative), the light does not hit the surface.

### 3. Specular Lighting
Simulates direct light reflection (the shiny white spot). Depends on the angle between "Reflection Direction" (R) and "View Direction" (V).
Specular = Ks * (R * V)^alpha * LightColor
Where alpha is the Shininess coefficient.

### 4. Shadows
To know if a point is in shadow:
1. Shoot a "Shadow Ray" from the intersection point towards the light source.
2. If this ray hits any object before reaching the light, the point is in shadow.
3. In shadow, we only calculate the Ambient component.

---

## 5. Textures & UV Mapping

Here comes the fun part: How to map an image (Texture) onto a 3D shape?

### What is UV?
UV are 2D coordinates (u, v) usually ranging between 0 and 1.
- **U**: Horizontal axis of the image.
- **V**: Vertical axis of the image.

The goal is to map a 3D point (x, y, z) on the shape's surface to a 2D point (u, v) to know which color to pick from the image.

### Calculating UV for each shape:

#### 1. Sphere (Spherical Mapping)
We use spherical coordinates (longitude and latitude).
- Calculate angle around Y axis (Azimuth) -> gives u.
- Calculate angle with Pole (Polar angle) -> gives v.

Equations (approximate):
u = 0.5 + atan2(z, x) / (2 * PI)
v = 0.5 - asin(y) / PI

#### 2. Plane (Planar Mapping)
Define two perpendicular axes on the plane surface (u_axis and v_axis).
Project point P onto these axes using dot product.
u = (P - Center) * u_axis
v = (P - Center) * v_axis
Usually, we take the modulus or use a repeat function because the plane is infinite.

#### 3. Cylinder (Cylindrical Mapping)
- **Body:** Similar to sphere for u (angle around axis). v is simply the relative height of the point on the axis.
- **Caps:** Treated like Plane (Planar Projection).

### Checkerboard
Once we have (u, v), we can create a checkerboard pattern mathematically without an image:
```c
int check = floor(u * size) + floor(v * size);
if (check % 2 == 0) return WHITE;
else return BLACK;
```

---

## 6. Bump Mapping (Surface Relief)

Bump Mapping gives an illusion of depth and roughness without actually changing the shape geometry.

**How it works:**
1. Use a "Height Map" image where white is high and black is low.
2. At each point, calculate the "Gradient" in the image at (u, v).
3. "Perturb" (tilt) the original Normal vector (N) based on this gradient.
4. Use the new Normal in lighting calculations.

Result: Light reflects as if the surface is bumpy, creating very realistic shadows and highlights.

**Algorithm (Perturb Normal):**
1. Calculate partial derivatives of height with respect to u and v (difference between pixel and neighbor).
2. Construct a local coordinate system (Tangent Space) using Normal (N), Tangent (T), and Bitangent (B).
3. Add vectors:
NewNormal = N + (T * Delta_u) + (B * Delta_v)
4. Normalize the new vector.

---

## 7. Main Program Loop

```text
For each pixel (y) in height:
  For each pixel (x) in width:
    1. Create a ray from camera passing through (x, y).
    2. Find closest intersection (t_min) with all scene objects.
    3. If no intersection -> Draw background color (or black).
    4. If intersection found:
       a. Calculate intersection point (P).
       b. Calculate Normal at P.
       c. Calculate (u, v) coordinates.
       d. Apply Bump Mapping to modify Normal (if any).
       e. Calculate Base Color (from texture or fixed color).
       f. Calculate Lighting (Ambient + Diffuse + Specular).
       g. Check Shadows (Shadow Rays).
       h. Combine colors and put result in pixel.
```

---

## Tips for Beginners

1. **Start Simple:** Draw a sphere with a single color and no lighting.
2. **Vectors are your friends:** Ensure `vec_dot`, `vec_cross`, `vec_normalize` functions work 100% correctly; any error there will break everything.
3. **Normalization:** Always normalize direction and normal vectors. Forgetting this is the cause of 90% of lighting issues.
4. **Epsilon:** When comparing floating point numbers, do not use `==`. When calculating shadows, start the ray slightly away from the surface (`P + Normal * EPSILON`) to avoid "Shadow Acne" where the object shadows itself incorrectly.
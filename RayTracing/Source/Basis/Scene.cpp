#include "Scene.h"
#include <omp.h>
//Basis
#include "Source/Basis/Camera.h"
#include "Source/Basis/HitRec.h"
#include "Source/Basis/ScatterRec.h"
#include "Source/Basis/Ray.h"

//Util
#include "Source/Utility/MathUtil.h"

//images
#include "Source/Image/Image.h"

//Shapes
#include "Source/Shape/Shape.h"
#include "Source/Shape/Sphere.h"
#include "Source/Shape/Rect.h"
#include "Source/Shape/ShapeList.h"
#include "Source/Shape/Rect.h"
#include "Source/Shape/FlipNormals.h"
#include "Source/Shape/Box.h"
#include "Source/Shape/ShapeBuilder.h"

//Texture
#include "Source/Texture/CheckerTexture.h"
#include "Source/Texture/ColorTexture.h"
#include "Source/Texture/ImageTexture.h"

//Material
#include "Source/Material/Dielectric.h"
#include "Source/Material/DiffuseLight.h"
#include "Source/Material/Lambertian.h"
#include "Source/Material/Metal.h"
#include "Source/Material/Material.h"

//pdf
#include "Source/Pdf/Pdf.h"
#include "Source/Pdf/CosinePdf.h"
#include "Source/Pdf/ShapePdf.h"
#include "Source/Pdf/MixturePdf.h"

constexpr float LIGHT_POS_X0 = 213.0f;
constexpr float LIGHT_POS_X1 = 343.0f;
constexpr float LIGHT_POS_Y0 = 227.0f;
constexpr float LIGHT_POS_Y1 = 332.0f;
constexpr float LIGHT_POS_K = 554.0f;


Scene::Scene(int width, int height, int samples) :
	_image(std::make_unique<Image>(width, height)), _backColor(0.1f), _samples(samples)
{
}

Scene::~Scene()
{

}

void Scene::Build()
{

	// Camera

	Vector3 eye(13, 2, 3);
	Vector3 center(0.0f, 0.f, 0.f);
	Vector3 vUp(0.0f, 1.0f, 0.0f);
	float fov = 60.0f;
	float aspect = static_cast<float>(this->_image->Width()) / static_cast<float>(this->_image->Height());
	_camera = std::make_unique<Camera>(eye, center, vUp, fov, aspect);


	// object

	ShapeList* world = new ShapeList();

	world->Add(std::make_shared<Sphere>(
		Vector3(0.0f, 2.0f, 0.0f), 2.0f,
		std::make_shared<Lambertian>(
			std::make_shared<ColorTexture>(Vector3(0.5f, 0.5f, 0.5f)))));
	world->Add(std::make_shared<Sphere>(
		Vector3(0.0f, -1000.0f, 0.0f), 1000.0f,
		std::make_shared<Lambertian>(
			std::make_shared<ColorTexture>(Vector3(0.8f, 0.8f, 0.8f)))));
	world->Add(std::make_shared<Rect>(
		3.0f, 5.0f, 1.0f, 3.0f, -2.0f, Rect::XY,
		std::make_shared<DiffuseLight>(
			std::make_shared<ColorTexture>(Vector3(4.0f)))));

	this->_world.reset(world);
}

void Scene::BuildConelBox()
{
	_backColor = Vector3(0);

	// Camera

	Vector3 lookfrom(278.0f, 278.0f, -800.0f);
	Vector3 lookat(278.0f, 278.0f, 0.0f);
	Vector3 vup(0.0f, 1.0f, 0.0f);
	float aspect = float(_image->Width()) / float(_image->Height());
	_camera = std::make_unique<Camera>(lookfrom, lookat, vup, 40.0f, aspect);

	// Shapes

	MaterialPtr red = std::make_shared<Lambertian>(
		std::make_shared<ColorTexture>(Vector3(0.65f, 0.05f, 0.05f)));
	MaterialPtr white = std::make_shared<Lambertian>(
		std::make_shared<ColorTexture>(Vector3(0.73f)));
	MaterialPtr green = std::make_shared<Lambertian>(
		std::make_shared<ColorTexture>(Vector3(0.12f, 0.45f, 0.15f)));
	MaterialPtr light = std::make_shared<DiffuseLight>(
		std::make_shared<ColorTexture>(Vector3(15.0f)));
	MaterialPtr metallic = std::make_shared<Metal>(
		std::make_shared<ColorTexture>(Vector3(0.8f, 0.85f, 0.88f)), 0.0f);
	MaterialPtr metal = std::make_shared<Dielectric>(1.5f);

	ShapeList* world = new ShapeList();
	ShapeBuilder builder;

	world->Add(builder.rectXZ(LIGHT_POS_X0, LIGHT_POS_X1, LIGHT_POS_Y0,
		LIGHT_POS_Y1, LIGHT_POS_K, light).flip().get());

	world->Add(builder.rectYZ(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, green).flip().get());
	world->Add(builder.rectYZ(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, red).get());
	world->Add(builder.rectXZ(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white).flip().get());
	world->Add(builder.rectXZ(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, white).get());
	world->Add(builder.rectXY(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white).flip().get());

	world->Add(builder.sphere(Vector3(190, 90, 190), 90, metal).get());

	world->Add(builder.box(Vector3(0.0f), Vector3(165.0f, 330.0f, 165.0f), white)
		.rotate(Vector3::yAxis(), 15.0f)
		.translate(Vector3(265.0f, 0.0f, 295.0f))
		.get());

	ShapeList* l = new ShapeList();
	l->Add(builder.rectXZ(LIGHT_POS_X0, LIGHT_POS_X1, LIGHT_POS_Y0, LIGHT_POS_Y1, LIGHT_POS_K, MaterialPtr()).get());
	l->Add(builder.sphere(Vector3(190, 90, 190), 90, MaterialPtr()).get());
	_light.reset(l);

	_world.reset(world);
}

Vector3 Scene::Color(const Ray & r, const Shape* world, const Shape* light, int depth)
{
	HitRec hrec = {};
	if (world->Hit(r, (0.0f + THRESHOLD), FLT_MAX, hrec)) {
		ScatterRec srec = {};
		Vector3 emitted = hrec.mat->Emitted(r, hrec);

		if (depth < MAX_DEPTH && hrec.mat->Scatter(r, hrec, srec))
		{

			if (srec.isSpecular) {
				return emitted + mulPerElem(srec.albedo, Color(srec.ray, world, light, depth + 1));
			}
			else
			{
				ShapePdf shapePdf(light, hrec.p);

				MixturePdf mixPdf(&shapePdf, srec.pdfValue);

				srec.ray = Ray(hrec.p, mixPdf.Generate(hrec));
				float pdfValue = mixPdf.Value(hrec, srec.ray.Direction());
				if (pdfValue > 0.0f) {

					float spdfValue = hrec.mat->ScatteringPdf(srec.ray, hrec);
					Vector3 albedo = srec.albedo * spdfValue;
					return emitted + Vectormath::Aos::mulPerElem(albedo, Color(srec.ray, world,light, depth + 1)) / pdfValue;
				}
				else
				{
					return emitted;

				}
			}
		}
		else
		{
			return emitted;
		}
	}
	return Background(r.Direction());
}

Vector3 Scene::BackgroundSky(const Vector3 & d) const
{
	Vector3 v = normalize(d);
	float t = 0.5f * (v.getY() + 1.0f);
	return lerp(t, Vector3(1.0f), Vector3(0.5f, 0.7f, 1.0f));
}

void Scene::Render()
{

	BuildConelBox();

	int nx = _image->Width();
	int ny = _image->Height();

	//openMP‚ð—p‚¢‚½•À—ñ‰»
#pragma omp parallel for schedule(dynamic, 1) num_threads(NUM_THREAD)
	for (int j = 0; j < ny; ++j) {
		thread_local Random random(42 - omp_get_thread_num());

		std::cerr << "Rendering (y = " << j << ") " << (100.0 * j / (ny - 1)) << "%" << std::endl;
		for (int i = 0; i < nx; ++i) {
			Vector3 c(0.0f);
			//SSAAˆ—
			for (int s = 0; s < _samples; ++s) {
				float u = float(i + random.GetRand()) / float(nx);
				float v = float(j + random.GetRand()) / float(ny);
				Ray r = _camera->getRay(u, v);
				c += Color(r, _world.get(),_light.get(), 0);
			}
			c /= static_cast<float>(_samples);
			_image->Write(i, j, c.getX(), c.getY(), c.getZ());

		}
	}

	_image->OutputImage("render.bmp");
}
